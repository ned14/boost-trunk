# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.util.set import *

class TestSet (unittest.TestCase):
    
    def test_different (self):
        self.assertEqual ([0, 1, 4, 6, 8, 9], difference ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], [2, 3, 5, 7]))
        
    def test_intersection (self):
        self.assertEqual ([2, 5, 7], intersection ([0, 1, 2, 4, 5, 6, 7, 8, 9], [2, 3, 5, 7]))

    def test_contains (self):
        self.assert_ (contains ([1, 2, 3], [1, 2, 3, 4]))
        self.assert_ (not contains ([1, 2, 5], [1, 2, 3, 4]))

    def test_equal (self):
        self.assert_ (equal ([1, 2, 3], [2, 3, 1]))
        self.assert_ (not equal ([1, 2, 3], [2, 3, 4, 1]))

######################################################################
if __name__ == '__main__': unittest.main ()
