# Copyright (c) Daniel Wallin 2007
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import os.path
import StringIO
import re

try:
    import xml.etree.cElementTree as ET
except ImportError:
    import elementtree.cElementTree as ET

try:
    set
except:
    from Sets import set

class TestResults(object):

    def __init__(self, source):
        self.dependencies = {}
        self.dependents = {}
        self.tests = set()
        self.results = {}
        if isinstance(source, basestring):
            source = StringIO.StringIO(source)
        self._read_xml(source)

    def _read_xml(self, source):
        i = iter(ET.iterparse(source, events=('start', 'end')))
        event, root = i.next()

        for event, elem in i:
            if event == 'end' and elem.tag == 'targets':
                break

        self.jam_version = root.find('jam').get('version')
        self.os = root.find('os')
        self.os = self.os.get('name'), self.os.get('platform'), self.os.text
        self.timestamp = root.find('timestamp').text
        self.directory = root.find('directory').text
        self.command = root.find('command').text

        self._read_targets(elem)
        root.clear()
        self._read_actions(i)

    def _read_targets(self, targets):
        for target in targets:
            name = target.find('name').text
            path = target.find('path')
            if path is None:
                continue
            path = path.text
            jam_target = target.find('jam-target').text
            jam_target = self._as_absolute_path(jam_target)
            self.dependencies[jam_target] = [self._as_absolute_path(d.text) 
                                             for d in target.find('dependencies')]
            for d in self.dependencies[jam_target]:
                self.dependents.setdefault(d, []).append(jam_target)
            if jam_target.endswith('.test'):
                self.tests.add(jam_target)

    gristed_re = re.compile('^<p([^>]+)>(.*)$')

    def _as_absolute_path(self, jam_target):
        m = self.gristed_re.match(jam_target)
        if m:
            result = os.path.join(self.directory, m.group(1), m.group(2))
        else:
            result = os.path.join(self.directory, jam_target)
        return os.path.normpath(result)

    def _read_actions(self, i):
        for event, elem in i: 
            if event == 'end' and elem.tag == 'action':
                status = elem.get('status')
                target = elem.find('jam-target')
                command = elem.find('command')
                output = elem.find('output')
                if target is None:
                    continue

                properties = {}
                for p in elem.find('properties') or []:
                    properties[p.get('name')] = p.text

                name = self._as_absolute_path(target.text)
                self.results[name] = (status == '0', command.text, output.text, properties)
                elem.clear()

    def _follow_dependencies(self, target):
        if target in self.results:
            result = self.results[target]
            if not result[0]:
                return [(target, result[1], result[2], result[3])]
            else:
                return []
        else:
            dependencies = self.dependencies.get(target, None)
            if dependencies:
                result = []
                for d in self.dependencies.get(target, []):
                    result.extend(self._follow_dependencies(d))
                return result
            return []

    # TOOD:
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
            if test in self.results:
                yield (test, 'success', None)
            else:
                failures = self._follow_dependencies(test)
                if failures:
                    yield (test, 'failed', failures)
                else:
                    yield (test, 'skipped', None)

