# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import property_set, property, feature
from boost.build.exceptions import *

def setup_features ():
    feature.feature ('a', ['A1', 'A2', 'A3'], [])
    feature.feature ('b', [], ['free'])
    feature.feature ('c', ['C'], ['propagated', 'optional', 'dependency'])
    feature.feature ('d', ['D'], ['propagated', 'dependency'])
    feature.feature ('e', ['E'], ['incidental'])
    
class TestPropertySet (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

        setup_features ()

    def test_init (self):
        raw = ['<a>A1', '<b>B1', '<c>C', '<d>D', '<e>E', '<a>A2', '<d>D:<a>A3']
        ps = property_set.PropertySet (raw)
        
        self.assertEqual (raw, ps.raw ())
        self.assertEqual (['<a>A1', '<c>C', '<d>D', '<a>A2', '<d>D:<a>A3'], ps.base ())
        self.assertEqual (['<b>B1'], ps.free ())
        self.assertEqual (['<c>C', '<d>D', '<d>D:<a>A3'], ps.dependency ())
        self.assertEqual (['<a>A1', '<b>B1', '<e>E', '<a>A2'], ps.non_dependency ())
        self.assertEqual (['<d>D:<a>A3'], ps.conditional ())
        self.assertEqual (['<a>A1', '<b>B1', '<c>C', '<d>D', '<e>E', '<a>A2'], ps.non_conditional ())
        self.assertEqual (['<e>E'], ps.incidental ())
    
    def test_refine (self):
        ps = property_set.PropertySet (['<a>A1', '<c>C', '<d>D', '<e>E', '<d>D:<a>A3'])
        requirements = property_set.PropertySet (['<a>A2', '<c>C', '<b>B2'])
        self.assertEqual (['<a>A2', '<b>B2', '<c>C', '<d>D', '<d>D:<a>A3', '<e>E'], 
            ps.refine (requirements).raw ())

    def test_create (self):
        ps = property_set.create (['<e>E', '<c>C', '<a>A1', '<e>E', '<c>C', '<d>D', '<d>D:<a>A3'])
        self.assertEqual (['<a>A1', '<c>C', '<d>D', '<d>D:<a>A3', '<e>E'], ps.raw ())

    def test_create_with_validation (self):
        feature.feature ('f', ['F'], ['implicit'])
        ps = property_set.create_with_validation (['<a>A1', 'F'])
        self.assertEqual (['<a>A1', '<f>F'], ps.raw ())
        
        self.assertRaises (InvalidFeature, property_set.create_with_validation, ['<a>A1', '<dummy>'])
        
    def test_add (self):
        # TODO: implement this
        pass
    
    def test_add_raw (self):
        # TODO: implement this
        pass
    
    def test_add_defaults (self):
        ps = property_set.empty ()
        self.assertEqual ([], ps.raw ())

        ps = ps.add_defaults ()
        self.assertEqual (['<a>A1', '<d>D', '<e>E'], ps.raw ())

        # Make sure it didn't touch the original
        ps = property_set.empty ()
        self.assertEqual ([], ps.raw ())

    def test_target_path (self):
        # TODO: implement this
        pass

    def evaluate_conditionals (self):
        # TODO: implement this
        pass

    def test_get (self):
        ps = property_set.create (['<e>E', '<c>C', '<a>A1', '<a>A2', '<c>C', '<d>D', '<d>D:<a>A3'])
        self.assertEqual (['E'], ps.get ('<e>'))
        self.assertEqual (['A1', 'A2'], ps.get ('<a>'))
        self.assertEqual (['D', 'D:<a>A3'], ps.get ('<d>'))

######################################################################
if __name__ == '__main__': unittest.main ()
