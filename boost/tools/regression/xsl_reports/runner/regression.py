
# Copyright (c) MetaCommunications, Inc. 2003-2004
#
# Distributed under the Boost Software License, Version 1.0. 
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)

import httplib
import tarfile
import socket
import time
import getopt
import glob
import shutil
import os.path
import os
import traceback
import string
import sys

regression_root = os.path.abspath( os.path.dirname( sys.argv[0] ) )
regression_results = os.path.join( regression_root, 'results' )
regression_log = os.path.join( regression_results, 'bjam.log' )

boost_root = os.path.join( regression_root, 'boost' )
xsl_reports_dir = os.path.join( boost_root, 'tools', 'regression', 'xsl_reports' )
comment_path = os.path.join( regression_root, 'comment.html' )
timestamp_path = os.path.join( boost_root, 'timestamp' )

cvs_command_line = 'cvs -d:ext:%(user)s@cvs.sourceforge.net:/cvsroot/boost -z9 %(command)s'

if sys.platform == 'win32': 
    bjam_name = 'bjam.exe'
    bjam_build_compiler = 'vc7'
    bjam_make_cmd = 'build.bat %s' % bjam_build_compiler
    bjam_location = 'bin.ntx86'
    process_jam_log_name = 'process_jam_log.exe'
    process_jam_log_toolset = 'vc7.1'
else:
    bjam_name = 'bjam'
    bjam_build_compiler = 'gcc'
    bjam_make_cmd = './build.sh %s' % bjam_build_compiler
    bjam_location = ''
    process_jam_log_name = "process_jam_log"
    process_jam_log_toolset = 'gcc'

bjam_path = os.path.join( regression_root, bjam_name )
process_jam_log_path = os.path.join( regression_root, process_jam_log_name )

def stdlog( message ):
    sys.stderr.write( '# %s\n' % message )
    sys.stderr.flush()

log = stdlog
utils = None



def tool_path( name ):
    return os.path.join( regression_results, name )


def rmtree( path ):
    if os.path.exists( path ):
        if sys.platform == 'win32':
            os.system( 'del /f /s /q "%s" >nul 2>&1' % path )
            shutil.rmtree( path )
        else:
            os.system( 'rm -f -r "%s"' % path )


def retry( f, args, max_attempts=2, sleep_secs=10 ):
    for attempts in range( max_attempts, -1, -1 ):
        try:
            return f( *args )
        except Exception, msg:
            log( '%s failed with message "%s"' % ( f.__name__, msg ) )
            if attempts == 0: 
                log( 'Giving up.' )
                raise

            log( 'Retrying (%d more attempts).' % attempts )
            time.sleep( sleep_secs )


def cleanup( args ):
    log( 'Cleaning up "%s" directory ...' % boost_root )
    rmtree( boost_root )
    
    log( 'Cleaning up "%s" directory ...' % regression_results )
    rmtree( regression_results )


def http_get( site, source, destination ):
    h = httplib.HTTPConnection( site )
    h.request( 'GET', source )
    
    response = h.getresponse()
    f = open( destination, 'wb' )
    while True:
        data = response.read( 16*1024 )
        if len( data ) == 0: break
        f.write( data )

    f.close()


def download_boost_tarball( destination, tag ):
    site = 'boost-consulting.com'
    tarball_name = 'boost.tar.bz2'
    tarball_path = os.path.join( destination, tarball_name )

    log( "Downloading '%s' for tag %s from %s "  % ( tarball_path, tag, site ) )
    if os.path.exists( tarball_path ):
        os.unlink( tarball_path )

    http_get(
          site
        , '/%s' % tarball_name # ignore tag for now
        , tarball_path
        )
        
    return tarball_path


def unpack_tarball( tarball_path, destination ):
    log( 'Looking for old unpacked archives...' )
    old_boost_dirs =  glob.glob( os.path.join( destination, 'boost-*' ) )

    for old_boost_dir in old_boost_dirs:
        log( 'Deleting old directory %s.' % old_boost_dir ) 
        rmtree( old_boost_dir )

    log( 'Unpacking boost tarball ("%s")...' % tarball_path )
    tar = tarfile.open( tarball_path, 'r|bz2' )
    for tarinfo in tar:
        tar.extract(tarinfo)
    tar.close()

    boost_dir = glob.glob( os.path.join( destination, 'boost-*' ) )[0]
    log( '    Unpacked into directory "%s"' % boost_dir )
    
    if os.path.exists( boost_root ):
        log( 'Deleting "%s" directory...' % boost_root )
        rmtree( boost_root )

    log( 'Renaming "%s" into "%s"' % ( boost_dir, boost_root ) )
    os.rename( boost_dir, boost_root )


def cvs_command( user, command ):
    cmd = cvs_command_line % { 'user': user, 'command': command }
    log( 'Executing CVS command "%s"' % cmd )
    rc = os.system( cmd )
    if rc != 0:
        raise Exception( 'Cvs command "%s" failed with code %d' % ( cmd, rc ) )


def cvs_checkout( user, tag, args ):
    if tag != 'CVS-HEAD':
        command = 'checkout -r %s boost' % tag
    else:
        command = 'checkout boost'
    
    os.chdir( regression_root )
    retry( 
         cvs_command
       , ( user, command )
       , max_attempts=5
       )


def get_source( user, tag, args ):
    log( "Getting sources ..." )

    if user is not None:
        cvs_checkout( user, tag, args )
    else:
        tarball_path = download_boost_tarball( regression_root, tag )
        unpack_tarball( tarball_path, regression_root )

    open( timestamp_path, 'w' ).close()


def update_source( user, tag, args ):
    if user is not None:
        log( 'Updating sources...' )
        cvs_update( user, tag, args )
    else:
        get_source( user, tag, args )


def build_bjam_if_needed():    
    global bjam_path
    if os.path.exists( bjam_path ):
        log( 'Found preinstalled "%s"; will use it.' % bjam_path )
        return
    
    log( 'Preinstalled "%s" is not found; building one...' % bjam_path )

    log( 'Locating bjam source directory...' )
    bjam_source_dir = os.path.join( boost_root, 'tools', 'build', 'jam_src' )
    
    if os.path.exists( bjam_source_dir ):
        log( 'Found bjam source directory "%s"' % bjam_source_dir )
        log( 'Building bjam using \"%s\"...' % bjam_build_compiler )
            
        log( "Building bjam (%s)" % bjam_make_cmd )
        utils.system( [ 
              'cd %s' % bjam_source_dir
            , bjam_make_cmd 
            ] )
    else:
        raise 'Could not find bjam source directory \"%s\"' % bjam_source_dir

    bjam_path = os.path.join( bjam_source_dir, bjam_location, bjam_name )
    if not os.path.exists( bjam_path ):
        raise 'Failed to find bjam (\"%s\") after build.' % bjam_path

    log( 'Bjam succesfully built in "%s" directory' % bjam_path )


def build_process_jam_log_if_needed():
    global process_jam_log_path
    if os.path.exists( process_jam_log_path ):
        log( 'Found preinstalled "%s"; will use it.' % process_jam_log_path )
        return
    
    log( 'Preinstalled "%s" is not found; building one.' % process_jam_log_path )
    
    process_jam_log_source_dir = os.path.join( boost_root, 'tools', 'regression', 'build' )

    log( 'Locating proces_jam_log source directory...' )
    if os.path.exists( process_jam_log_source_dir ):
        log( 'Found proces_jam_log source directory "%s"' % process_jam_log_source_dir )

        log( 'Building process_jam_log using toolset "%s"' % process_jam_log_toolset )
        utils.system( [ 
              'cd %s' % process_jam_log_source_dir
            , '%s -sTOOLS=%s' % ( bjam_path, process_jam_log_toolset )
            ] )

    else:
        raise 'Could not find process_jam_log source directory "%s"' % process_jam_log_source_dir

    process_jam_log_path = os.path.join( 
          boost_root, 'bin', 'boost', 'tools', 'regression', 'build'
        , process_jam_log_name, process_jam_log_toolset, 'release', process_jam_log_name
        )
    
    if not os.path.exists( process_jam_log_path ):
        raise 'Failed to find process_jam_log ("%s") after build.' % process_jam_log_path
    
    log( 'Process_jam_log succesfully built in "%s" directory' % process_jam_log_path )



def setup( comment_file, args ):
    sys.path.append( xsl_reports_dir )
    import utils as utils_module
    global utils    
    utils = utils_module
    
    if comment_file is None:
        log( 'Comment file "%s" not found; creating default comment.' % comment_path )
        f = open( comment_path, 'w' )
        f.write( '<p>Tests are run on %s platform.</p>' % string.capitalize( sys.platform ) )
        f.close()
    
    if not 'no-bjam' in args:
        build_bjam_if_needed()
    
    if not 'no-process_jam_log' in args:
        build_process_jam_log_if_needed()


def start_build_monitor():
    if sys.platform == 'win32':
        build_monitor = tool_path( 'build_monitor.exe' )
        if os.path.exists( build_monitor ):
            utils.system( [ 'start "" %s bjam.exe %d' % ( build_monitor, 3*60 ) ] )


def stop_build_monitor():
    if sys.platform == 'win32':
        build_monitor = tool_path( 'build_monitor.exe' )
        if os.path.exists( build_monitor ):
            utils.system( [ '%s build_monitor' %  tool_path( 'pskill.exe' ) ] )


def process_bjam_log():
    log( 'Getting test case results out of "%s"...' % regression_log )
    utils.checked_system( [ 
        "%s %s <%s" % (  
              process_jam_log_path
            , regression_results
            , regression_log
            )
        ] )
    

def test( 
          toolsets
        , args
        ):
    if args == []:
        args = [ "test", "process" ]

    try:
        start_build_monitor()
        cd = os.getcwd()
        os.chdir( os.path.join( boost_root, 'status' ) )

        log( 'Making "%s" directory...' % regression_results )
        utils.makedirs( regression_results )

        results_libs = os.path.join( regression_results, 'libs' )
        results_status = os.path.join( regression_results, 'status' )
        
        if "clean" in args:
            rmtree( results_libs )
            rmtree( results_status )

        if "test" in args:
            test_cmd = []
            if not toolsets is None:
                test_cmd.append( 'set TOOLS=%s' % string.join( toolsets, ' ' ) )
            test_cmd.append( 'set BOOST_ROOT=%s' % boost_root )
            test_cmd.append( '"%s" -d2 --dump-tests "-sALL_LOCATE_TARGET=%s" >>%s 2>&1'
                                      % (     bjam_path
                                            , regression_results
                                            , regression_log
                                            )
                                      )

            utils.checked_system( test_cmd, [ 1 ] )

        if "process" in args:
            process_bjam_log()

        os.chdir( cd )
    finally:
        stop_build_monitor()


def upload( 
          tag
        , runner_id
        , platform
        , user
        , comment_file
        , args
        ):
    import runner
    
    if comment_file is not None:
        global comment_path
        comment_path = os.path.join( regression_root, comment_file )
    
    runner.collect_and_upload_logs( 
          regression_results
        , runner_id
        , tag
        , platform
        , comment_path
        , time.strftime( 
              "%a, %d %b %Y %H:%M:%S +0000"
            , time.gmtime( os.stat( timestamp_path ).st_mtime )
            )
        , user
        )


def regression( 
          tag
        , runner
        , platform
        , user
        , comment_file
        , toolsets
        , incremental
        , mail = None
        , args = []
        ):

    try:
        mail_subject = "Boost regression for %s on %s \n" % ( tag, string.split(socket.gethostname(), '.')[0] )
        if incremental:
            update_source( user, tag, [] )
            setup( comment_file, [] )
        else:
            cleanup( args )
            get_source( user, tag, [] )
            setup( comment_file, [] )

        test( toolsets, [] )
        upload( tag, runner, platform, user, comment_file, [] )

        if mail:
            log( 'Sending report to "%s"' % mail )
            utils.send_mail( mail, mail_subject + ' completed successfully.' )
    except:
        if mail:
            log( 'Sending report to "%s"' % mail )
            msg = regression_log + [ "" ] + apply( traceback.format_exception, sys.exc_info() ) 
            utils.send_mail( mail, mail_subject + ' failed.', '\n'.join( msg ) )
        raise


def accept_args( args ):
    args_spec = [
          'tag='
        , 'runner='
        , 'platform='
        , 'user='
        , 'comment='
        , 'toolsets='
        , 'mail='
        , 'incremental'
        , 'help'
        ]
    
    options = {
          '--tag' :         'CVS-HEAD'
        , '--platform' :    sys.platform
        , '--user' :        None
        , '--comment' :     None
        , '--toolsets' :    None
        , '--mail' :        None
        }
    
    defaults_num = len( options )

    ( option_pairs, other_args ) = getopt.getopt( args, '', args_spec )
    map( lambda x: options.__setitem__( x[0], x[1] ), option_pairs )

    if ( options.has_key( '--help' ) or len( options.keys() ) == defaults_num ):
        usage()
        sys.exit( 1 )

    return ( 
          options[ '--tag' ]
        , options[ '--runner' ]
        , options[ '--platform']
        , options[ '--user' ]
        , options[ '--comment' ]
        , options[ '--toolsets' ]
        , options.has_key( '--incremental' )
        , options[ '--mail' ]
        , other_args
        )


commands = {
      'cleanup'         : cleanup
    , 'get-source'      : get_source
    , 'update-source'   : update_source
    , 'setup'           : setup
    , 'test'            : test
    , 'upload'          : upload
    , 'regression'      : regression
    }

def usage():
    print 'Usage: %s [command] options' % os.path.basename( sys.argv[0] )
    print    '''
Commands:
\t%s

Options:

\t--runner              runner ID (e.g. 'Metacomm')
\t--tag                 the tag for the results ('CVS-HEAD' by default)
\t--comment             an html comment file (will be inserted in the reports, 
\t                      'comment.html' by default)
\t--incremental         do incremental run (do not remove previous binaries)
\t--user                SourceForge user name for a shell/CVS account (optional)
\t--toolsets            comma-separated list of toolsets to test with (optional)
\t--mail                email address to send run notification to (optional)
''' % '\n\t'.join( commands.keys() )

    print 'Example:\n\t%s --runner=Metacomm' % os.path.basename( sys.argv[0] )


if len(sys.argv) > 1 and sys.argv[1] in commands:
    command = sys.argv[1]
    args = sys.argv[ 2: ]
else:
    command = 'regression'
    args = sys.argv[ 1: ]
    
commands[ command ]( *accept_args( args ) )
