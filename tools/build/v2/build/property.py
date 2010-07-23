# Status: ported, except for tests and --abbreviate-paths.
# Base revision: 64070
#
# Copyright 2001, 2002, 2003 Dave Abrahams 
# Copyright 2006 Rene Rivera 
# Copyright 2002, 2003, 2004, 2005, 2006 Vladimir Prus 
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt) 

import re
from b2.util.utility import *
from b2.build import feature
from b2.util import sequence
import b2.util.set
from b2.manager import get_manager

__re_two_ampersands = re.compile ('&&')
__re_comma = re.compile (',')
__re_split_condition = re.compile ('(.*):(<.*)')
__re_split_conditional = re.compile (r'(.+):<(.+)')
__re_colon = re.compile (':')
__re_has_condition = re.compile (r':<')
__re_separate_condition_and_property = re.compile (r'(.*):(<.*)')
__re_indirect_rule = re.compile("^([^%]*)%([^%]+)$")

class Property(object):

    __slots__ = ('_feature', '_value', '_condition')

    def __init__(self, feature, value, condition = []):
        assert(feature.free() or value.find(':') == -1)
        self._feature = feature
        self._value = value
        self._condition = condition

        
    def feature(self):
        return self._feature

    def value(self):
        return self._value

    def condition(self):
        return self._condition

    def to_raw(self):
        # FIXME: include condition!
        return "<" + self._feature.name() + ">" + self._value

    def __str__(self):
        return self.to_raw()

    def __hash__(self):
        # FIXME: consider if this class should be value-is-identity one
        return hash((self._feature, self._value, tuple(self._condition)))

    def __cmp__(self, other):
        return cmp((self._feature, self._value, self._condition),
                   (other._feature, other._value, other._condition))
                           

def create_from_string(s, allow_condition = False):

    condition = []
    if __re_has_condition.search(s):

        if not allow_condition:
            raise BaseException("Conditional property is not allowed in this context")

        m = __re_separate_condition_and_property.match(s)
        condition = m.group(1)
        s = m.group(2)

    # FIXME: break dependency cycle
    from b2.manager import get_manager

    feature_name = get_grist(s)
    if not feature_name:
        if feature.is_implicit_value(s):
            f = feature.implied_feature(s)
            value = s
        else:        
            raise get_manager().errors()("Invalid property '%s' -- unknown feature" % s)
    else:
        f = feature.get(feature_name)        

        value = get_value(s)
        if not value:
            get_manager().errors()("Invalid property '%s' -- no value specified" % s)


    if condition:
        condition = [create_from_string(x) for x in condition.split(',')]
                   
    return Property(f, value, condition)

def create_from_strings(string_list, validate=False):

    return [create_from_string(s, validate) for s in string_list]

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __results

    # A cache of results from as_path
    __results = {}
    
reset ()

        
def path_order (x, y):
    """ Helper for as_path, below. Orders properties with the implicit ones
        first, and within the two sections in alphabetical order of feature
        name.
    """
    if x == y:
        return 0
        
    xg = get_grist (x)
    yg = get_grist (y)

    if yg and not xg:
        return -1

    elif xg and not yg:
        return 1

    else:
        if not xg:            
            x = feature.expand_subfeatures([x])
            y = feature.expand_subfeatures([y])
        
        if x < y:
            return -1
        elif x > y:
            return 1
        else:
            return 0

def identify(string):
    return string 

# Uses Property
def refine (properties, requirements):
    """ Refines 'properties' by overriding any non-free properties 
        for which a different value is specified in 'requirements'. 
        Conditional requirements are just added without modification.
        Returns the resulting list of properties.
    """
    # The result has no duplicates, so we store it in a set
    result = set()
    
    # Records all requirements.
    required = {}
    
    # All the elements of requirements should be present in the result
    # Record them so that we can handle 'properties'.
    for r in requirements:
        # Don't consider conditional requirements.
        if r.condition():
            required[r.feature()] = r

    for p in properties:
        # Skip conditional properties
        if p.condition():
            result.add(p)
        # No processing for free properties
        elif p.feature().free():
            result.add(p)
        else:
            if required.has_key(p.feature()):
                result.add(required[p.feature()])
            else:
                result.add(p)

    return sequence.unique(list(result) + requirements)

def translate_paths (properties, path):
    """ Interpret all path properties in 'properties' as relative to 'path'
        The property values are assumed to be in system-specific form, and
        will be translated into normalized form.
        """
    result = []

    for p in properties:

        if p.feature().path():
            values = __re_two_ampersands.split(p.value())
            
            new_value = "&&".join(os.path.join(path, v) for v in values)

            if new_value != p.value():
                result.append(Property(p.feature(), new_value, p.condition()))
            else:
                result.append(p)
            
        else:
            result.append (p)

    return result

def translate_indirect(properties, context_module):
    """Assumes that all feature values that start with '@' are
    names of rules, used in 'context-module'. Such rules can be
    either local to the module or global. Qualified local rules
    with the name of the module."""
    result = []
    for p in properties:
        if p.value()[0] == '@':
            v = None
            m = p.value()[1:]
            if __re_indirect_rule.match(m):
                # Rule is already in indirect format
                # FIXME: it's not clear if this is necessary.
                v = m
            else:

                if not '.' in m:
                    # This is unqualified rule name. The user might want
                    # to set flags on this rule name, and toolset.flag
                    # auto-qualifies the rule name. Need to do the same
                    # here so set flag setting work.
                    # We can arrange for toolset.flag to *not* auto-qualify
                    # the argument, but then two rules defined in two Jamfiles
                    # will conflict.
                    m = context_module + "." + m

                v = m
                #v = indirect.make(m, context_module)
                get_manager().engine().register_bjam_action(v)
            
            result.append(Property(p.feature(), "@" + m, p.condition()))
        else:
            result.append(p)

    return result

def validate (properties):
    """ Exit with error if any of the properties is not valid.
        properties may be a single property or a sequence of properties.
    """
    
    if isinstance (properties, str):
        __validate1 (properties)
    else:
        for p in properties:
            __validate1 (p)

def expand_subfeatures_in_conditions (properties):

    result = []
    for p in properties:

        if not p.condition():
            result.append(p)

        for c in p.condition():

            if c.feature().name().startswith("toolset") or c.feature().name() == "os":
                # It common that condition includes a toolset which
                # was never defined, or mentiones subfeatures which
                # were never defined. In that case, validation will
                # only produce an spirious error, so don't validate.
                result.extend(feature.expand_subfeatures ([c], True))
            else:
                result.extend(feature.expand_subfeatures([c]))

    return result

# FIXME: this should go
def split_conditional (property):
    """ If 'property' is conditional property, returns
        condition and the property, e.g
        <variant>debug,<toolset>gcc:<inlining>full will become
        <variant>debug,<toolset>gcc <inlining>full.
        Otherwise, returns empty string.
    """
    m = __re_split_conditional.match (property)
    
    if m:
        return (m.group (1), '<' + m.group (2))

    return None

# FIXME: this should go
def is_conditional (property):
    """ Returns True if a property is conditional.
    """
    if __re_colon.search (replace_grist (property, '')):
        return True
    else:
        return False

def select (features, properties):
    """ Selects properties which correspond to any of the given features.
    """
    result = []
    
    # add any missing angle brackets
    features = add_grist (features)

    return [p for p in properties if get_grist(p) in features]

def validate_property_sets (sets):
    for s in sets:
        validate(s.all())

def evaluate_conditionals_in_context (properties, context):
    """ Removes all conditional properties which conditions are not met
        For those with met conditions, removes the condition. Properies
        in conditions are looked up in 'context'
    """
    base = []
    conditionals = []

    for p in properties:
        if __re_has_condition.search (p):
            conditionals.append (p)
        else:
            base.append (p)

    result = base
    for p in conditionals:

        # Separate condition and property
        s = __re_separate_condition_and_property.match (p)

        # Split condition into individual properties
        conditions = s.group (1).split (',')

        # Evaluate condition        
        if b2.util.set.contains (conditions, context):
            result.append (s.group (2))

    return result


def change (properties, feature, value = None):
    """ Returns a modified version of properties with all values of the
        given feature replaced by the given value.
        If 'value' is None the feature will be removed.
    """
    result = []
    
    feature = add_grist (feature)

    for p in properties:
        if get_grist (p) == feature:
            if value:
                result.append (replace_grist (value, feature))

        else:
            result.append (p)

    return result


################################################################
# Private functions

def __validate1 (property):
    """ Exit with error if property is not valid.
    """        
    msg = None

    if not property.feature().free():
        feature.validate_value_string (property.feature(), property.value())


###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#   
#   import utility : ungrist ;
#   import sequence : unique ;
#   import errors : error ;
#   import feature ;
#   import regex ;
#   import sequence ;
#   import set ;
#   import path ;
#   import assert ;
#   
#   


#   rule validate-property-sets ( property-sets * )
#   {
#       for local s in $(property-sets)
#       {
#           validate [ feature.split $(s) ] ;
#       }
#   }
#

def remove(attributes, properties):
    """Returns a property sets which include all the elements
    in 'properties' that do not have attributes listed in 'attributes'."""
    
    result = []
    for e in properties:
        attributes_new = feature.attributes(get_grist(e))
        has_common_features = 0
        for a in attributes_new:
            if a in attributes:
                has_common_features = 1
                break

        if not has_common_features:
            result += e

    return result


def take(attributes, properties):
    """Returns a property set which include all
    properties in 'properties' that have any of 'attributes'."""
    result = []
    for e in properties:
        if b2.util.set.intersection(attributes, feature.attributes(get_grist(e))):
            result.append(e)
    return result

def translate_dependencies(specification, project_id, location):

    result = []
    for p in specification:
        split = split_conditional(p)
        condition = ""
        if split:
            condition = split[0]
            p = split[1]

        f = get_grist(p)
        v = get_value(p)
        if "dependency" in feature.attributes(f):
            m = re.match("(.*)//(.*)", v)
            if m:
                rooted = m.group(1)
                if rooted[0] == '/':
                    # Either project id or absolute Linux path, do nothing.
                    pass
                else:
                    rooted = os.path.join(os.getcwd(), location, rooted[0])
                result.append(condition + f + rooted + "//" + m.group(2))
            elif os.path.isabs(m.group(v)):                
                result.append(condition + p)
            else:
                result.append(condition + f + project_id + "//" + v)
        else:
            result.append(condition + p)

    return result


class PropertyMap:
    """ Class which maintains a property set -> string mapping.
    """
    def __init__ (self):
        self.__properties = []
        self.__values = []
    
    def insert (self, properties, value):
        """ Associate value with properties.
        """
        self.__properties.append(properties)
        self.__values.append(value)

    def find (self, properties):
        """ Return the value associated with properties
        or any subset of it. If more than one
        subset has value assigned to it, return the
        value for the longest subset, if it's unique.
        """
        return self.find_replace (properties)

    def find_replace(self, properties, value=None):
        matches = []
        match_ranks = []
        
        for i in range(0, len(self.__properties)):
            p = self.__properties[i]
                        
            if b2.util.set.contains (p, properties):
                matches.append (i)
                match_ranks.append(len(p))

        best = sequence.select_highest_ranked (matches, match_ranks)

        if not best:
            return None

        if len (best) > 1:
            raise NoBestMatchingAlternative ()

        best = best [0]
            
        original = self.__values[best]

        if value:
            self.__values[best] = value

        return original

#   local rule __test__ ( )
#   {
#       import errors : try catch ;
#       import feature ;
#       import feature : feature subfeature compose ;
#       
#       # local rules must be explicitly re-imported
#       import property : path-order ;
#       
#       feature.prepare-test property-test-temp ;
#   
#       feature toolset : gcc : implicit symmetric ;
#       subfeature toolset gcc : version : 2.95.2 2.95.3 2.95.4
#         3.0 3.0.1 3.0.2 : optional ;
#       feature define : : free ;
#       feature runtime-link : dynamic static : symmetric link-incompatible ;
#       feature optimization : on off ;
#       feature variant : debug release : implicit composite symmetric ;
#       feature rtti : on off : link-incompatible ;
#   
#       compose <variant>debug : <define>_DEBUG <optimization>off ;
#       compose <variant>release : <define>NDEBUG <optimization>on ;
#   
#       import assert ;
#       import "class" : new ;
#       
#       validate <toolset>gcc  <toolset>gcc-3.0.1 : $(test-space) ;
#       
#       assert.result <toolset>gcc <rtti>off <define>FOO
#           : refine <toolset>gcc <rtti>off
#           : <define>FOO
#           : $(test-space)
#           ;
#   
#       assert.result <toolset>gcc <optimization>on
#           : refine <toolset>gcc <optimization>off
#           : <optimization>on
#           : $(test-space)
#           ;
#   
#       assert.result <toolset>gcc <rtti>off
#           : refine <toolset>gcc : <rtti>off : $(test-space)
#           ;
#   
#       assert.result <toolset>gcc <rtti>off <rtti>off:<define>FOO
#           : refine <toolset>gcc : <rtti>off <rtti>off:<define>FOO 
#           : $(test-space)
#           ;
#       
#       assert.result <toolset>gcc:<define>foo <toolset>gcc:<define>bar 
#           : refine <toolset>gcc:<define>foo : <toolset>gcc:<define>bar 
#           : $(test-space)
#           ;
#   
#       assert.result <define>MY_RELEASE
#           : evaluate-conditionals-in-context 
#             <variant>release,<rtti>off:<define>MY_RELEASE
#             : <toolset>gcc <variant>release <rtti>off
#                    
#           ;
#   
#       try ;
#           validate <feature>value : $(test-space) ;
#       catch "Invalid property '<feature>value': unknown feature 'feature'." ;
#   
#       try ;
#           validate <rtti>default : $(test-space) ;
#       catch \"default\" is not a known value of feature <rtti> ;
#       
#       validate <define>WHATEVER : $(test-space) ;
#   
#       try ;
#           validate <rtti> : $(test-space) ;
#       catch "Invalid property '<rtti>': No value specified for feature 'rtti'." ;
#   
#       try ;
#           validate value : $(test-space) ;
#       catch "value" is not a value of an implicit feature ;
#              
#   
#       assert.result <rtti>on 
#           : remove free implicit : <toolset>gcc <define>foo <rtti>on : $(test-space) ;
#   
#       assert.result <include>a 
#           : select include : <include>a <toolset>gcc ;
#   
#       assert.result <include>a 
#           : select include bar : <include>a <toolset>gcc ;
#   
#       assert.result <include>a <toolset>gcc
#           : select include <bar> <toolset> : <include>a <toolset>gcc ;
#       
#       assert.result <toolset>kylix <include>a 
#           : change <toolset>gcc <include>a : <toolset> kylix ;
#   
#       # Test ordinary properties 
#       assert.result 
#         : split-conditional <toolset>gcc 
#         ;
#       
#       # Test properties with ":"
#       assert.result
#         : split-conditional <define>FOO=A::B
#         ;
#       
#       # Test conditional feature
#       assert.result <toolset>gcc,<toolset-gcc:version>3.0 <define>FOO
#         : split-conditional <toolset>gcc,<toolset-gcc:version>3.0:<define>FOO
#         ;
#       
#       feature.finish-test property-test-temp ;
#   }
#   
    
