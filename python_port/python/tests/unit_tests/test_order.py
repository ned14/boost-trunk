# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.util.order import *

class TestOrder (unittest.TestCase):
    
    def test_different (self):
        c1 = Order ()
        c1.add_pair ('l1', 'l2')
        
        self.assertEqual (['l1', 'l2'], c1.order (['l1', 'l2']))
        self.assertEqual (['l1', 'l2'], c1.order (['l2', 'l1']))
        
        c1.add_pair ('l2', 'l3')
        self.assertEqual (['l1', 'l2'], c1.order (['l2', 'l1']))
        c1.add_pair ('x', 'l2')
        self.assertEqual (['l1', 'l2'], c1.order (['l2', 'l1']))
        self.assertEqual (['l1', 'l2', 'l3'], c1.order (['l2', 'l3', 'l1']))

######################################################################
if __name__ == '__main__': unittest.main ()
