# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.tools.make import *
from boost.build.build.targets import ProjectTarget
from boost.build.manager import Manager
from boost.build.engine.log_engine import *
from boost.build.build.project import ProjectModule
from boost.build.build import feature, property_set, action

class RuleRecorder:
    def __init__ (self):
        self.entries_ = []

    def make_rule (self, manager, target, sources, properties):
        self.entries_.append ((target, sources, properties))
        
    def entries (self): return self.entries_



class TestMake (unittest.TestCase):

    def setUp (self):
        helpers.reset ()

        self.manager_ = Manager (LogBuildSystem ())

        feature.feature ('a', ['A1', 'A2', 'A3'], [])
        feature.feature ('b', [], ['free'])
        feature.feature ('c', ['C'], ['propagated', 'optional', 'dependency'])
        feature.feature ('d', ['D'], ['propagated', 'optional'])
        feature.feature ('e', ['E'], ['incidental'])

    def test_construct (self):
        module = self.manager_.projects ().create ('.')
        name = 'MakeTarget'
        project = ProjectTarget ('Project', module, None, [], [])
        sources = []
        requirements = []
        recorder = RuleRecorder ()
        action.register ('make_rule', recorder.make_rule, '')
        default_build = []
        target = MakeTarget (project, name, sources, requirements, 'make_rule', default_build)
        
        construct_name = 'Target'
        source_targets = []
        properties = property_set.empty ()
        virtual_targets = target.construct (construct_name, source_targets, properties)
        # TODO: finished this
        
    def test_generate (self):
        recorder = RuleRecorder ()
        result = self.__doGenerate (recorder)
        
        build_properties = result.usage_requirements ()
        virtual_targets = result.targets ()
        self.assertEqual (property_set.empty (), build_properties)
        self.assertEqual (1, len (virtual_targets))
        vt = virtual_targets [0]
        self.assertEqual ('MakeTarget', vt.name ())

    # TODO: is this needed here? This is a test of the virtual targets.
    def test_actualize (self):
        recorder = RuleRecorder ()
        result = self.__doGenerate (recorder)
        
        virtual_targets = result.targets ()
        self.assertEqual (1, len (virtual_targets))
        virtual_target = virtual_targets [0]

        actual_targets = virtual_target.actualize ()
        expected = [(['<p./bin/>MakeTarget'], ['<l.>test_make/x.cpp'], ['<a>A1', '<b>B1', '<b>B2', '<e>E'])]
        self.assertEqual (expected, recorder.entries ())

    def test_make_rule (self):
        recorder = RuleRecorder ()

        module = self.manager_.projects ().create ('.')
        
        sources = ['test_make/x.cpp']
        make_rule = recorder.make_rule
        make (module, 'MakeTarget', sources, recorder.make_rule, ['<a>A1', '<b>B1', '<e>E'])
        
    def __doGenerate (self, recorder):
        module = self.manager_.projects ().create ('.')
        name = 'MakeTarget'
        project = ProjectTarget ('Project', module, None, [], [])
        sources = ['test_make/x.cpp']
        requirements = property_set.create (['<a>A1', '<b>B1', '<e>E'])
        make_rule = recorder.make_rule
        action.register ('my_make_rule', make_rule, [])

        default_build = property_set.create ([])
        target = MakeTarget (project, name, sources, requirements, 'my_make_rule', default_build)

        ps = property_set.create (['<a>A2', '<b>B2'])
        return target.generate (ps)

######################################################################
if __name__ == '__main__': unittest.main ()
