# Copyright David Abrahams 2007. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# This was output by "bjam -n --boost-dependency-info"
dependencies = '''test:
config:
algorithm: regex
regex: thread program_options
date_time: serialization
system:
thread: test
asio: thread system date_time
assign: test
any:
bimap: serialization
serialization:
bind:
circular_buffer:
concept_check:
conversion: test
disjoint_sets:
dynamic_bitset:
filesystem: system
foreach:
format: test
function: test
functional:
fusion:
gil:
graph: test serialization system filesystem
io: test
interprocess: thread
intrusive: thread
iostreams: test regex
iterator:
lambda: test
logic:
math: regex test
mpl:
numeric: test
multi_array: test
multi_index: serialization
optional:
parameter: python
python:
program_options:
property_map:
ptr_container: test serialization
random:
range: test
signals: test
smart_ptr:
spirit: thread
statechart: test
static_assert:
tr1:
tuple: test
type_traits:
typeof:
utility: test
variant:
wave: date_time filesystem system thread program_options
xpressive: test'''

    
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

libraries = []

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
    libraries.append(start)
    
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
    repo = 'file:///usr/local/share/svnroot/boost'
    
    print head % {
        'repo': repo
        } + ''.join([lib % {'libname':l} for l in libraries]) + tail
    
head = '''<?xml version="1.0" encoding="UTF-8"?>
<build xmlns:sh="http://bitten.cmlenz.net/tools/sh" 
       xmlns:x="http://bitten.cmlenz.net/tools/xml" 
       xmlns:svn="http://bitten.cmlenz.net/tools/svn"
       xmlns:python="http://bitten.cmlenz.net/tools/python"
>
  <step id="get-tool-source" description="Update tools source code to version being tested">
    <svn:checkout 
       dir_="tools_regression"
       url="%(repo)s/tools_regression"
    revision="${revision}" />
    <python:exec args="-c 'import shutil;shutil.copy(&quot;tools_regression/src/run.py&quot;, &quot;.&quot;')" />
    <svn:checkout 
       dir_="tools_bb"
       url="%(repo)s/tools/build/v2"
    revision="${revision}" />
    <svn:checkout 
       dir_="tools_jam"
       url="%(repo)s/tools/build/v2"
    revision="${revision}" />
  </step>

  <step id="build tools" description="Build regression testing tools">
    <python:exec file="run.py" args="--incremental --bjam-options=-j${boost.parallelism} ${boost.tool-build-options} setup" />
  </step>
  '''
lib ='''                                                     
  <step id="%(libname)s" description="Tests for %(libname)s">
    <python:exec file="run.py" args="--incremental --library=%(libname)s --bjam-options=-j${boost.parallelism} ${boost.lib-build-options} --bitten-report=results/%(libname)s.xml setup test-run test-process create-bitten-report" />
    <report category="test" file="results/%(libname)s.xml" />
  </step>
'''
tail ='''                                                     
</build>
'''

dump()
