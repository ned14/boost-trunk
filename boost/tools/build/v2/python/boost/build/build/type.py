#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

import re
import os
import os.path
from boost.build.util.utility import replace_grist, os_name
from boost.build.exceptions import *
from boost.build.build import feature

__re_hyphen = re.compile ('-')

def __register_features ():
    """ Register features need by this module.
    """
    # The feature is optional so that it is never implicitly added.
    # It's used only for internal purposes, and in all cases we
    # want to explicitly use it.
    feature.feature ('target-type', [], ['composite', 'optional'])
    feature.feature ('main-target-type', [], ['optional', 'incidental'])
    feature.feature ('base-target-type', [], ['composite', 'optional', 'free'])

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
        Note that this must be called _after_ resetting the module 'feature'.
    """    
    global __suffixes, __suffixes_to_types, __types, __rule_names_to_types
    
    __register_features ()

    # Stores suffixes for generated targets.
    # The key is the stringified set of properties, the value is the suffix.
    __suffixes = {}
    
    # Maps suffixes to types
    __suffixes_to_types = {}
    
    # A map with all the registered types, indexed by the type name
    # Each entry is a dictionary with following values:
    # 'base': the name of base type or None if type has no base
    # 'derived': a list of names of type which derive from this one
    # 'scanner': the scanner class registered for this type, if any
    __types = {}

    # Maps main rule names to the corresponding type.
    __rule_names_to_types = {}
    
reset ()


def register (type, suffixes = [], base_type = None):
    """ Registers a target type, possibly derived from a 'base-type'. 
        If 'suffixes' are provided, they list all the suffixes that mean a file is of 'type'.
        Also, the first element gives the suffix to be used when constructing and object of
        'type'.
        type: a string
        suffixes: None or a sequence of strings
        base_type: None or a string
    """
    # Type names cannot contain hyphens, because when used as
    # feature-values they will be interpreted as composite features
    # which need to be decomposed.
    if __re_hyphen.search (type):
        raise BaseException ('type name "%s" contains a hyphen' % type)
    
    if __types.has_key (type):
        raise BaseException ('Type "%s" is already registered.' % type)

    entry = {}
    entry ['base'] = base_type
    entry ['derived'] = []
    entry ['scanner'] = None
    __types [type] = entry
    
    if base_type:
        __types [base_type]['derived'].append (type)

    if len (suffixes) > 0:
        # Generated targets of 'type' will use the first of 'suffixes'
        # (this may be overriden)            
        set_generated_target_suffix (type, [], suffixes [0])
        
        # Specify mapping from suffixes to type
        register_suffixes (suffixes, type)
    
    feature.extend_feature ('target-type', type)
    feature.extend_feature ('main-target-type', type)
    feature.extend_feature ('base-target-type', type)

    if base_type:
        feature.compose ('<target-type>' + type, replace_grist (base_type, '<base-target-type>'))
        feature.compose ('<base-target-type>' + type, '<base-target-type>' + base_type)

    __register_main_rule (type)

def register_suffixes (suffixes, type):
    """ Specifies that targets with suffix from 'suffixes' have the type 'type'. 
        If a different type is already specified for any of syffixes, issues an error.
    """
    for s in suffixes:
        if __suffixes_to_types.has_key (s):
            old_type = __suffixes_to_types [s]
            if old_type != type:
                raise BaseException ('Attempting to specify type for suffix "%s"\nOld type: "%s", New type "%s"' % (s, old_type, type))
        else:
            __suffixes_to_types [s] = type

def registered (type):
    """ Returns true iff type has been registered.
    """
    return __types.has_key (type)

def validate (type):
    """ Issues an error if 'type' is unknown.
    """
    if not registered (type):
        raise BaseException ("Unknown target type '%s'" % type)

def set_scanner (type, scanner):
    """ Sets a scanner class that will be used for this 'type'.
    """
    validate (type)
    __types [type]['scanner'] = scanner

def get_scanner (type, property_set):
    """ Returns a scanner instance appropriate to 'type' and 'property_set'.
    """
    if registered (type):
        scanner = __types [type]['scanner']
        if scanner:
            # TODO: implement this
#            return [ scanner.get $(.scanner.$(type)) : [ $(property-set).raw ] ] ;
            pass
            
    return None

def all_bases (type):
    """ Returns type and all of its bases, in the order of their distance from type.
    """
    result = []
    while type:
        result.append (type)
        type = __types [type]['base']

    return result

def all_derived (type):
    """ Returns type and all classes that derive from it, in the order of their distance from type.
    """
    result = [type]
    for d in __types [type]['derived']:
        result.extend (all_derived (d))

    return result

def is_derived (type, base):
    """ Returns true if 'type' is 'base' or has 'base' as its direct or indirect base.
    """
    # TODO: this isn't very efficient, especially for bases close to type
    if base in all_bases (type):
        return True
    else: 
        return False

def is_subtype (type, base):
    """ Same as is_derived. Should be removed.
    """
    # TODO: remove this method
    return is_derived (type, base)

def set_generated_target_suffix (type, properties, suffix):
    """ Sets a target suffix that should be used when generating target 
        of 'type' with the specified properties. Can be called with
        empty properties if no suffix for 'type' was specified yet.
        This does not automatically specify that files 'suffix' have
        'type' --- two different types can use the same suffix for
        generating, but only one type should be auto-detected for
        a file with that suffix. User should explicitly specify which
        one.

        The 'suffix' parameter can be empty string ("") to indicate that
        no suffix should be used.
    """
    properties.append ('<target-type>' + type)
    __suffixes [str (properties)] = suffix

def change_generated_target_suffix (type, properties, suffix):
    """ Change the suffix previously registered for this type/properties 
        combination. If suffix is not yet specified, sets it.
    """
    set_generated_target_suffix (type, properties, suffix)

def generated_target_suffix (type, properties):
    """ Returns suffix that should be used when generating target of 'type',
        with the specified properties. If not suffix were specified for
        'type', returns suffix for base type, if any.
    """
    while type:
        all_properties = properties + ['<target-type>' + type]
        all_properties_str = str (all_properties)
        if __suffixes.has_key (all_properties_str):
            return __suffixes [all_properties_str]

        type = __types [type]['base']

    return None

def type (filename):
    """ Returns file type given it's name. If there are several dots in filename,
        tries each suffix. E.g. for name of "file.so.1.2" suffixes "2", "1", and 
        "so"  will be tried.
    """
    while 1:
        filename, suffix = os.path.splitext (filename)
        if not suffix: return None
        suffix = suffix [1:]
        
        if __suffixes_to_types.has_key (suffix):
            return __suffixes_to_types [suffix]

# NOTE: moved from tools/types/register
def register_type (type, suffixes, base_type = None, os = []):
    """ Register the given type on the specified OSes, or on remaining OSes
        if os is not specified.  This rule is injected into each of the type
        modules for the sake of convenience.
    """
    if registered (type):
        return

    if not os or os_name () in os:
        register (type, suffixes, base_type)



######################################################################################
# Private functions

def __register_main_rule (type):
    # We used to declare a main target rule only when 'main' parameter is specified. 
    # However, it's hard to decide that a type *never* will need a main target rule 
    # and so from time to time we needed to make yet another type 'main'. So, now 
    # main target rule is defined for each type.
     
    # TODO:
    # something along the lines of
    #   main_rule_name = type_to_rule_name (type)
    #   __rule_names_to_types [main_rule_name] = type
    #   import boost.build.build.project
    #   boost.build.build.project.ProjectModule.__dict__ [main_rule_name] = main_rule
    # How to define main_rule? Create a global object that catches all calls and
    # does what is needed dependeing on the method name?
    pass


###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#   # Given type, returns name of main target rule which creates
#   # targets of that type.
#   rule type_to_rule_name ( type )
#   {
#       # Lowercase everything. Convert underscores to dashes.ame.
#       import regex ;
#       local n = [ regex.split $(type:L) "_" ] ;
#       n = $(n:J=-) ;
#       return $(n) ;
#   }
#   
#   # Returns a type, given the name of a main rule.
#   rule type-from-rule-name ( main-target-name )
#   {
#       return $(.main-target-type.$(main-target-name)) ;
#   }
#   
#   rule main-target-rule ( name : sources * : requirements * : default-build * 
#                           : usage-requirements * )
#   {
#       # First find required target type, which is equal to the name used
#       # to invoke us.
#       local bt = [ BACKTRACE 1 ] ;
#       local rulename = $(bt[4]) ;
#       
#       # This rule may be only called from Jamfile, and therefore, 
#       # CALLER_MODULE is Jamfile module, which is used to denote 
#       # a project.
#       local project = [ project.current ] ;
#           
#       # This is a circular module dependency, so it must be imported here
#       import targets ;
#       return [ targets.create-typed-target $(.main-target-type.$(rulename)) : $(project)
#         : $(name) : $(sources) : $(requirements) 
#         : $(default-build) : $(usage-requirements) ] ;        
#   }
