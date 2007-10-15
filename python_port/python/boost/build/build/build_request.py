# Status: being ported by Vladimir Prus
#
#  (C) Copyright David Abrahams 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

import feature
from boost.build.util import set
from boost.build.util.utility import *

def expand_no_defaults (property_sets):
    """ Expand the given build request by combining all property_sets which don't
        specify conflicting non-free features.
    """
    # First make all features and subfeatures explicit
    expanded_property_sets = [ __apply_to_property_set (feature.expand_subfeatures, x) for x in property_sets ]
    
    # Now combine all of the expanded property_sets
    product = __x_product (expanded_property_sets)
    
    return product

def __apply_to_property_set (f, property_set):
    """ Transform property_set by applying f to each component property.
    """
    properties = feature.split (property_set)
    return '/'.join (f (properties))



def __x_product (property_sets):
    """ Return the cross-product of all elements of property_sets, less any
        that would contain conflicting values for single-valued features.
    """
    x_product_seen = []
    x_product_used = []
    feature_space = []
    return __x_product_aux (property_sets, x_product_seen, x_product_used, feature_space)
    
def __x_product_aux (property_sets, x_product_seen, x_product_used, feature_space):
    """ Implementation of __x_product.
    """
    result = []
    
    if property_sets:
        p = feature.split (property_sets [0])
    else:
        p = []
        
    f = set.difference (get_grist (p), feature.free_features ())
    
    seen = []
    # No conflict with things used at a higher level?
    if not set.intersection (f, x_product_used):
        # don't mix in any conflicting features
        local_x_product_used = x_product_used + f
        local_x_product_seen = []
        
        if len (property_sets) > 1:
            rest = __x_product_aux (property_sets [1:], local_x_product_seen, local_x_product_used, feature_space)
            result = [ property_sets [0] + '/' + x for x in rest]
        
        if not result and property_sets:
            result = [property_sets [0]]
        
        # If we didn't encounter a conflicting feature lower down,
        # don't recurse again.
        if not set.intersection (f, local_x_product_seen):
            property_sets = []
        
        seen = local_x_product_seen
    
    if len (property_sets) > 1:
        result.extend (__x_product_aux (property_sets [1:], x_product_seen, x_product_used, feature_space))
    x_product_seen += f + seen
    
    # Note that we've seen these features so that higher levels will
    # recurse again without them set.

    return result




###################################################################
# Still to port.
# Original lines are prefixed with "### "
#
### import sequence ;
### import set ;
### import regex ;
### import feature ;
### import property ;
### import numbers ;
### import container ;
### import "class" : new ;
### import string ;
### 
### 
### # Returns true if 'v' is either implicit value, or
### # the part before the first '-' symbol is implicit value
### local rule looks-like-implicit-value ( v )
### {
###     
###     if [ feature.is-implicit-value $(v) ]
###     {
###         return true ;
###     }
###     else
###     {
###         local split = [ regex.split $(v) - ] ;
###         if [ feature.is-implicit-value $(split[1]) ]
###         {
###             return true ;
###         }        
###     }
### }
### 
### 
### # Takes the command line tokens (such as taken from ARGV rule) and constructs
### # build request from it.
### # Returns a vector of two vectors (where "vector" means container.jam's "vector"). 
### # First is the set of targets specified in the command line, and second is
### # the set of requested build properties. 
### rule from-command-line ( command-line * )
### {
###     local targets ;
###     local properties ;
### 
###     command-line = $(command-line[2-]) ;
###     for local e in $(command-line)
###     {
###         if ! [ MATCH "^(-).*" : $(e) ] 
###         {
###             # Build request spec either has "=" in it, or completely
###             # consists of implicit feature values.
###             local fs = feature_space ;
###             if [ MATCH "(.*=.*)" : $(e) ] 
###                || [ looks-like-implicit-value $(e:D=) : $(feature_space) ] 
###             {
###                 properties += [ convert-command-line-element $(e) : $(feature_space) ] ;
###             }
###             else
###             {
###                 targets += $(e) ;
###             }
###         }
###     }
###     return [ new vector [ new vector $(targets) ] [ new vector $(properties) ] ] ;
### }
### 
### # Converts one element of command line build request specification into
### # internal form.
### local rule convert-command-line-element ( e )
### {
###     local result ;
###     local parts = [ regex.split $(e) "/" ] ;
###     for local p in $(parts) 
###     {
###         local m = [ MATCH "([^=]*)=(.*)" : $(p) ] ;
###         local lresult ;
###         if $(m) 
###         {
###             local feature = $(m[1]) ;
###             local values = [ regex.split $(m[2]) "," ] ;            
###             lresult = <$(feature)>$(values) ;            
###         }
###         else
###         {
###             lresult = [ regex.split $(p) "," ] ;
###         }
### 
###         if ! [ MATCH (.*-.*) : $(p) ]
###         {          
###             # property.validate cannot handle subfeatures,
###             # so we avoid the check here.
###             for local p in $(lresult)
###             {
###                 property.validate $(p) : $(feature_space) ;
###             }
###         }
###         
### 
###         if ! $(result) 
###         {
###             result = $(lresult) ;
###         }
###         else
###         {
###             result = $(result)/$(lresult) ;
###         }
###     }  
###     
###     return $(result) ;
### }
### 
### rule __test__ ( )
### {
###     import assert feature ;
###     
###     feature.prepare-test build-request-test-temp ;
###     
###     import build-request ;
###     import build-request : expand_no_defaults : build-request.expand_no_defaults ;
###     import errors : try catch ;
###     import feature : feature subfeature ;
### 
###     feature toolset : gcc msvc borland : implicit ;
###     subfeature toolset gcc : version : 2.95.2 2.95.3 2.95.4
###       3.0 3.0.1 3.0.2 : optional ;
### 
###     feature variant : debug release : implicit composite ;
###     feature inlining : on off ;
###     feature "include" : : free ;
### 
###     feature stdlib : native stlport : implicit ;
### 
###     feature runtime-link : dynamic static : symmetric ;
### 
### 
###     local r ;
### 
###     r = [ build-request.from-command-line bjam debug runtime-link=dynamic ] ;              
###     assert.equal [ $(r).get-at 1 ] : ;
###     assert.equal [ $(r).get-at 2 ] : debug <runtime-link>dynamic ;
### 
###     try ;
###     {
### 
###         build-request.from-command-line bjam gcc/debug runtime-link=dynamic/static ;
###     }
###     catch \"static\" is not a value of an implicit feature ;
### 
### 
###     r = [ build-request.from-command-line bjam -d2 --debug debug target runtime-link=dynamic ] ;
###     assert.equal [ $(r).get-at 1 ] : target ;
###     assert.equal [ $(r).get-at 2 ] : debug <runtime-link>dynamic ;
### 
###     r = [ build-request.from-command-line bjam debug runtime-link=dynamic,static ] ;
###     assert.equal [ $(r).get-at 1 ] : ;
###     assert.equal [ $(r).get-at 2 ] : debug <runtime-link>dynamic <runtime-link>static ;
### 
###     r = [ build-request.from-command-line bjam debug gcc/runtime-link=dynamic,static ] ;
###     assert.equal [ $(r).get-at 1 ] : ;
###     assert.equal [ $(r).get-at 2 ] : debug gcc/<runtime-link>dynamic 
###                  gcc/<runtime-link>static ;
### 
###     r = [ build-request.from-command-line bjam msvc gcc,borland/runtime-link=static ] ;
###     assert.equal [ $(r).get-at 1 ] : ;
###     assert.equal [ $(r).get-at 2 ] : msvc gcc/<runtime-link>static 
###                     borland/<runtime-link>static ;
### 
###     r = [ build-request.from-command-line bjam gcc-3.0 ] ;
###     assert.equal [ $(r).get-at 1 ] : ;
###     assert.equal [ $(r).get-at 2 ] : gcc-3.0 ;
### 
###     feature.finish-test build-request-test-temp ;
### }
### 
### 
