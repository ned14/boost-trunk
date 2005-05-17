#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

import property
from boost.build.exceptions import *

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __scanners, __scanner_cache

    # Maps registered scanner classes to relevant properties
    __scanners = {}
    
    # A cache of scanners.
    # The key is: class_name.properties_tag, where properties_tag is the concatenation 
    # of all relevant properties, separated by '-'
    __scanner_cache = {}
    
reset ()


def register (scanner_class, relevant_properties):
    """ Registers a new generator class, specifying a set of 
        properties relevant to this scanner.  Ctor for that class
        should have one parameter: list of properties.
    """
    __scanners [str (scanner_class)] = relevant_properties

def registered (scanner_class):
    """ Returns true iff a scanner of that class is registered
    """
    return __scanners.has_key (str (scanner_class))
    
def get (scanner_class, properties):
    """ Returns an instance of previously registered scanner
        with the specified properties.
    """
    scanner_name = str (scanner_class)
    
    if not registered (scanner_name):
        raise BaseException ("attempt to get unregisted scanner: %s" % scanner_name)

    relevant_properties = __scanners [scanner_name]
    r = property.select (relevant_properties, properties)

    scanner_id = scanner_name + '.' + '-'.join (r)
    
    if not __scanner_cache.has_key (scanner_name):
        __scanner_cache [scanner_name] = scanner_class (r)

    return __scanner_cache [scanner_name]
 

class Scanner:
    """ Base scanner class.
    """
    def __init__ (self):
        pass
    
    def pattern (self):
        """ Returns a pattern to use for scanning.
        """
        raise BaseException ("method must be overriden")

    def process (self, target, matches):
        """ Establish necessary relationship between targets,
            given actual target beeing scanned, and a list of
            pattern matches in that file.
        """
        raise BaseException ("method must be overriden")


###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#   #  Implements scanners: objects that compute implicit dependencies for
#   #  files, such as includes in C++.
#   #
#   #  Scanner has a regular expression used to find dependencies, some
#   #  data needed to interpret those dependencies (for example, include
#   #  paths), and a code which actually established needed relationship
#   #  between actual jam targets.
#   #
#   #  Scanner objects are created by actions, when they try to actualize
#   #  virtual targets, passed to 'virtual-target.actualize' method and are
#   #  then associated with actual targets. It is possible to use
#   #  several scanners for a virtual-target. For example, a single source
#   #  might be used by to compile actions, with different include paths.
#   #  In this case, two different actual targets will be created, each 
#   #  having scanner of its own.
#   #
#   #  Typically, scanners are created from target type and action's 
#   #  properties, using the rule 'get' in this module. Directly creating
#   #  scanners is not recommended, because it might create many equvivalent
#   #  but different instances, and lead in unneeded duplication of
#   #  actual targets. However, actions can also create scanners in a special
#   #  way, instead of relying on just target type.
#   
#   import "class" : new ;
#   import property virtual-target ;
#   
#   # Common scanner class, which can be used when there's only one
#   # kind of includes (unlike C, where "" and <> includes have different
#   # search paths).
#   class common-scanner : scanner 
#   {
#       import scanner ;
#       rule __init__ ( includes * )
#       {
#           scanner.__init__ ;
#           self.includes = $(includes) ;
#       }
#               
#       rule process ( target : matches * : binding )
#       {
#           local target_path = [ NORMALIZE_PATH $(binding:D) ] ;
#   
#           NOCARE $(matches) ;
#           INCLUDES $(target) : $(matches) ;
#           SEARCH on $(matches) = $(target_path) $(self.includes:G=) ;
#       
#           scanner.propagate $(__name__) : $(matches) : $(target) ;     
#       }
#   }



class ScannerRegistry:
    
    def __init__ (self, manager):
        self.manager_ = manager

    def install (self, scanner, target, vtarget):
        """ Installs the specified scanner on actual target 'target'. 
            vtarget: virtual target from which 'target' was actualized.
        """
        # TODO: actaully implement this
#        HDRSCAN on $(target) = [ $(scanner).pattern ] ;
#        SCANNER on $(target) = $(scanner) ;
#        HDRRULE on $(target) = scanner.hdrrule ;
        
        # scanner reflects difference in properties affecting    
        # binding of 'target', which will be known when processing
        # includes for it, will give information on how to
        # interpret quoted includes.
#        HDRGRIST on $(target) = $(scanner) ;
        pass

#   # Propagate scanner setting from 'including-target' to 'targets'.
#   rule propagate ( scanner : targets * : including-target )
#   {
#       HDRSCAN on $(targets) = [ on $(including-target) return $(HDRSCAN) ] ;
#       SCANNER on $(targets) = $(scanner) ;
#       HDRRULE on $(targets) = scanner.hdrrule ;
#       HDRGRIST on $(targets) = [ on $(including-target) return $(HDRGRIST) ] ;
#   }
#   
#   
#   rule hdrrule ( target : matches * : binding )
#   {
#       local scanner = [ on $(target) return $(SCANNER) ] ;
#       $(scanner).process $(target) : $(matches) : $(binding) ;
#   }
#   # hdrrule must be available at global scope so that it can be invoked
#   # by header scanning
#   IMPORT scanner : hdrrule : : scanner.hdrrule ;
#   
#   
#   
#   
