# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from build.virtual_target import VirtualTargetRegistry
from build.targets import TargetRegistry
from build.project import ProjectRegistry
from boost.build.util.logger import NullLogger
from build import build_request, property_set, feature

class Manager:
    """ This class is a facade to the Boost.Build system.
        It serves as the root to access all data structures in use.
    """
	
    def __init__ (self, engine):
        """ Constructor.
            engine: the build engine that will actually construct the targets.
        """
        self.engine_ = engine
        self.virtual_targets_ = VirtualTargetRegistry (self)
        self.projects_ = ProjectRegistry (self)
        self.targets_ = TargetRegistry ()
        self.logger_ = NullLogger ()
        
        # Object Map.
        # TODO: This is a kludge: maps object names to the actual instances.
        # Sometimes, objects are stored in properties, along with some grist.
        # This map is used to store the value and return an id, which can be later on used to retriev it back.
        self.object_map_ = {}
        
    def scanners (self):
        return self.scanners_

    def engine (self):
        return self.engine_
        
    def virtual_targets (self):
        return self.virtual_targets_

    def targets (self):
        return self.targets_

    def projects (self):
        return self.projects_
    
    def logger (self):
        return self.logger_

    def set_logger (self, logger):
        self.logger_ = logger

    def register_object (self, value):
        """ Stores an object in a map and returns a key that can be used to retrieve it.
        """
        key = 'object_registry_' + str (value)
        self.object_map_ [key] = value
        return key
    
    def get_object (self, key):
        """ Returns a previously registered object.
        """
        if not isinstance (key, str):
            # Probably it's the object itself.
            return key
            
        return self.object_map_ [key]

    def construct (self, properties = [], targets = []):
        """ Constructs the dependency graph.
            properties:  the build properties.
            targets:     the targets to consider. If none is specified, uses all.
        """
        property_groups = build_request.expand_no_defaults (properties)

        virtual_targets = []
        for p in property_groups:
            build_properties = property_set.create (feature.split (p))
        
            for target in targets:
                result = target.generate (build_properties)
                virtual_targets.extend (result [1])

        actual_targets = []
        for virtual_target in virtual_targets:
            actual_targets.extend (virtual_target.actualize ())
    