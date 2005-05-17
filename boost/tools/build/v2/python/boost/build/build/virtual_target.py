#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

#  Implements virtual targets, which correspond to actual files created during
#  build, but are not yet targets in Jam sense. They are needed, for example,
#  when searching for possible transormation sequences, when it's not known
#  if particular target should be created at all.
#
#
#                       +--------------------------+
#                       | VirtualTarget           |
#                       +==========================+
#                       | actualize                |
#                       +--------------------------+
#                       | actualize_action() = 0   |
#                       | actualize_location() = 0 |
#                       +----------------+---------+
#                                        |
#                                        ^
#                                       / \
#                                      +-+-+
#                                        |
#    +---------------------+     +-------+--------------+
#    | Action              |     | AbstractFileTarget   |
#    +=====================|   * +======================+
#    | action_name         |  +--+ action               |
#    | properties          |  |  +----------------------+
#    +---------------------+--+  | actualize_action()   |
#    | actualize()         |0..1 +-----------+----------+
#    | path()              |                 |
#    | adjust_properties() | sources         |
#    | actualize_sources() | targets         |
#    +------+--------------+                 ^
#           |                               / \
#           ^                              +-+-+
#          / \                               |
#         +-+-+                +-------------+-------------+
#           |                  |                           |
#           |           +------+---------------+  +--------+-------------+
#           |           | FileTarget           |  | SearchedLibTarget    |
#           |           +======================+  +======================+
#           |           | actualize-location() |  | actualize-location() |
#           |           +----------------------+  +----------------------+
#           |
#         +-+------------------------------+
#         |                                |
#    +----+----------------+     +---------+-----------+
#    | CompileAction       |     | LinkAction          |
#    +=====================+     +=====================+
#    | adjust_properties() |     | adjust_properties() |
#    +---------------------+     | actualize_sources() |
#                                +---------------------+
#
# The 'CompileAction' and 'LinkAction' classes are defined not here,
# but in builtin.jam modules. They are shown in the diagram to give
# the big picture.

import re
import os.path
import string

from boost.build.util import path, utility, set
from boost.build.util.utility import add_grist, get_grist, ungrist, replace_grist
from boost.build.util.sequence import unique
from boost.build.tools import common
from boost.build.exceptions import *
import toolset, type, action

__re_starts_with_at = re.compile ('^@(.*)')

class VirtualTargetRegistry:
    def __init__ (self, manager):
        self.manager_ = manager
        
        # A cache for FileTargets
        self.files_ = {}

        # A cache for targets.
        self.cache_ = {}
        
        # A map of actual names to virtual targets.
        self.actual_ = {}
        
    def register (self, target):
        """ Registers a new virtual target. Checks if there's already registered target, with the same
            name, type, project and subvariant properties, and also with the same sources
            and equal action. If such target is found it is retured and 'target' is not registered.
            Otherwise, 'target' is registered and returned.
        """
        # TODO: the original was
        #     local signature = [ sequence.join [ $(target).name ] : - ] ;    
        # is the join needed?
        # signature = '-'.join (target_name)
        signature = target.name ()

        result = None
        if not self.cache_.has_key (signature):
            self.cache_ [signature] = []

        for t in self.cache_ [signature]:
            a1 = t.action ()
            a2 = target.action ()
            
            if not result:
                if not a1 and not a2:
                    result = t
                else:
                    if a1 and a2 and a1.action_name () == a2.action_name () and a1.sources () == a2.sources ():
                        ps1 = a1.properties ()
                        ps2 = a2.properties ()
                        p1 = ps1.base () + ps1.free () + ps1.dependency ()
                        p2 = ps2.base () + ps2.free () + ps2.dependency ()
                        if p1 == p2:
                            result = t
        
        if not result:
            self.cache_ [signature].append (target)
            result = target
    
        return result

    def from_file (self, file, project):
        """ Creates a virtual target with appropriate name and type from 'file'.
            If a target with that name in that project was already created, returns that already
            created target.
            FIXME: more correct way would be to compute path to the file, based on name and source location
            for the project, and use that path to determine if the target was already created.
        """
        # Check if we've created a target corresponding to this file.
        source_location = project.get ('source-location')
        project_path = path.root (path.root (path.make (file), source_location), path.pwd ())

        if self.files_.has_key (project_path):
            return self.files_ [project_path]

        name = path.make (file)
        file_type = type.type (file)

        if not file_type:
            # warning "cannot determine type for file $(file)" ;
            result = FileTarget (file, False, None, project)
        else:
            v = FileTarget (name, False, file_type, project)
            result = v
        
        self.files_ [project_path] = result
        return result

    def add_suffix (self, specified_name, file_type, prop_set):
        """ Appends the suffix appropriate to 'type/property_set' combination
            to the specified name and returns the result.
        """
        suffix = type.generated_target_suffix (file_type, prop_set)

        if suffix:
            return specified_name + '.' + suffix

        else:
            return specified_name
    
    def register_actual_name (self, actual_name, virtual_target):
        if self.actual_.has_key (actual_name):
            cs1 = self.actual_ [actual_name].creating_subvariant ()
            cs2 = virtual_target.creating_subvariant ()
            cmt1 = cs1.main_target ()
            cmt2 = cs2.main_target ()            
            
            action1 = self.actual_ [actual_name].action ()
            action2 = virtual_target.action ()
            
            properties_added = []
            properties_removed = []
            if action1 and action2:
                p1 = action1.properties ()
                p1 = p1.raw ()
                p2 = action2.properties ()
                p2 = p2.raw ()
                
                properties_removed = set.difference (p1, p2)
                if not properties_removed: properties_removed = "none"

                properties_added = set.difference (p2, p1)
                if not properties_added: properties_added = "none"

            raise BaseException ("Duplicate name of actual target: '%s'\n" 
              "previous virtual target '%s'\n"
              "created from '%s'\n"
              "another virtual target '%s'\n"
              "created from '%s'\n"
              "added properties: '%s'\n"
              "removed properties: '%s'\n" % (actual_name,
                  self.actual_ [actual_name], cmt1.location (), virtual_target, 
                  cmt2.location (), properties_added, properties_removed))

        else:
            self.actual_ [actual_name] = virtual_target



class VirtualTarget:
    """ Potential target. It can be converted into jam target and used in
        building, if needed. However, it can be also dropped, which allows
        to search for different transformation and select only one.
        name:    name of this target.
        project: project to which this target belongs.
    """
    def __init__ (self, name, project):
        self.name_ = name
        self.project_ = project
        self.dependencies_ = []
        
        # Caches if dapendencies for scanners have already been set.
        self.made_ = {}

    def name (self):
        """ Name of this target.
        """
        return self.name_

    def project (self):
        """ Project of this target.
        """
        return self.project_


    def depends (self, d):
        """ Adds additional instances of 'VirtualTarget' that this
            one depends on.
        """
        self.dependencies_ = unique (self.dependencies_ + d).sort ()

    def dependencies (self):
        return self.dependencies_

    def actualize (self, scanner = None):
        """ Generates all the actual targets and sets up build actions for
            this target.
            
            If 'scanner' is specified, creates an additional target
            with the same location as actual target, which will depend on the
            actual target and be associated with 'scanner'. That additional
            target is returned. See the docs (#dependency_scanning) for rationale.
            Target must correspond to a file if 'scanner' is specified.
            
            If scanner is not specified, then actual target is returned.
        """
        actual_name = self.actualize_no_scanner ()

        if not scanner:
            return actual_name

        else:
            # Add the scanner instance to the grist for name.
            g = '-'.join ([ungrist (get_grist (actual_name)), str (scanner)])

            name = replace_grist (actual_name, '<' + g + '>')

            if not self.made_.has_key (name):
                self.made_ [name] = True

                self.project_.manager ().engine ().add_dependency (name, actual_name)

                self.actualize_location (name)

                self.project_.manager ().scanners ().install (scanner, name, str (self))

            return name

# private: (overridables)

    def actualize_action (self, target):
        """ Sets up build actions for 'target'. Should call appropriate rules
            and set target variables.
        """
        raise BaseException ("method should be defined in derived classes")

    def actualize_location (self, target):
        """ Sets up variables on 'target' which specify its location.
        """
        raise BaseException ("method should be defined in derived classes")
    
    def path (self):
        """ If the target is generated one, returns the path where it will be
            generated. Otherwise, returns empty list.
        """
        raise BaseException ("method should be defined in derived classes")
    
    def actual_name (self):
        """ Return that actual target name that should be used
            (for the case where no scanner is involved)
        """
        raise BaseException ("method should be defined in derived classes")

    def actualize_no_scanner (self):
        name = self.actual_name ()

        # Do anything only on the first invocation
        if not self.made_.has_key (name):
            self.made_ [name] = True
            
            self.project_.manager_.virtual_targets ().register_actual_name (name, self)

            for i in self.dependencies_:
                self.manager_.engine ().add_dependency (name, i.actualize ())

            self.actualize_location (name)
            self.actualize_action (name)

        return name




    
class AbstractFileTarget (VirtualTarget):
    """ Target which correspond to a file. The exact mapping for file
        is not yet specified in this class. (TODO: Actually, the class name
        could be better...)
        
        May be a source file (when no action is specified), or
        derived file (otherwise).
        
        The target's grist is concatenation of project's location,
        properties of action (for derived files), and, optionally,
        value identifying the main target.
        
        exact:  If non-empty, the name is exactly the name
                created file should have. Otherwise, the '__init__'
                method will add suffix obtained from 'type' by
                calling 'type.generated-target-suffix'.
                  
        type:   optional type of this target.
    """
    def __init__ (self, name, exact, type, project, action = None):
        VirtualTarget.__init__ (self, name, project)
            
        self.type_ = type

        self.action_ = action
        self.exact_name = exact
        
        if action:
            action.add_targets ([self])
 
            if self.type and not exact:
                self.__adjust_name (name)
        
        self.actual_name_ = None
        self.path_ = None
        self.intermediate_ = False
        self.creating_subvariant_ = None
        
        # True if this is a root target.
        self.root_ = False

    def type (self):
        return self.type_

    def set_type (self, type):
        self.type_ = type

        if not self.exact_name:
            self.__adjust_name (os.path.splitext (self.name_) [0])

    def set_path (self, path):
        """ Sets the path. When generating target name, it will override any path
            computation from properties.
        """
        self.path_ = path.native (path)

    def action (self):
        """ Returns the action.
        """
        return self.action_

    def root (self, set = None):
        """ Sets/gets the 'root' flag. Target is root is it directly correspods to some
            variant of a main target.
        """
        if set:
            self.root_ = True
        return self.root_

    def set_intermediate (self, value):
        self.intermediate_ = value
    
    def intermediate (self):
        return self.intermediate_

        """ Gets or sets the subvariant which created this target. Subvariant
            is set when target is brought into existance, and is never changed
            after that. In particual, if target is shared by subvariant, only 
            the first is stored.
            s:  If specified, specified the value to set,
                which should be instance of 'subvariant' class.
        """
    def creating_subvariant (self, s = None):

        if s and not self.creating_subvariant ():
            if self.creating_subvariant ():
                raise BaseException ("Attempt to change 'dg'")

            else:
                self.creating_subvariant_ = s

        return self.creating_subvariant_

    def actualize_action (self, target):
        if self.action_:
            self.action_.actualize ()
          
#       # Return a human-readable representation of this target
#       #
#       # If this target has an action, that's:
#       #
#       #    { <action_name>-<self.name_>.<self.type_> <action-sources>... }
#       #
#       # otherwise, it's:
#       #
#       #    { <self.name_>.<self.type_> }
#       #
#       rule str ( )
#       {
#           local action = [ action ] ;
#           
#           local name-dot-type = [ sequence.join $(self.name_) "."  $(self.type_) ] ;
#           
#           if $(action)
#           {
#               local sources = [ $(action).sources ] ;
#               
#               local action_name =  [ $(action).action_name ] ;            
#   
#               local ss ;            
#               for local s in $(sources)
#               {
#                   ss += [ $(s).str ] ;
#               }
#               
#               return "{" $(action_name)-$(name-dot-type) $(ss) "}" ;
#           }
#           else
#           {
#               return "{" $(name-dot-type) "}" ;
#           }
#       }
#   
#       rule less ( a )
#       {
#           if [ str ] < [ $(a).str ]
#           {
#               return true ;
#           }
#       }
#   
#       rule equal ( a )
#       {
#           if [ str ] = [ $(a).str ]
#           {
#               return true ;
#           }
#       }
#   
#   # private:

    def actual_name (self):
        if not self.actual_name_:
            grist = self.grist ()
            
            basename = path.native (self.name_)
            self.actual_name_ = '<' + grist + '>' + basename

        return self.actual_name_

    def grist (self):
        """Helper to 'actual_name', above. Compute unique prefix used to distinguish
            this target from other targets with the same name which create different
            file.
        """
        # Depending on target, there may be different approaches to generating
        # unique prefixes. We'll generate prefixes in the form 
        # <one letter approach code> <the actual prefix>
        path = self.path ()
        
        if path:
            # The target will be generated to a known path. Just use the path
            # for identification, since path is as unique as it can get.
            return 'p' + path

        else:
            # File is either source, which will be searched for, or is not a file at
            # all. Use the location of project for distinguishing.
            project_location = self.project_.get ('location')
            location_grist = '!'.join (string.split (project_location, '/'))
            
            if self.action_:
                ps = self.action_.properties ()
                property_grist = ps.as_path ()
                # 'property_grist' can be empty when 'ps' is an empty
                # property set.
                if property_grist:
                    location_grist = location_grist + '/' + property_grist
                        
            return 'l' + location_grist


    def __adjust_name (self, specified_name):
        if self.action_:
            ps = self.action_.properties ()
        else:
            ps = propery_set.empty ()

        tag = ps.get ('<tag>')

        if tag:
            if len (tag) > 1:
                raise BaseException ("<tag>@rulename is present but is not the only <tag> feature")
            rule_name = __re_starts_with_at.match (tag [0])
            if rule_name:
                self.name_ = rule_name (specified_name, self.type, ps)
            else:
                raise BaseException ("The value of the <tag> feature must be '@rule-name'")
        
        # If there's no tag or the tag rule returned nothing.
        if not tag or not self.name_:
            self.name_ = self.project_.manager ().virtual_targets ().add_suffix (specified_name, self.type_, ps)    



class FileTarget (AbstractFileTarget):
    """ File target with explicitly known location.

        The file path is determined as
           - value passed to the 'set_path' method, if any
           - for derived files, project's build dir, joined with components
             that describe action's properties. If the free properties
             are not equal to the project's reference properties
             an element with name of main target is added.
           - for source files, project's source dir
        
        The file suffix is
            - the value passed to the 'suffix' method, if any, or
            - the suffix which correspond to the target's type.
    """
    def __init__ (self, name, exact, type, project, action = None):
        AbstractFileTarget.__init__ (self, name, exact, type, project, action)
        
    def actualize_location (self, target):
        engine = self.project_.manager_.engine ()

        if self.action_:
            # This is a derived file.
            file_path = self.path ()
            engine.set_target_variable (target, 'LOCATE', file_path)

            # Make sure the path exists.
            engine.set_target_variable (target, 'LOCATE', file_path)
            engine.add_dependency (target, file_path)
            engine.set_update_action ('MkDir', file_path, [])

        else:
            # This is a source file.
            engine.set_target_variable (target, 'SEARCH', path.native (self.project_.get ('source-location')))
    

    def path (self):
        """ Returns the directory for this target.
        """
        if not self.path_:
            if self.action_:
                p = self.action_.properties ()
                target_path = p.target_path ()
                
                if target_path [1] == True:
                    # Indicates that the path is relative to
                    # build dir.
                    target_path = os.path.join (self.project_.build_dir (), target_path [0])
                                
                # Store the computed path, so that it's not recomputed
                # any more
                self.path_ = path.native (target_path)

        return self.path_


#   class notFileTarget : AbstractFileTarget
#   {
#       rule __init__ ( name : project )
#       {
#           AbstractFileTarget.__init__ $(name) : : $(project) ;
#       }
#       
#       # Returns nothing, to indicate that target path is not known.
#       rule path ( )
#       {
#           return ;
#       }
#               
#       rule actualize-location ( target )
#       {
#           NOTFILE $(target) ;
#           ALWAYS $(target) ;
#       }    
#   }    



class Action:
    """ Class which represents an action.
        Both 'targets' and 'sources' should list instances of 'VirtualTarget'.
        Action name should name a rule with this prototype
            rule action_name ( targets + : sources * : properties * )
        Targets and sources are passed as actual jam targets. The rule may
        not establish dependency relationship, but should do everything else.
    """
    def __init__ (self, manager, sources, action_name, prop_set):
        self.sources_ = sources
        self.action_name_ = action_name        
        self.properties_ = prop_set

        self.manager_ = manager
        self.engine_ = self.manager_.engine ()
        self.targets_ = []

        # Indicates whether this has been actualized or not.
        self.actualized_ = False
        
        self.dependency_only_sources_ = []
        self.actual_sources_ = []
        
    def add_targets (self, targets):
        self.targets_ += targets

    def targets (self):
        return self.targets_

    def sources (self):
        return self.sources_

    def action_name (self):
        return self.action_name_

    def properties (self):
        return self.properties_

    def actualize (self):
        """ Generates actual build instructions.
        """
        if self.actualized_:
            return
            
        self.actualized = True

        ps = self.properties ()
        properties = self.adjust_properties (ps)
        actual_targets = []
        
        for i in self.targets ():
            actual_targets.append (i.actualize ())

        self.actualize_sources (self.sources (), properties)

        self.engine_.add_dependency (actual_targets, self.actual_sources_ + self.dependency_only_sources_)

        raw_properties = properties.raw ()

        # TODO: check the comment below. Was self.action_name_ [1]
        # Action name can include additional argument to rule, which should not
        # be passed to 'set-target-variables'
        toolset.set_target_variables (self.manager_, self.action_name_, actual_targets, raw_properties)
        
        rule = action.find_rule (self.action_name_)
        rule (self.manager_, actual_targets, self.actual_sources_, raw_properties)
        
        engine = self.manager_.engine ()
        action_name = str (self.action_name_)

        #if not action.exists (action_name):
        #    raise NoAction ("No action defined for rule '%s'" % action_name)
        
        self.manager_.engine ().set_update_action (self.action_name_, actual_targets, self.actual_sources_)
        
        # Since we set up creating action here, we also set up
        # action for cleaning up
        self.manager_.engine ().set_update_action ('Clean', 'clean', actual_targets)

        return actual_targets

    def actualize_source_type (self, sources, prop_set):
        """ Helper for 'actualize_sources'.
            For each passed source, actualizes it with the appropriate scanner.
            Returns the actualized virtual targets.
        """
        result = []
        for i in sources:
            scanner = None
            
            if isinstance (i, str):
                i = self.manager_.get_object (i)
                
            if i.type ():
                scanner = type.get_scanner (i.type (), prop_set)

            result.append (i.actualize (scanner))
        
        return result
    
    def actualize_sources (self, sources, prop_set):
        """ Creates actual jam targets for sources. Initializes two member
            variables:
            'self.actual_sources_' -- sources which are passed to updating action
            'self.dependency_only_sources_' -- sources which are made dependencies, but
            are not used otherwise.
            
            New values will be *appended* to the variables. They may be non-empty,
            if caller wants it.
        """
        dependencies = self.properties_.get ('<dependency>')
                
        self.dependency_only_sources_ += self.actualize_source_type (dependencies, prop_set)
        self.actual_sources_ += self.actualize_source_type (sources, prop_set)

    def adjust_properties (self, prop_set):
        """ Determines real properties when trying building with 'properties'.
            This is last chance to fix properties, for example to adjust includes
            to get generated headers correctly. Default implementation returns
            its argument.
        """
        return prop_set


class NullAction (Action):
    """ Action class which does nothing --- it produces the targets with
        specific properties out of nowhere. It's needed to distinguish virtual
        targets with different properties that are known to exist, and have no 
        actions which create them.
    """
    def __init__ (self, manager, prop_set):
        Action.__init__ (self, manager, None, prop_set)
        
    def actualize (self):
        if not self.actualized_:
            self.actualized_ = True

            for i in self.targets ():
                i.actualize ()


def traverse (target, include_roots = False, include_sources = False):
    """ Traverses the dependency graph of 'target' and return all targets that will
        be created before this one is created. If root of some dependency graph is
        found during traversal, it's either included or not, dependencing of the
        value of 'include_roots'. In either case, sources of root are not traversed.
    """
    result = []
    
    if target.action ():
        action = target.action ()
        
        # This includes 'target' as well
        result += action.targets ()

        for t in action.sources ():
            
            # TODO: see comment in Manager.register_object ()
            if not isinstance (t, VirtualTarget):
                t = target.project_.manager_.get_object (t)
                
            if not t.root ():
                result += traverse (t, include_roots, include_sources)

            elif include_roots:
                result.append (t)

    elif include_sources:
        result.append (target)

    return result

#   # Takes an 'action' instances and creates new instance of it
#   # and all produced target. The rule-name and properties are set
#   # to 'new-rule-name' and 'new-properties', if those are specified.
#   # Returns the cloned action.
#   rule clone-action ( action : new-project : new-action-name ? : new-properties ? )
#   {
#       if ! $(new-action-name)
#       {
#           new-action-name = [ $(action).action-name ] ;
#       }
#       if ! $(new-properties)
#       {
#           new-properties = [ $(action).properties ] ;
#       }
#   
#       local action-class = [ modules.peek $(action) : __class__ ] ;
#       local cloned-action = [ class.new $(action-class)  
#         [ $(action).sources ] : $(new-action-name) : $(new-properties) ] ;
#                           
#       local cloned-targets ;
#       for local target in [ $(action).targets ]
#       {
#           local n = [ $(target).name ] ;
#           local cloned-target = [ class.new file-target $(n:D=) : [ $(target).type ] 
#             : $(new-project) : $(cloned-action) ] ;
#           local d = [ $(target).dependencies ] ;
#           if $(d)
#           {            
#               $(cloned-target).depends $(d) ;
#           }                    
#           $(cloned-target).root [ $(target).root ] ;
#           $(cloned-target).creating_subvariant [ $(target).creating_subvariant ] ;
#           
#           cloned-targets += $(cloned-target) ;
#       }        
#                       
#       return $(cloned-action) ;        
#   }

class Subvariant:
    
    def __init__ (self, main_target, prop_set, sources, build_properties, sources_usage_requirements, created_targets):
        """ 
        main_target:                 The instance of MainTarget class
        prop_set:                    Properties requested for this target
        sources:
        build_properties:            Actually used properties
        sources_usage_requirements:  Properties propagated from sources
        created_targets:             Top-level created targets
        """
        self.main_target_ = main_target
        self.properties_ = prop_set
        self.sources_ = sources
        self.build_properties_ = build_properties
        self.sources_usage_requirements_ = sources_usage_requirements
        self.created_targets_ = created_targets

        self.usage_requirements_ = None
        
        # Pre-compose the list of other dependency graphs, on which this one
        # depends
        deps = build_properties.get ('<implicit-dependency>')
        
        self.other_dg = []
        for d in deps:
            # TODO: the property must have the actual object here, not a string.
            value = replace_grist (d, '')
            self.other_dg.append (value.creating_subvariant ())

        self.other_dg = unique (self.other_dg)
  
               
    def main_target (self):
        return self.main_target_
    
    def created_targets (self):
        return self.created_targets_
    
    def requested_properties (self):
        return self.properties_
    
    def build_properties (self):
        return self.build_properties_
    
    def sources_usage_requirements (self):
        return self.sources_usage_requirements_
    
    def set_usage_requirements (self, usage_requirements):
        self.usage_requirements_ = usage_requirements
    
    def usage_requirements (self):
        return self.usage_requirements_
    
#       # Returns all targets referenced by this subvariant,
#       # either directly or indirectly, and 
#       # either as sources, or as dependency properties.
#       # Targets referred with dependency property are returned a properties,
#       # not targets.
#       rule all-referenced-targets ( )
#       {
#           # Find directly referenced targets.
#           local deps = [ $(self.build_properties_).dependency ] ;
#           local all-targets = $(self.sources_) $(deps) ;
#           
#           # Find other subvariants.
#           local r ;
#           for local t in $(all-targets)
#           {            
#               r += [ $(t:G=).creating_subvariant ] ;
#           }
#           r = [ sequence.unique $(r) ] ;
#           for local s in $(r) 
#           {
#               if $(s) != $(__name__)
#               {
#                   all-targets += [ $(s).all-referenced-targets ] ;
#               }            
#           }
#           return $(all-targets) ;                        
#       }

    def implicit_includes (self, feature, target_type):
        """ Returns the properties which specify implicit include paths to
            generated headers. This traverses all targets in this subvariant,
            and subvariants referred by <implcit-dependecy>properties.
            For all targets which are of type 'target-type' (or for all targets,
            if 'target_type' is not specified), the result will contain
            <$(feature)>path-to-that-target.
        """
#    {
#        local key = ii$(feature)-$(target_type:E="") ;
#        if ! $($(key))-is-nonempty
#        {
#            local target_paths = [ all-target-directories $(target_type) ] ;    
#            target_paths = [ sequence.unique $(target_paths) ] ;
#            local result = $(target_paths:G=$(feature)) ;
#            if ! $(result)
#            {
#                result = "" ;
#            }            
#            $(key) = $(result) ;
#        }
#        if $($(key)) = ""
#        {
#            return ;
#        }
#        else
#        {
#            return $($(key)) ;
#        }        
#    }
        # TODO: port above code
        return []
        
#       rule all-target-directories ( target_type ? )
#       {
#           if ! $(self.target-directories)
#           {
#               compute-target-directories $(target_type) ;
#           }                
#           return $(self.target-directories) ;
#       }
#       
#       rule compute-target-directories ( target_type ? )
#       {   
#           local result ;
#           for local t in $(self.created_targets_)
#           {
#               if $(target_type) && ! [ type.is-derived [ $(t).type ] $(target_type) ] 
#               {
#                   # Skip target which is of wrong type.
#               }
#               else
#               {                
#                   result = [ sequence.merge $(result) : [ $(t).path ] ] ;
#               }            
#           }
#           for local d in $(self.other_dg)
#           {
#               result += [ $(d).all-target-directories $(target_type) ] ;
#           }
#           self.target-directories = $(result) ;
#       }   
#   }
#   
