# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import action
from boost.build.exceptions import *

class TestAction (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

    def test_action (self):
        rule1 = 'rule1'
        rule2 = 'rule2'
        actions = ['command1', 'command2']

        action.action (rule1, actions)
        action.action (rule2, actions [0])

        it = action.enumerate ()
        self.assertEqual ((rule2, actions [0:1]), it.next ())
        self.assertEqual ((rule1, actions), it.next ())
        self.assertRaises (StopIteration, it.next)

    def test_find (self):
        rule_name = 'rule1'
        actions = ['command1', 'command2']
        action.action (rule_name, actions)
        self.assertEqual (actions, action.find (rule_name))
        self.assertRaises (NoAction, action.find, 'foobar')
        
######################################################################
if __name__ == '__main__': unittest.main ()
