# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import scanner

class DummyScanner (scanner.Scanner):
    
    def __init__ (self, properties):
        pass
        
class TestScanner (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()
        
    def test_register (self):
        scanner.register (DummyScanner, [])
        self.assert_ (scanner.registered (DummyScanner))
        scanner.get (DummyScanner, [])

######################################################################
if __name__ == '__main__': unittest.main ()
