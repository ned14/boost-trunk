
# Copyright (c) MetaCommunications, Inc. 2003-2004
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import shutil
import xml.sax.handler
import glob
import os.path
import os
import string
import time
import sys
import ftplib

import utils
import runner


report_types = [ 'us', 'ds', 'ud', 'dd', 'l', 'p', 'i', 'n', 'ddr', 'dsr' ]

if __name__ == '__main__':
    run_dir = os.path.abspath( os.path.dirname( sys.argv[ 0 ] ) )
else:
    run_dir = os.path.abspath( os.path.dirname( sys.modules[ __name__ ].__file__ ) )


def map_path( path ):
    return os.path.join( run_dir, path ) 


def xsl_path( xsl_file_name ):
    return map_path( os.path.join( 'xsl/v2', xsl_file_name ) )

class file_info:
    def __init__( self, file_name, file_size, file_date ):
        self.name = file_name
        self.size = file_size
        self.date = file_date

    def __repr__( self ):
        return "name: %s, size: %s, date %s" % ( self.name, self.size, self.date )

#
# Find the mod time from unix format directory listing line
#

def get_date( words ):
    date = words[ 5: -1 ]
    t = time.localtime()

    month_names = [ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" ]

    year = time.localtime()[0] # If year is not secified is it the current year
    month = month_names.index( date[0] ) + 1
    day = int( date[1] )
    hours = 0 
    minutes = 0

    if  date[2].find( ":" ) != -1:
        ( hours, minutes ) = [ int(x) for x in date[2].split( ":" ) ]
    else:
        # there is no way to get seconds for not current year dates
        year = int( date[2] )

    return ( year, month, day, hours, minutes, 0, 0, 0, 0 )

def list_ftp( f ):
    # f is an ftp object
    utils.log( "listing source content" )
    lines = []

    # 1. get all lines
    f.dir( lambda x: lines.append( x ) )

    # 2. split lines into words
    word_lines = [ x.split( None, 8 ) for x in lines ]

    result = [ file_info( l[-1], None, get_date( l ) ) for l in word_lines ]
    for f in result:
        utils.log( "    %s" % f )
    return result

def list_dir( dir ):
    utils.log( "listing destination content %s" % dir )
    result = []
    for file_name in  os.listdir( dir ):
        file_path = os.path.join( dir, file_name )
        if os.path.isfile( file_path ):
            # print f, time.localtime( os.path.getmtime( f ) )
            mod_time = time.localtime( os.path.getmtime( file_path ) )
            # no wday, yday and isdst
            mod_time = ( mod_time[0], mod_time[1], mod_time[2], mod_time[3], mod_time[4], mod_time[5], 0, 0, 0 )
            # no size (for now)
            result.append( file_info( file_name, None, mod_time ) )
    for fi in result:
        utils.log( "    %s" % fi )
    return result

def find_by_name( d, name ):
    for dd in d:
        if dd.name == name:
            return dd
    return None

def diff( s, d ):
    utils.log( "Finding files to copy" )
    result = []
    for source in s:
        found = find_by_name( d, source.name )
        if found is None: result.append( source.name )
        elif found.date != source.date: result.append( source.name )
        else:
            pass
    for f in result:
        utils.log( "    %s" % f )
    return result
        
        
def ftp_task( site, site_path , destination ):
    utils.log( 'Execting ftp from "ftp://%s/%s" -> %s' % ( site, site_path, destination ) )

    utils.log( '   logging on ftp site %s' % site )
    f = ftplib.FTP( site )
    f.login()
    utils.log( '   cwd to "%s"' % site_path )
    f.cwd( site_path )

    source_content = list_ftp( f )
    #print "\n".join( [ "%s" % x for x in source_content ] )

    # print ""
    
    destination_content = list_dir( destination )
    # print "\n".join( [ "%s" % x for x in destination_content ] )

    d = diff( source_content, destination_content )

    utils.log( "Copying update files" )
    for source in d:
        utils.log( 'Copying "%s"' % source )
        result = open( os.path.join( destination, source ), 'wb' )
        f.retrbinary( 'RETR %s' % source, result.write )
        result.close()
        m = time.mktime( find_by_name( source_content, source ).date )
        os.utime( os.path.join( destination, source ), ( m, m ) )
        
    


def sync_dirs( file_mask, source_dir, destination_dir, timestamp, do_sync ):
    utils.makedirs( destination_dir )
    files = glob.glob( os.path.join( source_dir, file_mask ) )
    for src in files:
        dst = os.path.join( destination_dir, os.path.basename( src ) )
        utils.log( '    "%s" <-> "%s"' % ( src, dst ) )
        if not os.path.exists( dst ) or timestamp( src ) > timestamp( dst ):
            do_sync( src )


def sync_archives_task( source_dir, processed_dir, unzip_func ):

    def _modtime_timestamp( file ):
        return os.stat( file ).st_mtime

    def _unzip( zip_file ):
        try:
            utils.log( '  Unzipping "%s" ...' % zip_file )
            unzip_func( zip_file, source_dir )
            utils.log( '  Copying "%s" into "%s"' % ( zip_file, processed_dir ) )
            shutil.copy2( zip_file, processed_dir )
        except Exception, msg:
            utils.log( '  Skipping "%s" due to errors (%s)' % ( zip_file, msg ) )

    utils.log( 'Unpacking updated archives in "%s"...' % source_dir )
    sync_dirs(
          '*.zip'
        , source_dir
        , processed_dir
        , _modtime_timestamp
        , _unzip
        )



def sync_xmls_task( source_dir, processed_dir, merged_dir, expected_results_file, failures_markup_file ):    

    def _xml_timestamp( xml_path ):

        class timestamp_reader( xml.sax.handler.ContentHandler ):
            def startElement( self, name, attrs ):
                if name == 'test-run':
                    self.timestamp = attrs.getValue( 'timestamp' )
                    raise self

        try:
            xml.sax.parse( xml_path, timestamp_reader() )
            raise 'Cannot extract timestamp from "%s". Invalid XML file format?' % xml_path
        except timestamp_reader, x:
            return x.timestamp

        
    def _process_updated_xml( xml ):
        utils.log( '  Merging "%s" with expected results...' % xml )
        utils.libxslt( 
            utils.log
            , xml
            , xsl_path( 'add_expected_results.xsl' )
            , os.path.join( merged_dir, os.path.basename( xml ) )
            , {
              "expected_results_file" : expected_results_file
              , "failures_markup_file": failures_markup_file
              }
            )
        
        utils.log( '  Copying "%s" into "%s"' % ( xml, processed_dir ) )
        shutil.copy2( xml, processed_dir )


    utils.log( 'Processing updated XMLs in "%s"...' % source_dir )
    sync_dirs(
          '*.xml'
        , source_dir
        , processed_dir
        , _xml_timestamp
        , _process_updated_xml
        )

class xmlgen( xml.sax.saxutils.XMLGenerator ):
    document_started = 0
        
    def startDocument(self):
        if not self.document_started:
            xml.sax.saxutils.XMLGenerator.startDocument( self )
            self.document_started = 1


def merge_processed_test_runs( test_runs_dir, tag, writer ):
    all_runs_xml = xmlgen( writer )
    all_runs_xml.startDocument()
    all_runs_xml.startElement( 'all-test-runs', {} )

    utils.log( 'Merging processed test runs into a single XML... %s' % test_runs_dir )
    files = glob.glob( os.path.join( test_runs_dir, '*.xml' ) )
    for test_run in files:
        try:
            utils.log( '  Writing "%s" into the resulting XML...' % test_run )
            xml.sax.parse( test_run, all_runs_xml  )
        except Exception, msg:
            utils.log( '  Skipping "%s" due to errors (%s)' % ( test_run, msg ) )

    all_runs_xml.endElement( 'all-test-runs' )
    all_runs_xml.endDocument()

def execute_tasks(
          tag
        , user
        , run_date
        , comment_file
        , results_dir
        , output_dir
        , reports
        , extended_test_results
        , dont_collect_logs
        , expected_results_file
        , failures_markup_file
        ):

    
    # results_xml_path = os.path.join( results_dir, results_xml )
    # utils.log( 'Merging test runs into "%s"...' % results_xml_path )


    incoming_dir = os.path.join( results_dir, 'incoming', tag )
    processed_dir = os.path.join( incoming_dir, 'processed' )
    merged_dir = os.path.join( processed_dir, 'merged' )
    if not os.path.exists( incoming_dir ):
        os.makedirs( incoming_dir )
    if not os.path.exists( processed_dir ):
        os.makedirs( processed_dir )
    if not os.path.exists( merged_dir ):
        os.makedirs( merged_dir )
    
    if not dont_collect_logs:
        ftp_site = 'fx.meta-comm.com'
        site_path = '/boost-regression/%s' % tag

        ftp_task( ftp_site, site_path, incoming_dir )


    sync_archives_task( incoming_dir, processed_dir, utils.unzip )
    sync_xmls_task( incoming_dir, processed_dir, merged_dir, expected_results_file, failures_markup_file )
    
    make_links_task( merged_dir
                     , output_dir
                     , tag
                     , run_date
                     , comment_file
                     , extended_test_results
                     , failures_markup_file )


    results_xml_path = os.path.join( output_dir, "extended_test_results.xml" )
    writer = open( results_xml_path, 'w' )
    merge_processed_test_runs( merged_dir, tag, writer )
    writer.close()

    
    make_result_pages(
          extended_test_results
        , expected_results_file
        , failures_markup_file
        , tag
        , run_date
        , comment_file
        , output_dir
        , reports
        )

def stamp( stamp_path, stamp_date_origin ):
    if not os.path.exists( stamp_path ):
        open( stamp_path, "w" ).close()

    timestamp = os.path.getmtime( stamp_date_origin )
    os.utime( stamp_path, ( timestamp, timestamp ) )

def timestamps_different( f1, f2 ):
    if not os.path.exists( f1 ) or not os.path.exists( f2 ):
        return 1
    else:
        return time.localtime( os.path.getmtime( f1 ) ) != time.localtime( os.path.getmtime( f2 ) )

def make_links_task( input_dir, output_dir, tag, run_date, comment_file, extended_test_results, failures_markup_file ):

    input_files = glob.glob( os.path.join( input_dir, "*.xml" ) )
    links = os.path.join( output_dir, 'links.html' )
    for input_file in input_files:
        stamp_file = input_file + ".links"

        if timestamps_different( input_file, stamp_file ):
            utils.makedirs( os.path.join( output_dir, 'output' ) )
            utils.log( '    Making test output files...' )
            utils.libxslt( 
                  utils.log
                , input_file
                , xsl_path( 'links_page.xsl' )
                , links
                , {
                      'source':                 tag
                    , 'run_date':               run_date 
                    , 'comment_file':           comment_file
                    , 'explicit_markup_file':   failures_markup_file
                    }
                )
        stamp( stamp_file, input_file )

         
    return links


def make_result_pages(
          extended_test_results
        , expected_results_file
        , failures_markup_file
        , tag
        , run_date
        , comment_file
        , output_dir
        , reports
        ):

    utils.log( 'Producing the reports...' )
    __log__ = 1
    
    if comment_file != '':
        comment_file = os.path.abspath( comment_file )
        
    links = os.path.join( output_dir, 'links.html' )
    
    utils.makedirs( os.path.join( output_dir, 'output' ) )
    for mode in ( 'developer', 'user' ):
        utils.makedirs( os.path.join( output_dir, mode , 'output' ) )
        
    issues = os.path.join( output_dir, 'developer', 'issues.html'  )
    if 'i' in reports:
        utils.log( '    Making issues list...' )
        utils.libxslt( 
              utils.log
            , extended_test_results
            , xsl_path( 'issues_page.xsl' )
            , issues
            , {
                  'source':                 tag
                , 'run_date':               run_date
                , 'comment_file':           comment_file
                , 'explicit_markup_file':   failures_markup_file
                }
            )

    for mode in ( 'developer', 'user' ):
        if mode[0] + 'd' in reports:
            utils.log( '    Making detailed %s  report...' % mode )
            utils.libxslt( 
                  utils.log
                , extended_test_results
                , xsl_path( 'result_page.xsl' )
                , os.path.join( output_dir, mode, 'index.html' )
                , { 
                      'links_file':             'links.html'
                    , 'mode':                   mode
                    , 'source':                 tag
                    , 'run_date':               run_date 
                    , 'comment_file':           comment_file
                    , 'expected_results_file':  expected_results_file
                    , 'explicit_markup_file' :  failures_markup_file
                    }
                )
    
    for mode in ( 'developer', 'user' ):
        if mode[0] + 's' in reports:
            utils.log( '    Making summary %s  report...' % mode )
            utils.libxslt(
                  utils.log
                , extended_test_results
                , xsl_path( 'summary_page.xsl' )
                , os.path.join( output_dir, mode, 'summary.html' )
                , { 
                      'mode' :                  mode 
                    , 'source':                 tag
                    , 'run_date':               run_date 
                    , 'comment_file':           comment_file
                    , 'explicit_markup_file' :  failures_markup_file
                    }
                )

    if "ddr" in reports:
        mode = 'developer'
        utils.log( '    Making detailed %s release report...' % mode )
        utils.libxslt( 
                  utils.log
                , extended_test_results
                , xsl_path( 'result_page.xsl' )
                , os.path.join( output_dir, "developer", 'index_release.html' )
                , { 
                      'links_file':             'links.html'
                    , 'mode':                   mode
                    , 'source':                 tag
                    , 'run_date':               run_date 
                    , 'comment_file':           comment_file
                    , 'expected_results_file':  expected_results_file
                    , 'explicit_markup_file' :  failures_markup_file
                    , 'release':                "yes"
                    }
                )

    if "dsr" in reports:
        mode = 'developer'
        utils.log( '    Making summary %s release report...' % mode )
        utils.libxslt(
                  utils.log
                , extended_test_results
                , xsl_path( 'summary_page.xsl' )
                , os.path.join( output_dir, "developer", 'summary_release.html' )
                , { 
                      'mode' :                  mode
                    , 'source':                 tag
                    , 'run_date':               run_date 
                    , 'comment_file':           comment_file
                    , 'explicit_markup_file' :  failures_markup_file
                    , 'release':                'yes'
                    }
                )
        
    if 'e' in reports:
        utils.log( '    Generating expected_results ...' )
        utils.libxslt(
              utils.log
            , extended_test_results
            , xsl_path( 'produce_expected_results.xsl' )
            , os.path.join( output_dir, 'expected_results.xml' )
            )

    if  'n' in reports:
        utils.log( '    Making runner comment files...' )
        utils.libxslt(
              utils.log
            , extended_test_results
            , xsl_path( 'runners.xsl' )
            , os.path.join( output_dir, 'runners.html' )
            )

    shutil.copyfile(
          xsl_path( 'html/master.css' )
        , os.path.join( output_dir, 'master.css' )
        )


def build_xsl_reports( 
          locate_root_dir
        , tag
        , expected_results_file
        , failures_markup_file
        , comment_file
        , results_dir
        , result_file_prefix
        , dont_collect_logs = 0
        , reports = report_types
        , user = None
        , upload = False
        ):

    ( run_date ) = time.strftime('%a, %d %b %Y %H:%M:%S +0000', time.gmtime() )
        
    bin_boost_dir = os.path.join( locate_root_dir, 'bin', 'boost' )
    
    output_dir = os.path.join( results_dir, result_file_prefix )
    utils.makedirs( output_dir )
    
    if expected_results_file != '':
        expected_results_file = os.path.abspath( expected_results_file )
    else:
        expected_results_file = os.path.abspath( map_path( 'empty_expected_results.xml' ) )


    extended_test_results = os.path.join( output_dir, 'extended_test_results.xml' )
        
    execute_tasks(
          tag
        , user
        , run_date
        , comment_file
        , results_dir
        , output_dir
        , reports
        , extended_test_results
        , dont_collect_logs
        , expected_results_file
        , failures_markup_file
        )

    if upload:
        upload_dir = 'regression-logs/'
        utils.log( 'Uploading  results into "%s" [connecting as %s]...' % ( upload_dir, user ) )
        
        archive_name = '%s.tar.gz' % result_file_prefix
        utils.tar( 
              os.path.join( results_dir, result_file_prefix )
            , archive_name
            )
        
        utils.sourceforge.upload( os.path.join( results_dir, archive_name ), upload_dir, user )
        utils.sourceforge.untar( os.path.join( upload_dir, archive_name ), user, background = True )


def accept_args( args ):
    args_spec = [ 
          'locate-root='
        , 'tag='
        , 'expected-results='
        , 'failures-markup='
        , 'comment='
        , 'results-dir='
        , 'results-prefix='
        , 'dont-collect-logs'
        , 'reports='
        , 'user='
        , 'upload'
        , 'help'
        ]
        
    options = { 
          '--comment': ''
        , '--expected-results': ''
        , '--failures-markup': ''
        , '--reports': string.join( report_types, ',' )
        , '--tag': None
        , '--user': None
        , 'upload': False
        }
    
    utils.accept_args( args_spec, args, options, usage )
    if not options.has_key( '--results-dir' ):
         options[ '--results-dir' ] = options[ '--locate-root' ]

    if not options.has_key( '--results-prefix' ):
        options[ '--results-prefix' ] = 'all'
    
    return ( 
          options[ '--locate-root' ]
        , options[ '--tag' ]
        , options[ '--expected-results' ]
        , options[ '--failures-markup' ]
        , options[ '--comment' ]
        , options[ '--results-dir' ]
        , options[ '--results-prefix' ]
        , options.has_key( '--dont-collect-logs' )
        , options[ '--reports' ].split( ',' )
        , options[ '--user' ]
        , options.has_key( '--upload' )
        )


def usage():
    print 'Usage: %s [options]' % os.path.basename( sys.argv[0] )
    print    '''
\t--locate-root         the same as --locate-root in compiler_status
\t--tag                 the tag for the results (i.e. 'CVS-HEAD')
\t--expected-results    the file with the results to be compared with
\t                      the current run
\t--failures-markup     the file with the failures markup
\t--comment             an html comment file (will be inserted in the reports)
\t--results-dir         the directory containing -links.html, -fail.html
\t                      files produced by compiler_status (by default the
\t                      same as specified in --locate-root)
\t--results-prefix      the prefix of -links.html, -fail.html
\t                      files produced by compiler_status
\t--user                SourceForge user name for a shell account
\t--upload              upload reports to SourceForge 

The following options are useful in debugging:

\t--dont-collect-logs dont collect the test logs
\t--reports           produce only the specified reports
\t                        us - user summary
\t                        ds - developer summary
\t                        ud - user detailed
\t                        dd - developer detailed
\t                        l  - links
\t                        p  - patches
\t                        x  - extended results file
\t                        i  - issues
\t                        n  - runner comment files
'''

def main():
    build_xsl_reports( *accept_args( sys.argv[ 1 : ] ) )

if __name__ == '__main__':
    main()
