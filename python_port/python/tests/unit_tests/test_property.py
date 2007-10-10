# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import property, feature
from boost.build.manager import Manager
from boost.build.exceptions import *

class TestPropertyMap (unittest.TestCase):
    
    def setUp (self):
        self.pm = property.PropertyMap ()

        self.pm.insert (['<toolset>gcc'], 'o')
        self.pm.insert (['<toolset>gcc', '<os>NT'], 'obj')
        self.pm.insert (['<toolset>gcc', '<os>CYGWIN'], 'obj')
   
    def test_find (self):
        self.assertEqual ('o', self.pm.find (['<toolset>gcc']))
        self.assertEqual ('obj', self.pm.find (['<toolset>gcc', '<os>NT']))
   
    def test_find (self):
        self.assertRaises (NoBestMatchingAlternative, self.pm.find, ['<toolset>gcc', '<os>NT', '<os>CYGWIN'])

class TestProperty (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()
        
        feature.feature ('a', ['A1', 'A2', 'A3'], [])
        feature.feature ('b', [], ['free'])
        feature.feature ('c', ['C'], ['propagated', 'optional', 'dependency'])
        feature.feature ('d', ['D'], ['propagated', 'dependency'])
        feature.feature ('e', ['E'], ['incidental'])
    
        feature.feature ('toolset', ['gcc'], ['implicit', 'symmetric'])
        feature.subfeature ('toolset', 'gcc', 'version', ['2.95.2', '2.95.3', '2.95.4', '3.0', '3.0.1', '3.0.2'])
        feature.subfeature ('toolset', 'gcc', 'os', ['linux', 'cygwin'], ['optional'])
        feature.subfeature ('toolset', 'gcc', 'cpu', ['x86', 'ppc'], ['optional'])
        feature.feature ('variant', ['debug'], ['implicit', 'composite', 'symmetric'])
        feature.compose ('<variant>debug', ['<define>_DEBUG', '<optimization>off'])
        feature.compose ('<variant>release', ['<define>_NDEBUG', '<optimization>on'])
        
        feature.feature ('define', [], ['free'])
        feature.feature ('optimization', ['on', 'off'], [])
        feature.feature ('rtti', ['on'], [])

    def test_path_order (self):
        self.assertEqual (0, property.path_order ('<define>foo', '<define>foo'))
        self.assertEqual (-1, property.path_order ('debug', '<define>foo'))
        self.assertEqual (1, property.path_order ('<define>foo', 'debug'))
        self.assertEqual (-1, property.path_order ('gcc', 'debug'))
        self.assertEqual (1, property.path_order ('debug', 'gcc'))
        self.assertEqual (-1, property.path_order ('<optimization>on', '<rtti>on'))
        self.assertEqual (1, property.path_order ('<rtti>on', '<optimization>on'))
        
        props = ['<rtti>on', 'gcc', 'debug']
        props.sort (property.path_order)
        self.assertEqual (['gcc', 'debug', '<rtti>on'], props)

    def test_as_path (self):
        self.assertEqual ('debug', property.as_path (['<optimization>off', '<variant>debug']))
        self.assertEqual ('gcc/debug/rtti-off', property.as_path (['<toolset>gcc', '<optimization>off', '<rtti>off', '<variant>debug']))

    def test_refine (self):
        properties = ['<a>A1', '<c>C', '<d>D', '<b>B2', '<e>E', '<d>D:<a>A3']
        requirements = ['<a>A2', '<c>C', '<b>B2']
        self.assertEqual (['<e>E', '<d>D', '<d>D:<a>A3', '<a>A2', '<b>B2', '<c>C', '<a>A2', '<c>C', '<b>B2'], 
            property.refine (properties, requirements))

    def test_translate_paths (self):
        # TODO: implement this
        pass

    def test_validate (self):
        # TODO: implement this
        pass

    def test_expand_subfeatures_in_conditions (self):
        # TODO: implement this
        pass

    def test_make (self):
       self.assertEqual (['<a>A1', '<toolset>gcc'], property.make (['<a>A1', 'gcc']))

    def test_select (self):
        self.assertEqual (['<a>A', '<c>C'], property.select (['<a>', 'c'], ['<a>A', '<b>B', '<c>C']))

    def test_validate_property_sets (self):
        # TODO: implement this
        pass

    def test_evaluate_conditionals_in_context (self):
        # TODO: implement this
        pass

    def test_split_conditional (self):
        self.assertEqual (('<variant>debug,<toolset>gcc', '<inlining>full'), property.split_conditional ('<variant>debug,<toolset>gcc:<inlining>full'))

    def test_change (self):
        properties = ['<a>A1', '<b>B1', '<a>A2', '<b>B2', '<c>C:<a>A3']
        self.assertEqual (['<a>AAA', '<b>B1', '<a>AAA', '<b>B2', '<c>C:<a>A3'], property.change (properties, '<a>', 'AAA'))
        self.assertEqual (['<b>B1', '<b>B2', '<c>C:<a>A3'], property.change (properties, 'a'))

######################################################################
if __name__ == '__main__': unittest.main ()
