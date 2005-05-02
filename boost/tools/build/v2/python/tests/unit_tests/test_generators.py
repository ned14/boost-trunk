# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import unittest, helpers
######################################################################

from boost.build.build import generators, type, property_set, feature, virtual_target
from boost.build.manager import Manager

class TestGenerators (unittest.TestCase):
    
    def setUp (self):
        helpers.reset ()

        self.manager_ = Manager (None)
        self.logger_ = self.manager_.logger ()
    
        type.register ('A', ['a'])
        type.register ('B', ['b'])
        type.register ('C', ['c'])
        type.register ('D', ['d'], 'B')
        type.register ('E', ['e'])
        
        feature.feature ('define', [], ['free'])

        g = generators.register_standard ('a_b', ['A'], ['B'], ['<define>XYZ'])
        g = generators.register_standard ('a_b_define_ABC', ['A'], ['B'], ['<define>ABC'])
        g = generators.register_standard ('ab_c', ['A', 'B'], ['C'])
        g = generators.register_standard ('a_e', ['A'], ['E'])
        
    def test_register (self):
        self.assertEqual ('a_b', generators.find ('a_b').id ())
        self.assertEqual ('a_b_define_ABC', generators.find ('a_b_define_ABC').id ())
        
    def test_construct (self):
        project = self.manager_.projects ().create ('.')
        name = None
        target_type = 'B'
        multiple = False
        prop_set = property_set.create (['<define>ABC'])
        sources = [ self.manager_.virtual_targets ().from_file ('1.a', project.target ()) ]
        allowed_type = None
        targets = generators.construct (project, name, target_type, multiple, prop_set, sources, allowed_type)
        # TODO: check return value
#        self.assert_ (targets)

    def test_find_viable_generators_aux (self):
        target_type = 'B'
        prop_set1 = property_set.create (['<define>ABC'])
        viable = generators.find_viable_generators_aux (self.logger_, target_type, prop_set1)
        self.assertEqual (1, len (viable))
        
        prop_set2 = property_set.create (['<define>ABC', '<define>XYZ'])
        viable = generators.find_viable_generators_aux (self.logger_, target_type, prop_set2)
        self.assertEqual (2, len (viable))

    def test_find_viable_generators (self):
        target_type = 'B'
        prop_set1 = property_set.create (['<define>ABC'])
        viable = generators.find_viable_generators (self.logger_, target_type, prop_set1)
        self.assertEqual (1, len (viable))
        
        prop_set2 = property_set.create (['<define>ABC', '<define>XYZ'])
        viable = generators.find_viable_generators (self.logger_, target_type, prop_set2)
        self.assertEqual (2, len (viable))
        
        # Check cache.
        viable = generators.find_viable_generators (self.logger_, target_type, prop_set2)
        self.assertEqual (2, len (viable))
        # TODO: check overrides
        
    def test_try_one_generator (self):
        project = self.manager_.projects ().create ('.')
        name = None
        multiple = False
        target_type = 'B'
        prop_set = property_set.create ([])
        sources = [ self.manager_.virtual_targets ().from_file ('1.a', project.target ()) ]

        g = generators.find ('a_b')
        (usage, targets) = generators.try_one_generator (project, name, g, multiple, target_type, prop_set, sources)
        self.assertEqual (property_set.empty (), usage)
        self.assertEqual (1, len (targets))
        self.assertEqual ('1.b', targets [0].name ())
    
        r = generators.try_one_generator (project, name, generators.find ('ab_c'), multiple, target_type, prop_set, sources)
        # TODO: check result
    
        r = generators.try_one_generator (project, name, generators.find ('a_e'), multiple, target_type, prop_set, sources)
        # TODO: check result
    
    def test_viable_source_types_for_generator (self):
        self.assertEqual (['A'], generators.viable_source_types_for_generator (generators.find ('a_b')))
        self.assertEqual (['A', 'B', 'D'], generators.viable_source_types_for_generator (generators.find ('ab_c')))
    
    def test_convert_to_consumable_types (self):
        # TODO: implement this
        pass
    
    def test_convert_multiple_sources_to_consumable_types (self):
        # TODO: implement this
        pass

    def test_composing_generator (self):
        # TODO: implement this
        pass

    def test_clone (self):
        original_g = generators.find ('a_b_define_ABC')
        new_g = original_g.clone ('new_a_b', ['<define>NEW_GEN'])
        self.assertEqual ('new_a_b', new_g.id ())
        self.assertEqual (['<define>ABC', '<define>NEW_GEN'], new_g.requirements ())

######################################################################
if __name__ == '__main__': unittest.main ()
