# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from boost.build.engine.engine import BuildSystem

class LogBuildSystem (BuildSystem):
    """ A build system for testing purposes. Only stores the data.
    """
    def __init__ (self):
        self.variables_ = {}
        self.dependencies_ = {}
        self.actions_bindings_ = []

    def do_set_target_variable (self, target, variable, value):
        if not self.variables_.has_key (target):
            self.variables_ [target] = {}
        
        if not self.variables_ [target].has_key (variable):
            self.variables_ [target][variable] = []

        self.variables_ [target][variable].append (value)

    def do_add_dependency (self, target, source):
            if not self.dependencies_.has_key (target):
                self.dependencies_ [target] = []
            self.dependencies_ [target].append (source)

    def do_set_update_action (self, action_name, targets, sources):
        self.actions_bindings_.append ((action_name, targets, sources))
         
    def variables (self):
        return self.variables_

    def dependencies (self):
        return self.dependencies_

    def action_bindings (self):
        return self.actions_bindings_
