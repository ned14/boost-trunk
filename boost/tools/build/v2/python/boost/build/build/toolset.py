#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

""" Support for toolset definition.
In BBv2, toolsets where defined using the a.b.c notation. In this port, '_' should be used instead of '.'.
"""

import feature, property, generators
from boost.build.util.utility import *
from boost.build.util import set

__re_split_last_segment = re.compile (r'^(.+)_([^_])*')
__re_two_ampersands = re.compile ('(&&)')
__re_first_segment = re.compile ('([^_]*).*')
__re_first_group = re.compile (r'[^_]*_(.*)')

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __rules, __module_flags, __flags_to_modules, __stv, __flag_no

    # A global counter used to set variables in the maps.
    # TODO: I think the code can be made simpler and this made unnecessary.
    __flag_no = 1
    
    # A map indexed by the rule or module name. The content of each entry is:
    # entry = {
    #     'flags': [],
    #     'variable': {},
    #     'values': {},
    #     'condition': {}
    # }
    #
    # Porting note. In the bjam version, each of this corresponds to .$(rule-or-module).xxx
    __rules = {}
    
    # Corresponds to .module-flags.xxx
    __module_flags = {}
    
    # Corresponds to .rule-or-module.$(.flag-no)
    __flags_to_modules = {}
    
    # A cache for varaible settings. The key is generated from the rule name and the properties.
    __stv = {}
    
reset ()

    
def normalize_condition (property_sets):
    """ Expands subfeatures in each property set.
        e.g
            <toolset>gcc-3.2
        will be converted to
        <toolset>gcc/<toolset-version>3.2

        TODO: does this one belong here or in feature?
    """
    result = []
    for p in property_sets:
        split = feature.split (p)
        expanded = feature.expand_subfeatures (split)
        result.append ('/'.join (expanded))

    return result

def flags (rule_or_module, variable_name, condition, values = []):
    """ Specifies the flags (variables) that must be set on targets under certain
        conditions, described by arguments.
        rule_or_module:   If contains dot, should be a rule name.
                          The flags will be applied when that rule is
                          used to set up build actions.
                          
                          If does not contain dot, should be a module name.
                          The flags will be applied for all rules in that
                          module.
                          If module for rule is different from the calling
                          module, an error is issued.

         variable_name:   Variable that should be set on target
         condition:       An optional condition when this flag should be applied.
                          Should be set of property sets. If one of
                          those property sets is contained in build
                          properties, the flag will be used.
                          Implied values are not allowed:
                          "<toolset>gcc" should be used, not just
                          "gcc". Subfeatures, like in "<toolset>gcc-3.2"
                          are allowed. If left empty, the flag will
                          always used.


         values:          The value to add to variable. If <feature>
                          is specified, then the value of 'feature' 
                          will be added.
    """
    if condition and not replace_grist (condition, ''):
        # We have condition in the form '<feature>', that is, without
        # value. That's a previous syntax:
        #
        #   flags gcc.link RPATH <dll-path> ;
        # for compatibility, convert it to
        #   flags gcc.link RPATH : <dll-path> ;                
        values = [ condition ]
        condition = None
    
    if condition:
        property.validate_property_sets (condition)
        condition = normalize_condition ([condition])
    
    __add_flag (rule_or_module, variable_name, condition, values)

def set_target_variables (manager, rule_or_module, targets, properties):
    """
    """
    key = str (rule_or_module.__name__) + '.' + str (properties)
    settings = __stv.get (key, None)
    if not settings:
        settings = __set_target_variables_aux  (manager, rule_or_module.__name__, properties)

        __stv [key] = settings
        
    if settings:
        for s in settings:
            for target in targets:
                manager.engine ().set_target_variable (target, s [0], s[1])

def find_property_subset (property_sets, properties):
    """ Returns the first element of 'property_sets' which is a subset of
        'properties', or an empty list if no such element exists.
        
            TODO: does this one belong here or in feature?
    """
    for s in property_sets:
        features = feature.split (s)
        if set.contains (features, properties):
            return s

    return None

def register (toolset):
    """ Registers a new toolset.
    """
    feature.extend_feature ('toolset', [toolset])

def inherit_generators (toolset, properties, base, generators_to_ignore):
    if not properties:
        properties = [replace_grist (toolset, '<toolset>')]
        
    base_generators = generators.generators_for_toolset (base)
    
    for g in base_generators:
        id = g.id ()
        
        if not id in generators_to_ignore:
            # Some generator names have multiple periods in their name, so
            # $(id:B=$(toolset)) doesn't generate the right new_id name.
            # e.g. if id = gcc.compile.c++, $(id:B=darwin) = darwin.c++,
            # which is not what we want. Manually parse the base and suffix
            # (if there's a better way to do this, I'd love to see it.)
            # See also register in module generators.
            base = id
            suffix = ''
            while os.path.splitext (base) [1]:
                suffix = os.path.splitext (base) [1] + suffix
                base = os.path.splitext (base) [0]

            new_id = toolset + suffix

            generators.register (g.clone (new_id, properties))

def inherit_flags (toolset, base, prohibited_properties = []):
    """ Inherits the properties set for another toolset.
        Properties listed in prohibited_properties won't
        be inherited. Note that <debug-symbols>on and
        <debug-symbols>off are two different properties
    """
    for f in __module_flags.get (base, []):
        rule_or_module = __flags_to_modules [f]

        entry = __rules [rule_or_module][f]
        
        if set.difference (entry ['condition'], prohibited_properties) or not entry ['condition']:
            match = __re_first_group.match (rule_or_module)
            rule_ = None
            if match:
                rule_ = match.group (1)

            new_rule_or_module = ''

            if rule_:
                new_rule_or_module = toolset + '.' + rule_

            else:
                new_rule_or_module = toolset

            __add_flag (new_rule_or_module, entry ['variable'], entry ['condition'], entry ['values'])


######################################################################################
# Private functions

def __set_target_variables_aux (manager, rule_or_module, properties):
    """ Given a rule name and a property set, returns a list of tuples of
        variables names and values, which must be set on targets for that
        rule/properties combination. 
    """
    result = []

    key = rule_or_module
    if __rules.has_key (key):
        for f in __rules [key]['flags']:
            entry = __rules [key][f]
            variable = entry ['variable']
            condition = entry ['condition']
            values = entry ['values']
            
            if not condition or find_property_subset (condition, properties):
                processed = []
                for v in values:
                    # The value might be <feature-name> so needs special
                    # treatment.
                    processed += __handle_flag_value (manager, v, properties)

                for r in processed:
                    result.append ((variable, r))
    
    # strip away last dot separated part and recurse.
    next = __re_split_last_segment.match (key)
    
    if next:
        result.extend (__set_target_variables_aux (manager, next.group (1), properties))

    return result

def __handle_flag_value (manager, value, properties):
    result = []
    
    if get_grist (value):
        matches = property.select (value, properties)
        for p in matches:
            att = feature.attributes (get_grist (p))
            
            ungristed = replace_grist (p, '')

            if 'dependency' in att:
                # the value of a dependency feature is a target
                # and must be actualized
                
                result.append (manager.targets ().find (ungristed).actualize ())

            elif 'path' in att or 'free' in att:
                values = []
                
                # Treat features with && in the value
                # specially -- each &&-separated element is considered
                # separate value. This is needed to handle searched
                # libraries, which must be in specific order.
                if not __re_two_ampersands.search (ungristed):
                    values.append (ungristed)

                else:
                    values += value.split ('&&')

                if 'path' in att:
                    result += [ Path.native (v) for v in values ]

                else:
                    result += values
            else:
                result.append (ungristed)
    else:
        result.append (value)

    return result

def __add_flag (rule_or_module, variable_name, condition, values):
    """ Adds a new flag setting with the specified values.
        Does no checking.
    """
    # Not '.' in names, use '_' instead.
    assert (not '.' in rule_or_module)

    rule_or_module.replace ('.', '_')
    if __rules.has_key (rule_or_module):
        current = __rules [rule_or_module]
    else:
        current = {
            'flags': []
        }
        
    entry = {
                'variable': variable_name,
                'values': values,
                'condition': condition
                }
   
    global __flag_no
    current ['flags'].append (__flag_no)
    current [__flag_no] = entry

    __rules [rule_or_module] = current
    
    # Store all flags for a module
    m = __re_first_segment.match (rule_or_module)
    if m:
        module_ = m.group (1)
        if not __module_flags.has_key (module_): __module_flags [module_] = []
        __module_flags [module_].append (__flag_no)
        
    # Store flag-no -> rule_or_module mapping
    __flags_to_modules [__flag_no] = rule_or_module

    __flag_no += 1

###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#   # Make toolset 'toolset', defined in a module of the same name,
#   # inherit from 'base'
#   # 1. The 'init' rule from 'base' is imported into 'toolset' with full
#   #    name. Another 'init' is called, which forwards to the base one.
#   # 2. All generators from 'base' are cloned. The ids are adjusted and 
#   #    <toolset> property in requires is adjusted too
#   # 3. All flags are inherited
#   # 4. All rules are imported.
#   rule inherit ( toolset : base )
#   {
#       import $(base) ;
#       
#       inherit_generators $(toolset) : $(base) ;
#       inherit-flags $(toolset) : $(base) ;
#       inherit-rules $(toolset) : $(base) ;
#   }
#   
#   rule inherit-rules ( toolset : base )
#   {
#       # It appears that "action" creates local rule... 
#       local base_generators = [ generators.generators_for_toolset $(base) ] ;
#       local rules ;
#       for local g in $(base_generators)
#       {
#           local id = [ MATCH "[^.]*\.(.*)" : [ $(g).id ] ] ;
#           rules += $(id) ;
#       }    
#       IMPORT $(base) : $(rules) : $(toolset) : $(rules) : localized ;
#       # Import the rules to the global scope
#       IMPORT $(toolset) : $(rules) : : $(toolset).$(rules) ;
#   }
#   
