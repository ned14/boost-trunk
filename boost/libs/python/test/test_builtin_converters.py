"""
>>> from builtin_converters import *
>>> rewrap_value_bool(None)
0
>>> rewrap_value_bool(0)
0
>>> rewrap_value_bool(33)
1
>>> rewrap_value_char('x')
'x'

  Note that there's currently silent truncation of strings passed to
  char arguments.

>>> rewrap_value_char('xy')
'x'
>>> rewrap_value_signed_char(42)
42
>>> rewrap_value_unsigned_char(42)
42
>>> rewrap_value_int(42)
42
>>> rewrap_value_unsigned_int(42)
42
>>> rewrap_value_short(42)
42
>>> rewrap_value_unsigned_short(42)
42
>>> rewrap_value_long(42)
42
>>> rewrap_value_unsigned_long(42)
42

>>> abs(rewrap_value_float(4.2) - 4.2) < .000001
1
>>> rewrap_value_double(4.2) - 4.2
0.0
>>> rewrap_value_long_double(4.2) - 4.2
0.0

>>> abs(rewrap_value_complex_float(4+.2j) - (4+.2j)) < .000001
1
>>> abs(rewrap_value_complex_double(4+.2j) - (4+.2j)) < .000001
1
>>> abs(rewrap_value_complex_long_double(4+.2j) - (4+.2j)) < .000001
1

>>> rewrap_value_cstring('hello, world')
'hello, world'
>>> rewrap_value_string('yo, wassup?')
'yo, wassup?'

  Note that we can currently get a mutable pointer into an immutable
  Python string:
  
>>> rewrap_value_mutable_cstring('hello, world')
'hello, world'

>>> rewrap_const_reference_bool(None)
0
>>> rewrap_const_reference_bool(0)
0
>>> rewrap_const_reference_bool('yes')
1
>>> rewrap_const_reference_char('x')
'x'

  Note that there's currently silent truncation of strings passed to
  char arguments.

>>> rewrap_const_reference_char('xy')
'x'
>>> rewrap_const_reference_signed_char(42)
42
>>> rewrap_const_reference_unsigned_char(42)
42
>>> rewrap_const_reference_int(42)
42
>>> rewrap_const_reference_unsigned_int(42)
42
>>> rewrap_const_reference_short(42)
42
>>> rewrap_const_reference_unsigned_short(42)
42
>>> rewrap_const_reference_long(42)
42
>>> rewrap_const_reference_unsigned_long(42)
42

>>> abs(rewrap_const_reference_float(4.2) - 4.2) < .000001
1
>>> rewrap_const_reference_double(4.2) - 4.2
0.0
>>> rewrap_const_reference_long_double(4.2) - 4.2
0.0

>>> abs(rewrap_const_reference_complex_float(4+.2j) - (4+.2j)) < .000001
1
>>> abs(rewrap_const_reference_complex_double(4+.2j) - (4+.2j)) < .000001
1
>>> abs(rewrap_const_reference_complex_long_double(4+.2j) - (4+.2j)) < .000001
1

>>> rewrap_const_reference_cstring('hello, world')
'hello, world'
>>> rewrap_const_reference_string('yo, wassup?')
'yo, wassup?'


Check that None <==> NULL

>>> rewrap_const_reference_cstring(None)

But when converted to a string rvalue, None becomes 'None':

>>> rewrap_const_reference_string(None)
'None'


Now check implicit conversions between floating/integer types

>>> rewrap_const_reference_float(42)
42.0

>>> rewrap_const_reference_int(42.0)
42

>>> rewrap_value_float(42)
42.0

>>> rewrap_value_int(42.0)
42

Check that classic classes also work

>>> class FortyTwo:
...     def __int__(self):
...         return 42
...     def __float__(self):
...         return 42.0
...     def __complex__(self):
...         return complex(4+.2j)
...     def __str__(self):
...         return '42'

>>> rewrap_const_reference_float(FortyTwo())
42.0
>>> rewrap_value_int(FortyTwo())
42
>>> rewrap_const_reference_string(FortyTwo())
'42'
>>> abs(rewrap_value_complex_double(FortyTwo()) - (4+.2j)) < .000001
1

"""
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
