r'''>>> import getting_started1
    >>> print getting_started1.greet()
    hello, world
    >>> number = 11
    >>> print number, '*', number, '=', getting_started1.square(number)
    11 * 11 = 121
'''

def run(args = None):
    if args is not None:
        import sys
        sys.argv = args
    import doctest, test_getting_started1
    doctest.testmod(test_getting_started1)

if __name__ == '__main__':
    run()
