# Copyright 2002-2005 Vladimir Prus.
# Copyright 2002-2003 Dave Abrahams.
# Copyright 2006 Rene Rivera.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#         http://www.boost.org/LICENSE_1_0.txt)

import TestCmd
from tree import build_tree, trees_difference
import copy
import fnmatch
import glob
import os
import re
import shutil
import string
import types
import time
import tempfile
import sys

def get_toolset():
    toolset = None;
    for arg in sys.argv[1:]:
        if not arg.startswith('-'):
            toolset = arg
    return toolset or 'gcc'

windows = 0
if os.environ.get('OS','').lower().startswith('windows') or \
       os.__dict__.has_key('uname') and \
       os.uname()[0].lower().startswith('cygwin'):
    windows = 1

suffixes = {}

# Prepare the map of suffixes
def prepare_suffix_map(toolset):
    global windows, suffixes    
    suffixes = {'.exe': '', '.dll': '.so', '.lib': '.a', '.obj': '.o'}
    if windows:
        suffixes = {}
        if toolset in ["gcc"]:
            suffixes['.lib'] = '.a' # static libs have '.a' suffix with mingw...
            suffixes['.obj'] = '.o'
    if os.__dict__.has_key('uname') and os.uname()[0] == 'Darwin':
        suffixes['.dll'] = '.dylib'

def re_remove(sequence,regex):
    me = re.compile(regex)
    result = filter( lambda x: me.match(x), sequence )
    for r in result:
        sequence.remove(r)

def glob_remove(sequence,pattern):
    result = fnmatch.filter(sequence,pattern)
    for r in result:
        sequence.remove(r)

lib_prefix = 1
if windows:
    lib_prefix = 0
        
    
    
#
# FIXME: this is copy-pasted from TestSCons.py
# Should be moved to TestCmd.py?
#
if os.name == 'posix':
    def _failed(self, status = 0):
        if self.status is None:
            return None
        if os.WIFSIGNALED(status):
            return None
        return _status(self) != status
    def _status(self):
        if os.WIFEXITED(self.status):
            return os.WEXITSTATUS(self.status)
        else:
            return None
elif os.name == 'nt':
    def _failed(self, status = 0):
        return not self.status is None and self.status != status
    def _status(self):
        return self.status

class Tester(TestCmd.TestCmd):
    """Class for testing Boost.Build.

    Optional argument `executable` indicates the name of the
    executable to invoke. Set this to "jam" to test Boost.Build v1
    behavior.

    Optional argument `work_dir` indicates an absolute directory, 
    where the test will run be run.
    """
    def __init__(self, arguments="", executable = 'bjam', match =
                 TestCmd.match_exact, boost_build_path = None,
                 translate_suffixes = 1, pass_toolset = 1,
                 workdir = '',
                 **keywords):

        self.original_workdir = os.getcwd()
        if workdir != '' and not os.path.isabs(workdir):
            raise "Parameter workdir <"+workdir+"> must point to a absolute directory: "

        self.last_build_time = 0
        self.translate_suffixes = translate_suffixes

        self.toolset = get_toolset()
        self.pass_toolset = pass_toolset

        prepare_suffix_map(pass_toolset and self.toolset or 'gcc')

        if not '--default-bjam' in sys.argv:
            jam_build_dir = ""
            if os.name == 'nt':
                jam_build_dir = "bin.ntx86"
            elif os.name == 'posix' and os.__dict__.has_key('uname'):
                if os.uname()[0].lower().startswith('cygwin'):
                    jam_build_dir = "bin.cygwinx86"
                    if 'TMP' in os.environ and os.environ['TMP'].find('~') != -1:
                        print 'Setting $TMP to /tmp to get around problem with short path names'
                        os.environ['TMP'] = '/tmp'
                elif os.uname()[0] == 'Linux':
                    cpu = os.uname()[4]
                    if re.match("i.86", cpu):
                        jam_build_dir = "bin.linuxx86";
                    else:
                        jam_build_dir = "bin.linux" + os.uname()[4]
                elif os.uname()[0] == 'SunOS':
                    jam_build_dir = "bin.solaris"
                elif os.uname()[0] == 'Darwin':
                    jam_build_dir = "bin.macosxppc"
                elif os.uname()[0] == "AIX":
                    jam_build_dir = "bin.aix"
                elif os.uname()[0] == "IRIX64":
                    jam_build_dir = "bin.irix"
                elif os.uname()[0] == "FreeBSD":
                    jam_build_dir = "bin.freebsd"
                elif os.uname()[0] == "OSF1":
                    jam_build_dir = "bin.osf"
                else:
                    raise "Don't know directory where jam is build for this system: " + os.name + "/" + os.uname()[0]
            else:
                raise "Don't know directory where jam is build for this system: " + os.name

            # Find there jam_src is located.
            # try for the debug version if it's lying around

            dirs = [os.path.join('../../../jam/src', jam_build_dir + '.debug'),
                    os.path.join('../../../jam/src', jam_build_dir),
                    os.path.join('../../jam_src', jam_build_dir + '.debug'),
                    os.path.join('../../jam_src', jam_build_dir),
                    os.path.join('../jam_src', jam_build_dir + '.debug'),
                    os.path.join('../jam_src', jam_build_dir),
                    ]

            for d in dirs:
                if os.path.exists(d):
                    jam_build_dir = d
                    break
            else:
                print "Cannot find built Boost.Jam"
                os.exit(1)

        verbosity = ['-d0', '--quiet']
        if '--verbose' in sys.argv:
            keywords['verbose'] = 1
            verbosity = ['-d+2']

        if boost_build_path is None:
            boost_build_path = self.original_workdir

        program_list = []
        
        if '--default-bjam' in sys.argv:
            program_list.append(executable)
            inpath_bjam = True
        else:
            program_list.append(os.path.join(jam_build_dir, executable))
            inpath_bjam = None
        program_list.append('-sBOOST_BUILD_PATH=' + boost_build_path)
        if verbosity:
            program_list += verbosity
        if arguments:
            program_list += arguments.split(" ")

        TestCmd.TestCmd.__init__(
            self
            , program=program_list
            , match=match
            , workdir = workdir
            , inpath = inpath_bjam
            , **keywords)

        os.chdir(self.workdir)

    def cleanup(self):
        try:
            TestCmd.TestCmd.cleanup(self)
            os.chdir(self.original_workdir)
        except AttributeError:
            # Whe this is called during by TestCmd.TestCmd.__del__ we can have both
            # 'TestCmd' and 'os' unavailable in our scope. Do nothing in this case.
            pass
            
    #
    # Methods that change working directory's content
    #
    def set_tree(self, tree_location):
        # Seem like it's not possible to remove a directory which is
        # current.
        d = os.getcwd()
        os.chdir(os.path.dirname(self.workdir))
        shutil.rmtree(self.workdir, ignore_errors=0)

        if not os.path.isabs(tree_location):
                tree_location = os.path.join(self.original_workdir, tree_location)
        shutil.copytree(tree_location, self.workdir)

        os.chdir(d)

        def make_writable(unused, dir, entries):
            for e in entries:
                name = os.path.join(dir, e)
                os.chmod(name, os.stat(name)[0] | 0222)

        os.path.walk(".", make_writable, None)


    def write(self, file, content):
        self.wait_for_time_change()
        nfile = self.native_file_name(file)
        try:
            os.makedirs(os.path.dirname(nfile))
        except Exception, e:
            pass
        open(nfile, "wb").write(content)

    def rename(self, old, new):
        try:
            os.makedirs(os.path.dirname(new))
        except:
            pass
        
        try:
            os.remove(new)
        except:
            pass
        
        os.rename(old, new)
        self.touch(new);

    def copy(self, src, dst):
        self.wait_for_time_change()
        self.write(dst, self.read(src))

    def copy_preserving_timestamp(self, src, dst):
        src_name = self.native_file_name(src)
        dst_name = self.native_file_name(dst)
        stats = os.stat(src_name)        
        self.write(dst, self.read(src))
        os.utime(dst_name, (stats.st_atime, stats.st_mtime))
        
    def touch(self, names):
        self.wait_for_time_change()
        for name in self.adjust_names(names):
                os.utime(self.native_file_name(name), None)

    def rm(self, names):
        self.wait_for_time_change()
        if not type(names) == types.ListType:
            names = [names]

        # Avoid attempts to remove current dir
        os.chdir(self.original_workdir)
        for name in names:
            n = self.native_file_name(name)
            n = glob.glob(n)
            if n:
                n = n[0]
                if os.path.isdir(n):
                    shutil.rmtree(n, ignore_errors=0)
                else:
                    os.unlink(n)

        # Create working dir root again, in case
        # we've removed it
        if not os.path.exists(self.workdir):
            os.mkdir(self.workdir)
        os.chdir(self.workdir)

    def expand_toolset(self, name):
        """Expands $toolset in the given file to tested toolset"""
        content = self.read(name)
        content = string.replace(content, "$toolset", self.toolset)
        self.write(name, content)
                                                        
    def dump_stdio(self):
        print "STDOUT ============"
        print self.stdout()    
        print "STDERR ============"
        print self.stderr()
        print "END ==============="
                    
    #
    #   FIXME: Large portion copied from TestSCons.py, should be moved?
    #
    def run_build_system(
        self, extra_args='', subdir='', stdout = None, stderr = '',
        status = 0, match = None, pass_toolset = None, **kw):

        if os.path.isabs(subdir):
            if stderr:
                print "You must pass a relative directory to subdir <"+subdir+">."
            status = 1
            return

        self.previous_tree = build_tree(self.workdir)

        if match is None:
            match = self.match

        if pass_toolset is None:
            pass_toolset = self.pass_toolset        

        try:
            kw['program'] = []
            kw['program'] += self.program
            if extra_args:
                kw['program'] += extra_args.split(" ")            
            if pass_toolset:
                kw['program'].append(self.toolset)
            kw['chdir'] = subdir
            apply(TestCmd.TestCmd.run, [self], kw)
        except:
            self.dump_stdio()
            raise

        if status != None and _failed(self, status):
            expect = ''
            if status != 0:
                expect = " (expected %d)" % status

            print '"%s" returned %d%s' % (
                kw['program'], _status(self), expect)

            self.fail_test(1)

        if not stdout is None and not match(self.stdout(), stdout):
            print "Expected STDOUT =========="
            print stdout
            print "Actual STDOUT ============"
            print self.stdout()
            stderr = self.stderr()
            if stderr:
                print "STDERR ==================="
                print stderr
            self.maybe_do_diff(self.stdout(), stdout)
            self.fail_test(1, dump_stdio = 0)

        # Intel tends to produce some message to stderr, which makes tests
        # fail
        intel_workaround = re.compile("^xi(link|lib): executing.*\n", re.M)
        actual_stderr = re.sub(intel_workaround, "", self.stderr())

        if not stderr is None and not match(actual_stderr, stderr):
            print "STDOUT ==================="
            print self.stdout()
            print "Expected STDERR =========="
            print stderr
            print "Actual STDERR ============"
            print actual_stderr
            self.maybe_do_diff(actual_stderr, stderr)
            self.fail_test(1, dump_stdio = 0)

        self.tree = build_tree(self.workdir)
        self.difference = trees_difference(self.previous_tree, self.tree)
        self.difference.ignore_directories()
        self.unexpected_difference = copy.deepcopy(self.difference)

        self.last_build_time = time.time()

    def read(self, name):
        return open(glob.glob(self.native_file_name(name))[0], "rb").read()

    def read_and_strip(self, name):
        lines = open(glob.glob(self.native_file_name(name))[0], "rb").readlines()
        result = string.join(map(string.rstrip, lines), "\n")
        if lines and lines[-1][-1] == '\n':
            return result + '\n'
        else:
            return result
    
    def fail_test(self, condition, dump_stdio = 1, *args):
        # If test failed, print the difference        
        if condition and hasattr(self, 'difference'):            
            print '-------- all changes caused by last build command ----------'
            self.difference.pprint()
            
        if condition and dump_stdio:
            self.dump_stdio()

        if condition and '--preserve' in sys.argv:
            print 
            print "*** Copying the state of working dir into 'failed_test' ***"
            print 
            path = os.path.join(self.original_workdir, "failed_test")
            if os.path.isdir(path):
                shutil.rmtree(path, ignore_errors=0)
            elif os.path.exists(path):
                raise "The path " + path + " already exists and is not directory";
            shutil.copytree(self.workdir, path)
                        
        TestCmd.TestCmd.fail_test(self, condition, *args)
        
    # A number of methods below check expectations with actual difference
    # between directory trees before and after build.
    # All the 'expect*' methods require exact names to be passed.
    # All the 'ignore*' methods allow wildcards.

    # All names can be lists, which are taken to be directory components
    def expect_addition(self, names):        
        for name in self.adjust_names(names):
                try:
                        glob_remove(self.unexpected_difference.added_files,name)
                except:
                        print "File %s not added as expected" % (name,)
                        self.fail_test(1)

    def ignore_addition(self, wildcard):
        self.ignore_elements(self.unexpected_difference.added_files, wildcard)

    def expect_removal(self, names):
        for name in self.adjust_names(names):
                try:
                        glob_remove(self.unexpected_difference.removed_files,name)
                except:
                        print "File %s not removed as expected" % (name,)
                        self.fail_test(1)

    def ignore_removal(self, wildcard):
        self.ignore_elements(self.unexpected_difference.removed_files, wildcard)

    def expect_modification(self, names):
        for name in self.adjust_names(names):
                try:
                        self.unexpected_difference.modified_files.remove(name)
                except:
                        print "File %s not modified as expected" % (name,)
                        self.fail_test(1)

    def ignore_modification(self, wildcard):
        self.ignore_elements(self.unexpected_difference.modified_files, wildcard)

    def expect_touch(self, names):
        
        d = self.unexpected_difference
        for name in self.adjust_names(names):

            # We need to check in both touched and modified files.
            # The reason is that:
            # (1) for windows binaries often have slight
            # differences even with identical inputs
            # (2) Intel's compiler for Linux has the same behaviour        
            filesets = [d.modified_files, d.touched_files]

            while filesets:
                try:
                    glob_remove(filesets[-1],name)
                    break
                except ValueError:
                    filesets.pop()

            if not filesets:
                print "File %s not touched as expected" % (name,)
                self.fail_test(1)


    def ignore_touch(self, wildcard):
        self.ignore_elements(self.unexpected_difference.touched_files, wildcard)

    def ignore(self, wildcard):
        self.ignore_elements(self.unexpected_difference.added_files, wildcard)
        self.ignore_elements(self.unexpected_difference.removed_files, wildcard)
        self.ignore_elements(self.unexpected_difference.modified_files, wildcard)
        self.ignore_elements(self.unexpected_difference.touched_files, wildcard)

    def expect_nothing(self, names):
        for name in self.adjust_names(names):
            if name in self.difference.added_files:
                print "File %s is added, but no action was expected" % (name,)
                self.fail_test(1)
            if name in self.difference.removed_files:
                print "File %s is removed, but no action was expected" % (name,)
                self.fail_test(1)
                pass
            if name in self.difference.modified_files:
                print "File %s is modified, but no action was expected" % (name,)
                self.fail_test(1)
            if name in self.difference.touched_files:
                print "File %s is touched, but no action was expected" % (name,)
                self.fail_test(1)

    def expect_nothing_more(self):

        # not totally sure about this change, but I don't see a good alternative
        if windows:
            self.ignore('*.ilk') # msvc incremental linking files
            self.ignore('*.pdb') # msvc program database files
            self.ignore('*.rsp') # response files
            self.ignore('*.tds') # borland debug symbols
            self.ignore('*.manifest') # msvc DLL manifests

        # debug builds of bjam built with gcc produce this profiling data
        self.ignore('gmon.out')
        self.ignore('*/gmon.out')
            
        if not self.unexpected_difference.empty():
           print 'FAILED'
           print '------- The following changes were unexpected ------- '
           self.unexpected_difference.pprint()
           self.fail_test(1)

    def _expect_line(self, content, expected):
        expected = expected.strip()
        lines = content.splitlines()
        found = 0
        for line in lines:
            line = line.strip()
            if fnmatch.fnmatch(line, expected):
                found = 1
                break

        if not found:
            print "Did not found expected line in output:"
            print expected
            print "The output was:"
            print content
            self.fail_test(1)

    def expect_output_line(self, expected):
        self._expect_line(self.stdout(), expected)

    def expect_content_line(self, name, expected):
        content = self._read_file(name)
        self._expect_line(content, expected)

    def _read_file(self, name, exact=0):
        name = self.adjust_names(name)[0]
        result = ""
        try:
            if exact:
                result = self.read(name)
            else:
                result = string.replace(self.read_and_strip(name), "\\", "/")
        except IOError:
            print "Note: could not open file", name
            self.fail_test(1)
        return result
            

    def expect_content(self, name, content, exact=0):
        actual = self._read_file(name, exact)
        content = string.replace(content, "$toolset", self.toolset+"*")

        matched = 0
        if exact:
            matched = fnmatch.fnmatch(actual,content)
        else:
            actual_ = map(lambda x: sorted(x.split()),actual.splitlines())
            content_ = map(lambda x: sorted(x.split()),content.splitlines())
            if len(actual_) == len(content_):
                matched = map(
                    lambda x,y: map(lambda n,p: fnmatch.fnmatch(n,p),x,y),
                    actual_, content_ )
                matched = reduce(
                    lambda x,y: x and reduce(
                        lambda a,b: a and b,
                    y ),
                    matched )

        if not matched:
            print "Expected:\n"
            print content
            print "Got:\n"
            print actual
            self.fail_test(1)

    def maybe_do_diff(self, actual, expected):
        if os.environ.has_key("DO_DIFF") and os.environ["DO_DIFF"] != '':
            
            e = tempfile.mktemp("expected")
            a = tempfile.mktemp("actual")
            open(e, "w").write(expected)
            open(a, "w").write(actual)
            print "DIFFERENCE"
            if os.system("diff -u " + e + " " + a):
                print "Unable to compute difference"               
            os.unlink(e)
            os.unlink(a)    
        else:
            print "Set environmental variable 'DO_DIFF' to examine difference." 

    # Helpers
    def mul(self, *arguments):
        if len(arguments) == 0:
                return None
        else:
                here = arguments[0]
                if type(here) == type(''):
                        here = [here]

                if len(arguments) > 1:
                        there = apply(self.mul, arguments[1:])
                        result = []
                        for i in here:
                                for j in there:
                                        result.append(i + j)
                        return result
                else:
                        return here



    # Internal methods
    def ignore_elements(self, list, wildcard):
        """Removes in-place, element of 'list' that match the given wildcard."""
        list[:] = filter(lambda x, w=wildcard: not fnmatch.fnmatch(x, w), list)

    def adjust_lib_name(self, name):
        global lib_prefix
        result = name
        
        pos = string.rfind(name, ".")
        if pos != -1:
            suffix = name[pos:]
            if suffix in [".lib", ".dll"]:
                (head, tail) = os.path.split(name)
                if lib_prefix:
                    tail = "lib" + tail
                    result = os.path.join(head, tail)
        return result
                
    def adjust_suffix(self, name):
        if not self.translate_suffixes:
            return name
        
        pos = string.rfind(name, ".")
        if pos != -1:
            suffix = name[pos:]
            name = name[:pos]

            if suffixes.has_key(suffix):
                suffix = suffixes[suffix]
        else:
            suffix = ''

        return name + suffix

    # Acceps either string of list of string and returns list of strings
    # Adjusts suffixes on all names.
    def adjust_names(self, names):
        if type(names) == types.StringType:
                names = [names]
        r = map(self.adjust_lib_name, names)
        r = map(self.adjust_suffix, r)
        r = map(lambda x, t=self.toolset: string.replace(x, "$toolset", t+"*"), r)
        return r

    def native_file_name(self, name):
        name = self.adjust_names(name)[0]
        elements = string.split(name, "/")
        return os.path.normpath(apply(os.path.join, [self.workdir]+elements))

    # Wait while time is no longer equal to the time last "run_build_system"
    # call finished.
    def wait_for_time_change(self):
        while int(time.time()) < int(self.last_build_time) + 1:
            time.sleep(0.1)

            
class List:

    def __init__(self, s=""):
        elements = []
        if isinstance(s, type("")):          
            # Have to handle espaced spaces correctly
            s = string.replace(s, "\ ", '\001')
            elements = string.split(s)
        else:
            elements = s;
            
        self.l = []            
        for e in elements:
            self.l.append(string.replace(e, '\001', ' '))

    def __len__(self):
        return len(self.l)

    def __getitem__(self, key):
        return self.l[key]

    def __setitem__(self, key, value):
        self.l[key] = value

    def __delitem__(self, key):
        del self.l[key]

    def __str__(self):
        return str(self.l)

    def __repr__(self):
        return ( self.__module__ + '.List('
                 + repr(string.join(self.l, ' '))
                 + ')')

    def __mul__(self, other):        
        result = List()
        if not isinstance(other, List):
            other = List(other)
        for f in self:
            for s in other:
                result.l.append(f + s)
        return result

    def __rmul__(self, other):
        if not isinstance(other, List):
            other = List(other)        
        return List.__mul__(other, self)

    def __add__(self, other):
        result = List()
        result.l = self.l[:] + other.l[:]
        return result

# quickie tests. Should use doctest instead.
if __name__ == '__main__':
    assert str(List("foo bar") * "/baz") == "['foo/baz', 'bar/baz']"
    assert repr("foo/" * List("bar baz")) == "__main__.List('foo/bar foo/baz')"
    print 'tests passed'




