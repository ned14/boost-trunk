#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

from boost.build.util.utility import *
import property, feature
from boost.build.exceptions import *
from boost.build.util.sequence import unique

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
    """
    global __cache

    # A cache of property sets
    # TODO: use a map of weak refs?
    __cache = {}
    
reset ()


def create (raw_properties = []):
    """ Creates a new 'PropertySet' instance for the given raw properties,
        or returns an already existing one.
    """
    raw_properties.sort ()
    raw_properties = unique (raw_properties)
 
    key = '-'.join (raw_properties)

    if not __cache.has_key (key):
        __cache [key] = PropertySet (raw_properties)

    return __cache [key]

def create_with_validation (raw_properties):
    """ Creates new 'PropertySet' instances after checking
        that all properties are valid and converting incidental
        properties into gristed form.
    """
    property.validate (raw_properties)
    
    return create (property.make (raw_properties))

def empty ():
    """ Returns PropertySet with empty set of properties.
    """
    return create ()
    


class PropertySet:
    """ Class for storing a set of properties.
        - there's 1<->1 correspondence between identity and value. No
          two instances of the class are equal. To maintain this property,
          the 'PropertySet.create' rule should be used to create new instances.
          Instances are immutable.

        - each property is classified with regard to it's effect on build
          results. Incidental properties have no effect on build results, from
          Boost.Build point of view. Others are either free, or non-free, which we
          call 'base'. Each property belong to exactly one of those categories and
          it's possible to get list of properties in each category.

          In addition, it's possible to get list of properties with specific
          attribute.

        - several operations, like and refine and as_path are provided. They all use
          caching whenever possible.
    """
    def __init__ (self, raw_properties = []):

        self.raw_ = raw_properties
        
        self.incidental_ = []
        self.free_ = []
        self.base_ = []
        self.dependency_ = []
        self.non_dependency_ = []
        self.conditional_ = []
        self.non_conditional_ = []
        self.propagated_ = []
        self.link_incompatible = []
        
        # A cache of refined properties.
        self.refined_ = {}
        
        # A cache of property sets created by adding properties to this one.
        self.added_ = {}

        # Cache for the default properties.
        self.defaults_ = None

        # Cache for the expanded properties.
        self.expanded_ = None

        # Cache for the property set containing propagated properties.
        self.propagated_ps_ = None
        
        # A map of features to its values.
        self.feature_map_ = None
        
        # A tuple (target path, is relative to build directory)
        self.target_path_ = None
        
        self.as_path_ = None
        
        # A cache for already evaluated sets.
        self.evaluated = {}
        
        for p in raw_properties:
            if not get_grist (p):
                raise BaseException ("Invalid property: '%s'" % p)
            
            att = feature.attributes (get_grist (p))
            
            # A feature can be both incidental and free,
            # in which case we add it to incidental.
            if 'incidental' in att:
                self.incidental_.append (p)
            elif 'free' in att:
                self.free_.append (p)
            else:
                self.base_.append (p)
        
            if 'dependency' in att:
                self.dependency_.append (p)
            else:
                self.non_dependency_.append (p)
            
            if property.is_conditional (p):
                self.conditional_.append (p)
            else:
                self.non_conditional_.append (p)
                                    
            if 'propagated' in att:
                self.propagated_.append (p)

            if 'link_incompatible' in att:
                self.link_incompatible.append (p)
    
    def raw (self):
        """ Returns the list of stored properties.
        """
        return self.raw_
    
    def base (self):
        """ Returns properties that are neither incidental nor free.
        """
        return self.base_
    
    def free (self):
        """ Returns free properties which are not dependency properties.
        """
        return self.free_

    def dependency (self):
        """ Returns dependency properties.
        """
        return self.dependency_
    
    def non_dependency (self):
        """ Returns properties that are not dependencies.
        """
        return self.non_dependency_
    
    def conditional (self):
        """ Returns conditional properties.
        """
        return self.conditional_
        
    def non_conditional (self):
        """ Returns properties that are not conditional.
        """
        return self.non_conditional_
              
    def incidental (self):
        """ Returns incidental properties.
        """
        return self.incidental_
    
    def refine (self, requirements):
        """ Refines this set's properties using the requirements passed as an argument.
        """
        str_req = str (requirements)
        if not self.refined_.has_key (str_req):
            r = property.refine (self.raw (), requirements.raw ())

            # TODO: what's the idea? Can this be done using exceptions?
            if not "@error" in str (r):
                self.refined_ [str_req] = create (r)
            else:
                self.refined_ [str_req] = r

        return self.refined_ [str_req]

    def add (self, ps):
        """ Creates a new property set containing the properties in this one,
            plus the ones of the property set passed as argument.
        """
        if not self.added_.has_key (str (ps)):
            self.added_ [str (ps)] = create (self.raw_ + ps.raw ())
        return self.added_ [str (ps)]
    
    def add_raw (self, properties):
        """ Creates a new property set containing the properties in this one,
            plus the ones passed as argument.
        """
        return self.add (create (properties))

    def add_defaults (self):
        if self.defaults_ == None:
            expanded = feature.add_defaults (self.raw_)
            self.defaults_ = create (expanded)
        return self.defaults_

    def expand (self):
        if self.expanded_ == None:
            expanded = feature.expand (self.raw_)
            self.expanded_ = create (expanded)
        return self.expanded_

    def propagated (self):
        if not self.propagated_ps_:
            self.propagated_ps_ = create (self.propagated_)
        return self.propagated_ps_
    
    def get (self, feature):
        """ Returns all values of 'feature'.
        """
        if not self.feature_map_:
            self.feature_map_ = {}

            # For each feature, create member var and assign all
            # values to it. Since all regular member vars start with
            # 'self', there will be no conflicts between names.
            for v in self.raw_:
                key = get_grist (v)
                if not self.feature_map_.has_key (key):
                    self.feature_map_ [key] = []
                self.feature_map_ [get_grist (v)].append (replace_grist (v, ''))
        
        return self.feature_map_.get (feature, [])
    
###################################################################
# Still to port.
# Original lines are prefixed with "#   "
#
#       rule expand-composites ( )
#       {
#           if ! $(self.composites)
#           {
#               self.composites = [ PropertySet.create
#                   [ feature.expand-composites $(self.raw_) ] ] ;
#           }
#           return $(self.composites) ;
#       }

    def evaluate_conditionals (self, context = None):
        if not context: context = self

        if not self.evaluated.has_key (context):
            self.evaluated [context] = create (property.evaluate_conditionals_in_context (self.raw_, context.raw ()))

        return self.evaluated [context]
    
#       rule link_incompatible ( )
#       {
#           if ! $(self.link_incompatible-ps)
#           {
#               self.link_incompatible-ps = 
#                 [ PropertySet.create $(self.link_incompatible) ] ;
#           }
#           return $(self.link_incompatible-ps) ;
#       }
#       
#       
#       rule run-actions ( )
#       {
#           if ! $(self.run)
#           {
#               self.run = [ PropertySet.create [ feature.run-actions $(self.raw_) ] ] ;
#           }
#           return $(self.run) ;
#       }
    
    def as_path (self):
        if not self.as_path_:
            self.as_path_ = property.as_path (self.base_)

        return self.as_path_

    def target_path (self):
        """ Computes the target path that should be used for 
            target with these properties.
            Returns a tuple of
              - the computed path
              - if the path is relative to build directory, a value of
                'true'. 
        """
        if not self.target_path_:
            # The <location> feature can be used to explicitly
            # change the location of generated targets
            l = self.get ('<location>')
            if l:
                computed = l
                is_relative = False

            else:
                p = self.as_path ()
                
                # Really, an ugly hack. Boost regression test system requires
                # specific target paths, and it seems that changing it to handle
                # other directory layout is really hard. For that reason,
                # we teach V2 to do the things regression system requires.
                # The value o '<location-prefix>' is predended to the path.
                prefix = self.get ('<location-prefix>')
                
                if prefix:
                    if len (prefix) > 1:
                        raise AlreadyDefined ("Two <location-prefix> properties specified: '%s'" % prefix)
                        
                    computed = os.path.join (prefix [0], p)

                else:
                    computed = p

                is_relative = True

            self.target_path_ = (computed, is_relative)
            
        return self.target_path_
    
    
#       rule link_incompatible-with ( ps )
#       {
#           if ! $(.li.$(ps))
#           {
#               local li1 = [ $(__name__).link_incompatible ] ;
#               local li2 = [ $(ps).link_incompatible ] ;            
#               if [ set.equal $(li1) : $(li2) ] 
#               {
#                   .li.$(ps) = false ;
#               }
#               else
#               {
#                   .li.$(ps) = true ;
#               }            
#           }    
#           if $(.li.$(ps)) = true
#           {
#               return true ;
#           }
#           else
#           {
#               return ;
#           }                
#       }
#       
    
