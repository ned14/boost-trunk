# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from boost.build.exceptions import NoAction
from boost.build.util.utility import split_action_id, to_seq

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

def register (id, rule, actions):
    """ Registers an action 'id' for a toolset.
        'id' is in the form 'toolset.specific_rule', where specific_rule is, e.g., compile.c++.
        'rule' is the function to be called during the set-up phase.
        'actions' is a sequence of string that are executed by the shell during the update phase.
        TODO: document variable expansion.
    """
    actions = to_seq (actions)

    if __all_actions.has_key (id):
        old = __all_actions [id]
        if not rule:
            rule = old [0]
        if not actions:
            actions = old [1]

    __all_actions [id] = (rule, actions)

def find_action (id):
    return __find (id) [1]

def find_rule (id):
    return __find (id) [0]

def enumerate ():
    return __all_actions.iteritems ()
    
def __find (id):
    """ Finds the actions associated with a rule.
        Raises NoAction is none is found.
    """
    v = __all_actions.get (id, None)

    if not v:
        raise NoAction ("No action found for rule '%s'" % id)

    return v


class BjamActionWrapper:
    """Class which allows to use actions defined in bjam.

       This class is a callable which takes a name of
       bjam action and can be used inside Python. Ideally, we should
       be able to use string as action name, but current code
       requires action to be callable.
    """

    def __init__(self, name):
        self.name_ = name
        self.__name__ = name

    def __call__(self, manager, targets, sources, properties):
        """Forwards the call to bjam."""
        print "Wrapper called"
        import bjam
        bjam.call(self.name_, targets, sources, properties)
        bjam.call('DEPENDS', targets, sources)

    def __str__(self):
        """This is called by the Action class to determine the
        name of bjam action. Returns the one passed to __init__."""
        return self.name_
    
