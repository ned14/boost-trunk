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

### import "class" : is-a new ;
### import container ;
### import utility : str equal ;
### import set sequence ;
### import assert ;
### import virtual-target ;
### import property_set ;
### 
### if "--debug-generators" in [ modules.peek : ARGV ] 
### {    
###     .debug = true ;
### }
### 
### # Outputs a debug message if generators debugging is on.
### # Each element of 'message' is checked to see if it's class instance.
### # If so, instead of the value, the result of 'str' call is output.
### local rule generators.dout ( message * )
### {
###     if $(.debug)
###     {                
###         ECHO [ sequence.transform utility.str : $(message) ] ;
###     }    
### }
### 
### 
### local rule indent ( )
### {
###     return $(.indent:J="") ;
### }
### 
### local rule increase-indent ( )
### {
###     .indent += "    " ;
### }
### 
### local rule decrease-indent ( )
### {
###     .indent = $(.indent[2-]) ;
### }
### 
### # Takes a vector of 'virtual-target' instances and makes a normalized
### # representation, which is the same for given set of targets,
### # regardless of their order.
### rule normalize-target-list ( targets )
### {
###     local v = [ $(targets).get ] ;
###     $(targets).set $(v[1]) [ sequence.insertion-sort $(v[2-]) : utility.less ] ;
### }
### 
### # Creates a generator
### class generator 
### {
###     import generators ;
###     import assert ;
###     import generators : indent increase-indent decrease-indent generators.dout ;
###     import generators ;
###     import set ;
###     import utility : equal ;
###     import feature ;
###     import errors : error ;
###     import sequence ;
###     import type ;
###     import virtual-target ;
###     import "class" : new ;
###     import property ;
###    
###     EXPORT class@generator : indent increase-indent decrease-indent generators.dout ;
###     
###     rule __init__ (  
###       id # identifies the generator - should be name of the rule which
###          # sets up build actions
###       composing ? # whether generator processes each source target in
###                   # turn, converting it to required types.
###                   # Ordinary generators pass all sources together to
###                   # recusrive generators.construct-types call.
###     
###     : source-types *  # types that this generator can handle
###     
###     : target_types-and-names +   
###       # types the generator will create and, optionally, names for
###       # created targets. Each element should have the form
###       #    type["(" name-pattern ")"]
###       # for example, obj(%_x). Name of generated target will be found
###       # by replacing % with the name of source, provided explicit name
###       # was not specified.
###     
###     : requirements *
###                 )
###     {                    
###         self.id = $(id) ;
###         self.composing = $(composing) ;
###         self.source-types = $(source-types) ;
###         self.target_types-and-names = $(target_types-and-names) ;
###         self.requirements = $(requirements) ;
###         
###         for local e in $(target_types-and-names)
###         {        
###             # Create three parallel lists: one with the list of target types,
###             # and two other with prefixes and postfixes to be added to target 
###             # name. We use parallel lists for prefix and postfix (as opposed
###             # to mapping), because given target type might occur several times,
###             # for example "H H(%_symbols)".
###             local m = [ MATCH ([^\\(]*)(\\((.*)%(.*)\\))? : $(e) ] ;
###             self.target_types += $(m[1]) ;
###             self.name-prefix += $(m[3]:E="") ;
###             self.name-postfix += $(m[4]:E="") ;
###         }
###                                     
###         # Note that 'transform' here, is the same as 'for_each'.
###         sequence.transform type.validate : $(self.source-types) ;
###         if $(self.target_types) != *
###         {        
###             sequence.transform type.validate : $(self.target_types) ;
###         }
###     }
###                             
###     ############## End of constructor #################
###     
###     rule id ( )
###     {
###         return $(self.id) ;
###     }
### 
###     # Returns the list of target type the generator accepts.
###     rule source-types ( )
###     {
###         return $(self.source-types) ;
###     }
### 
###     # Returns the list of target types that this generator produces.
###     # It is assumed to be always the same -- i.e. it cannot change depending
###     # list of sources.    
###     rule target_types ( )
###     {
###         return $(self.target_types) ;
###     }
### 
###     # Returns the required properties for this generator. Properties
###     # in returned set must be present in build properties if this 
###     # generator is to be used. If result has grist-only element,
###     # that build properties must include some value of that feature.
###     # XXX: remove this method?
###     rule requirements ( )
###     {
###         return $(self.requirements) ;
###     }
###     
###     # Returns a true value if the generator can be run with the specified 
###     # properties.
###     rule match-rank ( property_set-to-match )
###     {
###         # See if generator's requirements are satisfied by
###         # 'properties'.  Treat a feature name in requirements
###         # (i.e. grist-only element), as matching any value of the
###         # feature.
###         local all-requirements = [ requirements ] ;
###         
###         local property-requirements feature-requirements ;
###         for local r in $(all-requirements)
###         {
###             if $(r:G=)
###             {
###                 property-requirements += $(r) ;
###             }
###             else
###             {
###                 feature-requirements += $(r) ;
###             }                      
###         }
### 
###         local properties-to-match = [ $(property_set-to-match).raw ] ;
###         if $(property-requirements) in $(properties-to-match) 
###            && $(feature-requirements) in $(properties-to-match:G)
###         {
###             return true ;
###         }
###         else
###         {
###             return ;
###         }
###     }
###         
###     # Returns another generator which differers from $(self) in
###     # - id
###     # - value to <toolset> feature in properties
###     rule clone ( new-id : new-toolset-properties + )
###     {
###         return [ new $(__class__) $(new-id) $(self.composing)
###                  : $(self.source-types)
###                  : $(self.target_types-and-names) 
###                  # Note: this does not remove any subfeatures of <toolset>
###                  # which might cause problems
###                  : [ property.change $(self.requirements) : <toolset> ]
###                    $(new-toolset-properties)
###                ] ;
###     }
###     
###     # Tries to invoke this generator on the given sources. Returns a
###     # list of generated targets (instances of 'virtual-target').
###     rule run ( project  # Project for which the targets are generated
###                name ?   # Determines the name of 'name' attribute for 
###                         # all generated targets. See 'generated-targets' method.
###                : property_set # Desired properties for generated targets.
###                : sources +  # Source targets.
###                : multiple ? # Allows the rule to run generator several times and return
###                           # multiple targets of the same type. When this argument is not
###                           # given, 'run' will return the list of targets, which is equal
###                           # in size to the list of target types, and where type of
###                           # each target is the same as the corresponding element of
###                           # target type list. Non-empty value allows to return several
###                           # such target lists, joined together.
###              )
###     {
###         # multiple = true ; # The tests seem to tolerate this; will
###                           # remove the parameter altogether in the
###                           # next revision to see what I learn -- DWA 2003/5/6
###         
###         generators.dout [ indent ] "  generator" $(self.id) ;
###         generators.dout [ indent ] "  multiple:" $(mutliple) ;
###         generators.dout [ indent ] "  composing:" $(self.composing) ;        
###         
###         if ! $(self.composing) && $(sources[2]) && $(self.source-types[2])
###         {
###             errors.error "Unsupported source/source-type combination" ;
###         }
### 
###         if $(self.source-types[2])
###         {
###             multiple = ;
###         }
###                 
###         # We don't run composing generators if no name is specified. The reason
###         # is that composing generator combines several targets, which can have
###         # different names, and it cannot decide which name to give for produced
###         # target. Therefore, the name must be passed.
###         #
###         # This in effect, means that composing generators are runnable only
###         # at top-level of transofrmation graph, or if name is passed explicitly.
###         # Thus, we dissallow composing generators in the middle. For example, the
###         # transofrmation CPP -> OBJ -> STATIC_LIB -> RSP -> EXE won't be allowed 
###         # (the OBJ -> STATIC_LIB generator is composing)
###         if ! $(self.composing) || $(name)
###         {            
###             run-really $(project) $(name) : $(property_set) : $(sources) : $(multiple) ;
###         }        
###     }
###     
###     
###     rule run-really ( project name ? : property_set : sources + : multiple ? )
###     {
###         # Targets that this generator will consume directly.
###         local consumed = ;
###         # Targets that can't be consumed and will be returned as-is.
###         local bypassed = ;
###         
###         if $(self.composing)
###         {
###             convert-multiple-sources-to-consumable-types $(project)
###               : $(property_set) : $(sources) : consumed bypassed ;            
###         }
###         else
###         {               
###             convert-to-consumable-types $(project) $(name) : 
###               $(property_set) : $(sources) : $(multiple)
###                 :
###                 : consumed bypassed ;
###         }
###                 
###         local result ;
###         if $(consumed)  
###         {            
###             result = [ construct-result $(consumed) : $(project) $(name) 
###                      : $(property_set) ] ;
###             result += $(bypassed) ;
###         }
###                             
###                 
###         if $(result)
###         {
###            generators.dout [ indent ] "  SUCCESS: " $(result) ;
###         }
###         else
###         {
###             generators.dout [ indent ] "  FAILURE" ;
###         }
###         generators.dout ;
###         return $(result) ;        
###     }
### 
###     # Constructs the dependency graph that will be returned by this 
###     # generator
###     rule construct-result ( 
###         consumed + # Already prepared list of consumable targets
###                    # If generator requires several source files will contain 
###                    # exactly len $(self.source-types) targets with matching types
###                    # Otherwise, might contain several targets with the type of 
###                    # $(self.source-types[1])                               
###         : project name ? 
###         : property_set  # Properties to be used for all actions create here
###     )
###     {
###         local result ;
###         # If this is 1->1 transformation, apply it to all consumed targets in order.
###         if ! $(self.source-types[2]) && ! $(self.composing)
###         {
###             generators.dout [ indent ] "alt1" ;
###             for local r in $(consumed)
###             {                
###                 result += [ generated-targets $(r) : $(property_set) : $(project) $(name) ] ; #(targets) ;
###             }
###         }
###         else
###         {
###             generators.dout [ indent ] "alt2 : consumed is" $(consumed) ;
###             if $(consumed) 
###             {
###                 result += [ generated-targets $(consumed) : $(property_set) 
###                             : $(project) $(name) ] ;
###             }                        
###         }
###         return $(result) ;
###     }   
###     
###     # Constructs targets that are created after consuming 'sources'.
###     # The result will be the list of virtual-target, which the same length
###     # as 'target_types' attribute and with corresponding types.
###     # 
###     # When 'name' is empty, all source targets must have the same value of 
###     # the 'name' attribute, which will be used instead of the 'name' argument.
###     #
###     # The value of 'name' attribute for each generated target will be equal to
###     # the 'name' parameter if there's no name pattern for this type. Otherwise,
###     # the '%' symbol in the name pattern will be replaced with the 'name' parameter 
###     # to obtain the 'name' attribute.
###     #
###     # For example, if targets types are T1 and T2(with name pattern "%_x"), suffixes
###     # for T1 and T2 are .t1 and t2, and source if foo.z, then created files would
###     # be "foo.t1" and "foo_x.t2". The 'name' attribute actually determined the
###     # basename of a file.
###     #
###     # Note that this pattern mechanism has nothing to do with implicit patterns
###     # in make. It's a way to produce target which name is different for name of 
###     # source.
###     rule generated-targets ( sources + : property_set : project name ? )
###     {
###         if ! $(name)
###         {
###             name = [ utility.basename [ $(sources[1]).name ] ] ;
### 
###             for local s in $(sources[2])
###             {
###                 local n2 = [ utility.basename [ $(s).name ] ] ;
###                 if $(n2) != $(name)
###                 {
###                     error "$(self.id): source targets have different names: cannot determine target name" ;
###                 }
###             }
### 
###             # Names of sources might include directory. We should strip it.
###             name = $(name:D=) ;
###         }
###         
###         # Assign an action for each target
###         local action = [ action-class ] ;
###         local a = [ class.new $(action) $(sources) : $(self.id) : 
###                     $(property_set) ] ;
###                 
###         # Create generated target for each target type.
###         local targets ;
###         local pre = $(self.name-prefix) ;
###         local post = $(self.name-postfix) ;
###         for local t in $(self.target_types)                 
###         {      
###             local generated-name = $(pre[1])$(name)$(post[1]) ;
###             pre = $(pre[2-]) ;
###             post = $(post[2-]) ;
###             
###             targets += [ class.new file-target $(generated-name) 
###               : $(t) : $(project) : $(a) ] ;
###         }                 
###         for local t in $(targets)
###         {
###             $(t).set-intermediate true ;
###         }       
###         
###         return [ sequence.transform virtual-target.register : $(targets) ] ;
###     }    
###     
###     # Attempts to convert 'source' to the types that this generator can
###     # handle. The intention is to produce the set of targets can should be
###     # used when generator is run.
###     rule convert-to-consumable-types ( project name ? : 
###         property_set : sources + : multiple ? 
###         : only-one ? # convert 'source' to only one of source types
###                      # if there's more that one possibility, report an
###                      # error 
###         : consumed-var # name of variable which recieves all targets which 
###                        # can be consumed. 
###           bypassed-var # name variable which recieves all targets which 
###                        # cannot be consumed  
###     )
###     {        
###         # We're likely to be passed 'consumed' and 'bypassed'
###         # var names. Use "_" to avoid name conflicts.
###         local _consumed ;
###         local _bypassed ;
###         local missing-types ; 
### 
###         if $(sources[2])
###         {
###             # Don't know how to handle several sources yet. Just try 
###             # to pass the request to other generator
###             missing-types = $(self.source-types) ;
###         }
###         else
###         {            
###             consume-directly $(sources) : _consumed : missing-types ;
###         }
###         
###         # No need to search for transformation if
###         # some source type has consumed source and
###         # no more source types are needed.
###         if $(only-one) && $(_consumed) 
###         {
###             missing-types = ;
###         }
###             
###         #TODO: we should check that only one source type
###         #if create of 'only-one' is true.
###         # TODO: consider if consuned/bypassed separation should
###         # be done by 'construct-types'.
###                     
###         if $(missing-types)
###         {            
###             local transformed = [ generators.construct-types $(project) $(name)
###               : $(missing-types) : $(multiple) : $(property_set) : $(sources) ] ;
###                                 
###             # Add targets of right type to 'consumed'. Add others to
###             # 'bypassed'. The 'generators.construct' rule has done
###             # its best to convert everything to the required type.
###             # There's no need to rerun it on targets of different types.
###                 
###             # NOTE: ignoring usage requirements
###             for local t in $(transformed[2-])
###             {
###                 if [ $(t).type ] in $(missing-types)
###                 {
###                     _consumed += $(t) ;
###                 }
###                 else
###                 {
###                     _bypassed += $(t) ;
###                 }
###             }               
###         }   
###         
###         _consumed = [ sequence.unique $(_consumed) ] ;        
###         _bypassed = [ sequence.unique $(_bypassed) ] ;
###         
###         # remove elements of '_bypassed' that are in '_consumed'
###         
###         # Suppose the target type of current generator, X is produced from 
###         # X_1 and X_2, which are produced from Y by one generator.
###         # When creating X_1 from Y, X_2 will be added to 'bypassed'
###         # Likewise, when creating X_2 from Y, X_1 will be added to 'bypassed'
###         # But they are also in 'consumed'. We have to remove them from
###         # bypassed, so that generators up the call stack don't try to convert
###         # them. 
###             
###         # In this particular case, X_1 instance in 'consumed' and X_1 instance
###         # in 'bypassed' will be the same: because they have the same source and
###         # action name, and 'virtual-target.register' won't allow two different
###         # instances. Therefore, it's OK to use 'set.difference'.
###         
###         _bypassed = [ set.difference $(_bypassed) : $(_consumed) ] ;
###         
###                 
###         $(consumed-var) += $(_consumed) ;
###         $(bypassed-var) += $(_bypassed) ;
###     }
###     
###     # Converts several files to consumable types.
###     rule convert-multiple-sources-to-consumable-types
###       ( project : property_set : sources * : consumed-var bypassed-var : multiple ? )
###     {
###         multiple ?= * ;
###         # We process each source one-by-one, trying to convert it to
###         # a usable type.
###         local failed ;
###         while $(sources) && ! $(failed)
###         {
###             local _c ;
###             local _b ;
###             # TODO: need to check for failure on each source.
###             convert-to-consumable-types $(project) : $(property_set)
###               : $(sources[1]) : $(multiple) : true : _c _b ;
###             if ! $(_c)
###             {
###                 generators.dout [ indent ] " failed to convert " $(sources[1]) ;
###                 # failed = true ;
###             }
###             $(consumed-var) += $(_c) ;            
###             $(bypassed-var) += $(_b) ;
###             sources = $(sources[2-]) ;
###         }           
###         if $(failed)
###         {
###             $(consumed-var) = ;
###             $(bypassed-var) = ;
###         }        
###     }
###         
###     rule consume-directly ( source : consumed-var : missing-types-var )
###     {
###         local real-source-type = [ $(source).type ] ;
### 
###         for local st in $(self.source-types)
###         {
###             # The 'source' if of right type already)
###             if $(real-source-type) = $(st) || 
###               [ type.is-derived $(real-source-type) $(st) ]
###             {
###                 $(consumed-var) += $(source) ;
###             }
###             else
###             {
###                $(missing-types-var) += $(st) ;
###             }
###         }        
###     }
###     
###     
###     # Returns the class to be used to actions. Default implementation 
###     # returns "action".
###     rule action-class ( )
###     {
###         return "action" ;
###     }        
### }
### 
### import errors : error ;
### 
### .generators = ;
### 
### # Registers new generator instance 'g'.
### rule register ( g )
### {
###     .generators += $(g) ;
###                    
###     for local t in [ $(g).target_types ] 
###     {            
###         .generators.$(t) += $(g) ;
###     }    
###     
###     # Update the set of generators for toolset
###     
###     # TODO: should we check that generator with this id
###     # is not already registered. For example, the fop.jam
###     # module intentionally declared two generators with the
###     # same id, so such check will break it.
###     local id = [ $(g).id ] ;
###         
###     # Some generators have multiple periods in their name, so the
###     # normal $(id:S=) won't generate the right toolset name.
###     # e.g. if id = gcc.compile.c++, then
###     # .generators-for-toolset.$(id:S=) will append to
###     # .generators-for-toolset.gcc.compile, which is a separate
###     # value from .generators-for-toolset.gcc. Correcting this
###     # makes generator inheritance work properly.
###     # See also inherit-generators in module toolset
###     local base = $(id) ;
###     while $(base:S)
###     {
###         base = $(base:B) ;
###     }
###     .generators-for-toolset.$(base) += $(g) ;
### }
###     
### # Creates new instance of the 'generator' class and registers it.
### # Retursn the creates instance.
### # Rationale: the instance is returned so that it's possible to first register
### # a generator and then call 'run' method on that generator, bypassing all
### # generator selection.
### rule register-standard ( id : source-types + : target_types + : requirements * )
### 
### {
###     local g = [ new generator $(id) : $(source-types) : $(target_types)
###       : $(requirements) ] ;
###     register $(g) ;   
###     return $(g) ;
### }
### 
### # Creates new instance of the 'composing-generator' class and
### # registers it.
### rule register-composing ( id : source-types + : target_types + : requirements * )
### {
###     local g = [ new generator $(id) true : $(source-types) 
###                 : $(target_types) : $(requirements) ] ;
###     register $(g) ;
###     return $(g) ;
### }
### 
### # Returns all generators which belong to 'toolset', i.e. which
### # ids are $(toolset).<something>
### rule generators-for-toolset ( toolset )
### {
###     return $(.generators-for-toolset.$(toolset)) ;
### }
### 
### rule override ( overrider-id : overridee-id )
### {
###     .override.$(overrider-id) += $(overridee-id) ;    
### }
### 
### 
### 
###     
### # Set if results of the current generators search are going to be cached
### # This means no futher attempts to cache generators search should be
### # made.
### .caching = ;
### 
### # For all t in 'targets':
### # if [ $(t).type ] in $(target_types), add 't' to result
### # if [ $(t).type ] in base type for any of 'target_types', add 't' to result
### # otherwise, add 't' to extra.
### rule base-to-derived-type-conversion ( targets * : target_types +
###     : result-var extra-var )
### {
###     for local t in $(targets) 
###     {
###         if [ $(t).type ] in $(target_types)
###         {
###             $(result-var) += $(t) ;
###         }
###         else 
###         {
###             # We might have asked for a type 'D', but found only generator for
###             # a type 'B', where 'D' is derived from 'B'. In this case, the 
###             # generation succeeds, but we should change type of the generated target.
###             
###             local at = [ $(t).type ] ;
###             local found ;
###             for local tt in $(target_types)
###             {
###                 if ! $(found) && [ type.is-derived $(tt) $(at) ] 
###                 {
###                     $(t).set-type $(tt) ;
###                     $(result-var) += $(t) ;
###                     found = 1 ;
###                 }                
###             }            
###             if ! $(found)
###             {
###                 $(extra-var) += $(t) ;                
###             }            
###         }        
###     }    
### }
### 
### # Returns a list of source type which can possibly be converted
### # to 'target_type' by some chain of generator invocation.
### #
### # More formally, takes all generators for 'target_type' and
### # returns union of source types for those generators and result
### # of calling itself recusrively on source types.
### local rule viable-source-types-real ( target_type )
### {
###     local generators ;
###         
###     local t = [ type.all-bases $(target_type) ] ;
###     
###     local result ;
###     # 't' is the list of types which are not yet processed    
###     while $(t)
###     {
###         # Find all generators for current type. 
###         # Unlike 'find-viable-generators' we don't care about property_set.
###         local generators = $(.generators.$(t[1])) ;
###         t = $(t[2-]) ;
###         
###         for local g in $(generators)
###         {
###             for local source-type in [ $(g).source-types ] 
###             {
###                 if ! $(source-type) in $(result) 
###                 {
###                     # If generator accepts 'source-type' it
###                     # will happily accept any type derived from it
###                     local all = [ type.all-derived $(source-type) ] ;
###                     for local n in $(all)
###                     {
###                         if ! $(n) in $(result)
###                         {                                          
###                             t += $(n) ;
###                             result += $(n) ;
###                         }    
###                     }                    
###                 }                
###             }            
###         }        
###     }          
###         
###     result = [ sequence.unique $(result) ] ;
###     
###     return $(result) ;                
### }
### 
### # Helper rule, caches the result of 'viable-source-types-real'.
### rule viable-source-types ( target_type )
### {
###     local key = .vst.$(target_type) ;
###     if ! $($(key))
###     {
###         local v = [ viable-source-types-real $(target_type) ] ;
###         if ! $(v)
###         {
###             v = none ;
###         }
###         $(key) = $(v) ;
###     }
###     
###     if $($(key)) != none
###     {
###         return $($(key)) ;
###     }        
### }
### 
### # Returns the list of source types, which, when passed to 'run'
### # method of 'generator', has some change of being eventually used
### # (probably after conversion by other generators)
### rule viable-source-types-for-generator-real ( generator ) 
### {        
###     local source-types = [ $(generator).source-types ] ;
###     if ! $(source-types)
###     {
###         # If generator does not specify any source types,
###         # it might be special generator like builtin.lib-generator
###         # which just relays to other generators. Return '*' to
###         # indicate that any source type is possibly OK, since we don't
###         # know for sure.
###         return * ;
###     }
###     else
###     {            
###         local result ;
###         for local s in $(source-types)
###         {
###             result += [ type.all-derived $(s) ] 
###               [ generators.viable-source-types $(s) ] ;
###         }
###         result = [ sequence.unique $(result) ] ;
###         return $(result) ;
###     }        
### }    
### 
### # Helper rule, caches the result of 'viable-source-types-for-genrator'.
### local rule viable-source-types-for-generator ( generator )
### {
###     local key = .vstg.$(generator) ;
###     if ! $($(key))
###     {
###         local v = [ viable-source-types-for-generator-real $(generator) ] ;
###         if ! $(v)
###         {
###             v = none ;
###         }
###         $(key) = $(v) ;        
###     }
###     
###     if $($(key)) != none
###     {
###         return $($(key)) ;
###     }        
### }
### 
### 
### 
### # Returns usage requirements + list of created targets
### local rule try-one-generator-really ( project name ? : generator multiple ? : 
###     target_type : property_set : sources * )
### {
###     local targets =
###       [ $(generator).run $(project) $(name)
###                        : $(property_set)
###                        : $(sources)
###                        : $(multiple)
###       ] ;
###         
### 
###     # Generated targets that are of required types
###     local result ;
###     # Generated target of other types.
###     local extra ;
###     
###     local usage-requirements ;
###     if $(targets) && [ class.is-a $(targets[1]) : property_set ]
###     {
###         usage-requirements = $(targets[1]) ;
###         targets = $(targets[2-]) ;
###     }
###     else
###     {
###         usage-requirements = [ property_set.empty ] ;
###     }
###     
###     base-to-derived-type-conversion $(targets) : $(target_type) 
###         : result extra ;
###             
###     # Now try to convert extra targets 
###     # 'construct' will to its best to return only requested
###     # target types, so if we receive any extra from that call,
###     # we don't try to do anything about them.
###     local extra2 ;
###     if $(multiple) 
###     {
###         for local e in $(extra) 
###         {
###             local try2 = [ construct-types $(project) $(name) 
###                                          : $(target_type)
###                                          :
###                                          : $(property_set)
###                                          : $(e) ] ;
###             usage-requirements = [ $(usage-requirements).add $(try2[1]) ] ;
###             result += $(try2[2-]) ;
###         }    
###     }
###     else
###     {
###         extra2 = $(extra) ;
###     }
###     generators.dout [ indent ] "  generator" [ $(generator).id ] " spawned " ;
###     generators.dout [ indent ] " " $(result) -- $(extra2) ; 
###     if $(targets)
###     {
###         result = $(usage-requirements) $(result) ;
###     }    
###     return $(result) $(extra2) ;                     
### }
### 
### # Checks if generator invocation can be pruned, because it's guaranteed
### # to fail. If so, quickly returns empty list. Otherwise, calls
### # try-one-generator-really.
### local rule try-one-generator ( project name ? : generator multiple ? : 
###     target_type : property_set : sources * )
### {    
###     local source-types ;
###     for local s in $(sources)
###     {
###         source-types += [ $(s).type ] ;
###     }
###     local viable-source-types = 
###       [ viable-source-types-for-generator $(generator) ] ;
###     
###     if  $(source-types) && $(viable-source-types) != * && 
###       ! [ set.intersection $(source-types) : $(viable-source-types) ] 
###     {
###         local id = [ $(generator).id ] ;
###         generators.dout [ indent ] "generator '$(id)' pruned" ;
###         #generators.dout [ indent ] "source-types" '$(source-types)' ;
###         #generators.dout [ indent ] "viable-source-types" '$(viable-source-types)' ;
###     }          
###     else {
###         return [ try-one-generator-really $(project) $(name)
###           : $(generator) $(multiple) 
###             : $(target_type) : $(property_set) : $(sources) ] ;
###     }       
### }
### 
### 
### 
### rule construct-types ( project name ? : target_types + : multiple ? : 
###     property_set : sources + )
### {
###     local result ;
###     local matched-types ; 
###     local usage-requirements = [ property_set.empty ] ;
###     for local t in $(target_types)
###     {
###         local r = [ construct $(project) $(name) : $(t) $(multiple) : $(property_set) :
###           $(sources) ] ;
###         if $(r)
###         {
###             usage-requirements = [ $(usage-requirements).add $(r[1]) ] ;
###             result += $(r[2-]) ;
###             matched-types += $(t) ;
###         }
###     }
###     # TODO: have to introduce parameter controlling if
###     # several types can be matches and add appropriate
###     # checks 
### 
###     # TODO: need to review the documentation for
###     # 'construct' to see if it should return $(source) even
###     # if nothing can be done with it. Currents docs seem to
###     # imply that, contrary to the behaviour.
###     if $(result)
###     {
###         return $(usage-requirements) $(result) ;
###     }
###     else
###     {
###         return $(usage-requirements) $(sources) ;
###     }
### }
### 
### # Ensures all 'targets' have types. If this is not so, exists with 
### # error.
### local rule ensure-type ( targets * )
### {
###     for local t in $(targets)
###     {
###         if ! [ $(t).type ]
###         {
###             errors.error "target" [ $(t).str ] "has no type" ;
###         }        
###     }    
### }
### 
###     
### # Returns generators which can be used to construct target of specified type
### # with specified properties. Uses the following algorithm:
### # - iterates over requested target_type and all it's bases (in the order returned bt
### #   type.all-bases.
### # - for each type find all generators that generate that type and which requirements
### #   are satisfied by properties.
### # - if the set of generators is not empty, returns that set.
### #
### # Note: this algorithm explicitly ignores generators for base classes if there's
### # at least one generator for requested target_type.
### local rule find-viable-generators-aux ( target_type : property_set )
### {
###     # Select generators that can create the required target type.
###     local viable-generators = ;
###     local generator-rank = ;
### 
###     import type ;
###     # Try all-type generators first. Assume they have
###     # quite specific requirements.
###     local t = * [ type.all-bases $(target_type) ] ;
###     
###     generators.dout  [ indent ] find-viable-generators target_type= $(target_type) 
###       property_set= [ $(property_set).as-path ]
###           ;
###     
###     while $(t[1])
###     {
###         generators.dout  [ indent ] "trying type" $(t[1]) ;
###         for local g in $(.generators.$(t[1]))
###         {
###             generators.dout [ indent ] "trying generator" [ $(g).id ] "(" [ $(g).source-types ] -> [ $(g).target_types ] ")" ;
###             
###             local m = [ $(g).match-rank $(property_set) ] ;
###             if $(m) 
###             {
###                 generators.dout [ indent ] "  is viable" ;
###                 viable-generators += $(g) ;
###                 t = ;
###             }                                    
###         }
###         t = $(t[2-]) ;
###     }
###                             
###     return $(viable-generators) ;
### }
### 
### local rule find-viable-generators ( target_type : property_set )
### {
###     local key = $(target_type).$(property_set) ;
###     local l = $(.fv.$(key)) ;
###     if ! $(l)
###     {
###         l = [ find-viable-generators-aux $(target_type) : $(property_set) ] ;
###         if ! $(l)
###         {
###             l = none ;
###         }        
###         .fv.$(key) = $(l) ;
###     }
###     
###     if $(l) = none
###     {
###         l = ;
###     }
###                     
###     local viable-generators ;
###     for local g in $(l)
###     {
###         # Avoid trying the same generator twice on different levels.        
###         if ! $(g) in $(.active-generators) 
###         {
###             viable-generators += $(g) ;
###         }        
###     }
###     
###     # Generators which override 'all'.
###     local all-overrides ;
###     # Generators which are overriden
###     local overriden-ids ;    
###     for local g in $(viable-generators)
###     {
###         local id = [ $(g).id ] ;
###         local this-overrides = $(.override.$(id)) ;
###         overriden-ids += $(this-overrides) ;
###         if all in $(this-overrides)
###         {
###             all-overrides += $(g) ;
###         }        
###     }         
###     if $(all-overrides)
###     {
###         viable-generators = $(all-overrides) ;
###     }
###     local result ;
###     for local g in $(viable-generators)
###     {
###         if ! [ $(g).id ] in $(overriden-ids)
###         {
###             result += $(g) ;
###         }        
###     }
###         
###     return $(result) ;
### }    
### 
###     
### # Given a vector of vectors, of of them represents results of running some 
### # generator, returns the 'best' result, it it exists. Otherwise, exit with
### # and error. Result is returned as plain jam list.
### local rule select-dependency-graph ( options )
### {
###     if [ $(options).size ] = 0
###     {
###         return ;
###     }
###     else if [ $(options).size ] = 1
###     {
###         return [ $(options).get-at 1 ] ;
###     }
###     else
###     {
###         # We have several alternatives and need to check if they
###         # are the same. 
###         
###         for local r in [ $(options).get ] 
###         {
###             normalize-target-list $(r) ;
###             local v = [ $(r).get ] ;
###             generators.dout $(v[2-]) ;
###         }
###         
###         # One note why we can compare object names directly,
###         # without using deep copy. All the targets here are
###         # produced by some generators, and generators should
###         # pass the targets they've returned via 'virtual-target.register'.
###         # So, two elements can only be equivalent, if they are just
###         # the same object.       
###         local f = [ $(options).at 1 ] ;
###         f = [ $(f).get ] ;
###         f = $(f[2-]) ;
###         local mismatch ;
###         for local r in [ $(options).get ] 
###         {
###             local v = [ $(r).get ] ;
###             v = $(v[2-]) ;
###             if $(f) != $(v)
###             {
###                 mismatch = true ;
###             }
###         }
### 
###         if ! $(mismatch)
###         {
###             local v = [ $(options).at 1 ] ;
###             return [ $(v).get ] ;
###         }
###         else 
###         {                        
###             error [ $(options).size ] "possible generations for "
###                    $(target_types) "Can't handle this now." ;
###         }            
###     }                        
### }
###     
### .construct-stack = ;
### 
### # Attempts to construct target by finding viable generators, running them
### # and selecting the dependency graph
### local rule construct-really (
###    project name ? : target_type multiple ? : property_set : sources * )
### {
###     viable-generators = [ find-viable-generators $(target_type) : $(property_set) ] ;
###                     
###     local results = [ new vector ] ;
###     
###     generators.dout [ indent ] "*** " [ sequence.length $(viable-generators) ] 
###       " viable generators" ;
###     
###     for local g in $(viable-generators)
###     {
###         # This variable will be restored on exit from this scope.
###         local .active-generators = $(g) $(.active-generators) ;
###         
###         local r = [ try-one-generator $(project) $(name) : $(g) $(multiple) : $(target_type) :
###           $(property_set) : $(sources) ] ;
###         
###         if $(r)
###         {
###             $(results).push-back [ new vector $(r) ] ;
###         }
###     }
###     
###     return [ select-dependency-graph $(results) ] ;
### }       



def construct (project, name, target_type, multiple, property_set, sources, allowed_type):
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
        property_set (optional):
        sources (optional):
        allowed_type (optional):
    """
    # TODO: implement
    return None
###     allowed_type ?= $(target_type) ;
###     if (.construct-stack)
###     {
###         ensure-type $(sources) ;
###     }
### 
###     # Intermediate targets are not passed to generators
###     # and just returned unmodified.
###     local intermediate ;
###     if ! $(.construct-stack)
###     {
###         local sources2 ;
###         for local s in $(sources)
###         {
###             if ! [ $(s).intermediate ] 
###             {
###                 sources2 += $(s) ;
###             }
###             else
###             {
###                 intermediate += $(s) ;
###             }            
###         }
###         sources = $(sources2) ;
###     }
###         
###     .construct-stack += 1 ;
### 
###     increase-indent ;
###     
###     local m ;
###     if $(multiple)
###     {
###         m = "(may return multiple targets)" ;
###     }
###     generators.dout [ indent ] "*** construct" $(target_type) $(m) ;
###     
###     for local s in $(sources)
###     {
###         generators.dout [ indent ] "    from" $(s) ;
###     }
###     generators.dout [ indent ] "    properties:" [ $(property_set).raw ] ;        
###                
###     local result = [ construct-really $(project) $(name)  
###       : $(target_type) $(multiple) : $(property_set) : $(sources) ] ;
###                     
###     decrease-indent ;
###         
###     .construct-stack = $(.construct-stack[2-]) ;
###     
###     if ! $(.construct-stack)
###     {
###         result += $(intermediate) ;
###     }
###             
###     # For all targets of 'allowed_type', reset the 'intermediate' attribute.
###     if ! $(.construct-stack) && $(allowed_type) != * # This is first invocation in stack
###     {
###         local result2 ;
###         for local t in $(result[2-])
###         {
###             local type = [ $(t).type ] ;    
###             # Return only targets of the requested type, unless 'return-all'
###             # is specified. If we don't do this, then all targets calling
###             # 'construct' will get unused target returned, which will break
###             # checking for unused sources a bit harder.
###             if $(type) && ( $(type) = $(target_type) || [ type.is-derived $(type) $(allowed_type) ] )
###             {
###                 $(t).set-intermediate ;
###             }
###         }                
###     } 
###             
###     
###     return $(result) ;        
### }
### 
