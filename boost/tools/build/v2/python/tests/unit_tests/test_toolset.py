# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import toolset, feature
from boost.build.manager import Manager
from boost.build.engine.engine import BuildSystem
from boost.build.engine.log_engine import *

class TestToolset (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

        self.manager = Manager (LogBuildSystem ())
        
    def test_using (self):
        # TODO: implement this
        pass
        
    def test_normalize_condition (self):
        feature.feature ('toolset', ['gcc'], ['implicit'])
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
        toolset.set_target_variables (self.manager, 'gcc.compile', ['TargetA'], ['<optimization>off'])
        toolset.set_target_variables (self.manager, 'gcc.compile', ['TargetA'], ['<optimization>space'])
        toolset.set_target_variables (self.manager, 'gcc.compile', ['TargetB'], ['<inlining>full'])
        toolset.set_target_variables (self.manager, 'gcc.compile', ['TargetB'], ['<define>A', '<define>B'])

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

    def __setup_features_and_flags (self):
        feature.feature ('optimization', ['off', 'space', 'speed'], [])
        feature.feature ('inlining', ['off', 'full'], [])
        feature.feature ('debug-symbols', ['on', 'off'], [])
        feature.feature ('define', [], ['free'])

        toolset.flags ('gcc.compile', 'OPTIONS', '<optimization>off', ['-O0'])
        toolset.flags ('gcc.compile', 'OPTIONS', '<optimization>speed', ['-O3'])
        toolset.flags ('gcc.compile', 'OPTIONS', '<inlining>full', ['-finline-functions', '-Wno-inline'])

        toolset.flags ('gcc.compile', 'DEFINES', '<define>', [])

######################################################################
if __name__ == '__main__': unittest.main ()
