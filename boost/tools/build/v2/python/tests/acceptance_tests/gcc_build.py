# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import sys

import helpers
from boost.build.tools.make import *
from boost.build.build.project import ProjectModule
from boost.build.manager import Manager
from boost.build.engine.bjam import *
import boost.build.tools.builtin
import boost.build.tools.gcc

def run ():
    engine = BjamBuildSystem ()
    manager = Manager (engine)
    
    project = manager.projects ().create ('.')
    
    sources1 = ['x.cpp']
    requirements1 = ['<define>ABC']
    project.obj ('x.obj', sources1, requirements1)

    sources2 = ['y.cpp']
    requirements2 = ['<define>YUI']
    project.obj ('y.obj', sources2, requirements2)

    manager.construct (['<link-runtime>static', 'debug', 'release', '<define>DEF', '<user-interface>gui', '<user-interface>console'], [project.target ()])
    manager.construct (['debug', '<location-prefix>test'], [project.target ()])

    print engine.generate ()
    engine.build ()
                      

if __name__ == '__main__':
    
    run ()
