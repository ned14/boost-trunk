# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import type, property_set, feature
from boost.build.engine import *
from boost.build.exceptions import *

class TestType (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()
        
        type.register ('A', ['a'])
        type.register ('B1', ['b1'], 'A')
        type.register ('B2', ['b2'], 'A')
        type.register ('C1', ['c1'], 'B1')
             
    def test_register (self):
        self.assert_ (type.registered ('A'))
        self.assert_ (type.registered ('B1'))
        self.assertEqual (False, type.registered ('Dummy'))
        
        type.validate ('A')
        self.assertRaises (BaseException, type.validate, 'Dummy')
        
    def test_register_suffixes (self):
        type.register_suffixes (['x', 'xx'], 'X')
        type.register_suffixes (['xx'], 'X')
        
        self.assertRaises (BaseException, type.register_suffixes, ['x', 'xx'], 'Y')

    def test_all_bases (self):
        self.assertEqual (['A'], type.all_bases ('A'))
        self.assertEqual (['B1', 'A'], type.all_bases ('B1'))
        self.assertEqual (['C1', 'B1', 'A'], type.all_bases ('C1'))

    def test_all_derived (self):
        self.assertEqual (['A', 'B1', 'C1', 'B2'], type.all_derived ('A'))
        self.assertEqual (['B1', 'C1'], type.all_derived ('B1'))
        self.assertEqual (['C1'], type.all_derived ('C1'))

    def test_is_derived (self):
        self.assert_ (type.is_derived ('A', 'A'))
        self.assert_ (type.is_derived ('B1', 'A'))
        self.assert_ (type.is_derived ('C1', 'A'))
        self.assert_ (not type.is_derived ('C1', 'B2'))
    
    def test_generated_target_suffix (self):
        feature.feature ('x', ['X'])
        feature.feature ('y', ['Y'])

        self.assertEqual ('a', type.generated_target_suffix ('A', property_set.empty ()))
        type.register ('D', [], 'C1')
        self.assertEqual ('c1', type.generated_target_suffix ('D', property_set.empty ()))
        
        type.set_generated_target_suffix ('A', ['<x>X', '<y>Y'], 'axy')
        self.assertEqual ('axy', type.generated_target_suffix ('A', property_set.create (['<x>X', '<y>Y'])))
        self.assertEqual ('a', type.generated_target_suffix ('A', property_set.create (['<x>X'])))
    
    def test_type (self):
        self.assertEqual ('A', type.type ('file.a'))
        self.assertEqual ('A', type.type ('file.a.1.2'))
        self.assertEqual (None, type.type ('file.aaa.1.2'))
        type.register_suffixes (['aa', 'aaa'], 'A')
        self.assertEqual ('A', type.type ('file.aaa.1.2'))
        self.assertEqual (None, type.type ('file'))

######################################################################
if __name__ == '__main__': unittest.main ()
