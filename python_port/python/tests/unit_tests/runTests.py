# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import sys
import os.path
import unittest

import helpers

if __name__ == '__main__':

    if len (sys.argv) > 1:
        test_modules = sys.argv [1:]
    else:
        test_modules = [
            'test_virtual_target',
            'test_feature',
            'test_utility',
            'test_property',
            'test_type',
            'test_scanner',
            'test_toolset',
            'test_targets',
            'test_make',
            'test_property_set',
            'test_set',
            'test_action',
            'test_build_request',
            'test_builtin',
            'test_generators',
            'test_gcc',
            'test_order',
            'test_sequence'
        ]
    
    suite = unittest.TestSuite ()
    
    for module in test_modules:
        suite.addTest (unittest.defaultTestLoader.loadTestsFromName (module))

    unittest.TextTestRunner ().run (suite)
