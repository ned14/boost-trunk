# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.util.sequence import *

class TestSequence (unittest.TestCase):
    
    def test_unique (self):
        self.assertEqual (['a', 'c', 'b'], unique (['a', 'c', 'a', 'c', 'b', 'b']))
    
    def test_select_highest_ranked (self):
        self.assertEqual (['e-3', 'h-3'], select_highest_ranked (['e-1', 'e-3', 'h-3', 'm-2'], ['1', '3', '3', '2']))

######################################################################
if __name__ == '__main__': unittest.main ()
