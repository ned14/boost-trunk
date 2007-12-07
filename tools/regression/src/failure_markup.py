# Copyright David Abrahams 2007. Distributed under the Boost
# Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import re
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import elementtree.cElementTree as ET

# Map glob patterns to regexps
regexps = {}
def _glob2regex(glob):
    r = regexps.get(glob)
    if r:
        return r
    
    r = re.compile(
        '^%s$'
        % '.*'.join([ re.escape(part) for part in glob.split('*') ]))
    
    regexps[glob] = r
    return r

class Library(object):
    def __init__(self, element):
        self.element = element
        self.tests =  dict((t.attrib['name'],t) for t in element.findall('test'))

    def unusable(self, toolset):
        r = []
        
        for u in self.element.findall('mark-unusable'):
            for t in u.findall('toolset'):
                if _glob2regex(t.attrib['name']).match(toolset):
                    r += u.findall('note') or ['no note given']
                    break
            
        return r

    def test_info(self, test, toolset):
        r = []
        
        test_element = self.tests.get(test, [])
        for f in test_element:
            found = False
            for toolset_elt in f.findall('toolset'):
                if _glob2regex(toolset_elt.attrib['name']).match(toolset):
                    found = True
                    break
                
            if found:
                r.append(test_element)
              
        for f in self.element.findall('mark-expected-failures'):
            matched = {'toolset':False,'test':False}
            for e in f:
                tag = e.tag
                if e.tag != 'note':
                    if _glob2regex(e.attrib['name']).match(locals()[tag]):
                        matched[tag] = True
                        if not False in matched.itervalues():
                            r.append(f)
                            break
                        
        return r
        
class FailureMarkup(object):
    def __init__(self, stream):
        self.markup = ET.parse(stream).getroot()
        
        self.required_toolsets = set(
            c.attrib['name'] for c in self.markup.findall('mark-toolset') if c.attrib['status'] == 'required')
        
        self.libraries = dict(
            (l.attrib['name'], Library(l)) for l in self.markup.findall('library'))

        self.standard_notes = dict(
            (c.attrib['id'],c) for c in self.markup.findall('note'))


if __name__ == '__main__':
    exemplar = r'''<?xml version="1.0" encoding="utf-8"?>
<explicit-failures-markup xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xsi:noNamespaceSchemaLocation="explicit-failures.xsd">


    <!-- /////////////// Toolsets /////////////// -->
    <mark-toolset name="darwin-4.0.1" status="required"/>
    <mark-toolset name="gcc-3.4.3_sunos" status="required"/>
    <mark-toolset name="gcc-3_4_4_tru64" status="required"/>
    <mark-toolset name="gcc-4.1.2_sunos_i86pc" status="required"/>
    <!-- ... -->

    <!-- /////////////// Libraries /////////////// -->

    <!-- string_algo -->
    <library name="algorithm/string">
        <mark-unusable>
            <toolset name="borland-5.5*"/>
            <toolset name="msvc-7.1_stlport4"/>
            <toolset name="iw-7_1-vc6"/>
            <toolset name="gcc-2.95.3-stlport-4.5.3-linux"/>
            <note author="P.Droba">
                The compiler does not support features that are essential for the library.
            </note>
        </mark-unusable>

        <!-- category is optional; can be something like "Native
        compiler support" or "Corner-case tests" -->
        <test name="regex" category="...">
            <mark-failure>
                <toolset name="borland-5.9*"/>
                <toolset name="msvc-*"/>
                <!-- date is optional; format appears to be one of
                     
                     14 Feb 06
                     14 Feb 2006
                     2006-02-14

                  -->

                <note author="Andreas Huber" refid="0" date="..."/>
            </mark-failure>
        </test>

        <!-- reason is optional; apparently can be "?" but nothing else is ever used. -->
        <mark-expected-failures reason="...">
            <test name="*_emulation"/>
            <toolset name="msvc-6.5*"/>
            <toolset name="msvc-7.0"/>
            <toolset name="cw-8_*"/>
            <note author="Arkadiy Vertleyb">
                Emulation mode is not supported for this compiler.
            </note>
        </mark-expected-failures>

    </library>
    
    <!-- /////////////// Standard note definitions /////////////// -->

    <note id="0">
        This test fails only intermittently.
    </note>

    <note id="1">
        The failure is caused by a problem in Boost code. The Boost developers are aware of
        the problem and plan to fix it.
    </note>

</explicit-failures-markup>
'''
    import cStringIO
    f = FailureMarkup(cStringIO.StringIO(exemplar))
    for d in (
        'darwin-4.0.1', "gcc-3.4.3_sunos", "gcc-3_4_4_tru64",
        "gcc-4.1.2_sunos_i86pc"):
        
        assert d in f.required_toolsets

    assert 'foo' not in f.libraries
    assert 'algorithm/string' in f.libraries
    l = f.libraries['algorithm/string']
    assert l.unusable('borland-5.5.4')
    assert not l.unusable('borland-5.6')
    assert not l.test_info(test='foo', toolset='bar')
    assert not l.test_info(test='regex', toolset='gcc')
    
    info = l.test_info(test='regex', toolset='msvc-6.5')
    assert len(info) == 1
    assert info[0].tag == 'test'
    
    assert not l.test_info(test='foobar_emulation', toolset='gcc')
    info = l.test_info(test='foobar_emulation', toolset='msvc-6.5.1')
    assert len(info) == 1
    assert info[0].tag == 'mark-expected-failures'
