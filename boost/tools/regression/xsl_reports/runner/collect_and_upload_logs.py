
# Copyright (c) MetaCommunications, Inc. 2003-2004
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import xml.sax.saxutils
import zipfile

import os.path
import string
import sys


def process_xml_file( input_file, output_file ):
    utils.log( 'Processing test log "%s"' % input_file )
    
    f = open( input_file, 'r' )
    xml = f.readlines()
    f.close()
    
    for i in range( 0, len(xml)):
        xml[i] = string.translate( xml[i], utils.char_translation_table )

    output_file.writelines( xml )


def process_test_log_files( output_file, dir, names ):
    for file in names:
        if os.path.basename( file ) == 'test_log.xml':
            process_xml_file( os.path.join( dir, file ), output_file )


def collect_test_logs( input_dirs, test_results_writer ):
    __log__ = 1
    utils.log( 'Collecting test logs ...' )
    for input_dir in input_dirs:
        utils.log( 'Walking directory "%s" ...' % input_dir )
        os.path.walk( input_dir, process_test_log_files, test_results_writer )


def upload_results_file( user, tag, results_file ):
    upload_dir = 'regression-logs/incoming/%s/' % tag
    utils.log( 'Uploading test results file "%s" into "%s" [connecting as %s]...' % ( results_file, upload_dir, user ) )
    
    utils.sourceforge.upload( results_file, upload_dir, user )


def copy_comments( results_xml, comment_file ):
    results_xml.startElement( "comment", {} )

    utils.log( 'Reading comments file "%s"...' % comment_file )
    f = open( comment_file, 'r' )
    try:
        comments = f.read()
    finally:
        f.close()
        
    results_xml.characters( comments )
    results_xml.endElement( "comment" )


def collect_and_upload_logs( 
          locate_root_dir
        , runner
        , tag
        , platform
        , comment_file
        , timestamp
        , user
        ):
    
    test_results_file =  '%s.xml' % runner
    test_results_writer = open( test_results_file, "w" )
    utils.log( 'Collecting test logs into "%s"...' % test_results_file )
    
    results_xml = xml.sax.saxutils.XMLGenerator( test_results_writer )
    results_xml.startDocument()
    results_xml.startElement( 
          "test-run"
        , { 
              "tag":        tag
            , "platform":   platform
            , "runner":     runner
            , "timestamp":  timestamp 
            }
        )
    
    copy_comments( results_xml, comment_file )
    collect_test_logs( [ locate_root_dir ], test_results_writer )

    results_xml.endElement( "test-run" )
    results_xml.endDocument()
    utils.log( 'Done writing "%s"...' % test_results_file )

    utils.log( 'Compressing "%s"...' % test_results_file )
    
    test_results_archive = os.path.splitext( test_results_file )[0] + ".zip"
    z = zipfile.ZipFile( test_results_archive, "w", zipfile.ZIP_DEFLATED ) 
    z.write( test_results_file, os.path.basename( test_results_file ) )
    z.close()
    
    upload_results_file( user, tag, test_results_archive )


def accept_args( args ):
    args_spec = [ 
          'locate-root='
        , 'runner='
        , 'tag='
        , 'platform='
        , 'comment='
        , 'timestamp='
        , 'user='
        , 'help'
        ]
    
    options = {}
    utils.accept_args( args_spec, args, options, usage )
        
    return ( 
          options[ '--locate-root' ]
        , options[ '--runner' ]
        , options[ '--tag' ]
        , options[ '--platform']
        , options[ '--comment' ]
        , options[ '--timestamp' ]
        , options[ '--user' ]
        )


def usage():
    print 'Usage: %s [options]' % os.path.basename( sys.argv[0] )
    print    '''
\t--locate-root         directory to to scan for 'test_log.xml' files
\t--runner              runner ID (e.g. 'Metacomm')
\t--tag                 the tag for the results (e.g. 'CVS-HEAD')
\t--platform            platform name
\t--comment             an html comment file (will be inserted in the reports)
\t--timestamp           timestamp of the run
\t--user                SourceForge user name for a shell account
'''
    
def main():
    collect_and_upload_logs( *accept_args( sys.argv[ 1 : ] ) )


if __name__ != '__main__':  import utils
else:
    # in absense of relative import...
    xsl_path = os.path.abspath( os.path.dirname( sys.argv[ 0 ] ) )
    while os.path.basename( xsl_path ) != 'xsl_reports': xsl_path = os.path.dirname( xsl_path )
    sys.path.append( xsl_path )

    import utils
    main()
