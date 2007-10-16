# Status: being ported by Vladimir Prus.

# Copyright 2003, 2005 Dave Abrahams 
# Copyright 2006 Rene Rivera 
# Copyright 2003, 2004, 2005, 2006, 2007 Vladimir Prus 
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt) 

from boost.build.engine.engine import Engine
from boost.build.manager import Manager
from boost.build.util.path import glob
from boost.build.build import feature, property_set
from boost.build.build.targets import ProjectTarget
import boost.build.tools.common
import boost.build.tools.builtin
import boost.build.build.build_request

import bjam

import os
import sys

# FIXME:
# Returns the location of the build system. The primary use case
# is building Boost, where it's sometimes needed to get location
# of other components (like BoostBook files), and it's convenient
# to use location relatively to Boost.Build path.
#rule location ( )
#{
#    local r = [ modules.binding build-system ] ;
#    return $(r:P) ;
#}

# FIXME:
command_line_free_features = []
# Returns the property set with the
# free features from the currently processed
# build request.
#rule command-line-free-features ( )
#{
#    return $(.command-line-free-features) ;
#}

def get_boolean_option(name):
    match = "--" + name
    if match in argv:
        return 1
    else:
        return 0

def get_string_option(name):
    match = "--" + name + "="
    
    for arg in argv:
        if arg.startswith(match):
            return arg[len(match):]
    return None

def home_directories():
    if os.name == "nt":
        return [os.environ['HOMEDRIVE'] + os.envrion['HOMEPATH'],
                os.environ['HOME'],
                os.environ['USERPROFILE']]
    else:
        return [os.environ['HOME']]

ignore_config = 0
debug_config = 0

def load_config(manager, basename, path):
    """Unless ignore-config is set, search configuration
    basename.jam in path and loads it.  The jamfile module
    for that file will be loaded 'basename'."""

    if not ignore_config:
        found = glob(path, [basename + ".jam"])
        if found:
            found = found[0]
        if debug_config:
            print "notice: searching '%s' for '%s.jam'" % (path, basename)
            if found:
                print "notice: loading %s.jam from %s" % (basename, found)

        manager.projects().load_standalone(basename, found)

# FIXME: dummy is needed because calling a rule from jam with
# any parameters still passes on empty list.
def main(dummy):

    global argv
    global ignore_config
    global debug_config
    
    argv = bjam.variable("ARGV")
    boost_build_path = bjam.variable("BOOST_BUILD_PATH")

    engine = Engine()

    global_build_dir = get_string_option("build-dir")
    debug_config = get_boolean_option("debug-configuration")
    
    manager = Manager(engine, global_build_dir)

    # Check if we can load 'test-config.jam'. If we can, load it and
    # ignore user configs.
    
    test_config = glob(boost_build_path, ["test-config.jam"])
    if test_config:
        test_config = test_config[0]

    if test_config:
        if debug_config:
            print "notice: loading testing-config.jam from '%s'" % test_config
            print "notice: user-config.jam and site-config.jam will be ignored"

        manager.projects().load_standalone("test-config", test_config)


    ignore_config = test_config or get_boolean_option("ignore-config")
    user_path = home_directories() + boost_build_path

    site_path = ["/etc"] + user_path
    if bjam.variable("OS") in ["NT", "CYGWIN"]:
        site_path = [os.environ("SystemRoot")] + user_path

    load_config(manager, "site-config", site_path)

    user_config_path = get_string_option("user-config")
    if not user_config_path:
        user_config_path = os.environ.get("BOOST_BUILD_USER_CONFIG")

    if user_config_path:
        if debug_config:
            print "Loading explicitly specifier user configuration file:"
            print "    %s" % user_config_path
            
        manager.projects().load_standalone("user-config", user_config_path)

    else:
        load_config(manager, "user-config", user_path)
        

# FIXME:
## #
## # Autoconfigure toolsets based on any instances of --toolset=xx,yy,...zz or
## # toolset=xx,yy,...zz in the command line
## #
## local option-toolsets = [ regex.split-list [ MATCH ^--toolset=(.*) : $(argv) ] : "," ] ;
## local feature-toolsets = [ regex.split-list [ MATCH ^toolset=(.*) : $(argv) ] : "," ] ;

## # if the user specified --toolset=..., we need to add toolset=... to
## # the build request
## local extra-build-request ;

    extra_build_request = []

## if ! $(ignore-config)
## {
##     for local t in $(option-toolsets) $(feature-toolsets)
##     {
##         # Parse toolset-version/properties
##         local (t-v,t,v) = [ MATCH (([^-/]+)-?([^/]+)?)/?.* : $(t) ] ;
##         local toolset-version = $((t-v,t,v)[1]) ;
##         local toolset = $((t-v,t,v)[2]) ;
##         local version = $((t-v,t,v)[3]) ;

##         if $(debug-config)
##         {
##             ECHO notice: [cmdline-cfg] Detected command-line request for 
##               $(toolset-version): toolset= \"$(toolset)\" "version= \""$(version)\" ;
##         }

##         local known ;

##         # if the toolset isn't known, configure it now.
##         if $(toolset) in [ feature.values <toolset>  ]
##         {
##             known = true ;
##         }

##         if $(known) && $(version) 
##           && ! [ feature.is-subvalue toolset : $(toolset) : version : $(version) ]
##         {
##             known = ;
##         }

##         if ! $(known)
##         {
##             if $(debug-config)
##             {
##                 ECHO notice: [cmdline-cfg] toolset $(toolset-version) 
##                   not previously configured; configuring now ; 
##             }
##             toolset.using $(toolset) : $(version) ;
##         }
##         else
##         {
##             if $(debug-config)
##             {
##                 ECHO notice: [cmdline-cfg] toolset $(toolset-version) already configured ;
##             }
##         }

##         # make sure we get an appropriate property into the build request in
##         # case the user used the "--toolset=..." form
##         if ! $(t) in $(argv)
##             && ! $(t) in $(feature-toolsets) 
##         {
##             if $(debug-config)
##             {
##                 ECHO notice: [cmdline-cfg] adding toolset=$(t) "to build request." ;
##             }
##             extra-build-request += toolset=$(t) ;
##         }
##     }
## }


# FIXME:
## if USER_MODULE in [ RULENAMES ]
## {
##     USER_MODULE site-config user-config ;
## }

    if get_boolean_option("version"):
        # FIXME: Move to a separate module. Include bjam
        # verision.
        print "Boost.Build M15 (Python port in development)"
        sys.exit(0)

    boost.build.tools.common.init(manager)        

    # We always load project in "." so that 'use-project' directives has
    # any chance of been seen. Otherwise, we won't be able to refer to
    # subprojects using target ids.

    current_project = None
    projects = manager.projects()
    if projects.find(".", "."):
        current_project = projects.target(projects.load("."))

    # FIXME: revive this logic, when loading of gcc works
    if not feature.values("<toolset>") and not ignore_config and 0:
        default_toolset = "gcc" ;
        if bjam.variable("OS") == "NT":
            default_toolset = "msvc"
               
        print "warning: No toolsets are configured." ;
        print "warning: Configuring default toolset '%s'" % default_toolset
        print "warning: If the default is wrong, you may not be able to build C++ programs."
        print "warning: Use the \"--toolset=xxxxx\" option to override our guess."
        print "warning: For more configuration options, please consult"
        print "warning: http://boost.org/boost-build2/doc/html/bbv2/advanced/configuration.html"

        projects.project_rules().using([default_toolset])

    (target_ids, properties) = boost.build.build.build_request.from_command_line(
        argv[1:] + extra_build_request)

    if properties:
        expanded = boost.build.build.build_request.expand_no_defaults(properties)
        xexpanded = []
        for e in expanded:
            xexpanded.append(property_set.create(feature.split(e)))
        expanded = xexpanded
    else:
        expanded = property_set.empty()

    targets = []
    
    clean = get_boolean_option("clean")
    cleanall = get_boolean_option("clean-all")
    

    bjam_targets = []

    # Given a target id, try to find and return corresponding target.
    # This is only invoked when there's no Jamfile in "."
    # This code somewhat duplicates code in project-target.find but we can't  reuse
    # that code without project-targets instance.
    def find_target (target_id):
        split = target_id.split("//")
        pm = None
        if len(split) > 1:
            pm = projects.find(split[0], ".")
        else:
            pm = projects.find(target_id, ".")

        result = None
        if pm:
            result = projects.target(pm)

        if len(split) > 1:
            result = result.find(split[1])

    if not current_project and not target_ids:
        print "error: no Jamfile in current directory found, and no target references specified."
        sys.exit(1)

    for id in target_ids:
        if id == "clean":
            clean = 1
        else:
            t = None
            if current_project:
                t = current_project.find(id, no_error=1)
            else:
                t = find_target(id)

            if not t:
                print "notice: could not find main target '%s'" % id
                print "notice: assuming it's a name of file to create " ;
                bjam_targets.append(id)
            else:
                targets.append(t)

    if not targets:
        targets = [projects.target(projects.module_name("."))]
    
    virtual_targets = []

    # Virtual targets obtained when building main targets references on
    # the command line. When running
    #
    #   bjam --clean main_target
    #
    # we want to clean the files that belong only to that main target,
    # so we need to record which targets are produced.
    results_of_main_targets = []

    global command_line_free_features
    for p in expanded:
        command_line_free_features = property_set.create(p.free())
        
        for t in targets:
            g = t.generate(p)
            if not isinstance(t, ProjectTarget):
                results_of_main_targets.extend(g.targets())
            virtual_targets.extend(g.targets())

## # The cleaning is tricky. Say, if
## # user says: 
## #
## #    bjam --clean foo
## #
## # where 'foo' is a directory, then we want to clean targets
## # which are in 'foo' or in any children Jamfiles, but not in any
## # unrelated Jamfiles. So, we collect the list of project under which
## # cleaning is allowed.
## #

## local projects-to-clean ;
## local targets-to-clean ;
## if $(clean) || $(clean-all)
## {    
##     for local t in $(targets)
##     {
##         if [ class.is-a $(t) : project-target ]
##         {
##             projects-to-clean += [ $(t).project-module ] ;
##         }       
##     }
    
##     local subvariants ;
##     for local t in $(results-of-main-targets)
##     {
##         # Don't include roots or sources.
##         targets-to-clean += [ virtual-target.traverse $(t) ] ;
##     }
##     targets-to-clean = [ sequence.unique $(targets-to-clean) ] ;        
## }

## # Returns 'true' if 'project' is a child of 'current-project',
## # possibly indirect, or is equal to 'project'.
## # Returns 'false' otherwise.
## rule is-child ( project )
## {
##     if ! $(.is-child.$(project))
##     {
##         local r = false ;
##         if $(project) in $(projects-to-clean)
##         {            
##             r = true ;
##         }
##         else 
##         {
##             local parent = [ project.attribute $(project) parent-module ] ;
##             if $(parent) && $(parent) != user-config
##             {
##                 r = [ is-child $(parent) ] ;
##             }            
##         }       
        
##         .is-child.$(project) = $(r) ;
##     }
    
##     return $(.is-child.$(project)) ;    
## }


    actual_targets = []
    for t in virtual_targets:
        actual_targets.append(t.actualize())


    bjam.call("NOTFILE", "all")
    bjam.call("DEPENDS", "all", actual_targets)

    if bjam_targets:
        bjam.call("UPDATE", ["<e>%s" % x for x in bjam_targets])
    elif cleanall:
        bjam.call("UPDATE", "clean-all")
    elif clean:
        pass
## FIXME:
## Need to revive virtual-target.all-targets
##     local to-clean ;
##     for local t in [ virtual-target.all-targets ]
##     {
##         local p = [ $(t).project ] ;

##         # Remove only derived targets.
##         if [ $(t).action ]
##         {                    
##             if $(t) in $(targets-to-clean)
##               || [ is-child [ $(p).project-module ] ] = true
##               {
##                   to-clean += $(t) ;
##               }        
##         }        
##     }
##     local to-clean-actual ;
##     for local t in $(to-clean)
##     {
##         to-clean-actual += [ $(t).actualize ] ;
##     }
##     common.Clean clean : $(to-clean-actual) ;
##     UPDATE clean ;        

    else:
        bjam.call("UPDATE", "all")        
