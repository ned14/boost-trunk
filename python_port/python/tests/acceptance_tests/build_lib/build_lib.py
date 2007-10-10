# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import sys

import os.path
sys.path.append (os.path.split (os.getcwd ()) [0])

import helpers
from boost.build.tools.make import *
from boost.build.build.project import ProjectModule
from boost.build.manager import Manager
from boost.build.engine.bjam import *
import boost.build.tools.builtin
from boost.build.util.logger import TextLogger

def run ():

    # TODO: emulate user/site config
    from boost.build.tools import gcc
    gcc.init ()

    from boost.build.tools import darwin
    darwin.init ()

    engine = BjamBuildSystem ()
    manager = Manager (engine)
#    manager.set_logger (TextLogger ())
    
    project = manager.projects ().create (os.getcwd ())
    
    project.lib ('direct_lib', ['x.cpp', 'y.cpp', 'k.c'])
    project.exe ('direct_exe', ['e.cpp', 'direct_lib'])
    project.exe ('direct_exe_lib_property', ['e.cpp'], ['<library>direct_lib', '<location-prefix>via_property'])

#    manager.construct (['<link-runtime>static', 'debug', 'release', '<define>DEF', '<user-interface>gui', '<user-interface>console'], [project.target ()])
#    manager.construct (['debug', '<location-prefix>test'], [project.target ()])
#    manager.construct (['debug'], [project.target ()])
#    manager.construct (['<toolset>darwin', '<link>static'])
    manager.construct (['<toolset>darwin'])
#    manager.construct ()

    print engine.generate ()
    engine.build ()
                      

if __name__ == '__main__':
    
    run ()
