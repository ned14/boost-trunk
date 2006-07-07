'''
>>> from python_parameter import X
>>> x = X(y = 'baz')
>>> x.value
'foobaz'
>>> x.f(1,2)
3
>>> x.f(1,2,3)
6
>>> x.f(1,2, z = 3)
6
>>> x.f(z = 3, y = 2, x = 1)
6
>>> x.g()
'foobar'
>>> x.g(y = "baz")
'foobaz'
>>> x.g(x = "baz")
'bazbar'
>>> x.g(y = "foo", x = "bar")
'barfoo'
>>> y = x.h(x = "bar", y = "foo")
>>> assert x == y
>>> y = x(0)
>>> assert x == y
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, python 
    return doctest.testmod(python)

if __name__ == '__main__':
    import sys
    sys.exit(run()[0])
