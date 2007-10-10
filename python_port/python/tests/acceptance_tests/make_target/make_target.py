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

def make_rule (manager, target, sources, properties):
    pass

action.register ('my_make_rule', make_rule, ['cp $(>) $(<)'])

def run ():
    engine = BjamBuildSystem ()
    manager = Manager (engine)
    
    project = manager.projects ().create ('.')
    
    sources1 = ['x.cpp']
    requirements1 = ['<define>ABC']
    project.make ('Make1', sources1, 'my_make_rule', requirements1)

    sources2 = ['y.cpp']
    requirements2 = ['<define>YUI']
    project.make ('Make2', sources2, 'my_make_rule', requirements2)

    manager.construct (['<link-runtime>static', 'debug', 'release', '<define>DEF', '<user-interface>gui', '<user-interface>console'], [project.target ()])
    manager.construct (['debug', '<location-prefix>test'], [project.target ()])

    print engine.generate ()
    engine.build ()
                      

if __name__ == '__main__':
    
    run ()
