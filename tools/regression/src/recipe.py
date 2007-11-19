# Copyright David Abrahams 2007. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# This was output by "bjam -n --boost-dependency-info"

dependencies = '''test/build:
config/test/link:
algorithm/minmax/test:
algorithm/string/test: regex/build
regex/build:
date_time/build:
system/build:
thread/build:
asio/test: thread/build system/build date_time/build
assign/test: test/build
any/test:
bimap/test: serialization/build
serialization/build:
bind/test:
circular_buffer/test:
concept_check:
conversion/test: test/build
date_time/test: date_time/build serialization/build
disjoint_sets:
dynamic_bitset:
filesystem/build: system/build
filesystem/test: filesystem/build system/build
foreach/test:
format/test: test/build
function/test: test/build
functional/hash/test:
functional/hash/examples:
function_types/test:
fusion/test:
gil/test:
graph/test: test/build graph/build serialization/build system/build filesystem/build
graph/build:
io/test: test/build
interprocess/example: thread/build
interprocess/test: thread/build
intrusive/example: thread/build
intrusive/test:
iostreams/test: test/build iostreams/build regex/build
iostreams/build:
iterator/test:
lambda/test: test/build
logic/test:
math/test: regex/build test/build
mpl/test:
numeric/conversion/test:
numeric/interval/test: test/build
numeric/ublas/test:
multi_array/test: test/build
multi_index/test: serialization/build
optional/test:
parameter/test: python/build
python/build:
program_options/build:
program_options/test: program_options/build
property_map/test:
ptr_container/test: test/build serialization/build
python/test: python/build
random/test:
range/test: test/build
regex/test: regex/build thread/build regex/test/captures
regex/test/captures: regex/build
regex/example: regex/build program_options/build regex/test/captures
serialization/test: serialization/build
signals/build:
signals/test: test/build signals/build
smart_ptr/test:
spirit/test: thread/build
statechart/test: test/build
static_assert:
system/test: system/build
test/test: test/build
thread/test: test/build thread/build
tr1/test:
tuple/test: test/build
type_traits/test:
typeof/test:
utility/enable_if/test: test/build
utility/test: test/build
variant/test:
wave/test/build: date_time/build filesystem/build system/build thread/build wave/build program_options/build
wave/build: filesystem/build system/build thread/build date_time/build
xpressive/test: test/build'''

    
lines = dependencies.split('\n')
# create alphabetical ordering where possible
lines.sort()

# Graph representation
children = {}

for l in lines:
    dependent, dependencies = tuple(l.split(':'))
    children[dependent] = dependencies.split(' ')[1:]
    children[dependent].sort()


color = {}
gray = 'gray'
black = 'black'

class loop(Exception): pass

projects = []

# Depth first search for topological sort
def dfs(start):
    c = color.get(start)
    if (c == gray):
        raise loop, start
    if (c == black): # visited already
        return

    # starting a visit
    color[start] = gray

    # visit all children
    for child in children[start]:
        dfs(child)

    # okay, all children visited
    projects.append(start)
    
    # ending a visit
    color[start]=black

# There's a 1-1 mapping between lines and the nodes they name as dependents.  Go
# through them in alphabetical order
for l in lines:
    n = l[:l.find(':')]
    dfs(n)

import xml.dom.minidom

def dump():
    repo = 'https://svn.boost.org/svn/boost/branches/bitten'
    # repo = 'file:///usr/local/share/svnroot/boost'

    def is_test_project(path):
        e = path.split('/')
        # build/ subdirectories are always Jamfiles for library binaries, not
        # tests... except for wave which keeps tests in libs/wave/test/build :(
        return e[-1] != 'build' or 'test' in e[1:]

    import re
    
    print head_xml % {
        'repo': repo
        } + ''.join([
            project_xml % {'project_path':p, 'id':
                           re.sub('(.+)/test(/build)?(.*)', r'\1\3', p, 1)}
            for p in projects if is_test_project(p)]
        ) + tail_xml

    #     <python:exec module="shutil" args="-c 'shutil.copy(&quot;tools_regression/src/run.py&quot;, &quot;.&quot;')" />

head_xml = '''<?xml version="1.0" encoding="UTF-8"?>
<build xmlns:sh="http://bitten.cmlenz.net/tools/sh" 
       xmlns:x="http://bitten.cmlenz.net/tools/xml" 
       xmlns:svn="http://bitten.cmlenz.net/tools/svn"
       xmlns:python="http://bitten.cmlenz.net/tools/python"
>
  <step id="get-boost" description="Update Boost source code to version being tested">
    <svn:checkout 
       dir_="boost"
       url="https://svn.boost.org/svn/boost/trunk"
    revision="${revision}" />
  </step>
  <step id="get-tool-source" description="Update tools source code to version being tested">
    <svn:checkout 
       dir_="tools"
       url="%(repo)s/tools"
    revision="HEAD" />
    <svn:checkout 
       dir_="tools_regression"
       url="%(repo)s/tools/regression"
    revision="HEAD" />
    <svn:checkout 
       dir_="tools_bb"
       url="%(repo)s/tools/build/v2"
    revision="HEAD" />
    <svn:checkout 
       dir_="tools_bjam"
       url="%(repo)s/tools/jam/src"
    revision="HEAD" />
  </step>

  <step id="build tools" description="Build regression testing tools">
    <python:exec file="tools_regression/src/run.py" args="--incremental --debug-level=10 --bjam-options=-j${boost.parallelism} ${boost.tool-build-options} setup" />
  </step>
  '''
project_xml ='''                                                     
  <step id="%(id)s" description="Tests run in %(project_path)s" onerror="continue">
    <python:exec file="tools_regression/src/run.py" args="--incremental --clean-log --library=%(project_path)s --bjam-options=-j${boost.parallelism} ${boost.lib-build-options} --reflect-test-status --bitten-report=results/%(project_path)s.xml test-run create-bitten-report" />
    <report category="test" file="results/%(project_path)s.xml" />
  </step>
'''
tail_xml ='''                                                     
</build>
'''

dump()
