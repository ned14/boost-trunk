'''
>>> from operators_ext import *
>>> x = X(42)
>>> x.value()
42
>>> y = x - X(5)
>>> y.value()
37
>>> y = x - 4
>>> y.value()
38
>>> y = 3 - x
>>> y.value()
-39
>>> (-y).value()
39

>>> abs(y).value()
39

>>> x < 10
0
>>> x < 43
1

>>> 10 < x
1
>>> 43 < x
0

>>> x < y
0
>>> y < x
1

 ------
>>> x > 10
1
>>> x > 43
0

>>> 10 > x
0
>>> 43 > x
1

>>> x > y
1
>>> y > x
0

>>> y = x - 5
>>> x -= y
>>> x.value()
5

>>> z = Z(10)
>>> int(z)
10
>>> float(z)
10.0
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
