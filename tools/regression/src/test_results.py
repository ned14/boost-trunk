# Copyright (c) Daniel Wallin 2007
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import os.path
import StringIO

try:
    import xml.etree.cElementTree as ET
except ImportError:
    import elementtree.cElementTree as ET

try:
    set
except:
    from Sets import set

class Action(object):
    def __init__(self, jam_target, status, command, output, properties):
        self.jam_target = jam_target.text
        self.status = status
        self.command = command.text
        self.output = output is not None and output.text or ''
        self.properties = {}
        for p in properties or []:
            self.properties[p.get('name')] = p.text

class TestResults(object):

    def __init__(self, source):
        self.dependencies = {}
        self.dependents = {}
        self.tests = set()
        self.actions = {}
        self.target_name = {}
        self.directory = {}
        if isinstance(source, basestring):
            source = StringIO.StringIO(source)
            
        self._read_xml(source)

        # Find the set of targets that don't depend on anything else.
        # This sounds as though it's coded backwards, but when you iterate
        # through the "dependents" dictionary, you get the keys, which are all
        # dependencies.
        self.sources = set([ d for d in self.dependents if not d in
                             self.dependencies ])
        
    def _read_xml(self, source):
        i = iter(ET.iterparse(source, events=('start', 'end')))
        event, root = i.next()

        # Parse until all targets have been seen and added below root
        for event, elem in i:
            if event == 'end' and elem.tag == 'targets':
                break

        # Presumably all this other information is required to appear before the
        # end of the targets.
        self.jam_version = root.find('jam').get('version')
        self.os = root.find('os')
        self.os = self.os.get('name'), self.os.get('platform'), self.os.text
        self.timestamp = root.find('timestamp').text
        self.working_directory = root.find('directory').text
        self.command = root.find('command').text

        self._read_targets(elem)
        root.clear()
        self._read_actions(i)

    def _read_targets(self, targets):
        for target in targets:
            name = target.find('name').text
            directory = target.find('directory')
            
            if directory is None:
                continue
            
            jam_target = target.find('jam-target').text
            self.directory[jam_target] = directory.text
            self.target_name[jam_target] = name

            dependencies = target.find('dependencies')
            if dependencies is not None:
                self.dependencies[jam_target] = [ d.text for d in dependencies]
                for d in self.dependencies[jam_target]:
                    self.dependents.setdefault(d, []).append(jam_target)
                
            if jam_target.endswith('.test'):
                self.tests.add(jam_target)

    def _read_actions(self, i):
        for event, elem in i: 
            if event == 'end' and elem.tag == 'action':

                jam_target = elem.find('jam-target')
                self.actions[jam_target.text] = Action(
                    jam_target,
                    elem.get('status'),
                    elem.find('command'),
                    elem.find('output'),
                    elem.find('properties'))
                
                elem.clear()


    def _why_not_built(self, target):
        action = self.actions.get(target)
        if action:
            # target's dependencies were built; target itself failed
            return [action] 
        else:
            # target's build action never started.  Either target was already
            # up-to-date and thus skipped, or one of its dependencies failed.
            # Collect all failures of target's dependencies.
            results = []
            for d in self.dependencies.get(target, []):
                results.extend( self._why_not_built(d) )
            return results
            
    # TODO:
    # Compute the duration of the tests. It's not entirely
    # clear what this should consist of. We should probably
    # add up all the durations for the different stages in
    # the test. Ideally we would also factor in the duration
    # of building dependencies, but it's not clear how that
    # would work.

    def __iter__(self):
        return iter(self.result())

    def result(self):
        for test in self.tests:
            if test in self.actions:
                yield (test, 'success', None)
            else:
                failures = self._why_not_built(test)
                if failures:
                    yield (test, 'failed', failures)
                else:
                    yield (test, 'skipped', None)

if __name__ == '__main__':
    r = TestResults(open('/tmp/results.xml'))
    from pprint import pprint
    for x in r:
        pprint(x)
