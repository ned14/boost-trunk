#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

#   Supports 'abstract' targets, which are targets explicitly defined in Jamfile.
#
#   Abstract targets are represented by classes derived from 'AbstractTarget' class. 
#   The first abstract target is 'project_target', which is created for each
#   Jamfile, and can be obtained by the 'target' rule in the Jamfile's module.
#   (see project.jam). 
#
#   Project targets keep a list of 'MainTarget' instances.
#   A main target is what the user explicitly defines in a Jamfile. It is
#   possible to have several definitions for a main target, for example to have
#   different lists of sources for different platforms. So, main targets
#   keep a list of alternatives.
#
#   Each alternative is an instance of 'AbstractTarget'. When a main target
#   subvariant is defined by some rule, that rule will decide what class to
#   use, create an instance of that class and add it to the list of alternatives
#   for the main target.
#
#   Rules supplied by the build system will use only targets derived
#   from 'BasicTarget' class, which will provide some default behaviour.
#   There will be two classes derived from it, 'make-target', created by the
#   'make' rule, and 'TypedTarget', created by rules such as 'exe' and 'dll'.

#
#                         +------------------------+
#                         |AbstractTarget          |
#                         +========================+
#                         |name                    |
#                         |project                 |                                   
#                         |                        |                                   
#                         |generate(properties) = 0|                                   
#                         +-----------+------------+                                   
#                                     |                                                
#                                     ^                                                
#                                    / \                                               
#                                   +-+-+                                              
#                                     |                                                
#                                     |                                                
#            +------------------------+------+------------------------------+          
#            |                               |                              |          
#            |                               |                              |          
# +----------+-----------+            +------+------+                +------+-------+  
# | project_target       |            | MainTarget  |                | BasicTarget  |  
# +======================+ 1        * +=============+  alternatives  +==============+  
# | generate(properties) |o-----------+ generate    |<>------------->| generate     |  
# | main-target          |            +-------------+                | construct = 0|
# +----------------------+                                           +--------------+  
#                                                                           |          
#                                                                           ^          
#                                                                          / \         
#                                                                         +-+-+        
#                                                                           |          
#                                                                           |          
#                 ...--+----------------+------------------+----------------+---+      
#                      |                |                  |                    |      
#                      |                |                  |                    |      
#               ... ---+-----+   +------+-------+   +------+------+    +--------+-----+
#                            |   | TypedTarget  |   | make-target |    | stage-target |
#                            .   +==============+   +=============+    +==============+
#                            .   | construct    |   | construct   |    | construct    |
#                                +--------------+   +-------------+    +--------------+

import re
import os.path

from boost.build.util.utility import *
import property, project, virtual_target, property_set, feature, generators
from virtual_target import Subvariant
from boost.build.exceptions import *
from boost.build.util.sequence import unique
from boost.build.util import set, path

_re_separate_target_from_properties = re.compile (r'^([^<]*)(/(<.*))?$')

class TargetRegistry:
    
    def __init__ (self):
        # All targets that are currently being built.
        # Only the key is id (target), the value is the actual object.
        self.targets_being_built_ = {}

    def main_target_alternative (self, target):
        """ Registers the specified target as a main target alternatives.
            Returns 'target'.
        """
        target.project ().add_alternative (target)
        return target

    def main_target_sources (self, sources, main_target_name):
        """ Return the list of sources to use, if main target rule is invoked
            with 'sources'. If there are any objects in 'sources', they are treated
            as main target instances, and WRITEME.
        """
        result = []

        for t in sources:
            if isinstance (t, AbstractTarget):
                name = t.name ()
                
                # NOTE: on windows, this won't work if 'main_target_name'
                # is a single letter. But other alternatives are even worse.
                new_name = main_target_name + '..' + name
                t.rename (new_name)
                result.append (new_name)

            else:
                result.append (t)

        return result

    def main_target_requirements (self, specification, project):
        """ Returns the requirements to use when declaring a main target,
            which are obtained by:
            - translating all specified property paths, and
            - refining project requirements with the one specified for the target
          
            specification:  Properties explicitly specified for a main target
            project:        Project where the main target is to be declared
        """
        manager = project.manager ()
        
        loc = project.get ('location')
        requirements = property.translate_paths (specification, loc)
        requirements = property.expand_subfeatures_in_conditions (requirements)
        requirements = property_set.create (requirements)
        project_requirements = project.get ('requirements')
        requirements = project_requirements.refine (requirements)

        # TODO: check this
        if "@error" in str (requirements):
            raise BaseException ("Conflicting requirements for target: %s" % requirements)

        return requirements

    def main_target_usage_requirements (self, specification, project):
        """ Returns the use requirement to use when declaraing a main target,
            which are obtained by
            - translating all specified property paths, and
            - adding project's usage requirements
            specification:  Use-properties explicitly specified for a main target
            project:        Project where the main target is to be declared
        """
        loc = project.get ('location')

        project_usage_requirements = project.get ('usage-requirements')
            
        usage_requirements = property_set.create (property.translate_paths (specification, loc))
        
        return project_usage_requirements.add (usage_requirements)

    def main_target_default_build (self, specification, project):
        """ Return the default build value to use when declaring a main target,
            which is obtained by using specified value if not empty and parent's
            default build attribute otherwise.
            specification:  Default build explicitly specified for a main target
            project:        Project where the main target is to be declared
        """
        if specification:
            result = specification

        else:
            result = project.get ('default-build')

        return property_set.create_with_validation (result)

    def start_building (self, main_target_instance):
        """ Helper rules to detect cycles in main target references.
        """
        if self.targets_being_built_.has_key (id (main_target_instance)):
            names = []
            for t in self.targets_being_built_.values ():
                names.append (t.full_name ())
            
            raise Recursion ("Recursion in main target references" 
                "the following target are being built currently: '%s'" % names)
        
        self.targets_being_built_ [id (main_target_instance)] = main_target_instance

    def end_building (self, main_target_instance):
        assert (self.targets_being_built_.has_key (id (main_target_instance)))
        del self.targets_being_built_ [id (main_target_instance)]

    def create_typed_target (self, type, project, name, sources, requirements, default_build, usage_requirements):
        """ Creates a TypedTarget with the specified properties.
            The 'name', 'sources', 'requirements', 'default_build' and
            'usage_requirements' are assumed to be in the form specified
            by the user in Jamfile corresponding to 'project'.
        """
        return self.main_target_alternative (TypedTarget (name, project, type,
            self.main_target_sources (sources, name),
            self.main_target_requirements (requirements, project),
            self.main_target_default_build (default_build, project),
            self.main_target_usage_requirements (usage_requirements, project)))

class GenerateResult:
    
    def __init__ (self, ur = None, targets = []):
        self.__usage_requirements = ur
        self.__targets = targets

        if not self.__usage_requirements:
            self.__usage_requirements = property_set.empty ()

    def usage_requirements (self):
        return self.__usage_requirements

    def targets (self):
        return self.__targets
    
    def extend (self, other):
        assert (isinstance (other, GenerateResult))
        
        self.__usage_requirements = self.__usage_requirements.add (other.usage_requirements ())
        self.__targets.extend (other.targets ())
        self.__targets = unique (self.__targets)

class AbstractTarget:
    """ Base class for all abstract targets.
    """
    def __init__ (self, name, project, manager = None):
        """ manager:     the Manager object
            name:        name of the target
            project:     the project target to which this one belongs
            manager:the manager object. If none, uses project.manager ()
        """
        assert (isinstance (project, ProjectTarget))
        # Note: it might seem that we don't need either name or project at all.
        # However, there are places where we really need it. One example is error
        # messages which should name problematic targets. Another is setting correct
        # paths for sources and generated files.
        
        # Why allow manager to be specified? Because otherwise project target could not derive
        # from this class.
        if manager:
            self.manager_ = manager
        else:
            self.manager_ = project.manager ()

        self.name_ = name
        self.project_ = project
        
        # TODO: do we need this? If yes, how?
        # self.location_ = [ errors.nearest-user-location ] ;
        self.location_ = None
    
    def manager (self):
        return self.manager_
    
    def name (self):
        """ Returns the name of this target.
        """
        return self.name_
    
    def project (self):
        """ Returns the project for this target.
        """
        return self.project_
    
    def location (self):
        """ Return the location where the target was declared.
        """
        return self.location_
            
    def full_name (self):
        """ Returns a user-readable name for this target.
        """
        location = self.project ().get ('location')
        return location + '/' + self.name_
        
    def generate (self, property_set):
        """ Takes a property set.  Generates virtual targets for this abstract
            target, using the specified properties, unless a different value of some
            feature is required by the target. 
            On success, returns a GenerateResult instance with:
                - a property_set with the usage requirements to be
                  applied to dependents 
                - a list of produced virtual targets, which may be
                   empty.  
            If 'property_set' is empty, performs default build of this
            target, in a way specific to derived class.
        """
        raise BaseException ("method should be defined in derived classes")
    
    def rename (self, new_name):
        self.name_ = new_name


class ProjectTarget (AbstractTarget):
    """ Project target class (derived from 'AbstractTarget')

        This class these responsibilities:
        - maintaining a list of main target in this project and
          building it

        Main targets are constructed in two stages:
        - When Jamfile is read, a number of calls to 'add_alternative' is made.
          At that time, alternatives can also be renamed to account for inline
          targets.
        - The first time 'main-target' or 'has-main-target' rule is called,
          all alternatives are enumerated an main targets are created.
    """
    def __init__ (self, name, project_module, parent_project, requirements, default_build):
        AbstractTarget.__init__ (self, name, self, project_module.manager ())

        self.project_module_ = project_module
        self.location_ = project_module.attribute ('location')
        self.requirements_ = requirements
        self.default_build_ = default_build
       
        self.build_dir_ = None

        if parent_project:
            self.inherit (parent_project)
        
        # A cache of IDs
        self.ids_cache_ = {}
        
        # True is main targets have already been built.
        self.built_main_targets_ = False
        
        # A list of the registered alternatives for this project.
        self.alternatives_ = []

        # A map of all main targets.
        self.main_targets_ = {}
        
        # Targets marked as explicit.
        self.explicit_targets_ = []

    # TODO: This is needed only by the 'make' rule. Need to find the
    # way to make 'make' work without this method.
    def project_module (self):
        return self.project_module_
    
    def get (self, attribute):
        return self.project_module_.attribute (attribute)

    def build_dir (self):
        if not self.build_dir_:
            self.build_dir_ = self.get ('build-dir')
            if not self.build_dir_:
                self.build_dir_ = os.path.join (self.project_.get ('location'), 'bin')

        return self.build_dir_

    def generate (self, ps):
        """ Generates all possible targets contained in this project.
        """
        if self.manager_.logger ().on ():
            self.manager_.logger ().log (__name__, "Building project '%s' with '%s'" % (self.name (), ps.raw ()))
            self.manager_.logger ().increase_indent ()
        
        result = GenerateResult ()
                
        for t in self.targets_to_build ():
            g = t.generate (ps)
            result.extend (g)

        self.manager_.logger ().decrease_indent ()
        return result

    def add_alternative (self, target_instance):
        """ Add new target alternative.
        """
        if self.built_main_targets_:
            raise IllegalOperation ("add-alternative called when main targets are already created for project '%s'" % self.full_name ())

        self.alternatives_.append (target_instance)
    
        
    def targets_to_build (self):
        """ Computes and returns a list of AbstractTarget instances which
            must be built when this project is built.
        """
        result = []
        
        if not self.built_main_targets_:
            self.build_main_targets ()
        
        # Collect all main targets here, except for "explicit" ones.
        for n, t  in self.main_targets_.iteritems ():
            if not t.name () in self.explicit_targets_:
                result.append (t)

        # Collect all projects referenced via "projects-to-build" attribute.
        self_location = self.get ('location')
        for pn in self.get ('projects-to-build'):
            p = self.project_module_.registry ().module_name (Path.join (self_location, pn))
            result.append (self.project_module_.registry ().target (p))
                        
        return result
    
#       # Add 'target' to the list of targets in this project that should be build
#       # only by explicit request
#       rule mark-target-as-explicit ( target-name )
#       {
#           # Record the name of the target, not instance, since this
#           # rule is called before main target instaces are created.
#           self.explicit_targets_ += $(target-name) ;
#       }

    def create_main_target (self, name):
        """ Returns a 'MainTarget' class instance corresponding to the 'name'.
        """
        if not self.built_main_targets_:
            self.build_main_targets ()
                        
        return self.main_targets_.get (name, None)

#       # Tells if a main target with the specified name exists.
#       rule has-main-target ( name )
#       {
#           if ! $(self.built_main_targets_)
#           {
#               build_main_targets ;
#           }
#           
#           if $(self.main_targets_.$(name)) 
#           {
#               return true ;
#           } 
#       }
#   

    def find_really (self, id):
        """ Find and return the target with the specified id, treated
            relative to self.
        """
        result = None
        current_location = self.get ('location')

        __re_split_project_target = re.compile (r'(.*)//(.*)')
        split = __re_split_project_target.match (id)

        project_part = None
        target_part = id

        if split:
            project_part = split.group (1)
            target_part = split.group (2)

        project_registry = self.project_.manager ().projects ()
        
        extra_error_message = ''
        if project_part:
            # There's explicit project part in id. Looks up the
            # project and pass the request to it.
            pm = project_registry.find (project_part, current_location)
            
            if pm:
                project_target = project.target (pm)
                result = project_target.find (target_part, true)

            else:
                extra_error_message = "error: could not find project '$(project_part)'"

        else:
            # Interpret as filename            
            result = FileReference (self.manager_, path.make (id), self.project_)
            if not result.exists ():
                # File actually does not exist.            
                # Interpret target-name as name of main target
                result = self.create_main_target (id)
                
                # Interpret id as project-id
                if not result:
                    project_module = project_registry.find (id, current_location)
                    if project_module:
                        result = project.target (project_module)
                
        return result

    def find (self, id, no_error = False):
        v = self.ids_cache_.get (id, None)
        
        if not v:
            v = self.find_really (id)
            self.ids_cache_ [id] = v

        if v or no_error:
            return v

        raise BaseException ("Unable to find file or target named '%s'\nreferred from project at '%s'" % (id, self.get ('location')))

    
    def build_main_targets (self):
        self.built_main_targets_ = True
        
        for a in self.alternatives_:
            name = a.name ()
            if not self.main_targets_.has_key (name):
                t = MainTarget (name, self.project_)
                self.main_targets_ [name] = t
            
            self.main_targets_ [name].add_alternative (a)
    
#       # Accessor, add a constant.
#       rule add-constant (
#           name # Variable name of the constant.
#           : value # Value of the constant.
#           : type ? # Optional type of value.
#           )
#       {
#           switch $(type)
#           {
#               case path :
#                   value = [ path.root [ path.make $(value) ] $(self.location_) ] ;
#                   # Now make the value absolute path
#                   value = [ path.root $(value) [ path.pwd ] ] ;
#                   # Constants should be in platform-native form
#                   value = [ path.native $(value) ] ;
#           }
#           if ! $(name) in $(self.constants)
#           {
#               self.constants += $(name) ;
#           }
#           self.constant.$(name) = $(value) ;
#           # Inject the constant in the scope of project-root module
#           modules.poke $(self.project_module_) : $(name) : $(value) ;
#       }
#       
#       rule inherit ( parent )
#       {
#           for local c in [ modules.peek $(parent) : self.constants ] 
#           {
#               # No need to pass the type. Path constants were converted to
#               # absolute paths already by parent.
#               add-constant $(c) 
#                 : [ modules.peek $(parent) : self.constant.$(c) ] ;
#           }       
#   
#           # Import rules from parent 
#           local this-module = [ project_module ] ;
#           local parent-module = [ $(parent).project_module ] ;
#           # Don't import rules which comes from 'project-rules', they
#           # must be imported localized.
#           local user-rules = [ set.difference 
#               [ RULENAMES $(parent-module) ] :
#               [ RULENAMES project-rules ] ] ;
#           IMPORT $(parent-module) : $(user-rules) : $(this-module) : $(user-rules) ;
#           EXPORT $(this-module) : $(user-rules) ;
#       }
#       
#       
#       # Intern the constants from this project into the specified module.
#       #
#       rule intern-constants (
#           target-module # The module to intern into.
#           )
#       {
#           for local c in $(self.constants)
#           {
#               modules.poke $(target-module) : $(c) : $(self.constant.$(c)) ;
#           }
#       }
#   
#   }






class BasicTarget (AbstractTarget):
    """ Implements the most standard way of constructing main target
        alternative from sources. Allows sources to be either file or
        other main target and handles generation of those dependency
        targets.
    """
    def __init__ (self, name, project, sources, requirements = None, default_build = None, usage_requirements = None):
        AbstractTarget.__init__ (self, name, project)
    
        for s in sources:
            if get_grist (s):
                raise InvalidSource ("gristed element '%s' in sources for '%s'" % (s, name))
    
        self.sources_ = sources
        
        if not requirements: requirements = property_set.empty ()
        self.requirements_ = requirements

        if not default_build: default_build = property_set.empty ()
        self.default_build_ = default_build

        if not usage_requirements: usage_requirements = property_set.empty ()
        self.usage_requirements_ = usage_requirements
        
        # A cache for resolved references
        self.source_targets_ = None
        
        # A cache for generated targets
        self.generated_ = {}
        
        # A cache for build requests
        self.request_cache = {}
        
    def sources (self):
        """ Returns the list of AbstractTargets which are used as sources.
            The extra properties specified for sources are not represented.
        """
        if self.source_targets_ == None:
            self.source_targets_ = []
            for s in self.sources_:
                self.source_targets_.append (self.resolve_reference (s, self.project_))

        return self.source_targets_

    def requirements (self):
        return self.requirements_
                        
    def default_build (self):
        return self.default_build_

    def resolve_reference (self, target_reference, project):
        """ Given a target_reference, made in context of 'project',
            returns the AbstractTarget instance that is referred to, as well
            as properties explicitly specified for this reference.
        """
        # Separate target name from properties override
        split = _re_separate_target_from_properties.match (target_reference)
        if not split: raise BaseException ("Invalid reference: '%s'" % target_reference)
        
        id = split.group (1)
        
        sproperties = []
        
        if split.group (3):
            sproperties = property.make (Feature.split (split.group (3)))
            sproperties = self.manager.features ().expand_composites (sproperties)
    
        # Find the target
        target = project.find (id)
        
        return (target, property_set.create (sproperties))

    def generate (self, ps):
        """ Determines final build properties, generates sources,
            and calls 'construct'. This method should not be
            overridden.
        """
        if self.manager ().logger ().on ():
            self.manager ().logger ().log (__name__, "Building target '%s'" % self.name_)
            self.manager ().logger ().log (__name__, "Build request: '%s'" % str (ps.raw ()))
            self.manager ().logger ().increase_indent ()

        if not self.generated_.has_key (str (ps)):
            rproperties = self.common_properties (ps, self.requirements_)
            
            if self.manager ().logger ().on ():
                self.manager ().logger ().log (__name__, "Common properties are '%s'" % str (rproperties.raw ()))
            
            # TODO: check use of "@error".
            if not "@error" in str (rproperties):
                result = GenerateResult ()

                properties = rproperties.non_dependency ()
                
                (p, u) = self.generate_dependencies (rproperties.dependency (), rproperties)
                properties += p
                usage_requirements = u

                (source_targets, u) = self.generate_dependencies (self.sources_, rproperties)
                usage_requirements += u

                if self.manager_.logger ().on ():
                      self.manager_.logger ().log (__name__, "Usage requirements for '%s' are '%s'" % (self.name_, usage_requirements))

                rproperties = property_set.create (properties + usage_requirements)
                usage_requirements = property_set.create (usage_requirements)
                
                extra = rproperties.get ('<source>')
                source_targets += replace_grist (extra, '')
                source_targets = replace_references_by_objects (self.manager (), source_targets)
                
                # We might get duplicate sources, for example if
                # we link to two library which have the same <library> in
                # usage requirements.
                source_targets = unique (source_targets)

                result = self.construct (self.name_, source_targets, rproperties)

                gur = result [0]
                result = result [1]

                s = self.create_subvariant (result, ps, source_targets, rproperties, usage_requirements)

                ur = self.compute_usage_requirements (s)
                ur = ur.add (gur)
                s.set_usage_requirements (ur)
                self.generated_ [str (ps)] = GenerateResult (ur, result)
            else:
                self.generated_ [str (ps)] = GenerateResult (rproperties, [])
        else:
            if self.manager ().logger ().on ():
                self.manager ().logger ().log (__name__, "Already built")

        self.manager ().logger ().decrease_indent ()

        return self.generated_ [str (ps)]


    def common_properties (self, build_request, requirements):
        """ Given build request and requirements, return properties
            common to dependency build request and target build
            properties.
        """
        # For optimization, we add free requirements directly,
        # without using complex algorithsm.
        # This gives the complex algorithm better chance of caching results.
        free = requirements.free ()        
        non_free = property_set.create (requirements.base () + requirements.incidental ())
        
        key = str (build_request) + '-' + str (non_free)
        if not self.request_cache.has_key (key):
            self.request_cache [key] = self.__common_properties2 (build_request, non_free)       

        return self.request_cache [key].add_raw (free)
    
    def __common_properties2 (self, build_request, requirements):

        # This guarantees that default properties are present
        # in result, unless they are overrided by some requirement.
        # FIXME: There is possibility that we've added <foo>bar, which is composite
        # and expands to <foo2>bar2, but default value of <foo2> is not bar2,
        # in which case it's not clear what to do.
        # 
        build_request = build_request.add_defaults ()
        
        # Featured added by 'add_defaults' can be composite and expand
        # to features without default values -- so they are not added yet.
        # It could be clearer/faster to expand only newly added properties
        # but that's not critical.
        build_request = build_request.expand ()
        
        # Apply non-conditional requirements. 
        # There's a slight bug here: it's possible that conditional
        # requirement change a value set by non-conditional requirements. This
        # should be error, but we don't detect it yet.
        raw = build_request.raw ()
        raw = property.refine (raw, feature.expand (requirements.non_conditional ()))
        
        # We've collected properties that surely must be present in common
        # properties. We now try to figure out what other properties
        # should be added in order to satisfy rules (4)-(6) from the docs.
        conditionals = requirements.conditional ()

        prev = []        
        current = raw

        for i in range (0, len (conditionals) + 1):
            # Evaluate conditionals in context of current properties
            e = property.evaluate_conditionals_in_context (conditionals, current)
            if e == prev:
                # If we got the same result, we've found final properties.
                return property_set.create (current)

            else:
                # Oops, results of evaluation of conditionals has changes
                # Also 'current' contains leftover from previous evaluation.
                # Recompute 'current' using initial properties and conditional
                # requirements.
                prev = e
                current = property.refine (raw, feature.expand (e))
            
        raise BaseException ("Can't evaluate conditional properties '%s'" % str (conditionals))

    def match (self, property_set):
        """ Returns the alternative condition for this alternative, if
            the condition is satisfied by 'property_set'.
        """
        # The condition is composed of all base non-conditional properties.
        # It's not clear if we should expand 'self.requirements_' or not.
        # For one thing, it would be nice to be able to put
        #    <toolset>msvc-6.0 
        # in requirements.
        # On the other hand, if we have <variant>release in condition it 
        # does not make sense to require <optimization>full to be in
        # build request just to select this variant.
        bcondition = self.requirements_.base ()
        ccondition = self.requirements_.conditional ()
        condition = set.difference (bcondition, ccondition)
        if set.contains (condition, property_set.raw ()):
            return condition

        else:
            return None
    
    def generate_dependencies (self, dependencies, property_set):
        """ Takes a target reference, which might be either target id
            or a dependency property, and generates that target using
            'property_set' as build request.

            Returns a tuple (result, usage_requirements).
        """
        result_var = []
        usage_requirements = []
        for dependency in dependencies:
            grist = get_grist (dependency)
            id = replace_grist (dependency, '')
        
            result = self.generate_from_reference (id, self.project_, property_set)
        
            # TODO: this is a problem: the grist must be kept and the value
            #       is the object itself. This won't work in python.
            targets = [ self.manager_.register_object (x) for x in result.targets () ]
            
            result_var += replace_grist (targets, grist)
            usage_requirements += result.usage_requirements ().raw ()

        return (result_var, usage_requirements)
    
    def generate_from_reference (self, target_reference, project, property_set):
        """ Attempts to generate the target given by target reference, which
            can refer both to a main target or to a file.
            Returns a list consisting of
            - usage requirements
            - generated virtual targets, if any
            target_reference:  Target reference
            project:           Project where the reference is made
            property_set:      Properties of the main target that makes the reference
        """
        target, sproperties = self.resolve_reference (target_reference, project)
        
        # Take properties which should be propagated and refine them
        # with source-specific requirements.
        propagated = property_set.propagated ()
        rproperties = propagated.refine (sproperties)
        
        # TODO: check usage of @error
        if "@error" in str (rproperties):
            raise BaseException ("When building '%s' with properties '%s'\nInvalid properties specified: '%s'" % (self.full_name (), property_set.raw (), rproperties [1:]))
    
        return target.generate (rproperties)
    
    def compute_usage_requirements (self, subvariant):
        """ Given the set of generated targets, and refined build 
            properties, determines and sets appripriate usage requirements
            on those targets.
        """
        rproperties = subvariant.build_properties ()
        xusage_requirements = self.usage_requirements_.evaluate_conditionals (rproperties)
        
        # We generate all dependency properties and add them,
        # as well as their usage requirements, to result.
        (r1, r2) = self.generate_dependencies (xusage_requirements.dependency (), rproperties)
        extra = r1 + r2
                
        result = property_set.create (xusage_requirements.non_dependency () + extra)
        
        result = result.add (subvariant.sources_usage_requirements ())
        
        return result

    def create_subvariant (self, targets, build_request, sources, rproperties, usage_requirements):
        """ Creates a new subvariant-dg instances for 'targets'.
        """
        for e in targets:
            e.root (True)
        
        # Process all vtargets that will be created if this main target
        # is created.
        all_targets = []
        for e in targets:
            all_targets += virtual_target.traverse (e)

        s = Subvariant (self, build_request, sources, rproperties, usage_requirements, all_targets)

        for v in all_targets:
            if not v.creating_subvariant ():
                v.creating_subvariant (s)

        return s
        
    def construct (self, name, source_targets, properties):
        """ Constructs the virtual targets for this abstract targets and
            the dependecy graph. Returns a tuple consisting of the properties and the list of virtual targets.
            Should be overrided in derived classes.
        """
        raise BaseException ("method should be defined in derived classes")




class MainTarget (AbstractTarget):
    """ A named top-level target in Jamfile.
    """
    def __init__ (self, name, project):
        AbstractTarget.__init__ (self, name, project)    
        self.alternatives_ = []
        self.default_build_ = property_set.empty ()
        
    def add_alternative (self, target):
        """ Add a new alternative for this target.
        """
        d = target.default_build ()
        
        if self.alternatives_ and self.default_build_ != d:
            raise BaseException ("Default build must be identical in all alternatives\n"
              "main target is '%s'\n"
              "with '%s'\n"
              "differing from previous default build: '%s'" % (full_name (), d.raw (), self.default_build_.raw ()))

        else:
            self.default_build_ = d

        self.alternatives_.append (target)

    def __select_alternatives (self, property_set):
        """ Returns the best viable alternative for this property_set
            See the documentation for selection rules.
            # TODO: shouldn't this be 'alternative' (singular)?
        """
        # When selecting alternatives we have to consider defaults,
        # for example:
        #    lib l : l.cpp : <variant>debug ;
        #    lib l : l_opt.cpp : <variant>release ;
        # won't work unless we add default value <variant>debug.
        #
        # TODO: in BBv2 this was as shown below. Note that p is not defined.
        # property-set = [ $(p).add-defaults ] ;        
        property_set = property_set.add_defaults ()
        
        # The algorithm: we keep the current best viable alternative.
        # When we've got new best viable alternative, we compare it
        # with the current one. 
        best = None
        best_properties = None
                        
        if len (self.alternatives_) == 0:
            return None

        if len (self.alternatives_) == 1:
            return self.alternatives_ [0]

        for v in self.alternatives_:
            properties = v.match (property_set)
                       
            if properties:
                if not best:
                    best = v
                    best_properties = properties

                else:
                    if set.equal (properties, best_properties):
                        return None

                    elif set.contains (properties, best_properties):
                        # Do nothing, this alternative is worse
                        pass

                    elif set.contains (best_properties, properties):
                        best = v
                        best_properties = properties

                    else:
                        return None

        return best

    def apply_default_build (self, property_set):
        # 1. First, see what properties from default_build
        # are already present in property_set. 
        
        raw = property_set.raw ()
        specified_features = get_grist (raw)
        
        defaults_to_apply = []
        for d in self.default_build_.raw ():
            if not get_grist (d) in specified_features:
                defaults_to_apply.append (d)
        
        # 2. If there's any defaults to be applied, form the new
        # build request. Pass it throw 'expand-no-defaults', since
        # default_build might contain "release debug", which will
        # result in two property_sets.
        result = []
        if defaults_to_apply:

            # We have to compress subproperties here to prevent
            # property lists like:
            #
            #    <toolset>msvc <toolset-msvc:version>7.1 <threading>multi
            #
            # from being expanded into:
            #
            #    <toolset-msvc:version>7.1/<threading>multi
            #    <toolset>msvc/<toolset-msvc:version>7.1/<threading>multi
            #
            # due to cross-product property combination.  That may
            # be an indication that
            # build_request.expand-no-defaults is the wrong rule
            # to use here.
            compressed = feature.compress-subproperties (raw)

            properties = build_request.expand_no_defaults (compressed, defaults_to_apply)
              
            if properties:
                for p in properties:
                    result.append (property_set.create (feature.expand (feature.split (p))))

            else:
                result .append (property_set.empty ())
            
        else:
            result.append (property_set)

        return result

    def generate (self, ps):
        """ Select an alternative for this main target, by finding all alternatives
            which requirements are satisfied by 'properties' and picking the one with
            longest requirements set.
            Returns the result of calling 'generate' on that alternative.
        """
        self.manager_.targets ().start_building (self)

        # We want composite properties in build request act as if
        # all the properties it expands too are explicitly specified.
        ps = ps.expand ()
        
        all_property_sets = self.apply_default_build (ps)

        result = GenerateResult ()
        
        for p in all_property_sets:
            result.extend (self.__generate_really (p))

        self.manager_.targets ().end_building (self)

        return result
        
    def __generate_really (self, prop_set):
        """ Generates the main target with the given property set
            and returns a list which first element is property_set object
            containing usage_requirements of generated target and with
            generated virtual target in other elements. It's possible
            that no targets are generated.
        """
        best_alternative = self.__select_alternatives (prop_set)

        if not best_alternative:
            raise NoBestMatchingAlternative (
                "Failed to build '%s'\n"
                "with properties '%s'\n"
                "because no best-matching alternative could be found."
                  % (full_name, prop_set.raw ()))
                  
        result = best_alternative.generate (prop_set)
                    
        # Now return virtual targets for the only alternative
        return result
    
#       rule rename ( new_name )
#       {
#           AbstractTarget.rename $(new_name) ;
#           for local a in $(self.alternatives_)
#           {
#               $(a).rename $(new_name) ;
#           }
#           
#       }
#       
#   }

class FileReference (AbstractTarget):
    """ Abstract target which refers to a source file.
        This is artificial creature; it's usefull so that sources to 
        a target can be represented as list of abstract target instances.
    """
    def __init__ (self, manager, file, project):
        AbstractTarget.__init__ (self, file, project)
    
    def generate (self, properties):
         return GenerateResult (None, [ self.manager_.virtual_targets ().from_file (self.name_, self.project_) ])

    def exists (self):
        """ Returns true if the referred file really exists.
        """
        location = path.native (self.location ())
        location = self.location ()
        return os.path.isfile (location) or os.path.islink (location)

    def location (self):
        source_location = self.project_.get ('source-location')
        return path.root (self.name (), source_location)



class TypedTarget (BasicTarget):
    import generators
    
    def __init__ (self, name, project, type, sources, requirements, default_build, usage_requirements):
        BasicTarget.__init__ (self, name, project, sources, requirements, default_build, usage_requirements)
        self.type_ = type
    
    def type (self):
        return self.type_
            
    def construct (self, name, source_targets, prop_set):
        r = generators.construct (self.project_, name, self.type_, False, 
            property_set.create (prop_set.raw () + ['<main-target-type>' + self.type_]),
            source_targets)

        if not r:
            raise BaseException ("Unable to construct '%s'" % self.full_name ())
        
        return r
