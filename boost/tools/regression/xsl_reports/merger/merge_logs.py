
# Copyright (c) MetaCommunications, Inc. 2003-2004
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import xml.sax.saxutils
import xml.dom.minidom
import ftplib
import glob
import os.path
import sys


def download_from_ftp( destination_dir, tag ):
    ftp_site = 'fx.meta-comm.com'
    site_path = '/boost-regression/%s' % tag
    utils.log( 'Downloading test runs from  ftp://%s%s' % ( ftp_site, site_path ) )

    ftp = ftplib.FTP( ftp_site )
    ftp.login()
    ftp.cwd( site_path )
    
    files = ftp.nlst()
    for f in files:
        utils.log( '  Downloading %s into "%s" directory...' % ( f, destination_dir ) )
        result = open( os.path.join( destination_dir, f ), 'wb' )
        ftp.retrbinary( 'RETR %s' % f, result.write )
        result.close()

    ftp.quit()


def download_test_runs( incoming_dir, tag, user ):
    utils.log( 'Downloading test runs for tag "%s"...' % tag )

    destination_dir = os.path.join( incoming_dir, tag )
    utils.makedirs( destination_dir )
    
    if user is not None:
        utils.log( 'Downloading test runs from SourceForge [connecting as %s]...' % user )
        utils.sourceforge.download( 
              'regression-logs/incoming/%s/' % tag
            , destination_dir
            , user
            )
    
    download_from_ftp( destination_dir, tag )


def unzip_and_remove( zip_path, dir, unzip_func ):
    try:
        utils.log( '  Unzipping "%s" ...' % zip_path  )
        unzip_func( zip_path, dir )
        utils.log( '  Removing "%s" ...' % zip_path )
        os.unlink( zip_path )
    except Exception, msg:
        utils.log( '  Skipping "%s" due to errors (%s)' % ( zip_path, msg ) )


def unzip_test_runs( dir ):
    files_mask = os.path.join( dir, '*.zip' )

    files = glob.glob( files_mask )
    for f in files:
        unzip_and_remove( f, dir, utils.unzip )
        
    files = glob.glob( files_mask )
    if len( files ):
        utils.log( 'Warning: Some files could not be unzipped using the built-in \'zipfile\' module.' )
        utils.log( '         Trying to decompress them using a platform-specific tool...' )
        try: import unzip_cmd
        except ImportError:
            utils.log( '  Could not find \'unzip_cmd\' module in the script directory.' )
        else:
            for f in files:
                unzip_and_remove( f, dir, unzip_cmd.main )
        
        files = glob.glob( files_mask )
        if len( files ):
            utils.log( 'Warning: The following files have not been decompressed:' )
            for f in files:
                utils.log( '\t%s' % f )
                zip_path = '%s.xml' % os.path.splitext( f )[0]
                if os.path.exists( zip_path ):
                    os.unlink( zip_path )


class xmlgen( xml.sax.saxutils.XMLGenerator ):
    document_started = 0
        
    def startDocument(self):
        if not self.document_started:
            xml.sax.saxutils.XMLGenerator.startDocument( self )
            self.document_started = 1


def merge_test_runs( incoming_dir, tag, writer, dont_collect_logs ):
    test_runs_dir = os.path.join( incoming_dir, tag )
    
    if not dont_collect_logs:
        utils.log( 'Removing stale XMLs in "%s"...' % test_runs_dir )
        files = glob.glob( os.path.join( test_runs_dir, '*.xml' ) )
        for f in files:  
            utils.log( '  Removing "%s" ...' % f )
            os.unlink( f )

        utils.log( 'Unzipping new test runs...' )
        unzip_test_runs( test_runs_dir )
    
    all_runs_xml = xmlgen( writer )
    all_runs_xml.startDocument()
    all_runs_xml.startElement( 'all-test-runs', {} )

    utils.log( 'Processing test runs...' )
    files = glob.glob( os.path.join( test_runs_dir, '*.xml' ) )
    for test_run in files:
        try:
            utils.log( '  Writing "%s" into the resulting XML...' % test_run )
            xml.sax.parse( test_run, all_runs_xml  )
        except Exception, msg:
            utils.log( '  Skipping "%s" due to errors (%s)' % ( test_run, msg ) )

    all_runs_xml.endElement( 'all-test-runs' )
    all_runs_xml.endDocument()
    writer.close()


def merge_logs(
          tag
        , user
        , results_dir
        , results_xml
        , dont_collect_logs
        ):
    
    results_xml_path = os.path.join( results_dir, results_xml )
    utils.log( 'Merging test runs into "%s"...' % results_xml_path )
    
    incoming_dir = os.path.join( results_dir, 'incoming/' )

    utils.log( '  dont_collect_logs: %s' % dont_collect_logs )
    if not dont_collect_logs:
        download_test_runs( incoming_dir, tag, user )
    
    writer = open( results_xml_path, 'w' )
    merge_test_runs( incoming_dir, tag, writer, dont_collect_logs )

    utils.log( 'Done writing "%s"' % results_xml_path )


def accept_args( args ):
    args_spec = [ 
          'tag='
        , 'user='
        , 'results-dir='
        , 'results-xml='
        , 'dont-collect-logs'
        , 'help'
        ]

    options = { 
          '--results-xml' : 'all-runs.xml'
        , '--user' :        None
        , '--tag' :         'CVS-HEAD'
        }
    utils.accept_args( args_spec, args, options, usage )

    return (
          options[ '--tag' ]
        , options[ '--user' ]
        , options[ '--results-dir' ]
        , options[ '--results-xml' ]
        , options.has_key( '--dont-collect-logs' )
        )


def usage():
    print 'Usage: %s [options]' % os.path.basename( sys.argv[0] )
    print    '''
\t--results-dir         directory for the resulting XML/collected logs
\t--results-xml         name of the resulting XML document (default 'all-runs.xml')
\t--tag                 the tag for the results ('CVS-HEAD' by default)
\t--user                SourceForge user name for a shell account (optional,
\t                      if not provided, logs are collected from FTP only)
\t--dont-collect-logs   don't collect logs from SourceForge/FTP
'''
    
def main():
    merge_logs( *accept_args( sys.argv[ 1 : ] ) )
    

if __name__ != '__main__':  import utils
else:
    # in absense of relative import...
    xsl_path = os.path.abspath( os.path.dirname( sys.argv[ 0 ] ) )
    while os.path.basename( xsl_path ) != 'xsl_reports': xsl_path = os.path.dirname( xsl_path )
    sys.path.append( xsl_path )

    import utils
    main()
