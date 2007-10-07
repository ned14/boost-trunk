# Copyright Vladimir Prus 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# This module implements top-level logic when V2/Python is used under bjam.

import bjam
import sys
from boost.build.engine.engine import Engine
from boost.build.manager import Manager
from boost.build.build.loader import ProjectLoader
import boost.build.tools.builtin
from boost.build.build import property_set

import boost.build.tools.common

def main(argv):    
    print "Starting Boost.Build V2/Python"
    sys.argv = argv

    engine = Engine()
    manager = Manager(engine)

    boost.build.tools.common.init(manager)
    
    loader = ProjectLoader(manager.projects());
    project_here = loader.load('.')

    result = project_here.target().generate(property_set.empty())

    actual_targets = []
    for t in result.targets():
        actual_targets.append(t.actualize())
        
    bjam.call("set-top-level-targets", actual_targets)
    return []
    
    
