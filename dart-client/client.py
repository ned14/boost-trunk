#!/usr/bin/env python
#
#  Copyright (C) 2007 Troy Straszheim <troy@resophonic.com>
#
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#    http://www.boost.org/LICENSE_1_0.txt
#
#
#  Continuous/nightly testing script.
#
#  This script runs continuous and nightly tests in a continuous loop.
#
#  'client.py checkout' will check out the necessary source and set up
#  the necessary directories.
#
#  'client.py run'  will run the tests in an infinite loop.
#
#  The script runs the test which was run least recently.  It
#  determines how long it was since each test run with the *_dt(time)
#  functions in conf.py.  Nightly tests are run only once per day
#  because nightly_dt returns zero if its time argument occurs on the
#  same day as the current time.
#

import sys
import os.path
import time
import subprocess
from datetime import datetime, timedelta

configfile = "conf.py"

#
# Build class holds the information about each build.
#
# build_variant:  as specified in build_variants in the configuration file.
# ctest_variant:  as specified in ctest_variants in the configuration file (continuous/nightly).  
# revision:       svn revision of the local checkout as of the last time this test was run.
# last_start:     time this test was last started. 
#
class Build:
    def dir(self):
        return os.path.join(self.id, self.build_variant, self.ctest_variant)

    def srcdir(self):
        return os.path.join(self.dir(), "src")
    
    def builddir(self):
        return os.path.join(self.dir(), "build")

    def __str__(self):
        return self.id + "/" + self.build_variant + "/" + self.ctest_variant + " last_start @ " + str(self.last_start)

    def __init__(self, id_, build_variant_, ctest_variant_):
        self.id = id_
        self.build_variant = build_variant_
        self.ctest_variant = ctest_variant_
        self.last_start = datetime.now()
        
#
# svn checkout "url" to local directory "srcdir"
#
def svn_checkout(url, srcdir):
    try:
        retcode = subprocess.call([svn, "co", url, srcdir])
        if retcode < 0:
            print >>sys.stderr, "Child was terminated by signal ", -retcode
        else:
            print >>sys.stderr, "Child returned", retcode
    except OSError, e:
        print >> sys.stderr, "Execution failed:", e

#
# return the build that was run longest ago
# as reported by the *_dt functions in the config file.
#
def nextbuild(builds):
    nextbuild = Build('none', 'none', 'none')
    nextbuild_deltat = timedelta.min

    for b in builds:
        b_dt = ctest_variants[b.ctest_variant][1](b.last_start)
        if b_dt > nextbuild_deltat:
            nextbuild_deltat = b_dt
            nextbuild = b
    return nextbuild
    
#
# Create list of builds (used in initialization)
#
def initbuilds():
    builds = []
    for id in urls:
        for bv in build_variants:
            for cv in ctest_variants:
                build = Build(id, bv, cv)
                builds.append(build)
                print ">>> info: Build " + str(build)
    return builds

#
# print error message
#
def print_error(msg, cmd):
    sys.stderr.write('%s: Error: %s\n' % (cmd, msg))
    sys.exit(1)

#
# read the configuration file "configfile" into the current environment
#
def read_conf():
    if os.path.exists(configfile):
        execfile(configfile, globals())
    else:
        print_error("Config file '" + configfile + "' not found, run " + sys.argv[0] + " init first.", sys.argv[0])
        exit(1)

#
# take path to build/src directory and return absolute path
#
def absolute_path(p):
    return os.path.join(topdir, prefix, p)

#
# run cmake (but not make) for each build directory
#
def initialize_builds(argv):
    """
    Configures each build with cmake."""
    print "Making build directories..."
    for build in initbuilds():
        buildpath = absolute_path(build.builddir())
        srcpath = absolute_path(build.srcdir())
        try:
            if not os.path.isdir(buildpath):
                os.makedirs(buildpath)
                print ">>> Initializing " + buildpath
        except Exception, e:
            print "Directory %s exists, not creating (%s)" % (buildpath, str(e))
        os.chdir(buildpath)
        cmd = cmake + " " + " ".join(build_variants[build.build_variant]) + " " + srcpath
        print ">>> Executing " + cmd
        os.system(cmd)
    
#
# clean prefix and all subdirectores
#
def clean(argv):
    """
    Wipes prefix directory.""" 
    print "Obliterating [prefix] directories"
    for root, dirs, files in os.walk(prefix, topdown=False):
        for name in files:
            os.remove(os.path.join(root, name))
        for name in dirs:
            print "- ", os.path.join(root, name)
            os.rmdir(os.path.join(root, name))
#
# Create the necessary directories for the various build/test variants
# and checkout the source, but don't run cmake.
#
def checkout(argv):
    """
    Runs svn checkout for each build/variant."""
    for build in initbuilds():
        srcdir = absolute_path(build.srcdir())
        try:
            os.mkdir(srcdir)
        except:
            print "Directory %s exists, not creating." % build.id
            
        print "Checking out " + build.id
        svn_checkout(urls[build.id], srcdir)

#
#  Do the builds in an infinite loop.
#
def run(args):
    """
    Runs ctest over all builds/variants in a loop."""
    builds = initbuilds()
    while True:
        build = nextbuild(builds)
        print ">>> Starting " + str(build)
        srcdir = absolute_path(build.srcdir())
        build.last_start = datetime.now()
        os.chdir(absolute_path(build.builddir()))
        cmd = ctest + " " + " ".join(ctest_variants[build.ctest_variant][0])
        os.system(cmd)
        print ">>> Sleeping %s seconds..." % interbuild_sleep
        time.sleep(interbuild_sleep)

#
#  Do everything required to get up and running, clean.
#
def bootstrap(argv):
    """
    Does everything from scratch.  Wipes the source directory, checks
    out the source, initializes each build, runs ctest in a loop."""
    clean(argv)
    checkout(argv)
    initialize_builds(argv)
    run(argv)

def help(argv):
    """
    Prints this help."""
    print "Usage:\n%s <command>" % argv[0]
    print "See file %s for specific configuration." % configfile
    print "Available commands:"
    for (name, fn) in action_mapping.iteritems():
        print "  %s: %s" % (name, fn.__doc__)
#
# The main routine
#
topdir = '?'
def main(argv):
    globals()['topdir'] = os.getcwd()
    if argv[1] == "init":
        init(argv)
    elif not action_mapping.has_key(argv[1]):
        print_error("Command " + argv[1] + " not found", argv[0])
    else:
        read_conf()
        action_mapping[argv[1]](argv)

#
# map command-line strings to functions
#
action_mapping = {
    'help' : help,
    'checkout' : checkout,
    'clean' : clean,
    'bootstrap' : bootstrap,
    'initialize_builds' : initialize_builds,
    'run' : run,
    }

#
# standard python main-hook.
#
if __name__ == "__main__":
    if len(sys.argv) != 2:
        help(sys.argv)
    main(sys.argv)
