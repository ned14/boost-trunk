# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

class BuildSystem:
    """ The abstract interface to a build system.
    """
    def __init__ (self):
        pass

    def add_dependency (self, targets, sources):
        if isinstance (targets, str):
            targets = [targets]
        if isinstance (sources, str):
            sources = [sources]

        for target in targets:
            for source in sources:
                self.do_add_dependency (target, source)
    
    def set_target_variable (self, targets, variable, value):
        """ Sets a target variable.
            When building 'target', 'variable' will be set with 'value'
        """
        if isinstance (targets, str): 
            targets = [targets]

        for target in targets:
            self.do_set_target_variable (target, variable, value)

    def set_update_action (self, action_name, targets, sources):
        """ Binds a target to the corresponding update action.
            If target needs to be updated, the action registered with action_name will be used.
        """
        if isinstance (targets, str): 
            targets = [targets]
        self.do_set_update_action (action_name, targets, sources)

    # Overridables

    def build (self):
    	    """ Builds all targets in the dependency tree.
    	    """
    	    pass

    def clean (self):
    	    """ Cleans all targets in the dependency tree.
    	    """
    	    pass

    def add_not_file_target (self, target):
        """ Adds a target that is not a file.
        """
        pass

    def do_set_target_variable (self, target, variable, value):
        """ Sets a target variable.
            When building 'target', 'variable' will be set with 'value'
        """
        pass

    def do_add_dependency (self, target, source):
        """ Should be redefined by base classes.
            Sets a dependency between one target and one source.
        """
        pass

    def do_set_update_action (self, action_name, targets, sources):
        """ Binds a target to the corresponding update action.
            If target needs to be updated, the action registered with action_name will be used.
        """
        pass
         
        