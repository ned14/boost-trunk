# Copyright David Abrahams 2007. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

import os.path
import test_results

try:
    import xml.etree.cElementTree as ET
except ImportError:
    import elementtree.cElementTree as ET

def indent(elem, level=0):
    i = "\n" + level*"  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        for elem in elem:
            indent(elem, level+1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

def lib_subdir_and_test_name_from_target(target_name):
    l = []
    p = target_name.split('/')
    for x in p[p.index('libs')+1:]:
        if x.endswith('.test'):
            return '/'.join(l), x[:-5]
        l.append(x)
    return None
    
    
def create_bitten_reports(input_filename, failure_markup):
    failed = False
    results = test_results.TestResults(open(input_filename))

    report = ET.Element('report', category='test', 
                        generator="http://svn.boost.org/svn/boost/trunk/tools/"
                                  "regression/src/bitten_reports.py")

    for target, status, actions in results:
        if status == 'skipped':
            continue

        subdir, fixture = lib_subdir_and_test_name_from_target(target)

        if status == 'failed':
            path = os.path.split(subdir)
            if (path[-1] == 'test'):
                lib_name = '/'.join(path[:-1])
            else:
                lib_name = subdir

            l = failure_markup.libraries.get(lib_name)
            if l:
                a = actions[0]
                
                toolset = a.properties['toolset']
                toolset_version = a.properties['toolset-%s:version' % toolset]
                if toolset_version:
                    toolset = '-'.join((toolset,toolset_version))
                i = l.test_info(fixture, toolset)
                if i:
                    print 'Marked', target, 'because of markup:', '\n'.join(
                        [ET.tostring(x) for x in i])
                    status = 'marked'
                    print 'report status:', (status == 'failed') and 'failure' or 'success'

        if status == 'failed':
            bitten_status = 'failure'
            failed = True
        else:
            bitten_status = 'success'

        test = ET.SubElement(
                report, 'test', duration="0", 
                fixture=fixture,
                name=fixture,
                file='libs/%s/%s.cpp' % (subdir,fixture),
                status=bitten_status)
                                 
        if status is not 'success':
            stdout = ET.SubElement(test, 'stdout')
            stdout.text = '\n'.join([ ''.join((
                '\n====== COMMAND ======\n',
                a.command.strip(),
                '\n====== BEGIN OUTPUT ======\n',
                a.output, a.output[-1:] != '\n' and '\n' or ''
                '====== END OUTPUT ======\n'))
                            for a in actions ])
            
    indent(report)

    platform_report = ET.Element('report', category='platform')
    platform = ET.SubElement(platform_report, 'platform')

    platform.set('os', results.os[0])
    platform.set('platform', results.os[1])
    if results.os[2]:
        platform.set('os-extra', results.os[2])
    platform.set('jam-version', results.jam_version)
    platform.set('command', results.command)
    platform.set('timestamp', results.timestamp)

    indent(platform_report)
    return failed, ET.tostring(report, 'utf-8')

if __name__ == '__main__':
    from failure_markup import FailureMarkup
    print create_bitten_reports('/tmp/results.xml', FailureMarkup(open('../../../boost/status/explicit-failures-markup.xml')))
