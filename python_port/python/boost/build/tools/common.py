#  Copyright (C) Vladimir Prus 2002. Permission to copy, use, modify, sell and
#  distribute this software is granted provided this copyright notice appears in
#  all copies. This software is provided "as is" without express or implied
#  warranty, and with no claim as to its suitability for any purpose.

""" Provides actions common to all toolsets, for as making directories and
    removing files.
"""

import re
import bjam
import os

from boost.build.build import feature
from boost.build.util.utility import *
from boost.build.util import path

__re__before_first_dash = re.compile ('([^-]*)-')

def reset ():
    """ Clear the module state. This is mainly for testing purposes.
        Note that this must be called _after_ resetting the module 'feature'.
    """    
    global __had_unspecified_value, __had_value, __declared_subfeature, __all_signatures, __debug_configuration
    
    # Stores toolsets without specified initialization values.
    __had_unspecified_value = {}

    # Stores toolsets with specified initialization values.
    __had_value = {}
    
    # Stores toolsets with declared subfeatures.
    __declared_subfeature = {}
    
    # Stores all signatures of the toolsets.
    __all_signatures = {}

    __debug_configuration = '--debug-configuration' in bjam.variable('ARGV')
    
reset ()

def check_init_parameters (toolset, *args):
    """ The rule checks toolset parameters. Each trailing parameter 
        should be a tuple of parameter name and parameter value.
        The rule will check that each parameter either has value in
        each invocation, or has no value in each invocation. Also,
        the rule will check that the combination of all parameter values is
        unique in all invocations.
        
        Each parameter name corresponds to subfeature. This rule will declare subfeature
        the first time non-empty parameter value is passed, and will extend it with
        all the values.
        
        The return value from this rule is a condition to be used for flags settings.
    """
    sig = toolset
    condition = replace_grist (toolset, '<toolset>')
    
    for arg in args:
        name = arg [0]
        value = arg [1]
        
        str_toolset_name = str ((toolset, name))
        
        if value == '':
            condition = condition + '-' + value
            if __had_unspecified_value.has_key (str_toolset_name):
                raise BaseException ("'%s' initialization: parameter '%s' inconsistent\n" \
                "no value was specified in earlier initialization\n" \
                "an explicit value is specified now" % (toolset, name))

            # The logic below is for intel compiler. It calls this rule
            # with 'intel-linux' and 'intel-win' as toolset, so we need to
            # get the base part of toolset name.
            # We can't pass 'intel' as toolset, because it that case it will
            # be impossible to register versionles intel-linux and
            # intel-win of specific version.
            t = toolset
            m = __re__before_first_dash.match (toolset)
            if m:
                t = m.group (1)

            if not __had_value.has_key (str_toolset_name):
                if not __declared_subfeature.has_key (str (t, name)):
                    feature.subfeature ('toolset', t, name, [], ['propagated'])
                    __declared_subfeature [str (t, name)] = True

                __had_value [str_toolset_name] = True

            feature.extend_subfeature ('toolset', t, name, [value])

        else:
            if __had_value.has_key (str_toolset_name):
                raise BaseException ("'%s' initialization: parameter '%s' inconsistent\n" \
                "an explicit value was specified in an earlier initialization\n" \
                "no value is specified now" % (toolset, name))

            __had_unspecified_value [str_toolset_name] = True

        if value == None: value = ''
        
        sig = sig + value + '-'

    if __all_signatures.has_key (sig):
        message = "duplicate initialization of '%s' with the following parameters: " % toolset
        
        for arg in args:
            name = arg [0]
            value = arg [1]
            if value == None: value = '<unspecified>'
            
            message += "'%s' = '%s'\n" % (name, value)

        raise BaseException (message)

    __all_signatures [sig] = True

    # FIXME: we actually don't add any subfeatures to the condition
    return [condition]

# Ported from trunk@47077
def get_invocation_command_nodefault(
    toolset, tool, user_provided_command, additional_paths=[], path_last=None):
    """
        A helper rule to get the command to invoke some tool. If
        'user-provided-command' is not given, tries to find binary named 'tool' in
        PATH and in the passed 'additional-path'. Otherwise, verifies that the first
        element of 'user-provided-command' is an existing program.
        
        This rule returns the command to be used when invoking the tool. If we can't
        find the tool, a warning is issued. If 'path-last' is specified, PATH is
        checked after 'additional-paths' when searching for 'tool'.
    """
    if not user_provided_command:
        command = find_tool(tool, additional_paths, path_last) 
        if not command and __debug_configuration:
            print "warning: toolset", toolset, "initialization: can't find tool, tool"
            #FIXME
            #print "warning: initialized from" [ errors.nearest-user-location ] ;
    else:
        command = check_tool(user_provided_command)
        if not command and __debug_configuration:
            print "warning: toolset", toolset, "initialization:"
            print "warning: can't find user-provided command", user_provided_command
            #FIXME
            #ECHO "warning: initialized from" [ errors.nearest-user-location ]
            
    return command

def get_invocation_command (toolset, tool, user_provided_command = None, additional_paths = None, path_last = None):
    """ A helper rule to get the command to invoke some tool. The rule is either passed
        a user provided command, it which case it checks it for correctness, or it tries
        to find the tool using it's name, the PATH, and additional path.
        This rule returns the command to be used when invoking the tool. If we can't
        find the tool, a warning is issued.
        If 'path_last' is specified, path is checked after 'additional_paths'.
    """
    command = None
    
    if not user_provided_command:
        command = find_tool (tool, additional_paths, path_last)

        if not command:
            # TODO: what to do here? Use some global logger?
            # ECHO "warning: toolset $(toolset) initialization: can't find tool $(tool)" ;
            # ECHO "warning: initialized from" [ errors.nearest-user-location ] ;
            pass

    else:
        command = check_tool (user_provided_command)

        if not command:
            print "User-provided command not found"
            # It's possible, in theory, that user-provided command is OK, but we're
            # not smart enough to understand that. 

            # TODO: what to do here? Use some global logger?
            # ECHO "warning: toolset $(toolset) initialization: " ;
            # ECHO "warning: can't find user-provided command '$(user_provided_command:J= )'" ;
            # ECHO "warning: initialized from" [ errors.nearest-user-location ] ;
            pass

    if not command:
        command = user_provided_command

    if not command:
        command = tool

    return command

def get_absolute_tool_path(command):
    """
        Given an invocation command,
        return the absolute path to the command. This works even if commnad
        has not path element and is present in PATH.
    """
    if os.path.dirname(command):
        return os.path.dirname(command)
    else:
        programs = path.programs_path()
        m = path.glob(programs, [command, command + '.exe' ])
        if not len(m):
            print "Could not find:", command, "in", programs
        return os.path.dirname(m[0])

def find_tool (name, additional_paths = None, path_last = False):
    """ Attempts to find tool (binary) named 'name' in PATH and in 'additiona-paths'.
        If found in path, returns 'name'.
        If found in additional paths, returns full name. If there are several possibilities,
        returns them all.
        Otherwise, returns empty string.
        If 'path_last' is specified, path is checked after 'additional_paths'.
    """
    if not additional_paths:
        additional_paths = []
    programs = path.programs_path ()
    match = path.glob (programs, [name, name + '.exe'])
    additional_match = path.glob (additional_paths, [name, name + '.exe'])

    result = []
    if path_last:
        result = additional_match
        if not result and match:
            result = match

    else:
        if match:
            result = match

        elif additional_match:
            result = additional_match

    if result:
        return path.native (result [0])

# Checks if 'command' can be found either in path
# or is a full name to an existing file.
def check_tool_aux(command):
    dirname = os.path.dirname(command)
    if dirname:
        return os.path.exists(command)
    else:
        paths = bjam.variable("PATH") + bjam.variable("Path") + bjam.variable("path")
        if path.glob(paths, [command]):
            return command

def check_tool(command):
    # Checks that a tool can be invoked by 'command'. 
    # If command is not an absolute path, checks if it can be found in 'path'.
    # If comand is absolute path, check that it exists. Returns 'command'
    # if ok and empty string otherwise.
    if check_tool_aux(command[0]) or check_tool_aux(command[-1]):
        return command

def handle_options (tool, condition, command, options):
    """ Handle common options for toolset, specifically sets the following
        flag variables:
        - CONFIG_COMMAND to 'command'
        - OPTIONS for compile.c to the value of <cflags> in options
        - OPTIONS for compile.c++ to the value of <cxxflags> in options
        - OPTIOns for compile to the value of <compileflags> in options
        - OPTIONs for link to the value of <linkflags> in options
    """
    from boost.build.build import toolset

    assert (command)
    toolset.flags (tool, 'CONFIG_COMMAND', condition, [command])
    toolset.flags (tool + '.compile', 'OPTIONS', condition, feature.get_values ('<compileflags>', options))
    toolset.flags (tool + '.compile.c', 'OPTIONS', condition, feature.get_values ('<cflags>', options))
    toolset.flags (tool + '.compile.c++', 'OPTIONS', condition, feature.get_values ('<cxxflags>', options))
    toolset.flags (tool + '.link', 'OPTIONS', condition, feature.get_values ('<linkflags>', options))


### # returns the location of the "program files" directory on a windows
### # platform
### rule get-program-files-dir ( )
### {
###     local ProgramFiles = [ modules.peek : ProgramFiles ] ;
###     if $(ProgramFiles)
###     {
###         ProgramFiles = "$(ProgramFiles:J= )" ;
###     }
###     else
###     {
###         ProgramFiles = "c:\\Program Files" ;
###     }
###     return $(ProgramFiles) ;
### }
### 
### if [ os.name ] = NT
### {
###     RM = del /f ;
###     CP = copy ;
### }
### else
### {
###     RM = rm -f ;
###     CP = cp ;
### }
### 
### nl = "
### " ;
### 
### # Returns the command needed to set shell variable on the
### # current platform.
### rule variable-setting-command ( variable value )
### {
###     if [ os.name ] = NT
###     {
###         return "set $(variable)=$(value)$(nl)" ;
###     }
###     else
###     {
###         return "$(variable)=$(value)" ;
###     }
### }
### 
### # Returns the command needed to set shell variable on the
### # current platform. Each element of values is expected to be a path,
### # elements are joined with os-specific characer which delimits paths in
### # environment variables.
### #
### # Each element of value can have the form '$VARIABLE'. This means that
### # the value of environment variable 'VARIABLE' should be used. For example:
### # 
### #   common.path-variable-setting-command PATH : $PATH foo : exported ;
### #
### # would add 'foo' to the end of 'PATH' variable.
### rule path-variable-setting-command ( variable : values * : exported ? )
### {   
###     local result ;
###     
###     # Handle references to variables.
###     local values2 ;
###     # Create regex. Dollar is in separate variable to avoid
###     # interpreting it as variable access in bjam.
###     d = $ ;
###     # Backslash protects special meaning of '$' in regexps.
###     r = \\$(d)(.*) ;
###     for local v in $(values)
###     {
###         local m = [ MATCH $(r) : $(v) ] ;
###         if $(m) && [ os.name ] = NT 
###         {
###             values2 += %$(m)% ;
###         }          
###         else
###         {            
###             # If there's no match, just add the value
###             # If there's match but we're not on NT, the $VAR syntax
###             # is already OK.
###             values2 += $(v) ;
###         }
###     }
###     values = $(values2) ;
###         
###     if [ os.name ] = NT
###     {
###         result = set $(variable)=$(values:J=";")$(nl) ;                
###     }
###     else
###     {
###         # We can't put ":" directly in :J modifier.
###         local sep = ":" ;
###         if $(exported)
###         {                       
###             result = $(variable)=$(values:J=$(sep));export $(variable) ;
###         }
###         else
###         {
###             result = $(variable)=$(values:J=$(sep)) ;    
###         }                
###     }
###     return $(result:J=" ") ;
### }
### 
### 
### # Return a command which can create a file. If 'r' is result of invocation,
### # then 
### #   r foobar
### # will create foobar with unspecified content. What happens if file already 
### # exists is unspecified.
### rule file-creation-command ( )
### {
###     if [ modules.peek : NT ]
###     {
###         return "echo. > " ;
###     }
###     else
###     {
###         return "touch " ;
###     }
### }
### 
###         
### rule MkDir
### {
###     # If dir exists, don't update it
###     # Do this even for $(DOT).
### 
###     NOUPDATE $(<) ;
### 
###     if $(<) != $(DOT) && ! $($(<)-mkdir)
###     {
###         local s ;
### 
###         # Cheesy gate to prevent multiple invocations on same dir
###         # MkDir1 has the actions
###         # Arrange for jam dirs
### 
###         $(<)-mkdir = true ;
###         MkDir1 $(<) ;
###         Depends dirs : $(<) ;
### 
###         # Recursively make parent directories.
###         # $(<:P) = $(<)'s parent, & we recurse until root
### 
###         s = $(<:P) ;
### 
###         if $(NT)
###         {
###             switch $(s)
###             {
###                 case *:   : s = ;
###                 case *:\\ : s = ;
###             }
###         }
###         
###         if $(s) && $(s) != $(<)
###         {
###             Depends $(<) : $(s) ;
###             MkDir $(s) ;
###         }
###         else if $(s)
###         {
###             NOTFILE $(s) ;
###         }
###     }
### }
### 
### actions MkDir1
### {
###     mkdir "$(<)"
### }
### 
### actions piecemeal together existing Clean
### {
###     $(RM) "$(>)"
### }
### 
### rule copy 
### {    
### }
### 
### 
### actions copy
### {
###     $(CP) "$(>)" "$(<)"
### }
### 
### # Cause creation of response file, containing the sources in 'sources'
### # All the targets in 'targets' will depend on response file, and response
### # file will be created before the targets are built.
### rule response-file ( targets + : sources * : the-response-file : properties * )
### {
###     # Manufacture a fake target for response file.
###     # If response file is in targets, we're in trouble.
###     # The actions for response file are already generated, and bjam thinks it's 
###     # created. So setting dependency on response file will not help to create
###     # it before other targets. So, we need another target.
###     
###     local g = [ utility.ungrist $(the-response-file:G) ] ;
###     local rsp = $(the-response-file:G=$(g)-rsp) ;
###     LOCATE on $(rsp) = [ on $(the-response-file) return $(LOCATE) ] ;    
###     DEPENDS $(targets) : $(rsp) ;
###     # Cause RSP to be recreated if sources are out-of-date.
###     DEPENDS $(rsp) : $(sources) ;
###         
###     # Add libraries from <library> property to the list of sources.
###     local libraries ;
###     for local p in $(properties)
###     {
###         if $(p:G) = <library-file> && 
###           ! [ type.is-derived [ $(p:G=).type ] SHARED_LIB ] 
###         {
###             libraries += $(p:G=) ;
###         }          
###     }
###     # Get real jam targets
###     local xlibraries ;
###     for local l in $(libraries)
###     {
###         xlibraries += [ $(l).actualize ] ;
###     }
###     
###     sources += $(xlibraries) ; 
###        
###     response-file-1 $(rsp) : $(sources[1]) ;
###     if $(sources[2-])
###     {
###         response-file-2 $(rsp) : $(sources[2-]) ;
###     }
###     
###     print.output $(rsp) ;
###     print.text [ utility.apply-default-suffix .lib :
###         [ on $(targets[1])
###           return "$(LIBRARY_OPTION)$(FINDLIBS_ST)"
###             "$(LIBRARY_OPTION)$(FINDLIBS_SA)"
###         ] ] ;
### 
###     print.text
###         [ on $(targets[1])
###           return -D$(DEFINES) -I\"$(INCLUDES)\"
###         ] ;
### }
### 
### # response-file generation is broken up into two phases, the first of
### # which overwrites any existing file and the second of which appends
### # to the file, piecemeal, so that no command-line is too long.
### actions quietly response-file-1
### {
###     echo "$(>)" > "$(<)"
### }
### 
### actions quietly piecemeal response-file-2
### {
###     echo "$(>)" >> "$(<)"
### }
### 
### rule __test__ ( ) {
### 
###     import assert ;
###     
###     local save-os = [ modules.peek os : name ] ;
###     
###     modules.poke os : name : LINUX ;
###     
###     assert.result "PATH=foo:$PATH:bar" :
###       path-variable-setting-command PATH : foo $PATH bar ;
###     
###     modules.poke os : name : NT ;
###     
### nl = "
### " ;
###     
###     assert.result "set PATH=foo;%PATH%;bar$(nl)" :
###       path-variable-setting-command PATH : foo $PATH bar ;
### 
### 
###     modules.poke os : name : $(save-os) ;      
###       
### }

# FIXME: global variable
made_dirs = {}

def mkdir(engine, path_target):
    """Creates dependencies that cause directory 'path_target' to be created"""

    # If dir exists, don't update it
    # Do this even for $(DOT).
    bjam.call("NOUPDATE", path_target)

    if path_target != "." and not made_dirs.has_key(path_target):
        made_dirs[path_target] = 1
        engine.set_update_action("common.MkDir1", path_target, [], None)

        parent = os.path.dirname(path_target)
        # Part of original Jam code, supposed to prevent
        # calling mkdir on drive letters.
        if len(parent) == 2 and parent[1] == ':':
            parent = None
        if len(parent) == 3 and parent[1] == ':' and parent[2] == '\\':
            parent = None

        if parent and parent != path_target:
            engine.add_dependency(path_target, parent)
            mkdir(engine, parent)
        elif parent:
            bjam.call("NOTFILE", parent)

def init(manager):
    engine = manager.engine()

    engine.register_action ("common.MkDir1", 'mkdir "$(<)"')
    engine.register_action ("common.Clean", 'rm -rf "$(>)"')

    import boost.build.tools.make
    import boost.build.build.alias
