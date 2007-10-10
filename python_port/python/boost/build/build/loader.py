# Copyright Vladimir Prus 2002-2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# This module is responsibile for loading projects defined by Jamfiles.
# It depends on the 'bjam' module, provided by bjam executable and so
# it made standalone, so that the 'project' module can be used without
# bjam

import sys
import os

import project
from boost.build.util import path, set
import bjam


class ProjectLoader:
    """Loads projects defined by Jamfiles.

       Has the logic to find the Jamfile for a directory, load Jamfile
       (by calling back bjam), and load the parents/inherit attributes.
    """

    JAMROOT = ["project-root.jam", "Jamroot", "jamroot", "Jamroot.jam", "jamroot.jam"]
    JAMFILES = ["[Jj]amfile.v2", "[Jj]amfile", "[Jj]amfile.jam"]

    def __init__(self, registry):
        self.registry_ = registry
        # A map of location to 0 or 1, that indicate if a project for
        # a specific directory was created
        self.known_locations_ = {}

    def load(self, location):
        """Loads the Jamfile for the specified location and
           returns ProjectModule instance."""
        
        if "--debug-loading" in sys.argv:
            print "Loading project at '%s'" % location

        if self.project_for_dir(location):
            return
       
        project_module = self.__load(location)

        return project_module

    def project_for_dir(self, location):
        """Returns 1 if a ProjectModule instance for this location was
           already created, and 0 otherwise."""        
        absolute_location = path.root (location, path.pwd())
        try:
            return self.known_locations_[absolute_location]
        except KeyError:
            return None
    

    def find_jamfile(self, location, no_errors=False):
        jamfiles = path.glob(location, self.JAMROOT)
        if not jamfiles:
            jamfiles = path.glob(location, self.JAMFILES)

        # If multiple Jamfiles found in the same place, warn about this.
        # And ensure we use only one of them.
        # As a temporary convenience measure, if there's Jamfile.v2 amount
        # found files, suppress the warning and use it.
        if len(jamfiles) > 1:
           
            v2_jamfiles = filter(lambda x: x == "Jamfile.v2" or\
                                 x == "jamfile.v2", jamfiles)
   
            if len(v2_jamfiles) == 1:
                jamfiles = v2_jamfiles
            else:
                print "warning: Found multiple Jamfiles at '%s'!" % location
                print "Loading the first one: '%s'" % jamfiles[0]

        if not jamfiles:
            if no_errors:
                return None
            else:
                raise "error: Unable to load Jamfile"
            #           errors.error
#               "Unable to load Jamfile." :
#               "Could not find a Jamfile in directory '$(dir)'". : 
#               "Attempted to find it with pattern '"$(JAMFILE:J=" ")"'." :
#               "Please consult the documentation at 'http://www.boost.org'." ;
#       }
        return os.path.normpath(path.root(jamfiles[0], path.pwd()))

    #   
#   # Load a Jamfile at the given directory. Returns nothing.
#   # Will attempt to load the file as indicated by the JAMFILE patterns. 
#   # Effect of calling this rule twice with the same 'dir' is underfined.
#
    def __load(self, location):
        jamfile = self.find_jamfile(location)
       
        return self.initialize(jamfile)

#   # Initialize the module for a project. 
#   #
    def initialize(self, location):
        parent = None
        if not os.path.basename(location) in self.JAMROOT:
            # Remove the name of Jamfile from 'location'
            dir = os.path.dirname(location)
            while 1:
                # Get parent directory
                parent_dir = os.path.dirname(dir)
                if not parent_dir or parent_dir == location:
                    break

                # See if we've loaded Jamfile in that dir
                parent = self.project_for_dir(parent_dir)
                if parent:
                    break

                # See if there's a Jamfile we can load
                if self.find_jamfile(parent_dir, True):
                    parent = self.load(parent_dir)
                    break

                dir = parent_dir
                
            if not parent:
                print "ERROR: could not find parent project"

        # TODO: inherit attributes here

        # Loading of parents might have caused loading of this project,
        # so do final check before creating project_module
        project_module = self.project_for_dir(location)
        if not project_module:
            project_module = self.registry_.create(location, parent)
            absolute_location = path.root (location, path.pwd())
            self.known_locations_[absolute_location] = 1

            project_context = ProjectContext(self, project_module)
            bjam.call("load", project_module.module_name(), location) #project_module.module_name(), location)
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
        #project_module.attributes().dump()

        project_module.attributes().dump()
        return project_module

class ProjectContext:
    """Class which provides basic rules callable inside Jamfile.

       An instance of this class is created for each project and associated
       with the project module. Each bound method of the instance will be
       then exported to bjam, so that methods of the instance can be called
       in Jamfile. Because it's method of the *instance*, not functions, we'll
       know which Jamfile invoked them without any global variables.
    """

    def __init__(self, project_registry, project_module):
        self.registry_ = project_registry
        self.project_module_ = project_module

        # Find all the methods of this instance, and import them (bounded)
        # into Jamfile.


        # The the class' dict -- the methods are not present in instance's
        # dict.
        # TODO: the name 'set.difference' is confusing --
        # the function operates on sequences.
        names = set.difference(self.__class__.__dict__, ["__init__"])
        for n in names:            
            # Using 'getattr' here gives us a bound method,
            # while using self.__dict__[r] would give unbound one.
            v = getattr(self, n)
            if callable(v):
                print "Importing '%s' to bjam" % n
                bjam.import_rule(self.project_module_.module_name(), n, v)
                
    def project(self, id, *options):
        print "The 'project' rule called from Jamfile"
        if id:
            print "Id is specified"
        else:
            print "No id"

        attributes = self.project_module_.attributes()

        if id:
            assert(len(id) == 1)
            id = id[0]
            if id[0] != '/':
                id = '/' + id
            self.registry_.register_id(id, self.project_module_)
            attributes.set('id', id)
                
        for a in options:
            attributes.set(a[0], a[1:])

    def make(self, target_name, sources, generating_rule, requirements=[]):
        import boost.build.tools.make
        
        boost.build.tools.make.make(self.project_module_, target_name[0],
                                    sources, generating_rule[0],
                                    requirements)

