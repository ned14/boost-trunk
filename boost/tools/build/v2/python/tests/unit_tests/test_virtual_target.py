# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build.virtual_target import *

class TestVirtualTargetRegistry (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

    def test_from_file (self):
        # TODO: implement this
        pass

    def test_traverse (self):
        # TODO: implement this
        pass


class TestSubvariant (unittest.TestCase):

    def setUp ():
        helpers.reset ()
 
######################################################################
if __name__ == '__main__': unittest.main ()
