#  Copyright (c) 2004 Vladimir Prus.
#
#  Use, modification and distribution is subject to the Boost Software
#  License Version 1.0. (See accompanying file LICENSE_1_0.txt or
#  http://www.boost.org/LICENSE_1_0.txt)

""" This file implements linking semantics common to all unixes. On unix, static
    libraries must be specified in a fixed order on the linker command line. Generators
    declared there store information about the order and use it properly.
"""

import builtin
from boost.build.build import action, generators

class UnixLinkingGenerator (builtin.LinkingGenerator):
    
    def __init__ (self, id, rule, composing, source_types, target_types, requirements):
        LinkingGenerator.__init__ (self, id, rule, composing, source_types, target_types, requirements)
    
    def run (self, project, name, prop_set, sources, multiple):
        result = LinkingGenerator.run (project, name, prop_set, sources, multiple)
        set_library_order (sources, prop_set, result [1])
                                
        return result
    
    def generated_targets (self, sources, prop_set, project, name):
        sources2 = []
        libraries = []
        for l in sources:
            if type.is_derived (l.type (), 'LIB'):
                libraries.append (l)

            else:
                sources2.append (l)
        
        sources = sources2 + order_libraries (libraries)
        
        return LinkingGenerator.generated_targets (sources, prop_set, project, name)


class UnixArchiveGenerator (builtin.ArchiveGenerator):
    def __init__ (self, id, rule, composing, source_types, target_types, requirements):
        builtin.ArchiveGenerator.__init__ (self, id, rule, composing, source_types, target_types, requirements)
        
    def run (self, project, name, prop_set, sources, multiple):
        result = ArchiveGenerator.run (project, name, prop_set, sources, multiple)
        set_library_order (sources, prop_set, result)
        return result

class UnixSearchedLibGenerator (builtin.SearchedLibGenerator):
    
    def __init__ (self):
        builtin.SearchedLibGenerator.__init__ (self)
    
    def optional_properties (self):
        return self.requirements ()
              
    def run (self, project, name, prop_set, sources, multiple):
        result = SearchedLibGenerator.run (project, name, prop_set, sources, multiple)
        
        set_library_order (sources, prop_set, result)
        
        return result

class UnixPrebuiltLibGenerator (generators.Generator):
    def __init__ (self, id, rule, composing, source_types, target_types_and_names, requirements):
        generators.Generator.__init__ (self, id, rule, composing, source_types, target_types_and_names, requirements)

    def run (self, project, name, prop_set, sources, multiple):
        f = prop_set.get ('<file>')
        set_library_order_aux (f, sources)
        return (f, sources)

### # The derived toolset must specify their own rules and actions.
def prebuilt ():
    pass

action.action (prebuilt, [])

generators.register (UnixPrebuiltLibGenerator ('unix.prebuilt', prebuilt, False, [], ['LIB'], ['<file>', '<toolset>unix']))





### # Declare generators
### generators.register [ new UnixLinkingGenerator unix.link : LIB OBJ : EXE 
###     : <toolset>unix ] ;
### 
### generators.register [ new UnixArchiveGenerator unix.archive : OBJ : STATIC_LIB 
###     : <toolset>unix ] ;
### 
### generators.register [ new UnixLinkingGenerator unix.link.dll : LIB OBJ : SHARED_LIB 
###     : <toolset>unix ] ;
### 
### generators.register [ new UnixSearchedLibGenerator 
###    unix.SearchedLibGenerator : : SEARCHED_LIB : <toolset>unix ] ;
### 
### 
### # The derived toolset must specify their own actions.
### actions link {
### }
### 
### actions link.dll {
### }
### 
### actions archive {    
### }
### 
### actions searched-lib-generator {    
### }
### 
### actions prebuilt {
### }
### 
###     
### 
### 
### 
### .order = [ new order ] ;
### 
### rule set_library_order_aux ( from * : to * )
### {        
###     for local f in $(from)
###     {
###         for local t in $(to)
###         {            
###             if $(f) != $(t)
###             {                
###                 $(.order).add-pair $(f) $(t) ;
###             }            
###         }        
###     }    
### }
### 
### rule set_library_order ( sources * : prop_set : result * )
### {
###     local used-libraries ;
###     local deps = [ $(prop_set).dependency ] ;        
###     for local l in $(sources) $(deps:G=)        
###     {
###         if [ $(l).type ] && [ type.is-derived [ $(l).type ] LIB ]
###         {
###             used-libraries += $(l) ;
###         }
###     }
### 
###     local created-libraries ;
###     for local l in $(result)
###     {
###         if [ $(l).type ] && [ type.is-derived [ $(l).type ] LIB ] 
###         {
###             created-libraries += $(l) ;
###         }            
###     }
###     
###     created-libraries = [ set.difference $(created-libraries) : $(used-libraries) ] ;
###     set_library_order_aux $(created-libraries) : $(used-libraries) ;
### }
### 
### rule order_libraries ( libraries * )
### {
###     local r = [ $(.order).order $(libraries) ] ;
###     return $(r) ;
### }
###      
