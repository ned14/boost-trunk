'''
>>> from enum_ext import *

>>> identity(color.red)
enum_ext.color.red

>>> identity(color.green)
enum_ext.color.green

>>> identity(color.blue)
enum_ext.color.blue

>>> identity(color(1))
enum_ext.color.red

>>> identity(color(2))
enum_ext.color.green

>>> identity(color(3))
enum_ext.color(3)

>>> identity(color(4))
enum_ext.color.blue

>>> try: identity(1)
... except TypeError: pass
... else: print 'expected a TypeError'

'''

def run(args = None):
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print "running..."
    import sys
    sys.exit(run()[0])
