# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import build_request, feature
from boost.build.exceptions import *

class TestBuildRequest (unittest.TestCase):

    def setUp (self):
        helpers.reset ()
        feature.feature ('toolset', ['gcc', 'msvc', 'borland'], ['implicit'])
        feature.subfeature ('toolset', 'gcc', 'version', ['2.95.2', '2.95.3', '2.95.4', '3.0', '3.0.1', '3.0.2'], ['optional'])
    
        feature.feature ('variant', ['debug', 'release'], ['implicit', 'composite'])
        feature.feature ('inlining', ['on', 'off'])
        feature.feature ('include', [], ['free'])
        feature.feature ('stdlib', ['native', 'stlport'], ['implicit'])
        feature.feature ('runtime-link', ['dynamic', 'static'], ['symmetric'])
        
    def test_build_request (self):

        self.assertEqual ([], build_request.expand_no_defaults ([]))
    
        self.assertEqual (['<toolset>gcc/<toolset-gcc:version>3.0.1/<stdlib>stlport/<variant>debug',
            '<toolset>msvc/<stdlib>stlport/<variant>debug',
            '<toolset>msvc/<variant>debug'], 
            build_request.expand_no_defaults (['gcc-3.0.1/stlport', 'msvc/stlport', 'msvc', 'debug']))
    
        self.assertEqual (['<toolset>gcc/<toolset-gcc:version>3.0.1/<stdlib>stlport/<variant>debug',
            '<toolset>msvc/<variant>debug',
            '<variant>debug/<toolset>msvc/<stdlib>stlport'],
            build_request.expand_no_defaults (['gcc-3.0.1/stlport', 'msvc', 'debug', 'msvc/stlport']))
    
        self.assertEqual (['<toolset>gcc/<toolset-gcc:version>3.0.1/<stdlib>stlport/<variant>debug/<inlining>off',
            '<toolset>gcc/<toolset-gcc:version>3.0.1/<stdlib>stlport/<variant>release/<inlining>off'],
            build_request.expand_no_defaults (['gcc-3.0.1/stlport', 'debug', 'release', '<inlining>off']))
    
        self.assertEqual (['<include>a/b/c/<toolset>gcc/<toolset-gcc:version>3.0.1/<stdlib>stlport/<variant>debug/<include>x/y/z',
            '<include>a/b/c/<toolset>msvc/<stdlib>stlport/<variant>debug/<include>x/y/z',
            '<include>a/b/c/<toolset>msvc/<variant>debug/<include>x/y/z'],
            build_request.expand_no_defaults (['<include>a/b/c', 'gcc-3.0.1/stlport', 'msvc/stlport', 'msvc', 'debug', '<include>x/y/z']))
        
######################################################################
if __name__ == '__main__': unittest.main ()
