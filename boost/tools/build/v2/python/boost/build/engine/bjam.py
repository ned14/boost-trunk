# Copyright Pedro Ferreira 2005. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

from boost.build.build import action
import log_engine


class BjamBuildSystem (log_engine.LogBuildSystem):
    def __init__ (self):
        log_engine.LogBuildSystem.__init__ (self)
        self.all_targets_ = []

    def generate2(self):
        # TODO: __define_common_variables
        import bjam
        dependencies = self.dependencies ()
        result = ''
        for target, sources in dependencies.iteritems ():
            bjam.call('fffff')
        
    def generate (self):

        result = ''
        
        result += self.__define_common_variables ()
        result += '\n'
        result += self.__do_actions ()
        result += '\n'
        result += self.__do_variables ()
        result += '\n'
        result += self.__do_dependencies ()
        result += '\n'
        result += self.__do_action_bindings ()
        result += '\n'
        result += self.__do_depends_all ()
        return result

    def __define_common_variables (self):
        """ Define varialbes commonly used in update actions.
        """
        return '_ = " " ;\nSPACE = " " ;'
    
    def __quote (self, values):
        quoted = [ '"' + v + '"' for v in values ] 
        return ' '.join (quoted)
        
    def __do_variables (self):
        variables = self.variables ()
        result = ''
        for name, value in variables.iteritems ():
            for variable, values in value.iteritems ():
                result += variable + ' on "' + name + '" = ' + self.__quote (values)
                result += ' ;\n'
    
        return result

    def __do_dependencies (self):
        dependencies = self.dependencies ()
        result = ''
        for target, sources in dependencies.iteritems ():
            result += 'DEPENDS ' + target + ' : ' + self.__quote (sources) + ' ;\n'
        return result

    def __do_actions (self):
        result = ''
        for id, value in action.enumerate ():
            result += 'actions ' + id + '\n{\n'
            for v in value [1]:
                result += '    ' + v + '\n'
            result += '}\n\n'
                
        return result

    def __do_action_bindings (self):
        action_bindings = self.action_bindings ()
        result = ''
        for action, targets, sources in action_bindings:
            result += action + ' ' + self.__quote (targets) + ' : ' + self.__quote (sources) + ' ;\n'
            
            if not 'clean' in targets:
                self.all_targets_.extend (targets)
            
        return result

    def __do_depends_all (self):
        result = 'DEPENDS all : ' + '\n    '.join (self.all_targets_) + '\n    ;\n'
        result += """
local clean ;

if "--clean" in $(ARGV)
{
    clean = true ;
}

if $(clean)
{
    UPDATE clean ;
}
else
{
    UPDATE all ;
}
"""
        return result

