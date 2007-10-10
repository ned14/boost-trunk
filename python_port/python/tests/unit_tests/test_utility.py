# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.util.utility import *
from boost.build.exceptions import *

class TestGrist (unittest.TestCase):
    
    def test_grist (self):
        self.assertEqual (['<a>', '<b>'], add_grist (['a', '<b>']))
        self.assertEqual ('<a>', add_grist ('a'))
    
    def test_replace_grist (self):
        self.assertEqual ('<new>A', replace_grist ('<old>A', '<new>'))
        self.assertEqual ('<new>', replace_grist ('<old>', '<new>'))
        self.assertEqual ('<new>A', replace_grist ('A', '<new>'))
        self.assertEqual (['<new>A', '<new>B'], replace_grist (['<old>A', '<old>B'], '<new>'))

    def test_get_value (self):
        self.assertEqual ('A', get_value ('<a>A'))
        self.assertEqual ('', get_value ('<a>'))
        self.assertEqual ('A', get_value ('A'))
        self.assertEqual (['A', 'B'], get_value (['<a>A', '<b>B']))
    
    def test_get_grist (self):
        self.assertEqual ('<grist>', get_grist ('<grist>A'))
        self.assertEqual ('', get_grist ('A'))
        self.assertEqual ('<grist>', get_grist ('<grist>'))

    def test_ungrist (self):
        self.assertEqual ('A', ungrist ('<A>'))
        self.assertEqual ('A', ungrist ('<A>'))
        self.assertEqual (['A', 'B'], ungrist (['<A>', '<B>']))
        self.assertRaises (BaseException, ungrist, 'abc')
        self.assertRaises (BaseException, ungrist, '<A>abc')

    def test_replace_suffix (self):
        self.assertEqual ('A.yyy', replace_suffix ('A', '.yyy'))
        self.assertEqual ('A.yyy', replace_suffix ('A.xxx', '.yyy'))
        self.assertEqual ('A.zzz.k.yyy', replace_suffix ('A.zzz.k.xxx', '.yyy'))
        self.assertEqual ('A', replace_suffix ('A.xxx', ''))
    
    def test_forward_slashes (self):
        self.assertEqual (r'a/b/c/d/e', forward_slashes (r'a/b\c/d\e'))
        
    def test_split_action_id (self):
        self.assertEqual (('gcc', 'compile.c++'), split_action_id ('gcc.compile.c++'))
        self.assertEqual (('gcc', 'compile'), split_action_id ('gcc.compile'))
        self.assertEqual (('gcc', ''), split_action_id ('gcc'))

######################################################################
if __name__ == '__main__': unittest.main ()
