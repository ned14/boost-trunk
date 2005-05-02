#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

""" Defines standard features and rules.
"""

import sys
from boost.build.build import feature, property, virtual_target, generators, type, property_set
from boost.build.util.utility import *
from boost.build.util import path
import boost.build.tools.types 

# Records explicit properties for a variant.
# The key is the variant name.
__variant_explicit_properties = {}

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __variant_explicit_properties

    __variant_explicit_properties = {}

def variant (name, parents_or_properties, explicit_properties = []):
    """ Declares a new variant.
        First determines explicit properties for this variant, by
        refining parents' explicit properties with the passed explicit
        properties. The result is remembered and will be used if
        this variant is used as parent.
        
        Second, determines the full property set for this variant by
        adding to the explicit properties default values for all properties 
        which neither present nor are symmetric.
        
        Lastly, makes appropriate value of 'variant' property expand
        to the full property set.
        name:                   Name of the variant
        parents_or_properties:  Specifies parent variants, if 
                                'explicit_properties' are given,
                                and explicit_properties otherwise.
        explicit_properties:    Explicit properties.
    """
    parents = []
    if not explicit_properties:
        if get_grist (parents_or_properties [0]):
            explicit_properties = parents_or_properties

        else:
            parents = parents_or_properties

    else:
        parents = parents_or_properties

    # The problem is that we have to check for conflicts
    # between base variants.
    if len (parents) > 1:
        raise BaseException ("Multiple base variants are not yet supported")
    
    inherited = []
    # Add explicitly specified properties for parents
    for p in parents:
        # TODO: the check may be stricter
        if not feature.is_implicit_value (p):
            raise BaseException ("Invalid base varaint '%s'" % p)
        
        inherited += __variant_explicit_properties [p]

    property.validate (explicit_properties)
    explicit_properties = property.refine (inherited, explicit_properties)
    
    # Record explicitly specified properties for this variant
    # We do this after inheriting parents' properties, so that
    # they affect other variants, derived from this one.
    __variant_explicit_properties [name] = explicit_properties
           
    feature.extend_feature ('variant', [name])
    feature.compose (replace_grist (name, '<variant>'), explicit_properties)

def register_globals ():
    """ Registers all features and variants declared by this module.
    """

    # This feature is used to determine which OS we're on.
    # In future, this may become <target-os> and <host-os>
    # TODO: check this. Compatibility with bjam names? Subfeature for version?
    os = sys.platform
    feature.feature ('os', [os], ['propagated', 'link-incompatible'])
    
    feature.feature ('toolset', [], ['implicit', 'propagated' ,'symmetric'])
    
    feature.feature ('stdlib', ['native'], ['propagated', 'composite'])
    
    feature.feature ('link', ['shared', 'static'], ['propagated'])
    feature.feature ('link-runtime', ['shared', 'static'], ['propagated'])
    feature.feature ('runtime-debugging', ['on', 'off'], ['propagated'])
    
    
    feature.feature ('optimization',  ['off', 'speed', 'space'], ['propagated'])
    feature.feature ('profiling', ['off', 'on'], ['propagated'])
    feature.feature ('inlining', ['off', 'on', 'full'], ['propagated'])
    
    feature.feature ('threading', ['single', 'multi'], ['propagated'])
    feature.feature ('rtti', ['on', 'off'], ['propagated'])
    feature.feature ('exception-handling', ['on', 'off'], ['propagated'])
    feature.feature ('debug-symbols', ['on', 'off'], ['propagated'])
    feature.feature ('define', [], ['free'])
    feature.feature ('include', [], ['free', 'path']) #order-sensitive
    feature.feature ('cflags', [], ['free'])
    feature.feature ('cxxflags', [], ['free'])
    feature.feature ('linkflags', [], ['free'])
    feature.feature ('archiveflags', [], ['free'])
    feature.feature ('version', [], ['free'])
    
    feature.feature ('location-prefix', [], ['free'])
    
    # The following features are incidental, since
    # in themself they have no effect on build products.
    # Not making them incidental will result in problems in corner
    # cases, for example:
    # 
    #    unit-test a : a.cpp : <use>b ;
    #    lib b : a.cpp b ;
    # 
    # Here, if <use> is not incidental, we'll decide we have two 
    # targets for a.obj with different properties, and will complain.
    #
    # Note that making feature incidental does not mean it's ignored. It may
    # be ignored when creating the virtual target, but the rest of build process
    # will use them.
    feature.feature ('use', [], ['free', 'dependency', 'incidental'])
    feature.feature ('dependency', [], ['free', 'dependency', 'incidental'])
    feature.feature ('implicit-dependency', [], ['free', 'dependency', 'incidental'])
    
    feature.feature ('source', [], ['free', 'dependency', 'incidental'])
    feature.feature ('library', [], ['free', 'dependency', 'incidental'])
    feature.feature ('file', [], ['free', 'dependency', 'incidental'])
    feature.feature ('find-shared-library', [], ['free']) #order-sensitive ;
    feature.feature ('find-static-library', [], ['free']) #order-sensitive ;
    feature.feature ('library-path', [], ['free', 'path']) #order-sensitive ;
    # Internal feature.
    feature.feature ('library-file', [], ['free', 'dependency'])
    
    feature.feature ('name', [], ['free'])
    feature.feature ('tag', [], ['free'])
    feature.feature ('search', [], ['free', 'path']) #order-sensitive ;
    feature.feature ('location', [], ['free', 'path'])
    
    feature.feature ('dll-path', [], ['free', 'path'])
    feature.feature ('hardcode-dll-paths', ['true', 'false'], ['incidental'])
    
    
    # This is internal feature which holds the paths of all dependency
    # dynamic libraries. On Windows, it's needed so that we can all
    # those paths to PATH, when running applications.
    # On Linux, it's needed to add proper -rpath-link command line options.
    feature.feature ('xdll-path', [], ['free', 'path'])
    
    #provides means to specify def-file for windows dlls.
    feature.feature ('def-file', [], ['free', 'dependency'])
    
    # This feature is used to allow specific generators to run.
    # For example, QT tools can only be invoked when QT library
    # is used. In that case, <allow>qt will be in usage requirement
    # of the library.
    feature.feature ('allow', [], ['free'])
    
    # Windows-specific features
    feature.feature ('user-interface', ['console', 'gui', 'wince', 'native', 'auto'], [])
    feature.feature ('variant', [], ['implicit', 'composite', 'propagated', 'symmetric'])


    variant ('debug', ['<optimization>off', '<debug-symbols>on', '<inlining>off', '<runtime-debugging>on'])
    variant ('release', ['<optimization>speed', '<debug-symbols>off', '<inlining>full', 
                         '<runtime-debugging>off', '<define>NDEBUG'])
    variant ('profile', ['release'], ['<profiling>on', '<debug-symbols>on'])

    type.register ('H', ['h'])
    type.register ('HPP', ['hpp'], 'H')
    type.register ('C', ['c'])
    

reset ()
register_globals ()

class SearchedLibTarget (virtual_target.AbstractFileTarget):
    def __init__ (self, name, project, shared, real_name, search, action):
        AbstractFileTarget.__init__ (self, name, False, 'SEARCHED_LIB', project, action)
        
        self.shared_ = shared
        self.real_name_ = real_name
        if not self.real_name_:
            self.real_name_ = name
        self.search_ = search

    def shared (self):
        return self.shared_
    
    def real_name (self):
        return self.real_name_
    
    def search (self):
        return self.search_
        
    def actualize_location (self, target):
        project.manager ().engine ().add_not_file_target (target)
    
    def path (self):
        pass


###################################################################
# Still to port.
# Original lines are prefixed with "### "

### class c-scanner : scanner 
### {
###     import regex virtual-target path scanner ;    
###     
###     rule __init__ ( includes * )
###     {
###         scanner.__init__ ;
###     
###         self.includes = $(includes) ;
###     }    
### 
###     rule pattern ( )
###     {
###         return "#[ \t]*include[ ]*(<(.*)>|\"(.*)\")" ;
###     }
### 
###     rule process ( target : matches * : binding )
###     {
###         local angle = [ regex.transform $(matches) : "<(.*)>" ] ;
###         local quoted = [ regex.transform $(matches) : "\"(.*)\"" ] ;
### 
###         # CONSIDER: the new scoping rule seem to defeat "on target" variables.
###         local g = [ on $(target) return $(HDRGRIST) ] ;  
###         local b = [ NORMALIZE_PATH $(binding:D) ] ;
### 
###         # Attach binding of including file to included targets.
###         # When target is directly created from virtual target
###         # this extra information is unnecessary. But in other
###         # cases, it allows to distinguish between two headers of the 
###         # same name included from different places.      
###         # We don't need this extra information for angle includes,
###         # since they should not depend on including file (we can't
###         # get literal "." in include path).
###         local g2 = $(g)"#"$(b) ;
###        
###         angle = $(angle:G=$(g)) ;
###         quoted = $(quoted:G=$(g2)) ;
###         
###         local all = $(angle) $(quoted) ;
### 
###         INCLUDES $(target) : $(all) ;
###         NOCARE $(all) ;
###         SEARCH on $(angle) = $(self.includes:G=) ;
###         SEARCH on $(quoted) = $(b) $(self.includes:G=) ;
###         
###         # Just propagate current scanner to includes, in a hope
###         # that includes do not change scanners. 
###         scanner.propagate $(__name__) : $(angle) $(quoted) : $(target) ;
###     }        
### }
### 
### scanner.register c-scanner : include ;
### 
### type.set-scanner CPP : c-scanner ;

class LibGenerator (generators.Generator):
    """ The generator class for libraries (target type LIB). Depending on properties it will
        request building of the approapriate specific type -- SHARED_LIB, STATIC_LIB or 
        SHARED_LIB.
    """

    def __init__ (self, id = 'LibGenerator', composing = True, source_types = [], target_types_and_names = ['LIB'], requirements = []):
        generators.Generator.__init__ (self, id, composing, source_types, target_types_and_names, requirements)
    
    def run (self, project, name, prop_set, sources, multiple):
        # The lib generator is composing, and can be only invoked with
        # explicit name. This check is present in generator.run (and so in
        # builtin.LinkingGenerator), but duplicate it here to avoid doing
        # extra work.
        if name:
            properties = prop_set.raw ()
            # Determine the needed target type
            actual_type = None
            properties_grist = get_grist (properties)
            if '<search>' in properties_grist or '<name>' in properties_grist:
                actual_type = 'SEARCHED_LIB'
            elif '<file>' in properties_grist:
                # The generator for 
                actual_type = 'LIB'
            elif '<link>shared' in properties:
                actual_type = 'SHARED_LIB'
            else:
                actual_type = 'STATIC_LIB'

            prop_set = prop_set.add_raw (['<main-target-type>LIB'])

            # Construct the target.
            return generators.construct (project, name, actual_type, True, prop_set, sources, 'LIB')

    def viable_source_types (self):
        return ['*']

generators.register (LibGenerator ())

### # The implementation of the 'lib' rule. Beyond standard syntax that rule allows
### # simplified:
### #    lib a b c ;
### # so we need to write code to handle that syntax. 
### rule lib ( names + : sources * : requirements * : default-build * 
###     : usage-requirements * )
### {
###     local project = [ project.current ] ;
###     
###     # This is a circular module dependency, so it must be imported here
###     import targets ;
### 
###     local result ;
###     if ! $(sources) && ! $(requirements) 
###       && ! $(default-build) && ! $(usage-requirements)
###     {
###         for local name in $(names)
###         {    
###             result += [ 
###             targets.main-target-alternative
###               [ new typed-target $(name) : $(project) : LIB 
###                 : 
###                 : [ targets.main-target-requirements $(requirements) <name>$(name)  :
###                     $(project) ] 
###                 : [ targets.main-target-default-build $(default-build) : $(project) ]
###                 : [ targets.main-target-usage-requirements $(usage-requirements) : $(project) ]
###              ] ] ;        
###         }        
###     }
###     else
###     {
###         if $(names[2])
###         {
###             errors.user-error "When several names are given to the 'lib' rule" :
###               "it's not allowed to specify sources or requirements. " ;
###         }
###                 
###         local name = $(names[1]) ;
###         result = [ targets.main-target-alternative
###           [ new typed-target $(name) : $(project) : LIB
###             : [ targets.main-target-sources $(sources) : $(name) ] 
###             : [ targets.main-target-requirements $(requirements) : $(project) ] 
###             : [ targets.main-target-default-build $(default-build) : $(project) ]
###             : [ targets.main-target-usage-requirements $(usage-requirements) : $(project) ]
###          ] ] ;
###     }    
###     return $(result) ;
### }
### IMPORT $(__name__) : lib : : lib ;

class SearchedLibGenerator (generators.Generator):
    def __init__ (self, id = 'SearchedLibGenerator', composing = False, source_types = [], target_types_and_names = ['SEARCHED_LIB'], requirements = []):
        # TODO: the comment below looks strange. There are no requirements!
        # The requirements cause the generators to be tried *only* when we're building
        # lib target and there's 'search' feature. This seems ugly --- all we want
        # is make sure SearchedLibGenerator is not invoked deep in transformation
        # search.
        generators.Generator.__init__ (self, id, composing, source_types, target_types_and_names, requirements)
    
    def run (self, project, name, prop_set, sources, multiple):
        if not name:
            return ([], [])

        # If name is empty, it means we're called not from top-level.
        # In this case, we just fail immediately, because SearchedLibGenerator
        # cannot be used to produce intermediate targets.
        
        properties = prop_set.raw ()
        shared = '<link>shared' in properties

        a = NullAction (project.manager (), prop_set)
        
        real_name = feature.get_values ('<name>', properties) [0]
        search = feature.get_values ('<search>', properties) [0]
        t = SearchedLibTarget (name, project, shared, real_name, search, a)

        # We return sources for a simple reason. If there's
        #    lib png : z : <name>png ; 
        # the 'z' target should be returned, so that apps linking to
        # 'png' will link to 'z', too.
        return (virtual_target.register (t), sources)

generators.register (SearchedLibGenerator ())

### class prebuilt-lib-generator : generator
### {
###     rule __init__ ( * : * )
###     {
###         generator.__init__ $(1) : $(2) : $(3) : $(4) : $(5) : $(6) : $(7) : $(8) : $(9) ;
###     }
### 
###     rule run ( project name ? : prop_set : sources * : multiple ? )
###     {
###         local f = [ $(prop_set).get <file> ] ;
###         return $(f) $(sources) ;
###     }    
### }
### 
### generators.register 
###   [ new prebuilt-lib-generator builtin.prebuilt : : LIB : <file> ] ;


class CompileAction (virtual_target.Action):
    def __init__ (self, manager, sources, action_name, prop_set):
        virtual_target.Action.__init__ (self, manager, sources, action_name, prop_set)

    def adjust_properties (self, prop_set):
        """ For all virtual targets for the same dependency graph as self, 
            i.e. which belong to the same main target, add their directories
            to include path.
        """
        s = self.targets () [0].creating_subvariant ()

        return prop_set.add_raw (s.implicit_includes ('include', 'H'))

class CCompilingGenerator (generators.Generator):
    """ Declare a special compiler generator.
        The only thing it does is changing the type used to represent
        'action' in the constructed dependency graph to 'CompileAction'.
        That class in turn adds additional include paths to handle a case
        when a source file includes headers which are generated themselfs.
    """
    def __init__ (self, id, composing, source_types, target_types_and_names, requirements):
        # TODO: (PF) What to do with optional_properties? It seemed that, in the bjam version, the arguments are wrong.
        generators.Generator.__init__ (self, id, composing, source_types, target_types_and_names, requirements)
            
    def action_class (self):
        return CompileAction

def register_c_compiler (id, source_types, target_types, requirements, optional_properties = []):
    g = CCompilingGenerator (id, False, source_types, target_types, requirements + optional_properties)
    return generators.register (g)


class LinkingGenerator (generators.Generator):
    """ The generator class for handling EXE and SHARED_LIB creation.
    """
    def __init__ (self, id, composing, source_types, target_types_and_names, requirements):
        generators.Generator.__init__ (self, id, composing, source_types, target_types_and_names, requirements)
        
    def run (self, project, name, prop_set, sources, multiple):
        sources.extend (prop_set.get ('<library>'))
        
        # Add <library-path> properties for all searched libraries
        extra = []
        for s in sources:
            if s.type () == 'SEARCHED_LIB':
                search = s.search ()
                extra.append (replace_grist (search, '<library-path>'))
                   
        if prop_set.get ('<hardcode-dll-paths>') == ['true'] and type.is_derived (self.target_types_ [0], 'EXE'):
            xdll_path = prop_set.get ('<xdll-path>')
            # It's possible that we have libraries in sources which did not came
            # from 'lib' target. For example, libraries which are specified
            # just as filenames as sources. We don't have xdll-path properties
            # for such target, but still need to add proper dll-path properties.
            for s in sources:
                if type.is_derived (s.type (), 'SHARED_LIB') and not s.action ():
                    # Unfortunately, we don't have a good way to find the path
                    # to a file, so use this nasty approach.
                    p = s.project ()
                    location = path.root (s.name (), p.get ('source-location'))
                    xdll_path.append (path.parent (location))
                          
            extra += [ replace_grist (x, '<dll-path>') for x in xdll_path ]
        
        if extra:
            prop_set = prop_set.add_raw (extra)
                        
        result = generators.Generator.run (self, project, name, prop_set, sources, multiple)
        
        return (self.extra_usage_requirements (result, prop_set), result)
    
    def extra_usage_requirements (self, created_targets, prop_set):
        
        result = property_set.empty ()
        extra = []
                        
        # Add appropriate <xdll-path> usage requirements.
        raw = prop_set.raw ()
        if '<link>shared' in raw:
            paths = []
            
            # TODO: is it safe to use the current directory? I think we should use 
            # another mechanism to allow this to be run from anywhere.
            pwd = os.getcwd ()
            
            for t in created_targets:
                if type.is_derived (t.type (), 'SHARED_LIB'):
                    paths.append (path.root (path.make (t.path ()), pwd))

            extra += replace_grist (paths, '<xdll-path>')
        
        # We need to pass <xdll-path> features that we've got from sources,
        # because if shared library is built, exe which uses it must know paths
        # to other shared libraries this one depends on, to be able to find them
        # all at runtime.
                        
        # Just pass all features in property_set, it's theorically possible
        # that we'll propagate <xdll-path> features explicitly specified by
        # the user, but then the user's to blaim for using internal feature.                
        values = prop_set.get ('<xdll-path>')
        extra += replace_grist (values, '<xdll-path>')
        
        if extra:
            result = property_set.create (extra)

        return result

    def generated_targets (self, sources, prop_set, project, name):

        # sources to pass to inherited rule
        sources2 = []
        # properties to pass to inherited rule
        properties2  = []
        # sources which are libraries
        libraries  = []
        
        # Searched libraries are not passed as argument to linker
        # but via some option. So, we pass them to the action
        # via property. 
        properties2 = prop_set.raw ()
        fsa = []
        fst = []
        for s in sources:
            if type.is_derived (s.type (), 'SEARCHED_LIB'):
                name = s.real_name ()
                if s.shared ():
                    fsa.append (name)

                else:
                    fst.append (name)

            else:
                sources2.append (s)

        properties2 += '&&'.join (replace_grist (fsa, '<find-shared-library>'))
        properties2 += '&&'.join (replace_grist (fst, '<find-static-library>'))
                
        spawn = generators.Generator.generated_targets (self, sources2, property_set.create (properties2), project, name)
        
        return spawn

### rule register-linker ( id composing ? : source_types + : target_types + :
###                             requirements * )
### {
###     local g = [ new LinkingGenerator $(id) $(composing) : $(source_types) 
###                 : $(target_types) : $(requirements) ] ;
###     generators.register $(g) ;
### }

class ArchiveGenerator (generators.Generator):
    """ The generator class for handling STATIC_LIB creation.
    """
    def __init__ (self, id, composing, source_types, target_types_and_names, requirements):
        generators.Generator.__init__ (self, id, composing, source_types, target_types_and_names, requirements)
        
    def run (self, project, name, prop_set, sources, multiple):
        sources += prop_set.get ('<library>')
        
        result = generators.Generator.run (self, project, name, prop_set, sources, multiple)
             
        return result

### rule register-archiver ( id composing ? : source_types + : target_types + :
###                             requirements * )
### {
###     local g = [ new ArchiveGenerator $(id) $(composing) : $(source_types) 
###                 : $(target_types) : $(requirements) ] ;
###     generators.register $(g) ;
### }
### 
### 
### IMPORT $(__name__) : register-linker register-archiver 
###   : : generators.register-linker generators.register-archiver ;
### 
### 
### 
