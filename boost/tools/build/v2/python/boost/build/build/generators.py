#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

#  Manages 'generators' --- objects which can do transformation between different
#  target types and contain algorithm for finding transformation from sources
#  to targets.
#
#  The main entry point to this module is generators.construct rule. It is given
#  a list of source targets, desired target type and a set of properties.
#  It starts by selecting 'viable generators', which have any chances of producing
#  the desired target type with the required properties. Generators are ranked and
#  a set of most specific ones is selected.
# 
#  The most specific generators have their 'run' methods called, with the properties
#  and list of sources. Each one selects target which can be directly consumed, and
#  tries to convert the remaining ones to the types it can consume. This is done
#  by recursively calling 'construct' with all consumable types.
#
#  If the generator has collected all the targets it needs, it creates targets 
#  corresponding to result, and returns it. When all generators have been run,
#  results of one of them are selected and returned as result.
#
#  It's quite possible that 'construct' returns more targets that it was asked for.
#  For example, it was asked to target type EXE, but the only found generators produces
#  both EXE and TDS (file with debug) information. The extra target will be returned.
#
#  Likewise, when generator tries to convert sources to consumable types, it can get
#  more targets that it was asked for. The question is what to do with extra targets.
#  Boost.Build attempts to convert them to requested types, and attempts as early as
#  possible. Specifically, this is done after invoking each generator. (Later I'll 
#  document the rationale for trying extra target conversion at that point).
#
#  That early conversion is not always desirable. Suppose a generator got a source of
#  type Y and must consume one target of type X_1 and one target of type X_2.
#  When converting Y to X_1 extra target of type Y_2 is created. We should not try to
#  convert it to type X_1, because if we do so, the generator will get two targets
#  of type X_1, and will be at loss as to which one to use. Because of that, the
#  'construct' rule has a parameter, telling if multiple targets can be returned. If
#  the parameter is false, conversion of extra targets is not performed.


import re
import os.path
import type, virtual_target, property_set
from boost.build.util.logger import *
from boost.build.util.utility import *
from boost.build.util import set

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __generators, __type_to_generators, __generators_for_toolset, __construct_stack
    global __overrides, __active_generators
    global __viable_generators_cache, __viable_source_types_cache

    __generators = {}
    __type_to_generators = {}
    __generators_for_toolset = {}
    __overrides = {}
    
    # TODO: can these be global? 
    __construct_stack = []
    __viable_generators_cache = {}
    __viable_source_types_cache = {}
    __active_generators = []

reset ()

_re_separate_types_prefix_and_postfix = re.compile ('([^\\(]*)(\\((.*)%(.*)\\))?')

def normalize_target_list (targets):
    """ Takes a vector of 'virtual-target' instances and makes a normalized
        representation, which is the same for given set of targets,
        regardless of their order.
    """
    return (targets [0], targets [1].sort ())


class Generator:
    """ Creates a generator.
            manager:                 the build manager.
            id:                      identifies the generator
            
            rule:                    the rule which sets up build actions.

            composing:               whether generator processes each source target in
                                     turn, converting it to required types.
                                     Ordinary generators pass all sources together to
                                     recusrive generators.construct_types call.

            source_types (optional): types that this generator can handle
    
            target_types_and_names:  types the generator will create and, optionally, names for
                                     created targets. Each element should have the form
                                         type["(" name-pattern ")"]
                                     for example, obj(%_x). Name of generated target will be found
                                     by replacing % with the name of source, provided explicit name
                                     was not specified.
    
            requirements (optional)
    """
    def __init__ (self, manager, id, rule, composing, source_types, target_types_and_names, requirements):
        self.manager_ = manager
        self.id_ = id
        self.rule_ = rule
        self.composing_ = composing
        self.source_types_ = source_types
        self.target_types_and_names_ = target_types_and_names
        self.requirements_ = requirements
        
        self.target_types_ = []
        self.name_prefix_ = []
        self.name_postfix_ = []
        
        for e in target_types_and_names:
            # Create three parallel lists: one with the list of target types,
            # and two other with prefixes and postfixes to be added to target 
            # name. We use parallel lists for prefix and postfix (as opposed
            # to mapping), because given target type might occur several times,
            # for example "H H(%_symbols)".
            m = _re_separate_types_prefix_and_postfix.match (e)
            
            if not m:
                raise BaseException ("Invalid type and name '%s' in declaration of type '%s'" % (e, id))
            
            target_type = m.group (1)
            if not target_type: target_type = ''
            prefix = m.group (3)
            if not prefix: prefix = ''
            postfix = m.group (4)
            if not postfix: postfix = ''
            
            self.target_types_.append (target_type)
            self.name_prefix_.append (prefix)
            self.name_postfix_.append (postfix)

        for x in self.source_types_:
            type.validate (x)

        if len (self.target_types_) != 1 or self.target_types_ [0] != '*':
            for x in self.target_types_:
                type.validate (x)

    def id (self):
        return self.id_

    def source_types (self):
        """ Returns the list of target type the generator accepts.
        """
        return self.source_types_

    def target_types (self):
        """ Returns the list of target types that this generator produces.
            It is assumed to be always the same -- i.e. it cannot change depending
            list of sources.    
        """
        return self.target_types_

    def requirements (self):
        """ Returns the required properties for this generator. Properties
            in returned set must be present in build properties if this 
            generator is to be used. If result has grist-only element,
            that build properties must include some value of that feature.
        """
        return self.requirements_

    def match_rank (self, property_set_to_match):
        """ Returns true if the generator can be run with the specified 
            properties.
        """
        # See if generator's requirements are satisfied by
        # 'properties'.  Treat a feature name in requirements
        # (i.e. grist-only element), as matching any value of the
        # feature.
        all_requirements = self.requirements ()
        
        property_requirements = []
        feature_requirements = []
        for r in all_requirements:
            if get_value (r):
                property_requirements.append (r)

            else:
                feature_requirements.append (r)

        properties_to_match = property_set_to_match.raw ()
        
        return set.contains (property_requirements, properties_to_match) \
            and set.contains (feature_requirements, get_grist (properties_to_match))
        
###     # Returns another generator which differers from $(self) in
###     # - id
###     # - value to <toolset> feature in properties
###     rule clone ( new-id : new-toolset-properties + )
###     {
###         return [ new $(__class__) $(new-id) $(self.composing_)
###                  : $(self.source_types_)
###                  : $(self.target_types_and_names_) 
###                  # Note: this does not remove any subfeatures of <toolset>
###                  # which might cause problems
###                  : [ property.change $(self.requirements_) : <toolset> ]
###                    $(new-toolset-properties)
###                ] ;
###     }

    def run (self, project, name, prop_set, sources, multiple):
        """ Tries to invoke this generator on the given sources. Returns a
            list of generated targets (instances of 'virtual-target').

            project:        Project for which the targets are generated.
            
            name:           Determines the name of 'name' attribute for 
                            all generated targets. See 'generated_targets' method.
                            
            prop_set:       Desired properties for generated targets.
            
            sources:        Source targets.
            
            multiple:       Allows the rule to run generator several times and return
                            multiple targets of the same type. When this argument is not
                            given, 'run' will return the list of targets, which is equal
                            in size to the list of target types, and where type of
                            each target is the same as the corresponding element of
                            target type list. Non-empty value allows to return several
                            such target lists, joined together.
        """
        # TODO: check this
        # multiple = true ; # The tests seem to tolerate this; will
                          # remove the parameter altogether in the
                          # next revision to see what I learn -- DWA 2003/5/6
        
        if self.manager_.logger ().on ():
            self.manager_.logger ().log (__name__, "  generator '%s'" % self.id_)
            self.manager_.logger ().log (__name__, "  multiple: '%s'" % multiple)
            self.manager_.logger ().log (__name__, "  composing: '%s'" % self.composing_)
        
        if not self.composing_ and len (sources) > 1 and len (self.source_types_) > 1:
            raise BaseException ("Unsupported source/source_type combination")

        if len (self.source_types_) > 1:
            multiple = False
                
        # We don't run composing generators if no name is specified. The reason
        # is that composing generator combines several targets, which can have
        # different names, and it cannot decide which name to give for produced
        # target. Therefore, the name must be passed.
        #
        # This in effect, means that composing generators are runnable only
        # at top-level of transofrmation graph, or if name is passed explicitly.
        # Thus, we dissallow composing generators in the middle. For example, the
        # transofrmation CPP -> OBJ -> STATIC_LIB -> RSP -> EXE won't be allowed 
        # (the OBJ -> STATIC_LIB generator is composing)
        if not self.composing_ or name:
            return self.run_really (project, name, prop_set, sources, multiple)
        else:
            return []

    def run_really (self, project, name, prop_set, sources, multiple):

        # consumed: Targets that this generator will consume directly.
        # bypassed: Targets that can't be consumed and will be returned as-is.
        
        if self.composing_:
            (consumed, bypassed) = self.convert_multiple_sources_to_consumable_types (project, prop_set, sources)

        else:
            (consumed, bypassed) = self.convert_to_consumable_types (project, name, prop_set, sources, multiple, False)
                
        result = []
        if consumed:
            result = self.construct_result (consumed, project, name, prop_set)
            result.extend (bypassed)

        if result:
            if self.manager_.logger ().on ():
                self.manager_.logger ().log (__name__, "  SUCCESS: ", result)

        else:
                self.manager_.logger ().log (__name__, "  FAILURE")

        return result

    def construct_result (self, consumed, project, name, prop_set):
        """ Constructs the dependency graph that will be returned by this 
            generator.
                consumed:        Already prepared list of consumable targets
                                 If generator requires several source files will contain 
                                 exactly len $(self.source_types_) targets with matching types
                                 Otherwise, might contain several targets with the type of 
                                 self.source_types_ [0]
                project:
                name:
                prop_set:        Properties to be used for all actions create here
        """
        result = []
        # If this is 1->1 transformation, apply it to all consumed targets in order.
        if len (self.source_types_) < 2 and not self.composing_:
            if self.manager_.logger ().on ():
                self.manager_.logger ().log (__name__, "alt1")

            for r in consumed:
                result.extend (self.generated_targets ([r], prop_set, project, name))

        else:
            if self.manager_.logger ().on ():
                self.manager_.logger ().log (__name__, "alt2 : consumed is ", consumed)

            if consumed:
                result.extend (self.generated_targets (consumed, prop_set, project, name))

        return result

    def generated_targets (self, sources, prop_set, project, name):
        """ Constructs targets that are created after consuming 'sources'.
            The result will be the list of virtual-target, which the same length
            as 'target_types' attribute and with corresponding types.
            
            When 'name' is empty, all source targets must have the same value of 
            the 'name' attribute, which will be used instead of the 'name' argument.
            
            The value of 'name' attribute for each generated target will be equal to
            the 'name' parameter if there's no name pattern for this type. Otherwise,
            the '%' symbol in the name pattern will be replaced with the 'name' parameter 
            to obtain the 'name' attribute.
            
            For example, if targets types are T1 and T2(with name pattern "%_x"), suffixes
            for T1 and T2 are .t1 and t2, and source if foo.z, then created files would
            be "foo.t1" and "foo_x.t2". The 'name' attribute actually determined the
            basename of a file.
            
            Note that this pattern mechanism has nothing to do with implicit patterns
            in make. It's a way to produce target which name is different for name of 
            source.
        """
        if not name:
            name = os.path.splitext (sources [0].name ()) [0]

            for s in sources [1:]:
                n2 = os.path.splitext (s.name ()) [0]
                if n2 != name:
                    raise BaseException ("'%s': source targets have different names: cannot determine target name" % self.id ())

            # Names of sources might include directory. We should strip it.
            name = os.path.basename (name)
        
        # Assign an action for each target
        action = self.action_class ()
        
        a = action (self.manager_, sources, self.rule_, prop_set)
                
        # Create generated target for each target type.
        targets = []
        pre = self.name_prefix_
        post = self.name_postfix_
        for t in self.target_types_:
            generated_name = pre [0] + name + post [0]
            pre = pre [1:]
            post = post [1:]
            
            targets.append (virtual_target.FileTarget (generated_name, False, t, project, a))

        for t in targets:
            t.set_intermediate (True)
        
        return [ self.manager_.virtual_targets ().register (t) for t in targets ]

    def convert_to_consumable_types (self, project, name, prop_set, sources, multiple, only_one):
        """ Attempts to convert 'source' to the types that this generator can
            handle. The intention is to produce the set of targets can should be
            used when generator is run.
            only_one:   convert 'source' to only one of source types
                        if there's more that one possibility, report an
                        error.
                        
            Returns a pair:
                consumed: all targets that can be consumed. 
                bypassed: all targets that cannot be consumed.
        """
        consumed = []
        bypassed = []
        missing_types = [] 

        if len (sources) > 1:
            # Don't know how to handle several sources yet. Just try 
            # to pass the request to other generator
            missing_types = self.source_types_

        else:
            (c, m) = self.consume_directly (sources [0])
            consumed += c
            missing_types += m
        
        # No need to search for transformation if
        # some source type has consumed source and
        # no more source types are needed.
        if only_one and consumed:
            missing_types = []
            
        #TODO: we should check that only one source type
        #if create of 'only_one' is true.
        # TODO: consider if consuned/bypassed separation should
        # be done by 'construct_types'.
                    
        if missing_types:
            transformed = construct_types (project, name, missing_types, multiple, prop_set, sources)
                                
            # Add targets of right type to 'consumed'. Add others to
            # 'bypassed'. The 'generators.construct' rule has done
            # its best to convert everything to the required type.
            # There's no need to rerun it on targets of different types.
                
            # NOTE: ignoring usage requirements
            for t in transformed [1]:
                if t.type () in missing_types:
                    consumed.append (t)

                else:
                    bypassed.append (t)
        
        consumed = unique (consumed)
        bypassed = unique (bypassed)
        
        # remove elements of 'bypassed' that are in 'consumed'
        
        # Suppose the target type of current generator, X is produced from 
        # X_1 and X_2, which are produced from Y by one generator.
        # When creating X_1 from Y, X_2 will be added to 'bypassed'
        # Likewise, when creating X_2 from Y, X_1 will be added to 'bypassed'
        # But they are also in 'consumed'. We have to remove them from
        # bypassed, so that generators up the call stack don't try to convert
        # them. 

        # In this particular case, X_1 instance in 'consumed' and X_1 instance
        # in 'bypassed' will be the same: because they have the same source and
        # action name, and 'virtual-target.register' won't allow two different
        # instances. Therefore, it's OK to use 'set.difference'.
        
        bypassed = set.difference (bypassed, consumed)

        return (consumed, bypassed)
    

    def convert_multiple_sources_to_consumable_types (self, project, prop_set, sources, multiple):
        """ Converts several files to consumable types.
        """
        if not multiple:
            multiple = '*'
        
        consumed = []
        bypassed = []

        # We process each source one-by-one, trying to convert it to
        # a usable type.
        for s in sources:
            # TODO: need to check for failure on each source.
            (c, b) = convert_to_consumable_types (project, None, prop_set, s, multiple, True)
            if not c:
                self.manager_.logger ().log (__name__, " failed to convert ", s)

            consumed.extend (c)
            bypassed.extend (b)

        return (consumed, bypassed)

    def consume_directly (self, source):
        real_source_type = source.type ()

        consumed = []
        missing_types = []
        for st in self.source_types_:
            # The 'source' if of right type already)
            if real_source_type == st or type.is_derived (real_source_type, st):
                consumed.append (source)

            else:
               missing_types.append (st)
       
        return (consumed, missing_types)
    
    def action_class (self):
        """ Returns the class to be used to actions. Default implementation 
            returns "action".
        """
        return virtual_target.Action


def find (id):
    """ Finds the generator with id. Returns None if not found.
    """
    return __generators.get (id, None)

def register (id, g):
    """ Registers new generator instance 'g'.
    """
    __generators [id] = g
                   
    for t in g.target_types ():
        values = __type_to_generators.get (t, [])
        values.append (g)
        __type_to_generators [t] = values

    # Update the set of generators for toolset

    # TODO: should we check that generator with this id
    # is not already registered. For example, the fop.jam
    # module intentionally declared two generators with the
    # same id, so such check will break it.
    id = g.id ()

    base = id
    while (os.path.splitext (base) [1]):
        base = os.path.splitext (base) [0]

    values = __generators_for_toolset.get (base, [])
    values.append (g)
    __generators_for_toolset [base] = values

def register_standard (manager, id, rule, source_types, target_types, requirements = []):
    """ Creates new instance of the 'generator' class and registers it.
        Returns the creates instance.
        Rationale: the instance is returned so that it's possible to first register
        a generator and then call 'run' method on that generator, bypassing all
        generator selection.
    """
    g = Generator (manager, id, rule, False, source_types, target_types, requirements)
    register (id, g)
    return g

def register_composing (id, rule, source_types, target_types, requirements = []):
    g = Generator (id, rule, True, source_types, target_types, requirements)
    register (id, g)
    return g

def generators_for_toolset (toolset):
    """ Returns all generators which belong to 'toolset'.
    """
    return __generators_for_toolset.get (toolset, [])

def override (overrider_id, overridee_id):
    prev = __overrides.get (overrider_id, [])
    prev.append (overridee_id)
    __overrides.get [overrider_id] = prev

def base_to_derived_type_conversion (targets, target_types):
    """ For all t in 'targets':
        if [ $(t).type ] in $(target_types), add 't' to result
        if [ $(t).type ] in base type for any of 'target_types', add 't' to result
        otherwise, add 't' to extra.
    """
    result = []
    extra = []
    for t in targets:
        if t.type () in target_types:
            result.append (t)

        else:
            # We might have asked for a type 'D', but found only generator for
            # a type 'B', where 'D' is derived from 'B'. In this case, the 
            # generation succeeds, but we should change type of the generated target.
            
            at = t.type ()
            found = False
            for tt in target_types:
                if not found and type.is_derived (tt, at):
                    t.set_type (tt)
                    result.append (t)
                    found = True

            if not found:
                extra.append (t)
                
    return (result, extra)

def __viable_source_types_real (target_type):
    """ Returns a list of source type which can possibly be converted
        to 'target_type' by some chain of generator invocation.
        
        More formally, takes all generators for 'target_type' and
        returns union of source types for those generators and result
        of calling itself recusrively on source types.
    """
    generators = []
        
    t = type.all_bases (target_type)
    
    result = []
    # 't' is the list of types which are not yet processed    
    while t:
        # Find all generators for current type. 
        # Unlike 'find_viable_generators' we don't care about prop_set.
        generators = __type_to_generators.get (t [0], [])
        t = t [1:]
        
        for g in generators:
            for source_type in g.source_types ():
                if not source_type in result:
                    # If generator accepts 'source_type' it
                    # will happily accept any type derived from it
                    all = type.all_derived (source_type)
                    for n in all:
                        if not n in result:
                            t.append (n)
                            result.append (n)
        
    result = unique (result)
    
    return result


def viable_source_types (target_type):
    """ Helper rule, caches the result of '__viable_source_types_real'.
    """
    if not __viable_source_types_cache.has_key (target_type):
         __viable_source_types_cache [target_type] = __viable_source_types_real (target_type)
    return __viable_source_types_cache [target_type]

def viable_source_types_for_generator_real (generator):
    """ Returns the list of source types, which, when passed to 'run'
        method of 'generator', has some change of being eventually used
        (probably after conversion by other generators)
    """
    source_types = generator.source_types ()

    if not source_types:
        # If generator does not specify any source types,
        # it might be special generator like builtin.lib-generator
        # which just relays to other generators. Return '*' to
        # indicate that any source type is possibly OK, since we don't
        # know for sure.
        return ['*']

    else:
        result = []
        for s in source_types:
            result += type.all_derived (s) + viable_source_types (s)

        result = unique (result)
        return result

def viable_source_types_for_generator (generator):
    """ Caches the result of 'viable_source_types_for_generator'.
    """
    key = str (generator)
    if not __viable_source_types_cache.has_key (key):
        __viable_source_types_cache [key] = viable_source_types_for_generator_real (generator)
    
    return __viable_source_types_cache [key]

def try_one_generator_really (project, name, generator, multiple, target_type, properties, sources):
    """ Returns usage requirements + list of created targets.
    """
    targets = generator.run (project, name, properties, sources, multiple)

    usage_requirements = []
    if targets and isinstance (targets [0], property_set.PropertySet):
        usage_requirements = targets [0]
        targets = targets [1:]

    else:
        usage_requirements = property_set.empty ()
    
    if targets == None: targets = []
    # (Generated targets that are of required types, Generated target of other types)
    (result, extra) = base_to_derived_type_conversion (targets, [target_type])
            
    # Now try to convert extra targets 
    # 'construct' will to its best to return only requested
    # target types, so if we receive any extra from that call,
    # we don't try to do anything about them.
    extra2 = []
    if multiple:
        for e in extra:
            try2 = construct_types (project, name, target_type, False, properties, e)
            usage_requirements = usage_requirements.add (try2 [0])
            result.extend (try2 [1:])

    else:
        extra2 = extra

    if project.manager ().logger ().on ():
        project.manager ().logger ().log (__name__, "  generator '%s' spawned " % generator.id ())
        project.manager ().logger ().log (__name__, " '%s' -- '%s'" % (result, extra2))

    if targets:
        result = (usage_requirements, result)

    return (result [0], result [1] + extra2)


def try_one_generator (project, name, generator, multiple, target_type, properties, sources):
    """ Checks if generator invocation can be pruned, because it's guaranteed
        to fail. If so, quickly returns empty list. Otherwise, calls
        try_one_generator_really.
    """
    source_types = []

    for s in sources:
        source_types.append (s.type ())

    viable_source_types = viable_source_types_for_generator (generator)
    
    if  source_types and viable_source_types != ['*'] and not set.intersection (source_types, viable_source_types):
        if project.manager ().on ():
            id = generator.id ()
            project.manager ().log (__name__, "generator '%s' pruned" % id)
            project.manager ().log (__name__, "source_types" '%s' % source_types)
            project.manager ().log (__name__, "viable_source_types '%s'" % viable_source_types)
        
        return []

    else:
        return try_one_generator_really (project, name, generator, multiple, target_type, properties, sources)


def construct_types (project, name, target_types, multiple, prop_set, sources):
    result = []
    usage_requirements = property_set.empty ()

    for t in target_types:
        r = construct (project, name, t, multiple, prop_set, sources)

        if r:
            (ur, targets) = r
            usage_requirements = usage_requirements.add (ur)
            result.extend (targets)

    # TODO: have to introduce parameter controlling if
    # several types can be matched and add appropriate
    # checks 

    # TODO: need to review the documentation for
    # 'construct' to see if it should return $(source) even
    # if nothing can be done with it. Currents docs seem to
    # imply that, contrary to the behaviour.
    if result:
        return (usage_requirements, result)

    else:
        return (usage_requirements, sources)

def __ensure_type (targets):
    """ Ensures all 'targets' have types. If this is not so, exists with 
        error.
    """
    for t in targets:
        if not t.type ():
            raise BaseException ("target '%s' has no type" % t.str ())

def find_viable_generators_aux (logger, target_type, prop_set):
    """ Returns generators which can be used to construct target of specified type
        with specified properties. Uses the following algorithm:
        - iterates over requested target_type and all it's bases (in the order returned bt
          type.all-bases.
        - for each type find all generators that generate that type and which requirements
          are satisfied by properties.
        - if the set of generators is not empty, returns that set.
        
        Note: this algorithm explicitly ignores generators for base classes if there's
        at least one generator for requested target_type.
    """
    # Select generators that can create the required target type.
    viable_generators = []

    import type

    # Try all-type generators first. Assume they have
    # quite specific requirements.
    t = ['*'] + type.all_bases (target_type)
    
    logger.log (__name__, "find_viable_generators target_type = '%s'  property_set = '%s'" % (target_type, prop_set.as_path ()))
    
    while t:
        logger.log (__name__, "trying type ", t [0])
        
        generators_for_this_type = __type_to_generators.get (t [0], [])

        for g in generators_for_this_type:
            logger.log (__name__, "trying generator '%s' (%s -> %s)" % (g.id (), g.source_types (), g.target_types ()))
    
            m = g.match_rank (prop_set)
            if m:
                logger.log (__name__, "  is viable")
                viable_generators.append (g)
                t = []

        t = t [1:]

    return viable_generators

def find_viable_generators (logger, target_type, prop_set):
    key = target_type + '.' + str (prop_set)

    l = __viable_generators_cache.get (key, None)

    if not l:
        l = find_viable_generators_aux (logger, target_type, prop_set)

        __viable_generators_cache [key] = l

    viable_generators = []
    for g in l:
        # Avoid trying the same generator twice on different levels.
        # TODO: is this really used?
        if not g in __active_generators:
            viable_generators.append (g)

    # Generators which override 'all'.
    all_overrides = []
    
    # Generators which are overriden
    overriden_ids = [] 
       
    for g in viable_generators:
        id = g.id ()
        
        this_overrides = __overrides.get (id, [])
        
        if this_overrides:
            overriden_ids.extend (this_overrides)
            if 'all' in this_overrides:
                all_overrides.append (g)

    if all_overrides:
        viable_generators = all_overrides

    result = []
    for g in viable_generators:
        if not g.id () in overriden_ids:
            result.append (g)
        
    return result

    
def select_dependency_graph (logger, options):
    """ Given a vector of vectors, each one of them representing results of running some 
        generator, returns the 'best' result, it exists. Otherwise, exit with
        an error. Result is returned as plain sequence.
    """
    if len (options) == 0:
        return []

    if len (options) == 1:
        return options [0]

    # We have several alternatives and need to check if they
    # are the same. 
    
    for r in options:
        r = normalize_target_list (r)
        if logger.on ():
            logger.log (__name__, r [1:])
    
    # One note why we can compare object names directly,
    # without using deep copy. All the targets here are
    # produced by some generators, and generators should
    # pass the targets they've returned via 'virtual-target.register'.
    # So, two elements can only be equivalent, if they are just
    # the same object.       
    f = options [0]
    f = f [1:]

    mismatch = False
    for r in options:
        v = r
        v = v [1:]

        if f != v:
            mismatch = True

    if not mismatch:
        v = options [0]
        return v

    else:
        raise BaseException ("%d possible generations for '%s'. Can't handle this now." % (len (options), target_types))
    
def __construct_really (project, name, target_type, multiple, prop_set, sources):
    """ Attempts to construct target by finding viable generators, running them
        and selecting the dependency graph.
    """
    viable_generators = find_viable_generators (project.manager ().logger (), target_type, prop_set)
                    
    result = []
    
    project.manager ().logger ().log (__name__, "*** %d viable generators" % len (viable_generators))
    
    for g in viable_generators:
        # This variable will be restored on exit from this scope.

        # TODO: why is this used? I don't see it anywhere.
        # local .active-generators = $(g) $(.active-generators) ;
        
        r = try_one_generator (project, name, g, multiple, target_type, prop_set, sources)
        
        if r:
            result.append (r)
    
    return select_dependency_graph (project.manager ().logger (), result)



def construct (project, name, target_type, multiple, prop_set, sources, allowed_type = None):
    """ Attempts to create target of 'target_type' with 'properties'
        from 'sources'. The 'sources' are treated as a collection of
        *possible* ingridients -- i.e. it is not required to consume
        them all. If 'multiple' is true, the rule is allowed to return
        several targets of 'target_type'.          
        
        Returns a list of target. When this invocation is first instance of
        'construct' in stack, returns only targets of requested 'target_type',
        otherwise, returns also unused sources and additionally generated
        targets.    
        
        Does not return target which are not of 'allowed_type' or of type derived from
        it. If 'allowed_type' is not specified, it's defaulted to 'target_type'.
        See lib-target-class for use case of this.
        project:
        name (optional):
        target_type:
        multiple (optional):
        prop_set (optional):
        sources (optional):
        allowed_type (optional):
    """
    if not allowed_type:
        allowed_type = target_type

    # TODO: Why is global needed here?
    global __construct_stack
    if __construct_stack:
        __ensure_type (sources)

    # Intermediate targets are not passed to generators
    # and just returned unmodified.
    intermediate = []
    if not __construct_stack:
        sources2 = []
        for s in sources:
            if not s.intermediate ():
                sources2.append (s)

            else:
                intermediate.append (s)

        sources = sources2
        
    __construct_stack.append (1)

    if project.manager ().logger ().on ():
        project.manager ().logger ().increase_indent ()
        
        m = ''
        if multiple:
            m = " (may return multiple targets)"

        project.manager ().logger ().log (__name__, "*** construct ", target_type, m)
        
        for s in sources:
            project.manager ().logger ().log (__name__, "    from ", s)

        project.manager ().logger ().log (__name__, "    properties: ", prop_set.raw ())
             
    result = __construct_really (project, name, target_type, multiple, prop_set, sources)

    project.manager ().logger ().decrease_indent ()
        
    __construct_stack = __construct_stack [1:]
    
    if not __construct_stack:
        result = (result [0], result [1] + intermediate)
            
    # For all targets of 'allowed_type', reset the 'intermediate' attribute.
    if not __construct_stack and allowed_type != '*': # This is first invocation in stack
        result2 = []
        for t in result [1]:
            t_type = t.type ()

            # Return only targets of the requested type, unless 'return-all'
            # is specified. If we don't do this, then all targets calling
            # 'construct' will get unused target returned, which will break
            # checking for unused sources a bit harder.
            if t_type and (t_type == target_type or type.is_derived (t_type, allowed_type)):
                t.set_intermediate (False)
            
    return result  
