# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build.targets import *
from boost.build.build.project import ProjectModule
from boost.build.manager import Manager
from boost.build.exceptions import *

class TestTargetRegistry (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

    def test_main_target_alternative (self):
        # TODO: implement this
        pass
        
    def test_main_target_sources (self):
        # TODO: implement this
        pass
        
class TestBasicTarget (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

    def test_init (self):
        manager = Manager (None)
        name = 'target'
        module = manager.projects ().create ('.')
        project = ProjectTarget ('project', module, None, [], [])
        sources = ['a.cpp', 'b.cpp']
        target = BasicTarget (name, project, sources)
        self.assertEqual (name, target.name ())
        self.assertRaises (InvalidSource, BasicTarget, name, project, sources + ['<a>A'])
        
    def test_sources (self):
        # TODO: implement this
        pass

    def test_resolve_reference (self):
        # TODO: implement this
        pass

    def test_generate (self):
        # TODO: implement this
        pass
        
    def test_common_properties (self):
        # TODO: implement this
        pass


class TestProjectTarget (unittest.TestCase):

    def setUp (self):
        helpers.reset ()
    
    def test_find (self):
        # TODO: implement this
        pass


class TestTypedTarget (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()
        self.registry_ = TargetRegistry ()

    def test_create (self):
        manager = Manager (None)
        module = manager.projects ().create ('.')
        project = ProjectTarget ('project', module, None, [], [])

        feature.feature ('<a>', [], ['free'])
        
        type = 'EXE'
        name = 'test_target'
        sources = []
        requirements = [ '<a>AAA' ]
        default_build = []
        usage_requirements = []
        
        target = self.registry_.create_typed_target (type, project, name, sources, 
                     requirements, default_build, usage_requirements)
                     
        self.assertEqual ('test_target', target.name ())
        self.assertEqual (requirements, target.requirements ().raw ())

######################################################################
if __name__ == '__main__': unittest.main ()
