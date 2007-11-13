
import os
import string
import sys

def system( commands ):
    if sys.platform == 'win32':
        f = open( 'tmp.cmd', 'w' )
        f.write( string.join( commands, '\n' ) )
        f.close()
        rc = os.system( 'tmp.cmd' )
        return rc
    else:
        rc = os.system( '&&'.join( commands ) )
        if os.WIFEXITED(rc):
            return os.WEXITSTATUS(rc)
        elif os.WIFSIGNALED(rc):
            return -os.WTERMSIG(rc)
        elif os.WIFSTOPPED(rc):
            return -os.WSTOPSIG(rc)
        return 0
    
def checked_system( commands, valid_return_codes = [ 0 ] ):
    rc = system( commands ) 
    if rc not in [ 0 ] + valid_return_codes:
        raise Exception( 'Command sequence "%s" failed with return code %d' % ( commands, rc ) )
    return rc
