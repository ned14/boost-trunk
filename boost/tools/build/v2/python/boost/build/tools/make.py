#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

""" This module defines the 'make' main target rule.
"""
import os
from boost.build.build.targets import BasicTarget
from boost.build.build.virtual_target import FileTarget, Action
from boost.build.build import property_set, type
from boost.build.util.utility import replace_suffix
from boost.build.exceptions import *

class MakeTarget (BasicTarget):
    def __init__ (self, project, name, sources, requirements, make_rule, default_build):
        BasicTarget.__init__ (self, name, project, sources, requirements, default_build)
       
        if not callable (make_rule):
            raise BaseException ("make rule '%s' must be callable" % make_rule)
            
        self.project_ = project
        self.make_rule_ = make_rule
        
    def construct (self, name, source_targets, ps):
        a = Action (self.manager_, source_targets, self.make_rule_, ps)
        t = FileTarget (self.name_, True, type.type (self.name_), self.project_, a)

        return (property_set.empty (), [ self.manager ().virtual_targets ().register (t) ])

def make (project, target_name, sources, generating_rule, requirements):
    """ Declares the 'make' main target.
    """
    targets = project.manager ().targets ()
    
    targets.main_target_alternative (MakeTarget (project.target (), 
        target_name,
        targets.main_target_sources (sources, target_name),
        targets.main_target_requirements (requirements, project.target ()),
        generating_rule,
        targets.main_target_default_build ([], project.target ())))

import boost.build.build.project
boost.build.build.project.ProjectModule.__dict__ ['make'] = make
