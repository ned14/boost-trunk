# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from boost.build.exceptions import NoAction

""" Manages actions.
    Actions are accosiated with rules.
    When a rule is invoked for a target, the corresponding action is set up.
    If the target needs to be updated, the action is excuted.
    TODO: plenty to do here, regarding the actions model, namely how to support different build systems.
    See bjam and SCons.
"""

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __all_actions

    __all_actions = {}

reset ()

def action (rule_name, actions):
    """ Associates 'actions' with 'rule_name', overwriting any action previosly defined for this rule.
        'actions' is a sequence of strings, which are passed to the shell.
        TODO: document variable expansion.
    """
    if isinstance (actions, str): 
        actions = [actions]

    __all_actions [str (rule_name)] = actions

def exists (rule_name):
    """ Returns true iff actions are associated with 'rule_name'.
    """
    return __all_actions.has_key (str (rule_name))

def find (rule_name):
    """ Finds the actions associated with a rule.
        Raises NoAction is none is found.
    """
    if not __all_actions.has_key (str (rule_name)):
        raise NoAction ("No action found for rule '%s'" % rule_name)
    
    return __all_actions [str (rule_name)]

def enumerate ():
    """ Returns an iterator for the actions map.
    """
    return __all_actions.iteritems ()
