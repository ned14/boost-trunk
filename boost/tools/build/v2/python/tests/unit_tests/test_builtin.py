# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.tools import builtin
from boost.build.build import feature
from boost.build.exceptions import *

class TestBuiltin (unittest.TestCase):

    def setUp (self):
        helpers.reset ()
        
    def test_variant (self):
        feature.feature ('variant', [], ['implicit', 'composite', 'propagated', 'symmetric'])
        feature.feature ('<a>', ['A1', 'A2'], ['free'])
        feature.feature ('<b>', ['B1', 'B2'])
        builtin.variant ('v1', ['<a>A1', '<b>B1'])
        builtin.variant ('v2', ['<a>A2', '<b>B2'])
        self.assertEqual (['v1', 'v2'], feature.values ('<variant>'))
        self.assertEqual (['<variant>v1', '<a>A1', '<b>B1'], feature.expand_composites (['<variant>v1']))
        self.assertEqual (['<variant>v2', '<a>A2', '<b>B2'], feature.expand_composites (['<variant>v2']))

        builtin.variant ('v11', ['v1'], ['<b>B2'])
        self.assertEqual (['<variant>v11', '<a>A1', '<b>B2'], feature.expand_composites (['<variant>v11']))

        builtin.variant ('v12', ['v1'], ['<a>A2'])
        self.assertEqual (['<variant>v12', '<a>A1', '<b>B1', '<a>A2'], feature.expand_composites (['<variant>v12']))
        
######################################################################
if __name__ == '__main__': unittest.main ()
