# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import toolset, feature
from boost.build.tools import builtin
from boost.build.manager import Manager
from boost.build.engine.engine import BuildSystem
from boost.build.engine.log_engine import *

class TestToolset (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()
        builtin.register_globals ()

        self.manager = Manager (LogBuildSystem ())
        
    def test_using (self):
        # TODO: implement this
        pass
        
    def test_normalize_condition (self):
        feature.extend_feature ('toolset', ['gcc'])
        feature.subfeature ('toolset', 'gcc', 'version', ['3.2'])

        self.assertEqual (['<toolset>gcc/<toolset-gcc:version>3.2'], toolset.normalize_condition (['<toolset>gcc-3.2']))

    def test_flags (self):
        # TODO: implement this
        pass

    def test_find_property_subset (self):
        p = ['<b>0', '<c>1', '<d>2', '<e>3', '<f>4']
        self.assertEqual ('<c>1/<d>2/<e>3', toolset.find_property_subset (['<c>1/<d>2/<e>3', '<a>0/<b>0/<c>1', '<d>2/<e>5', '<a>9'], p))
        self.assertEqual (None, toolset.find_property_subset (['<a>0/<b>0/<c>9/<d>9/<e>5', '<a>9'], p))

    def test_set_target_variables (self):
        
        self.__setup_features_and_flags ()
        toolset.set_target_variables (self.manager, 'dummy_compile', ['TargetA'], ['<optimization>off'])
        toolset.set_target_variables (self.manager, 'dummy_compile', ['TargetA'], ['<optimization>space'])
        toolset.set_target_variables (self.manager, 'dummy_compile', ['TargetB'], ['<inlining>full'])
        toolset.set_target_variables (self.manager, 'dummy_compile', ['TargetB'], ['<define>A', '<define>B'])

        variables = {
            'TargetA': { 
                'OPTIONS': ['-O0']
                },
            'TargetB': { 
                'OPTIONS': ['-finline-functions', '-Wno-inline'],
                'DEFINES': ['A', 'B']
                }
            }
        self.assertEqual (variables, self.manager.engine ().variables ())

    def test_register (self):
        self.assert_ (not 'a' in feature.values ('<toolset>'))
        toolset.register ('a')
        self.assert_ ('a' in feature.values ('<toolset>'))
        
    def __setup_features_and_flags (self):
        toolset.flags ('dummy_compile', 'OPTIONS', '<optimization>off', ['-O0'])
        toolset.flags ('dummy_compile', 'OPTIONS', '<optimization>speed', ['-O3'])
        toolset.flags ('dummy_compile', 'OPTIONS', '<inlining>full', ['-finline-functions', '-Wno-inline'])

        toolset.flags ('dummy_compile', 'DEFINES', '<define>', [])

    def test_inherit_generators (self):
        # TODO: implement this
        pass

    def test_inherit_flags (self):
        # TODO: implement this
        pass
        
######################################################################
if __name__ == '__main__': unittest.main ()
