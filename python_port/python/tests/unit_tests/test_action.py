# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import action
from boost.build.exceptions import *

def rule1 (): pass
def rule2 (): pass
actions = ['command1', 'command2']

class TestAction (unittest.TestCase):
    
    def setUp (self):
        action.reset ()

        action.register ('gcc.compile.c', rule1, actions)
        action.register ('gcc.compile.c++', rule2, actions [0])

    def test_register (self):
        
        it = action.enumerate ()
        
        self.assertEqual (('gcc.compile.c', (rule1, actions)), it.next ())
        self.assertEqual (('gcc.compile.c++', (rule2, [actions [0]])), it.next ())

    def test_find (self):
        self.assertEqual (actions, action.find_action ('gcc.compile.c'))
        self.assertEqual (rule1, action.find_rule ('gcc.compile.c'))
        self.assertEqual (rule2, action.find_rule ('gcc.compile.c++'))

        self.assertRaises (NoAction, action.find_rule, 'gcc.link')
        self.assertRaises (NoAction, action.find_action, 'gcc.link')
    
    def test_override (self):
        action.register ('gcc.compile.c', rule2, None)
        self.assertEqual (rule2, action.find_rule ('gcc.compile.c'))
        self.assertEqual (actions, action.find_action ('gcc.compile.c'))

        action.register ('gcc.compile.c++', None, actions)
        self.assertEqual (rule2, action.find_rule ('gcc.compile.c++'))
        self.assertEqual (actions, action.find_action ('gcc.compile.c++'))

######################################################################
if __name__ == '__main__': unittest.main ()
