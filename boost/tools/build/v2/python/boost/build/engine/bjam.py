# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from boost.build.build import action
bjam_interface = __import__('bjam')
import log_engine


class BjamBuildSystem (log_engine.LogBuildSystem):
    def __init__ (self):
        log_engine.LogBuildSystem.__init__ (self)
        self.all_targets_ = []

    def do_set_update_action (self, action_name, targets, sources):
        bjam_interface.call("set-update-action", action_name, targets, sources)

    def do_set_target_variable (self, target, variable, value):
        bjam_interface.call("set-target-variable", target, variable, value)
    
    def do_add_dependency (self, target, source):
        bjam_interface.call("DEPENDS", target, source)
        
