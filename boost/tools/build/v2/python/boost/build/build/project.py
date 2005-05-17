#  Copyright (C) Vladimir Prus and Rene Rivera 2002.
#  Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

#  Implements project representation and loading.
#   Each project is represented by 
#   - a module where all the Jamfile content live. 
#   - an instance of 'ProjectAttributes' class.
#     (given module name, can be obtained by 'attributes' rule)
#   - an instance of 'project-target' class (from targets.jam)
#     (given a module name, can be obtained by 'target' rule)
#
#  Typically, projects are created as result of loading Jamfile, which is
#  done by rules 'load' and 'initialize', below. First, module for Jamfile
#  is loaded and new ProjectAttributes instance is created. Some rules
#  necessary for project are added to the module (see 'project-rules' module)
#  at the bottom of this file.
#  Default project attributes are set (inheriting attributes of parent project, if
#  it exists). After that, Jamfile is read. It can declare its own attributes,
#  via 'project' rule, which will be combined with already set attributes.
#
#
#  The 'project' rule can also declare project id, which will be associated with 
#  the project module.
#
#  There can also be 'standalone' projects. They are created by calling 'initialize'
#  on arbitrary module, and not specifying location. After the call, the module can
#  call 'project' rule, declare main target and behave as regular projects. However,
#  since it's not associated with any location, it's better declare only prebuilt 
#  targets.
#
#  The list of all loaded Jamfile is stored in variable .project-locations. It's possible
#  to obtain module name for a location using 'module_name' rule. The standalone projects
#  are not recorded, the only way to use them is by project id.

from boost.build.util import path, set
from boost.build.build import property_set, property
import boost.build.build.targets

import sys
import os.path

class ProjectAttributes:
    """ Class keeping all the attributes of a project.
        The standard attributes are "id", "location", "project-root", "parent"
        "requirements", "default-build", "source-location" and "projects-to-build".
    """
    def __init__ (self, manager, location, parent=None):

        self.manager_ = manager
        
        # The directory of the project.
        self.location_ = location

        # A map with all attributes. The key is the attribute name.
        self.attributes_ = {}
        
        self.attributes_['location'] = location
        self.attributes_['source-location'] = location
        empty = property_set.empty ()
        self.attributes_['requirements'] = empty
        self.attributes_['usage-requirements'] = empty
        
        # TODO: For some reason, usage-requirements are a list, rather than a property set
        self.attributes_['default-build'] = []
        
        if parent:
            self.inherit(parent)
            
    def set (self, attribute, specification, exact = False):
        """ Set the named attribute from the specification given by the user.
            The value actually set may be different.
            exact: if True, sets the value from 'specification' without any processing.
        """
        if exact:
            self.attributes_ [attribute] = specification
            return
        
        if attribute == "requirements":
            specification = property.translate_paths (specification, self.location_)
            specification = property.expand_subfeatures_in_conditions (specification)
            specification = property.make (specification)
            result = property_set.create (specification)
            
            # If we have inherited properties, need to refine them with the
            # specified.
            if self.attributes_.has_key ('requirements'):
                result = self.attributes_ ['requirements'].refine (result)

            if "@error" in str (result):
                # TODO: check usage of result for error signalling
                raise BaseException ("Requirements for project at '%s'"
                    "conflict with parent's.`n"
                    "Explanation: %s"  % (self.location_, result))

            else:
                self.attributes_ ['requirements'] = result

        elif attribute == "usage-requirements":
            unconditional = []
            for p in specification:
                split = property.split_conditional (p)
                if not split: 
                    unconditional.append (p)
                else:
                    unconditional.append (split [2])
            
            non_free = property.remove ('free', unconditional)
            
            if non_free:
                raise BaseException ("usage-requirements '%s' have non-free properties" % (specification, non_free))

            t = property.translate_paths (specification, self.location_)

            if self.attributes_.has_key ('usage-requirements'):
                self.attributes_ ['usage-requirements'] = property_set.create (
                    self.get('usage-requirements').raw() + t)

            else:
                self.attributes_ ['usage-requirements'] = property_set.create (t)

        elif attribute == "default-build":
            self.attributes_ ['default-build'] = properties.make (specification)

        elif attribute == "source-location":
            self.attributes_ ['source-location'] = path.root (path.make (specification), self.location_)

        elif attribute == "build-dir":
            self.attributes_ ['build-dir'] = path.root (specification, self.location_)

        elif not attribute in ["id", "default-build", "location", "source-location",
            "parent", "projects-to-build"]:
            raise BaseException ("Invalid project attribute '%s' specified for project at '%s'" % (attribute, self.location_))

        else:
            self.attributes_ [attribute] = specification

    def get (self, attribute):
        if self.attributes_.has_key (attribute):
            return self.attributes_ [attribute]
        else:
            return ''

    def inherit(self, parent):
        self.attributes_['default-build'] = parent.get('default-build')
        self.attributes_['requirements'] = parent.get('requirements')
        self.attributes_['usage-requirements'] = parent.get('usage-requirements')

        parent_build_dir = parent.get('build-dir')
        if parent_build_dir:
            # Have to compute relative path from parent dir to our dir
            # Convert both paths to absolute, since we cannot
            # find relative path from ".." to "."
        
            parent_dir = path.root(parent.get('location'), path.pwd())
            our_dir = path.root(self.get('location'), path.pwd())
            self.attributes_['build-dir'] = os.path.join(
                parent_dir, path.relative(our_dir, parent_dir))

    def dump(self):
        for k in self.attributes_:
            print k, " : ", self.attributes_[k]



class ProjectModule:
    """Project abstraction.

       In V2/Jam, projects were identified by bjam module corresponding
       to the Jamfile. This design was moved to V2/Python, but should
       be revised after we've done with the porting. This class should
       be gone and we should be using ProjectTarget instead.
    """
    
    def __init__ (self, registry, location, parent):

        self.registry_ = registry
        manager = self.registry_.manager_

        parent_attributes = None
        parent_target = None
        if parent:
            parent_attributes = parent.attributes()
            parent_target = parent.target()

        self.attributes_ = ProjectAttributes (manager, location,
                                              parent_attributes)

        # The unambiguous name of the module, based on its location.
        self.module_name_ = None
        
        from targets import ProjectTarget
        self.target_ = ProjectTarget (self.module_name (), 
            self, 
            parent_target, 
            self.attribute ('requirements'), 
            [])
        
    def attributes (self):
        """ Returns the project-attribute instance.
        """
        return self.attributes_
    
    def attribute (self, attribute):
        """ Returns the value of the specified attribute.
        """
        return self.attributes_.get (attribute)

    def manager (self):
        return self.attributes_.manager_

    def target (self):
        return self.target_

    def module_name (self):
        if not self.module_name_:
            # Root the path, so that locations are always umbiguious.
            # Without this, we can't decide if '../../exe/program1' and '.'
            # are the same paths, or not.
            jamfile_location = path.root (self.attributes_.location_, path.pwd ())
            self.module_name_ = 'Jamfile<' + jamfile_location + '>'

        return self.module_name_


class ProjectRegistry:
    """ A factory and a registry of project modules.
    """
    def __init__ (self, manager):
        self.manager_ = manager

        # A map of all projects.
        self.projects_ = {}
        # A map from project id to ProjectModule instance
        self.id_to_module_ = {}
        # A map from project modules to the corresponding project target
        self.project_modules_to_targets_ = {}
        
    def create (self, location, parent=None):        
        project = ProjectModule (self, location, parent)
        
        module_name = project.module_name ()
        if self.projects_.has_key (module_name):
            raise BaseException ("A project already exists in this location: '%s'" % module_name)
            
        self.projects_ [module_name] = project
        
        return project        
    
    def projects (self):
        return self.projects_.iteritems ()


###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#   import modules : peek poke ;
#   import numbers ;
#   import path ;
#   import sequence ;
#   import errors : error ;
#   
#   import print ;
#   import "class" : new ;
#   import errors ;
#   import assert ;
#   import property-set ;
#   
#   #
#   #   Loads jamfile at the given location. After loading, project global
#   #   file and jamfile needed by the loaded one will be loaded recursively.
#   #   If the jamfile at that location is loaded already, does nothing.
#   #   Returns the project module for the Jamfile.
#   #

                   
#           # We want to make sure that child project are loaded only
#           # after parent projects. In particular, because parent projects
#           # define attributes whch are inherited by children, and we don't
#           # want children to be loaded before parents has defined everything.
#           # So, for "build-project" and "use-project" we only record relevant
#           # information, and actually load the mentioned projects after
#           # loading the current Jamfile.       
#           for local p in [ attribute $(module_name) projects-to-build ]
#           {
#               load [ path.join $(jamfile-location) $(p) ] ;
#           }
#   
#           local used = [ modules.peek $(module_name) : .used-projects ] ;
#                   import project ;
#           while $(used)
#           {
#               local id = $(used[1]) ;
#               local where = $(used[2]) ;
#               
#               project.use $(id) : [ path.root 
#                   [ path.make $(where) ] $(jamfile-location) ] ;
#               used = $(used[3-]) ;
#           }        
#       }                
#       return $(module_name) ;        
#   }        
#   



#   # Loads parent of Jamfile at 'location'. Issues an error if nothing is found.
#   rule load-parent ( location )
#   {
#       local found = [ path.glob-in-parents $(location) : 
#         $(JAMROOT) $(JAMFILE) ] ;
#       
#       if ! $(found)
#       {
#           ECHO "error: Could not find parent for project at '$(location)'" ;
#           ECHO "error: Did not find Jamfile or project-root.jam in any parent directory." ;
#           EXIT ;
#       }
#       
#       return [ load $(found[1]:D) ] ;    
#   }
#   
#   # Makes the specified 'module' act as if it were a regularly loaded Jamfile 
#   # at 'location'. If Jamfile is already located for that location, it's an 
#   # error. 
#   rule act-as-jamfile ( module : location )
#   {
#       if [ module_name $(location) ] in $(.jamfile-modules)
#       {
#           errors.error "Jamfile was already loaded for '$(location)'" ;
#       }
#       # Set up non-default mapping from location to module.
#       .module.$(location) = $(module) ;    
#       
#       # Add the location to the list of project locations
#       # so that we don't try to load Jamfile in future
#       .jamfile-modules += [ module_name $(location) ] ;
#       
#       initialize $(module) : $(location) ;
#   }
#   
#   
    # Given 'name' which can be project-id or plain directory name,
    # return project module corresponding to that id or directory.
    # Returns nothing of project is not found.
    def find (self, name, current_location):
        project_module = None
        
        # Try interpreting name as project id.
        if path.is_rooted (name):
            project_module =  self.id_to_module_.get (name, None)
                    
        if not project_module:
            location = path.root (path.make (name), current_location)
            
            raise Exception ('Cannot load Jamfiles yet')
            # If no project is registered for the given location, try to
            # load it. First see if we have Jamfile. If not we might have project
            # root, willing to act as Jamfile. In that case, project-root
            # must be placed in the directory referred by id.
            
#               project_module = [ module_name $(location) ] ;
#               if ! $(project_module) in $(.jamfile-modules) 
#               {
#                   if [ find-jamfile $(location) : no-error ]
#                   {
#                       project_module = [ load $(location) ] ;            
#                   }        
#                   else
#                   {
#                       project_module = ;
#                   }
#               }                    
#           }
#           
#           return $(project_module) ;
#       }
    
#   #
#   # Returns the name of module corresponding to 'jamfile-location'.
#   # If no module corresponds to location yet, associates default
#   # module name with that location.
#   #    
#   rule module_name ( jamfile-location )
#   {
#       if ! $(.module.$(jamfile-location))
#       {
#           # Root the path, so that locations are always umbiguious.
#           # Without this, we can't decide if '../../exe/program1' and '.'
#           # are the same paths, or not.
#           jamfile-location = [ path.root $(jamfile-location) [ path.pwd ] ] ;
#           .module.$(jamfile-location) =  Jamfile<$(jamfile-location)> ;
#       }
#       return $(.module.$(jamfile-location)) ;
#   }
#   
#   # Default patterns to search for the Jamfiles to use for build
#   # declarations.
#   #
#   JAMFILE = [ modules.peek : JAMFILE ] ;

#   
#   # Find the Jamfile at the given location. This returns the exact names of
#   # all the Jamfiles in the given directory. The optional parent-root argument
#   # causes this to search not the given directory but the ones above it up
#   # to the directory given in it.
#   #

       

#   local rule find-jamfile (
#       dir # The directory(s) to look for a Jamfile.
#       parent-root ? # Optional flag indicating to search for the parent Jamfile.
#       : no-errors ?
#       )
#   {
#       # Glob for all the possible Jamfiles according to the match pattern.
#       #
#       local jamfile-glob = ;
#       if $(parent-root)
#       {
#           if ! $(.parent-jamfile.$(dir))
#           {     
#               .parent-jamfile.$(dir) = 
#                 [ path.glob-in-parents $(dir) : $(JAMFILE)  ] ;            
#           }        
#           jamfile-glob = $(.parent-jamfile.$(dir)) ;                            
#       }
#       else
#       {
#           if ! $(.jamfile.$(dir))
#           {            
#               .jamfile.$(dir) = [ path.glob $(dir) : $(JAMFILE) ] ;         
#           }   
#           jamfile-glob = $(.jamfile.$(dir)) ;
#           
#       }
#       
#       local jamfile-to-load = $(jamfile-glob) ;
#       # Multiple Jamfiles found in the same place. Warn about this.
#       # And ensure we use only one of them.
#       # As a temporary convenience measure, if there's Jamfile.v2 amount
#       # found files, suppress the warning and use it.
#       #
#       if $(jamfile-to-load[2-])
#       {
#           local v2-jamfiles = [ MATCH (.*[Jj]amfile\\.v2) : $(jamfile-to-load) ] ;
#   
#           if $(v2-jamfiles) && ! $(v2-jamfiles[2])
#           {
#               jamfile-to-load = $(v2-jamfiles) ;
#           }        
#           else
#           {                    
#               ECHO
#                 "warning: Found multiple Jamfiles at '"$(dir)"'!"
#                   "Loading the first one: '" [ path.basename $(jamfile-to-load[1]) ]  "'." ;
#           }
#                       
#           jamfile-to-load = $(jamfile-to-load[1]) ;
#       }    
#       
#       # Could not find it, error.
#       #
#       if ! $(no-errors) && ! $(jamfile-to-load)
#       {
#           errors.error
#               "Unable to load Jamfile." :
#               "Could not find a Jamfile in directory '$(dir)'". : 
#               "Attempted to find it with pattern '"$(JAMFILE:J=" ")"'." :
#               "Please consult the documentation at 'http://www.boost.org'." ;
#       }
#   
#       return $(jamfile-to-load) ;
#   }

#   
#       # Now load the Jamfile in it's own context.
#       # Initialization might have load parent Jamfiles, which might have
#       # loaded the current Jamfile with use-project. Do a final check to make
#       # sure it's not loaded already.
#       if ! $(jamfile-module) in $(.jamfile-modules)
#       {           
#           .jamfile-modules += $(jamfile-module) ;        
#           modules.load $(jamfile-module) :  [ path.native $(jamfile-to-load) ] : . ;
#           if $(jamfile-to-load:BS) in $(JAMROOT)
#           {
#               jamfile = [ find-jamfile $(dir) : no-errors ] ;
#               # project-root.jam might have loaded some modules which used 
#               # project.initialize, and clobbered .current-project
#               .current-project = [ target $(module_name) ] $(.current-project) ;            
#               if $(jamfile)
#               {                
#                   load-aux $(jamfile-module) : [ path.native $(jamfile) ] ;
#               }            
#           }        
#       }
#       .current-project = $(.current-project[2-]) ;
#   }
#   
#   
#   rule load-aux ( module_name : file )
#   {
#       if USER_MODULE in [ RULENAMES ]
#       {            
#           USER_MODULE $(module_name) ;
#       }
#       
#       module $(module_name)
#       {
#           include $(2) ;
#           local rules = [ RULENAMES $(1) ] ;
#           IMPORT $(1) : $(rules) : $(1) : $(1).$(rules) ;
#       }    
#   }
#   
#   
#   

        
            
#       # Import rules common to all project modules from project-rules module,
#       # defined at the end of this file.
#       modules.clone-rules project-rules $(module_name) ;
#   
#       # We search for parent/project-root only if jamfile was specified --- i.e
#       # if the project is not standalone.
#       if $(location)
#       {

#           local parent-module ;
#           if ! $(basename) in $(JAMROOT)
#           {
#               parent-module = [ load-parent $(location) ] ;
#               inherit-attributes $(module_name) : $(parent-module) ;
#           }
#                           
#           local parent ;
#           if $(parent-module)
#           {
#               parent = [ target $(parent-module) ] ;
#           }
#   
#           if ! $(.target.$(module_name))
#           {
#               .target.$(module_name) = [ new project-target $(module_name)               
#                : $(module_name) $(parent)
#              : [ attribute $(module_name) requirements ] ] ;
#               
#               if --debug-loading in [ modules.peek : ARGV ]
#               {
#                   ECHO "Assigned project target" $(.target.$(module_name)) 
#                     "to '$(module_name)'" ;
#               }
#               
#               
#           }                
#       }    
#       
#       .current-project = [ target $(module_name) ] $(.current-project) ;
#   }
#   
#   # Make 'project_module' inherit attributes of project root and parent module.
#   rule inherit-attributes ( project_module : parent-module )
#   {
#       local attributes = $($(project_module).attributes) ;        
#       local pattributes = [ attributes $(parent-module) ] ;
#       $(attributes).set parent : [ path.parent 
#           [ path.make [ modules.binding $(parent-module) ] ] ] ;
#       $(attributes).set default-build 
#         : [ $(pattributes).get default-build ] ;
#       $(attributes).set requirements
#         : [ $(pattributes).get requirements ] : exact ;
#       $(attributes).set usage-requirements
#         : [ $(pattributes).get usage-requirements ] : exact ;
#       local parent-build-dir = [ $(pattributes).get build-dir ] ;
#       if $(parent-build-dir)
#       {            
#           # Have to compute relative path from parent dir to our dir
#           # Convert both paths to absolute, since we cannot
#           # find relative path from ".." to "."
#           
#           local location = [ attribute $(project_module) location ] ;
#           local parent-location = [ attribute $(parent-module) location ] ;
#           
#           local pwd = [ path.pwd ] ;
#           local parent-dir = [ path.root $(parent-location) $(pwd) ] ;
#           local our-dir = [ path.root $(location) $(pwd) ] ;
#           $(attributes).set build-dir : [ path.join $(parent-build-dir) 
#             [ path.relative $(our-dir) $(parent-dir) ] ] : exact ;
#       }        
#   }
#   
#
    def register_id (self, id, project_module):
        """ Associate the given id with the given project module.
        """
        self.id_to_module_ [id] = project_module

#       # Returns the value of the given attribute.
#       rule get ( attribute )
#       {
#           return $(self.$(attribute)) ;
#       }
#   
#       # Prints the project attributes.
#       rule print ( )
#       {
#           local id = $(self.id) ; id ?= (none) ;
#           local parent = $(self.parent) ; parent ?= (none) ;
#           print.section "'"$(id)"'" ;
#           print.list-start ;
#           print.list-item "Parent project:" $(parent) ;
#           print.list-item "Requirements:" [ $(self.requirements).raw ] ;
#           print.list-item "Default build:" $(self.default-build) ;
#           print.list-item "Source location:" $(self.source-location) ;
#           print.list-item "Projects to build:" 
#                               [ sequence.insertion-sort $(self.projects-to-build) ] ;
#           print.list-end ;
#       }
#       
#   }
#   
#   # Returns the project which is currently being loaded
#   rule current ( )
#   {
#       return $(.current-project[1]) ;
#   }
#   
#   # Returns the project-attribute instance for the specified jamfile module.
#   rule attributes ( project )
#   {
#       return $($(project).attributes) ;
#   }
#   
#   # Returns the value of the specified attribute in the specified jamfile module.
#   rule attribute ( project attribute )
#   {
#       return [ $($(project).attributes).get $(attribute) ] ;        
#   }
#   

    def target (self, project_module):
        """ Returns the project target corresponding to the 'project_module'.
        """
        id = str (project_module)
        t = self.project_modules_to_targets_.get (id, None)
        
        if not t:
            t = targets.ProjectTarget (id, project_module, None, project_module.attribute ('requirements'))
            self.project_modules_to_targets_ [id] = t

        return t

#   # Use/load a project.
#   rule use ( id : location )
#   {
#       local saved-project = $(.current-project) ;
#       local project_module = [ project.load $(location) ] ;
#       local declared-id = [ project.attribute $(project_module) id ] ;
#          
#       if ! $(declared-id) || $(declared-id) != $(id)
#       {
#           # The project at 'location' either have no id or
#           # that id is not equal to the 'id' parameter.
#           if $($(id).jamfile-module) 
#             && $($(id).jamfile-module) != $(project_module)
#           {
#               errors.user-error 
#                 "Attempt to redeclare already existing project id" ;
#           }                  
#           $(id).jamfile-module = $(project_module) ;
#       }
#       .current-project = $(saved-project) ;
#   }


#   
#   # This module defines rules common to all projects
#   module project-rules
#   {
#       # Make toolset.using accessible in project context
#       import toolset : using ;
#       EXPORT project-rules : using ;
#       
#       rule project ( id ? : options * : * )
#       {
#           import project ;
#           import path ;
#                   
#           local attributes = [ project.attributes $(__name__) ] ;
#           if $(id) 
#           {
#              id = [ path.root $(id) / ] ;
#              project.register-id $(id) : $(__name__) ;
#              $(attributes).set id : $(id) ;
#           }
#   
#           for n in 2 3 4 5 6 7 8 9
#           {
#               local option = $($(n)) ;
#               if $(option) 
#               {
#                   $(attributes).set $(option[1]) : $(option[2-]) ;
#               }
#           }
#       }
#       
#       # Declare and set a project global constant. Project global constants are
#       # normal variables but should not be changed. They are applied to every
#       # child Jamfile.
#       #
#       rule constant (
#           name # Variable name of the constant.
#           : value # Value of the constant.
#           )
#       {
#           import project ;
#           local p = [ project.target $(__name__) ] ;
#           $(p).add-constant $(name) : $(value) ;        
#       }
#       
#       # Declare and set a project global constant, whose value is a path. The
#       # path is adjusted to be relative to the invocation directory. The given
#       # value path is taken to be either absolute, or relative to this project
#       # root.  
#       rule path-constant (
#           name # Variable name of the constant.
#           : value # Value of the constant.
#           )
#       {
#           import project ;
#           local p = [ project.target $(__name__) ] ;
#           $(p).add-constant $(name) : $(value) : path ;
#       }
#   
#   
#       rule use-project ( id : where )
#       {
#           # See comment in 'load' for explanation.
#           .used-projects += $(id) $(where) ;
#       }
#   
#       rule build-project ( dir )
#       {
#           import project ;
#           local attributes = [ project.attributes $(__name__) ] ;
#   
#           local now = [ $(attributes).get projects-to-build ] ;
#           $(attributes).set projects-to-build : $(now) $(dir) ;
#       }
#       
#       rule explicit ( target-names * )
#       {
#           import project ;
#           local t = [ project.target $(__name__) ] ;
#           for local n in $(target-names)
#           {            
#               $(t).mark-target-as-explicit $(n) ;
#           }        
#       }    
#       
#       rule glob ( wildcards + )
#       {
#           import path ;
#           import project ;
#           
#           local location = [ project.attribute $(__name__) source-location ] ;
#   
#           local result ;
#           local paths = [ path.glob $(location) : $(wildcards) ] ;   
#           if $(wildcards:D)
#           {
#               # The paths we've found are relative to current directory,
#               # but the names specified in sources list are assumed to
#               # be relative to source directory of the corresponding
#               # prject. So, just make the name absolute.
#               for local p in $(paths)
#               {
#                   result += [ path.root $(p) [ path.pwd ] ] ;
#               }                
#           }
#           else 
#           {
#               # There were not directory in wildcard, so the files are all
#               # in the source directory of the project. Just drop the
#               # directory, instead of making paths absolute.
#               result = $(paths:D="") ;
#           }
#   
#           return $(result) ;                
#       }        
#   }
#   
#   
#   local rule __test__ ( )
#   {
#       import assert ;
#   }


