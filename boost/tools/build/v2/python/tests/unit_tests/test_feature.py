# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import sys, os.path, unittest, helpers
######################################################################

from boost.build.build import feature
from boost.build.engine import *
from boost.build.exceptions import *

class TestFeature (unittest.TestCase):
    
    def setUp (self):

        helpers.reset ()
        # Other modules register features, so we must clean this here.
        feature.reset ()

        feature.feature ('toolset', ['gcc'], ['implicit'])
        feature.subfeature ('toolset', 'gcc', 'version', ['2.95.2', '2.95.3', '2.95.4', '3.0', '3.0.1', '3.0.2'])
        feature.subfeature ('toolset', 'gcc', 'os', ['linux', 'cygwin'], ['optional'])
        feature.subfeature ('toolset', 'gcc', 'cpu', ['x86', 'ppc'], ['optional'])

        feature.extend_feature ('toolset', ['msvc'])
        feature.subfeature ('toolset', 'msvc', 'version', ['6.0', '7.0', '7.1'])

        feature.feature ('variant', ['debug', 'release'], ['implicit', 'composite', 'symmetric'])
        feature.compose ('<variant>debug', ['<define>_DEBUG', '<optimization>off'])
        feature.compose ('<variant>release', ['<define>_NDEBUG', '<optimization>on'])
        
        feature.feature ('define', [], ['free'])
        feature.feature ('optimization', ['on', 'off'], [])
        feature.feature ('stdlib', ['native'], [])
        feature.feature ('runtime-link', ['dynamic', 'static'], ['symmetric'])

    def test_add_feature (self):
        feature.reset ()
        feature_f = { 
            'values': ['value1', 'value2'],
            'attributes': ['free'],
            'subfeatures': [],
            'default': 'value1'
            }

        feature.feature ('f', feature_f ['values'], feature_f ['attributes'])
        
        it = feature.enumerate ()
        f = it.next ()[1]
        self.assertRaises (StopIteration, it.next)
        self.assertEqual (feature_f, f)
        
        feature.extend_feature ('f', ['value3', 'value4'])
        feature_f ['values'].extend (['value3', 'value4'])
        self.assertEqual (feature_f, f)

        self.assertRaises (AlreadyDefined, feature.feature, 'f', [], [])
        self.assertRaises (InvalidAttribute, feature.feature, 'x', [], ['implicit', 'free'])
        self.assertRaises (InvalidAttribute, feature.feature, 'y', [], ['propagated', 'free'])
        self.assertRaises (InvalidAttribute, feature.feature, 'foobar', [], ['baz'])

    def test_set_default (self):
        feature.extend_feature ('optimization', ['speed', 'space'])
        feature.set_default ('optimization', 'space')
        self.assertEqual (['<optimization>space'], feature.defaults (['<optimization>']))
        
    def test_compose (self):
        # TODO: implement me
        pass
        
    def test_attributes (self):
        self.assertEqual ([], feature.attributes ('<optimization>'))
        self.assertEqual (['free'], feature.attributes ('<define>'))
        self.assertEqual (['implicit', 'composite', 'symmetric'], feature.attributes ('<variant>'))
        
    def test_valid (self):
        self.assertEqual (True, feature.valid ('<define>'))
        self.assertEqual (False, feature.valid ('<aaa>'))

    def test_validate_feature (self):
        feature.validate_feature ('<optimization>')
        self.assertRaises (InvalidFeature, feature.validate_feature, '<aaa>')

    def test_defaults (self):
        self.assertEqual (['<runtime-link>dynamic', '<optimization>on'], 
            feature.defaults (['<runtime-link>', '<define>', '<optimization>']))

    def test_values (self):
        self.assertEqual (['on', 'off'], feature.values ('<optimization>'))

    def test_is_implicit_value (self):
        self.assertEqual (True, feature.is_implicit_value ('gcc'))
        self.assertEqual (True, feature.is_implicit_value ('debug'))
        self.assertEqual (False, feature.is_implicit_value ('on'))

    def test_subfeature (self):
        # TODO: implement this
        pass
        
    def test_extend_subfeature (self):
        # TODO: implement this
        pass
        
    def test_compress_subproperties (self):
        # TODO: implement this
        pass

    def test_validate_value_string (self):
        feature.validate_value_string ('<optimization>', 'on')
        self.assertRaises (InvalidValue, feature.validate_value_string, '<toolset>', 'digital_mars')
        
    def test_minimize (self):
        e1 = feature.expand (['gcc-3.0.1', 'debug', '<optimization>on', '<stdlib>native'])
        self.assertEqual (['gcc-3.0.1', 'debug', '<optimization>on'], feature.minimize (e1))
    
        e2 = feature.expand (['gcc-3.0.1', 'debug', '<optimization>off', '<runtime-link>dynamic'])
        self.assertEqual (['gcc-3.0.1', 'debug', '<runtime-link>dynamic'], feature.minimize (e2))
    
        e3 = feature.expand (['gcc-3.0.1', 'debug', '<optimization>off'])
        self.assertEqual (['gcc-3.0.1', 'debug'], feature.minimize (e3))
    
        e4 = feature.expand (['debug', '<optimization>on'])
        self.assertEqual (['debug', '<optimization>on'], feature.minimize (e4))
    
        self.assertEqual (['gcc-3.0'], feature.minimize (['<toolset>gcc', '<toolset-gcc:version>3.0']))
        self.assertEqual (['gcc-3.0'], feature.minimize (['<toolset-gcc:version>3.0', '<toolset>gcc']))
    
        
    def test_implied_subeature (self):
        self.assertEqual ('<toolset>', feature.implied_feature ('gcc-3.0.1'))
        self.assertRaises (InvalidValue, feature.implied_feature, ('x4-y1'))
    
        self.assertEqual ('gcc:version', feature.implied_subfeature ('toolset', '3.0.1', 'gcc'))
        self.assertRaises (InvalidValue, feature.implied_subfeature, 'x', 'z1', 'x2')

    def test_expand_subfeatures (self):        
        # TODO: according to the documentation of the implementation, the 'gcc:' should not be in the grists.
        # However, it seems that BBv2 did put it there.
        self.assertEqual (['<toolset>gcc', '<toolset-gcc:version>2.95.2', '<toolset-gcc:os>linux', '<toolset-gcc:cpu>x86'], feature.expand_subfeatures (['gcc-2.95.2-linux-x86']))
        self.assertEqual (['<toolset>gcc', '<toolset-gcc:version>3.0.1'], feature.expand_subfeatures (['<toolset>gcc-3.0.1']))
        self.assertEqual (['<toolset>gcc', '<toolset-gcc:version>3.0.1', '<toolset-gcc:os>linux'], feature.expand_subfeatures (['<toolset>gcc-3.0.1-linux']))
        self.assertEqual (['<define>foo=x-y'], feature.expand_subfeatures (['<define>foo=x-y']))

    def test_get_values (self):
        self.assertEqual (['a', 'c', 'e'], feature.get_values ('<x>', ['<x>a', '<y>b', '<x>c', '<y>d', '<x>e']))

    def test_free_features (self):
        self.assertEqual (['<define>'], feature.free_features ())
        feature.feature ('k', ['kk'], ['path', 'free'])
        self.assertEqual (['<define>', '<k>'], feature.free_features ())

    def test_expand_composite (self):
        feature.feature ('k', ['vk'], ['composite'])
        feature.compose ('<k>', ['<a>', '<b>', '<c>'])
        self.assertEqual (['<k>', '<a>', '<b>', '<c>'], feature.expand_composite ('<k>'))

    def test_expand_composites (self):
        feature.feature ('k', ['vk'], ['composite'])
        feature.compose ('<k>', ['<a>', '<b>', '<c>'])

        feature.feature ('l', ['vl'], ['composite'])
        feature.compose ('<l>', ['<a>', '<d>'])

        self.assertEqual (['<k>', '<a>', '<b>', '<c>', '<l>', '<d>'], feature.expand_composites (['<k>', '<l>']))

    def test_split_top_feature (self):
        # TODO: implement this
        pass

    def test_expand (self):
        e = ['<toolset>gcc', '<toolset-gcc:version>3.0.1', '<variant>debug', '<define>_DEBUG', '<optimization>on', '<stdlib>native']
        self.assertEqual (e, feature.expand (['gcc-3.0.1', 'debug', '<optimization>on', '<stdlib>native']))

        self.assertRaises (FeatureConflict, feature.expand, ['release', '<optimization>off', '<optimization>on'])

        feature.feature ('composed', ['a'], ['implicit', 'composite', 'symmetric'])
        feature.compose ('<composed>a', ['<optimization>off'])
        self.assertRaises (FeatureConflict, feature.expand, ['release', 'a'])
        

    def test_add_defaults (self):

        self.assertEqual (['<runtime-link>static', '<define>foobar', '<optimization>on', 
                '<toolset>gcc:<define>FOO', '<toolset>gcc', '<variant>debug', 
                '<stdlib>native', '<toolset-gcc:version>2.95.2'], 
            feature.add_defaults (['<runtime-link>static', '<define>foobar', 
                '<optimization>on', '<toolset>gcc:<define>FOO']))

        feature.feature ('fu', ['fu1', 'fu2'], ['optional'])
        feature.subfeature ('fu', None, 'subfu', ['x', 'y', 'z'], ['optional'])
        feature.subfeature ('fu', None, 'subfu2', ['q', 'y', 'rs'], [])

        self.assertEqual (['<runtime-link>static', '<define>foobar', '<optimization>on', 
                '<toolset>gcc:<define>FOO', '<fu>fu1', '<toolset>gcc', '<variant>debug', 
                '<stdlib>native', '<fu-subfu2>q', '<toolset-gcc:version>2.95.2'], 
            feature.add_defaults (['<runtime-link>static', '<define>foobar', 
                '<optimization>on', '<toolset>gcc:<define>FOO', '<fu>fu1']))

        self.assertEqual (['<runtime-link>static', '<define>foobar', '<optimization>on', 
                '<toolset>gcc:<define>FOO', '<toolset>gcc', '<variant>debug', 
                '<stdlib>native', '<toolset-gcc:version>2.95.2'], 
            feature.add_defaults (['<runtime-link>static', '<define>foobar', 
                '<optimization>on', '<toolset>gcc:<define>FOO']))

        self.assertEqual (['<runtime-link>static', '<define>foobar', '<optimization>on', 
                '<toolset>gcc:<define>FOO', '<fu>fu1', '<toolset>gcc', '<variant>debug', 
                '<stdlib>native', '<fu-subfu2>q', '<toolset-gcc:version>2.95.2'], 
            feature.add_defaults (['<runtime-link>static', '<define>foobar', 
                '<optimization>on', '<toolset>gcc:<define>FOO', '<fu>fu1']))

    def test_is_subfeature_of (self):
        self.assertEqual (True, feature.is_subfeature_of ('<toolset>gcc', '<toolset-gcc:version>'))
    
    def test_split (self):
        self.assertEqual (['v1', 'v2', 'vN-1', '<fN>vN', '<fN+1>vN+1', '<fM>vM'], feature.split ('v1/v2/vN-1/<fN>vN/<fN+1>vN+1/<fM>vM'))

        self.assertEqual (['<x>y/z', '<a>b/c', '<d>e/f'], feature.split ('<x>y/z/<a>b/c/<d>e/f'))
        self.assertEqual (['<x>y/z', '<a>b/c', '<d>e/f'], feature.split ('<x>y\\z\\<a>b\\c\\<d>e\\f'))
        self.assertEqual (['a', 'b', 'c', '<d>e/f/g', '<h>i/j/k'], feature.split ('a/b/c/<d>e/f/g/<h>i/j/k'))
        self.assertEqual (['a', 'b', 'c', '<d>e/f/g', '<h>i/j/k'], feature.split ('a\\b\\c\\<d>e\\f\\g\\<h>i\\j\\k'))

    def test_compress_subproperties (self):
        # TODO: implement this
        pass

######################################################################
if __name__ == '__main__': unittest.main ()
