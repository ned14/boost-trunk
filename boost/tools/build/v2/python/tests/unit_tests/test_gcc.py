# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.tools import builtin
from boost.build.build import feature
from boost.build.exceptions import *
import boost.build.tools.types

class TestGcc (unittest.TestCase):

    def setUp (self):
        helpers.reset ()
        builtin.register_globals ()
        boost.build.tools.types.register_all ()
        
    def test_init (self):
        from boost.build.tools import gcc
        
        self.assert_ ('gcc' in feature.values ('<toolset>'))
        gcc.init ()
        
######################################################################
if __name__ == '__main__': unittest.main ()
