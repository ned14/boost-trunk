r'''
//  (C) Copyright David Abrahams 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  The author gratefully acknowleges the support of Dragon Systems, Inc., in
//  producing this work.

//  Revision History:
//  04 Mar 01 Changed name of extension module so it would work with DebugPython,
//            fixed exception message checking to work with Python 2.0
//            (Dave Abrahams)

Load up the extension module

    >>> from boost_python_test import *

Automatic checking of the number and type of arguments. Foo's constructor takes
a single long parameter. 

    >>> try:
    ...     ext = Foo()
    ... except TypeError, err:
    ...     assert re.match(r'function .* exactly 1 argument;? \(?0 given\)?',
    ...                     str(err))
    ... else:
    ...     print 'no exception'

    >>> try: ext = Foo('foo')
    ... except TypeError, err:
    ...    assert_integer_expected(err)
    ... else:
    ...    print 'no exception'

    >>> ext = Foo(1)

Call a virtual function. This call takes a trip into C++ where
FooCallback::add_len() looks up the Python "add_len" attribute and finds the
wrapper for FooCallback::default_add_len(), which in turn calls Foo::add_len(). 

    >>> ext.add_len('hello')
    6
    >>> ext.set(3)
    >>> ext.add_len('hello')
    8

Call a pure virtual function which should have been overridden, but was not.

    >>> ext.call_pure()
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: pure

We can subclass Foo.

    >>> class Subclass(Foo):
    ...     def __init__(self, seq):
    ...         Foo.__init__(self, len(seq))
    ...         
    ...     def pure(self):
    ...         return 'not pure anymore!'
    ...     
    ...     def get(self):
    ...         return Foo.add_len(self, '')
    ...     
    ...     def add_len(self, s):
    ...         print 'called add_len()'
    ...         return self.get() + len(s)
    ... 
    >>> b = Subclass('yippee')
    >>> b.get()
    6
    >>> b.mumble()
    'mumble'
    >>> b.call_pure()
    'not pure anymore!'

None corresponds to a NULL pointer or smart pointer
    >>> f = foo_factory(1)
    >>> f.add_len('xxx')
    1000
    >>> foo_factory(0) is None
    1
    >>> foo_ptr_is_null(None)
    1
    >>> foo_ptr_is_null(f)
    0
    >>> foo_shared_ptr_is_null(None)
    1
    >>> foo_shared_ptr_is_null(f)
    0
    
If no __init__ function is defined, the one from the base class takes effect, just
like in a Python class.

    >>> class DemonstrateInitPassthru(Foo): pass
    ... 
    >>> q = DemonstrateInitPassthru(1)
    >>> q.add_len("x")
    2

If we don't initialize the base class, we'll get a RuntimeError when we try to
use its methods. The test illustrates the kind of error to expect.

    >>> class BadSubclass(Foo):
    ...     def __init__(self): pass
    ...
    >>> barf = BadSubclass()
    >>> barf.set(4)
    Traceback (innermost last):
       ...
    RuntimeError: __init__ function for extension class 'Foo' was never called.

Here we are tesing that the simple definition procedure used in the C++ demo
file for classes without any virtual functions actually worked.

    >>> bar = Bar(3, 4)
    >>> bar.first()
    3
    >>> bar.second()
    4
    >>> baz = Baz()

We can actually return the wrapped classes by value

    >>> baz.pass_bar(bar).first()
    3
    >>> bar.pass_baz(baz) is baz # A copy of the return value is made.
    0
    >>> type(bar.pass_baz(baz)) is type(baz)
    1

And, yes, we can multiply inherit from these classes.

    >>> class MISubclass(Subclass, Bar):
    ...     def __init__(self, s):
    ...         Subclass.__init__(self, s)
    ...         Bar.__init__(self, 0, len(s))
    ...
    >>> mi = MISubclass('xx')
    >>> mi.first()
    0
    >>> mi.second()
    2
    >>> mi.mumble()
    'mumble'

We can even mulitply inherit from built-in Python classes, even if they are
first in the list of bases

    >>> class RealPythonClass:
    ...     def real_python_method(self):
    ...         print 'RealPythonClass.real_python_method()'
    ...     def other_first(self, other):
    ...         return other.first()
    
    >>> class MISubclass2(RealPythonClass, Bar):
    ...    def new_method(self):
    ...        print 'MISubclass2.new_method()'
    ...    bound_function = RealPythonClass().other_first
    ...
    >>> mi2 = MISubclass2(7, 8)
    >>> mi2.first() # we can call inherited member functions from Bar
    7
    >>> mi2.real_python_method() # we can call inherited member functions from RealPythonClass
    RealPythonClass.real_python_method()
    
    >>> mi2.new_method() # we can call methods on the common derived class
    MISubclass2.new_method()

  We can call unbound methods from the base class accessed through the derived class
    >>> MISubclass2.real_python_method(mi2)
    RealPythonClass.real_python_method()

  We have not interfered with ordinary python bound methods
    >>> MISubclass2.bound_function(mi2)
    7
    >>> mi2.bound_function()
    7
    
Any object whose class is derived from Bar can be passed to a function expecting
a Bar parameter:

    >>> baz.pass_bar(mi).first()
    0

But objects not derived from Bar cannot:

    >>> baz.pass_bar(baz)
    Traceback (innermost last):
        ...
    TypeError: extension class 'Baz' is not convertible into 'Bar'.

The clone function on Baz returns a smart pointer; we wrap it into an
extension_instance and  make it look just like any other Baz obj.

    >>> baz_clone = baz.clone()
    >>> baz_clone.pass_bar(mi).first()
    0

Functions expecting an std::auto_ptr<Baz> parameter will not accept a raw Baz

    >>> try: baz.eat_baz(Baz())
    ... except RuntimeError, err:
    ...     assert re.match("Object of extension class 'Baz' does not wrap <.*>.",
    ...                     str(err))
    ... else:
    ...     print 'no exception'

We can pass std::auto_ptr<Baz> where it is expected

    >>> baz.eat_baz(baz_clone)

And if the auto_ptr has given up ownership?

    # MSVC6 ships with an outdated auto_ptr that doesn't get zeroed out when it
    # gives up ownership. If you are using MSVC6 without the new Dinkumware
    # library, SGI STL or the STLport, expect this test to crash unless you put
    # --broken-auto-ptr on the command line.
    >>> if not '--broken-auto-ptr' in sys.argv:
    ...     try: baz_clone.clone()
    ...     except RuntimeError, err:
    ...         assert re.match('Converting from python, pointer or smart pointer to <.*> is NULL.', str(err))
    ...     else:
    ...         print 'no exeption'
    
Polymorphism also works:
    
    >>> polymorphic_foo = baz.create_foo()
    >>> polymorphic_foo.call_pure()
    'this was never pure!'
    >>> baz.get_foo_value(polymorphic_foo)
    1000

Pickling tests:

    >>> world.__module__
    'boost_python_test'
    >>> world.__safe_for_unpickling__
    1
    >>> world.__reduce__()
    'world'
    >>> reduced = world('Hello').__reduce__()
    >>> reduced[0] == world
    1
    >>> reduced[1:]
    (('Hello',), (0,))
    >>> import StringIO
    >>> import cPickle
    >>> pickle = cPickle
    >>> for number in (24, 42):
    ...     wd = world('California')
    ...     wd.set_secret_number(number)
    ...     # Dump it out and read it back in.
    ...     f = StringIO.StringIO()
    ...     pickle.dump(wd, f)
    ...     f = StringIO.StringIO(f.getvalue())
    ...     wl = pickle.load(f)
    ...     #
    ...     print wd.greet(), wd.get_secret_number()
    ...     print wl.greet(), wl.get_secret_number()
    ...
    Hello from California! 24
    Hello from California! 24
    Hello from California! 42
    Hello from California! 0

Pickle safety measures:
    >>> r=Rational(3, 4)
    >>> r
    Rational(3, 4)
    >>> try: s=pickle.dumps(r)
    ... except RuntimeError, err: print err[0]
    ... 
    Incomplete pickle support (__dict_defines_state__ not set)
    >>> class myrational(Rational):
    ...   __dict_defines_state__ = 1 # this is a lie but good enough for testing.
    ...             
    >>> r=myrational(3, 4)
    >>> r
    Rational(3, 4)
    >>> s=pickle.dumps(r)

    >>> class myworld(world):
    ...   def __init__(self):
    ...     world.__init__(self, 'anywhere')
    ...     self.x = 1
    ... 
    >>> w = myworld()
    >>> w.greet()
    'Hello from anywhere!'
    >>> w.__dict__
    {'x': 1}
    >>> try: s=pickle.dumps(w)
    ... except RuntimeError, err: print err[0]
    ... 
    Incomplete pickle support (__getstate_manages_dict__ not set)

    >>> class myunsafeworld(myworld):
    ...   __getstate_manages_dict__ = 1 # this is a lie but good enough for testing.
    ... 
    >>> w = myunsafeworld()
    >>> w.greet()
    'Hello from anywhere!'
    >>> w.__dict__
    {'x': 1}
    >>> s=pickle.dumps(w)

Special member attributes. Tests courtesy of Barry Scott <barry@scottb.demon.co.uk>

    >>> class DerivedFromFoo(Foo):
    ...     def __init__(self):
    ...         Foo.__init__( self, 1 )
    ...     def fred(self):
    ...         'Docs for DerivedFromFoo.fred'
    ...         print 'Barry.fred'
    ...     def __del__(self):
    ...         print 'Deleting DerivedFromFoo'

    >>> class Base:
    ...     i_am_base = 'yes'
    ...     def fred(self):
    ...         'Docs for Base.fred'
    ...         pass


    >>> class DerivedFromBase(Base):
    ...     i_am_derived_from_base = 'yes'
    ...     def fred(self):
    ...         'Docs for DerivedFromBase.fred'
    ...         pass

    >>> df = DerivedFromFoo()
    >>> dir(df)
    []
    >>> dir(DerivedFromFoo)
    ['__del__', '__doc__', '__init__', '__module__', 'fred']
    >>> df.__dict__
    {}

    >>> df.fred.__doc__
    'Docs for DerivedFromFoo.fred'
    >>> db = DerivedFromBase()
    >>> dir(db)
    []
    >>> dir(DerivedFromBase)
    ['__doc__', '__module__', 'fred', 'i_am_derived_from_base']
    >>> db.__dict__
    {}
    >>> db.fred.__doc__
    'Docs for DerivedFromBase.fred'

Special member functions in action
    >>> del df
    Deleting DerivedFromFoo
    
    # force method table sharing
    >>> class DerivedFromStringMap(StringMap): pass
    ...
    
    >>> m = StringMap()

__getitem__(<unknown key>)
    >>> m[1]
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 1

__setitem__()
  
    >>> m[1] = 'hello'

__getitem__(<known key>)    
    >>> m[1]
    'hello'
    
__delitem__(<known key>)
    >>> del m[1]
    >>> m[1]            # prove that it's gone
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 1

__delitem__(<unknown key>)
    >>> del m[2]
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 2

__length__()
    >>> len(m)
    0
    >>> m[3] = 'farther'
    >>> len(m)
    1

Check for sequence/mapping confusion:
    >>> for x in m:
    ...     print x
    ...
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    KeyError: 0

Check for the ability to pass a non-const reference as a constructor parameter
    >>> x = Fubar(Foo(1))
    
Some simple overloading tests:
    >>> r = Range(3)
    >>> print str(r)
    (3, 3)
    >>> r.start
    3
    >>> r.finish
    3
    >>> r.__len__()
    0
    >>> r.__len__(4)
    >>> r.finish
    7
    >>> try: r = Range('yikes')
    ... except TypeError, e:
    ...     assert re.match(
    ... 'No overloaded functions match [(]Range, str[a-z]*[)]\. Candidates are:\n.*\n.*',
    ...  str(e))
    ... else: print 'no exception'
    
Sequence tests:
    >>> len(Range(3, 10))
    7
    
    >>> map(lambda x:x, Range(3, 10))
    [3, 4, 5, 6, 7, 8, 9]
    
    >>> map(lambda x:x, Range(3, 10)[-2:])
    [8, 9]
    
    >>> map(lambda x:x, Range(3, 10)[:-4])
    [3, 4, 5]
    
    >>> map(lambda x:x, Range(3, 10)[4:])
    [7, 8, 9]
      
    >>> map(lambda x:x, Range(3, 10)[4:100])
    [7, 8, 9]
      
    >>> map(lambda x:x, Range(3, 10)[20:])
    []
      
    >>> map(lambda x:x, Range(3, 10)[0:4])
    [3, 4, 5, 6]

Numeric tests:
    >>> x = Rational(2,3)
    >>> y = Rational(1,4)
    >>> print x + y
    11/12
    >>> print x - y
    5/12
    >>> print x * y
    1/6
    >>> print x / y
    8/3
    >>> print x + 1 # testing coercion
    5/3
    >>> print 1 + x # coercion the other way
    5/3
    
delete non-existent attribute:
    del m.foobar
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: delete non-existing obj attribute
    
Testing __getattr__ and __getattr__<name>:
  
    >>> n = IntPair(1, 2)
    >>> n.first
    1
    >>> n.second
    2
    >>> n.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: third

Testing __setattr__ and __setattr__<name>:
    >>> n.first = 33 # N.B  __setattr__first sets first to 
    >>> n.first      # the negative of its argument.
    -33
    >>> n.second = 66
    >>> n.second
    66
    
Testing __delattr__ and __delattr__<name>:
    >>> del n.first
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: first can't be deleted!
    >>> del n.second
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!
    >>> del n.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!
    
    # Now show that we can override it.
    
    >>> class IntTriple(IntPair):
    ...     def __getattr__(self, s):
    ...         if s in ['first', 'second']:
    ...             return IntPair.__getattr__(self, s)
    ...         elif s == 'third':
    ...             return 3
    ...         else:
    ...             raise AttributeError(s)
    ...     
    ...     # Also show that __setattr__ is supported
    ...     def __setattr__(self, name, value):
    ...         raise AttributeError('no writable attributes')
    ...
    >>> p = IntTriple(0, 1)
    >>> p.first
    0
    >>> p.second
    1
    >>> p.third
    3
    >>> p.bax
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: bax
    >>> p.third = 'yes'
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: no writable attributes
    >>> del p.third
    Traceback (innermost last):
      File "<stdin>", line 1, in ?
    AttributeError: Attributes can't be deleted!

demonstrate def_readonly, def_read_write:
    >>> sp = StringPair("hello", "world")
    >>> sp.first  # first is read-only
    'hello'
    >>> first_string(sp) # prove that we're not just looking in sp's __dict__
    'hello'
    >>> sp.first = 'hi' # we're not allowed to change it
    Traceback (innermost last):
      File "<string>", line 1, in ?
    AttributeError: 'first' attribute is read-only
    >>> first_string(sp) # prove that it hasn't changed
    'hello'
    
    >>> sp.second  # second is read/write
    'world'
    >>> second_string(sp)
    'world'
    >>> sp.second = 'universe' # set the second attribute
    >>> sp.second
    'universe'
    >>> second_string(sp)  # this proves we didn't just set it in sp's __dict__
    'universe'

some __str__ and __repr__ tests:
    >>> sp
    ('hello', 'universe')
    >>> repr(sp)
    "('hello', 'universe')"
    >>> str(sp)
    "('hello', 'universe')"

  Range has a __str__ function but not a __repr__ function
    >>> range = Range(5, 20)
    >>> str(range)
    '(5, 20)'
    >>> assert re.match('<Range object at [0-9a-fA-FxX]+>', repr(range))

__hash__ and __cmp__ tests:
    # Range has both __hash__ and __cmp__, thus is hashable
    >>> colors = { Range(3,4): 'blue', Range(7,9): 'red' }
    >>> colors[Range(3,4)]
    'blue'

    # StringPair has only __cmp__
    >>> { StringPair('yo', 'eddy'): 1 }
    Traceback (innermost last):
      File "<string>", line 1, in ?
    TypeError: unhashable type

    # But it can be sorted
    >>> stringpairs = [ StringPair('yo', 'eddy'), StringPair('yo', 'betty'), sp ]
    >>> stringpairs.sort()
    >>> stringpairs
    [('hello', 'universe'), ('yo', 'betty'), ('yo', 'eddy')]
    
make_pair is a global function in the module.

    >>> couple = make_pair(3,12)
    >>> couple.first
    3
    >>> couple.second
    12

Testing __call__:
    >>> couple2 = make_pair(3, 7)
    >>> comparator = CompareIntPair()
    >>> comparator(couple, couple)
    0
    >>> comparator(couple, couple2)
    0
    >>> comparator(couple2, couple)
    1

Testing overloaded free functions
    >>> overloaded()
    'Hello world!'
    >>> overloaded(1)
    1
    >>> overloaded('foo')
    'foo'
    >>> overloaded(1,2)
    3
    >>> overloaded(1,2,3)
    6
    >>> overloaded(1,2,3,4)
    10
    >>> overloaded(1,2,3,4,5)
    15
    >>> try: overloaded(1, 'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(int, str[a-z]*\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'
    
Testing overloaded constructors

    >>> over = OverloadTest()
    >>> over.getX()
    1000
    >>> over = OverloadTest(1)
    >>> over.getX()
    1
    >>> over = OverloadTest(1,1)
    >>> over.getX()
    2
    >>> over = OverloadTest(1,1,1)
    >>> over.getX()
    3
    >>> over = OverloadTest(1,1,1,1)
    >>> over.getX()
    4
    >>> over = OverloadTest(1,1,1,1,1)
    >>> over.getX()
    5
    >>> over = OverloadTest(over)
    >>> over.getX()
    5
    >>> try: over = OverloadTest(1, 'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(OverloadTest, int, str[a-z]*\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'
    
Testing overloaded methods

    >>> over.setX(3)
    >>> over.overloaded()
    3
    >>> over.overloaded(1)
    1
    >>> over.overloaded(1,1)
    2
    >>> over.overloaded(1,1,1)
    3
    >>> over.overloaded(1,1,1,1)
    4
    >>> over.overloaded(1,1,1,1,1)
    5
    >>> try: over.overloaded(1,'foo')
    ... except TypeError, err:
    ...     assert re.match("No overloaded functions match \(OverloadTest, int, str[a-z]*\)\. Candidates are:",
    ...                     str(err))
    ... else:
    ...     print 'no exception'

Testing base class conversions

    >>> testUpcast(over)
    Traceback (innermost last):
    TypeError: extension class 'OverloadTest' is not convertible into 'Base'.
    >>> der1 = Derived1(333)
    >>> der1.x()
    333
    >>> testUpcast(der1)
    333
    >>> der1 = derived1Factory(1000)
    >>> testDowncast1(der1)
    1000
    >>> testDowncast2(der1)
    Traceback (innermost last):
    TypeError: extension class 'Base' is not convertible into 'Derived2'.
    >>> der2 = Derived2(444)
    >>> der2.x()
    444
    >>> testUpcast(der2)
    444
    >>> der2 = derived2Factory(1111)
    >>> testDowncast2(der2)
    Traceback (innermost last):
    TypeError: extension class 'Base' is not convertible into 'Derived2'.
    
Testing interaction between callbacks, base declarations, and overloading
- testCallback() calls callback() (within C++)
- callback() is overloaded (in the wrapped class CallbackTest)
- callback() is redefined in RedefineCallback (overloading is simulated by type casing)
- testCallback() should use the redefined callback()

    >>> c = CallbackTest()
    >>> c.testCallback(1)
    2
    
    >>> try: c.testCallback('foo')
    ... except TypeError, err: assert_integer_expected(err)
    ... else: print 'no exception'

    >>> c.callback(1)
    2
    >>> c.callback('foo')
    'foo 1'
    
    >>> import types
    >>> class RedefineCallback(CallbackTest):
    ...     def callback(self, x): 
    ...             if type(x) is types.IntType:
    ...                     return x - 2
    ...             else:
    ...                     return CallbackTest.callback(self,x)
    ... 
    >>> r = RedefineCallback()
    >>> r.callback(1)
    -1
    >>> r.callback('foo')
    'foo 1'
    
    >>> try: r.testCallback('foo')
    ... except TypeError, err: assert_integer_expected(err)
    ... else: print 'no exception'
    
    >>> r.testCallback(1)
    -1
    >>> testCallback(r, 1)
    -1

Regression test for a reference-counting bug thanks to Mark Evans
(<mark.evans@clarisay.com>)
    >>> sizelist([])
    0.0
    >>> sizelist([1, 2, 4])
    3.0
    
And another for doubles
    >>> vector_double().push_back(3.0)

Tests for method lookup in the context of inheritance
Set up the tests

    >>> a1 = A1()
    >>> a2 = A2()
    >>> b1 = B1()
    >>> b2 = B2()
    >>> pa1_a1 = factoryA1asA1()
    >>> pb1_a1 = factoryB1asA1()
    >>> pb2_a1 = factoryB2asA1()
    >>> pc_a1 = factoryCasA1()
    >>> pa2_a2 = factoryA2asA2()
    >>> pb1_a2 = factoryB1asA2()
    >>> pb1_b1 = factoryB1asB1()
    >>> pc_b1 = factoryCasB1()
    >>> class DA1(A1):
    ...     def overrideA1(self):
    ...         return 'DA1.overrideA1'
    ...
    >>> da1 = DA1()
    >>> class DB1(B1):
    ...     def overrideA1(self):
    ...         return 'DB1.overrideA1'
    ...     def overrideB1(self):
    ...         return 'DB1.overrideB1'
    ...
    >>> db1 = DB1()
    >>> class DB2(B2): pass
    ...
    >>> db2 = DB2()

test overrideA1

    >>> a1.overrideA1()
    'A1::overrideA1'
    >>> b1.overrideA1()
    'B1::overrideA1'
    >>> b2.overrideA1()
    'B2::overrideA1'
    >>> da1.overrideA1()
    'DA1.overrideA1'
    >>> db1.overrideA1()
    'DB1.overrideA1'
    >>> pa1_a1.overrideA1()
    'A1::overrideA1'
    >>> pb1_a1.overrideA1()
    'B1::overrideA1'
    >>> pb2_a1.overrideA1()
    'B2::overrideA1'
    >>> pb1_b1.overrideA1()
    'B1::overrideA1'
    >>> pc_a1.overrideA1()
    'B1::overrideA1'
    >>> pc_b1.overrideA1()
    'B1::overrideA1'

test call_overrideA1

    >>> call_overrideA1(a1)
    'A1::overrideA1'
    >>> call_overrideA1(b1)
    'B1::overrideA1'
    >>> call_overrideA1(b2)
    'B2::overrideA1'
    >>> call_overrideA1(da1)
    'DA1.overrideA1'
    >>> call_overrideA1(db1)
    'DB1.overrideA1'
    >>> call_overrideA1(pa1_a1)
    'A1::overrideA1'
    >>> call_overrideA1(pb1_a1)
    'B1::overrideA1'
    >>> call_overrideA1(pb2_a1)
    'B2::overrideA1'
    >>> call_overrideA1(pb1_b1)
    'B1::overrideA1'
    >>> call_overrideA1(pc_a1)
    'B1::overrideA1'
    >>> call_overrideA1(pc_b1)
    'B1::overrideA1'

test inheritA1

    >>> a1.inheritA1()
    'A1::inheritA1'
    >>> b1.inheritA1()
    'A1::inheritA1'
    >>> b2.inheritA1()
    'A1::inheritA1'
    >>> da1.inheritA1()
    'A1::inheritA1'
    >>> db1.inheritA1()
    'A1::inheritA1'
    >>> pa1_a1.inheritA1()
    'A1::inheritA1'
    >>> pb1_a1.inheritA1()
    'A1::inheritA1'
    >>> pb2_a1.inheritA1()
    'A1::inheritA1'
    >>> pb1_b1.inheritA1()
    'A1::inheritA1'
    >>> pc_a1.inheritA1()
    'A1::inheritA1'
    >>> pc_b1.inheritA1()
    'A1::inheritA1'

test call_inheritA1

    >>> call_inheritA1(a1)
    'A1::inheritA1'
    >>> call_inheritA1(b1)
    'A1::inheritA1'
    >>> call_inheritA1(b2)
    'A1::inheritA1'
    >>> call_inheritA1(da1)
    'A1::inheritA1'
    >>> call_inheritA1(db1)
    'A1::inheritA1'
    >>> call_inheritA1(pa1_a1)
    'A1::inheritA1'
    >>> call_inheritA1(pb1_a1)
    'A1::inheritA1'
    >>> call_inheritA1(pb2_a1)
    'A1::inheritA1'
    >>> call_inheritA1(pb1_b1)
    'A1::inheritA1'
    >>> call_inheritA1(pc_a1)
    'A1::inheritA1'
    >>> call_inheritA1(pc_b1)
    'A1::inheritA1'

test inheritA2

    >>> a2.inheritA2()
    'A2::inheritA2'
    >>> b1.inheritA2()
    'A2::inheritA2'
    >>> b2.inheritA2()
    'A2::inheritA2'
    >>> db1.inheritA2()
    'A2::inheritA2'
    >>> pa2_a2.inheritA2()
    'A2::inheritA2'
    >>> pb1_a2.inheritA2()
    'A2::inheritA2'
    >>> pb1_b1.inheritA2()
    'A2::inheritA2'

test overrideB1

    >>> b1.overrideB1()
    'B1::overrideB1'
    >>> db1.overrideB1()
    'DB1.overrideB1'
    >>> pb1_b1.overrideB1()
    'B1::overrideB1'
    >>> pc_b1.overrideB1()
    'C::overrideB1'

test call_overrideB1

    >>> call_overrideB1(b1)
    'B1::overrideB1'
    >>> call_overrideB1(db1)
    'DB1.overrideB1'
    >>> call_overrideB1(pb1_a1)
    'B1::overrideB1'
    >>> call_overrideB1(pc_a1)
    'C::overrideB1'
    >>> call_overrideB1(pb1_b1)
    'B1::overrideB1'
    >>> call_overrideB1(pc_b1)
    'C::overrideB1'

test inheritB2

    >>> b2.inheritB2()
    'B2::inheritB2'
    >>> db2.inheritB2()
    'B2::inheritB2'

========= test the new def_raw() feature ==========

    >>> r = RawTest(1)
    >>> raw(r,1,third=1,fourth=1)
    4
    >>> r.raw(1,third=1,fourth=1)
    4
    >>> raw(r,1,third=1,f=1)
    Traceback (innermost last):
    KeyError: fourth
    >>> raw(r,1,third=1)
    Traceback (innermost last):
    TypeError: wrong number of arguments
    >>> raw(r,1)
    Traceback (innermost last):
    TypeError: wrong number of arguments
    >>> raw()
    Traceback (innermost last):
    TypeError: wrong number of arguments
    >>> raw1(1,second=1)
    2
    >>> raw1(1)
    1
    >>> raw1(second=1)
    1
    >>> raw1()
    0
    >>> raw2(1,second=1)
    2
    >>> raw2(1)
    1
    >>> raw2(second=1)
    1
    >>> raw2()
    0
    
========= test export of operators ==========

    >>> i = Int(2)
    >>> j = i+i
    >>> j.i()
    4
    >>> j = i-i
    >>> j.i()
    0
    >>> j = i*i
    >>> j.i()
    4
    >>> i<i
    0
    >>> cmp(i,i)
    0
    >>> k = Int(5)
    >>> j = divmod(k, i)
    >>> j[0].i()
    2
    >>> j[1].i()
    1
    >>> j = pow(i, k)
    >>> j.i()
    32
    >>> j = pow(i, k, k)
    >>> j.i()
    2
    >>> j = -i
    >>> j.i()
    -2
    >>> str(i)
    '2'
    >>> try: j = i/i
    ... except TypeError, err:
    ...     assert re.match(r'(bad|unsupported) operand type\(s\) for /',
    ...                     str(err))
    ... else: print 'no exception'
    
    >>> j = abs(i)
    Traceback (innermost last):
    TypeError: bad operand type for abs()
    >>> j = i+1
    >>> j.i()
    3
    >>> j = i-1
    >>> j.i()
    1
    >>> j = i*1
    >>> j.i()
    2
    >>> i<1
    0
    >>> cmp(i,1)
    1
    >>> j = pow(i, 5)
    >>> j.i()
    32
    >>> j = pow(i, 5, k)
    Traceback (innermost last):
    TypeError: bad operand type(s) for pow()
    >>> j = pow(i, 5, 5)
    Traceback (innermost last):
    TypeError: bad operand type(s) for pow()
    >>> j = i/1
    Traceback (innermost last):
    TypeError: bad operand type(s) for /
    >>> j = 1+i
    >>> j.i()
    3
    >>> j = 1-i
    >>> j.i()
    -1
    >>> j = 1*i
    >>> j.i()
    2
    >>> 1<i
    1
    >>> cmp(1,i)
    -1
    >>> j = 1/i
    Traceback (innermost last):
    TypeError: bad operand type(s) for /
    >>> pow(1,i)
    Traceback (innermost last):
    TypeError: bad operand type(s) for pow()

Test operator export to a subclass

    # force method table sharing
    >>> class IntDerived1(Int): pass
    ...

    >>> class IntDerived(Int):
    ...     def __init__(self, i):
    ...             Int.__init__(self, i)
    ...     def __str__(self):
    ...             return 'IntDerived: ' + str(self.i())
    ... 
    >>> f = IntDerived(3)
    >>> str(f)
    'IntDerived: 3'
    >>> j = f * f
    >>> j.i()
    9
    >>> j = f * i
    >>> j.i()
    6
    >>> j = f * 5
    >>> j.i()
    15
    >>> j = i * f
    >>> j.i()
    6
    >>> j = 5 * f
    >>> j.i()
    15


========= Prove that the "phantom base class" issue is resolved ==========

    >>> assert pa1_a1.__class__ == A1
    >>> assert pb1_a1.__class__ == A1
    >>> assert pb2_a1.__class__ == A1
    >>> assert pc_a1.__class__ == A1
    >>> assert pa2_a2.__class__ == A2
    >>> assert pb1_a2.__class__ == A2
    >>> assert pb1_b1.__class__ == B1
    >>> assert pc_b1.__class__ == B1
    >>> assert A1 in B1.__bases__
    >>> assert A2 in B1.__bases__
    >>> assert A1 in B2.__bases__
    >>> assert A2 in B2.__bases__
    >>> assert A1 in DA1.__bases__
    >>> assert B1 in DB1.__bases__
    >>> assert B2 in DB2.__bases__
    
===============================================================
test methodologies for wrapping functions that return a pointer

    >>> get_record().value
    1234

    In this methodology, the referent is copied
    >>> get_record() == get_record()
    0

======== Enums and non-method class attributes ==============
    >>> eo = EnumOwner(EnumOwner.one, EnumOwner.two)
    >>> eo.first
    1
    >>> eo.second
    2
    >>> eo.first = EnumOwner.three
    >>> eo.second = EnumOwner.one
    >>> eo.first
    3
    >>> eo.second
    1

======== test [plain] char converters ==============
    >>> get_plain_char()
    'x'
    >>> use_plain_char('a')
    'aaa'
    >>> use_const_plain_char('b')
    'bbbbb'

======== test std::complex converters ==============
    >>> c = dpolar(3, 5)
    >>> type(c)
    <type 'complex'>
    >>> '%.3g' % (dreal(c))
    '0.851'
    >>> '%.3g' % (dimag(c))
    '-2.88'
    >>> '%.3g' % (freal(c))
    '0.851'
    >>> '%.3g' % (fimag(c))
    '-2.88'
    >>> c = fpolar(7, 13)
    >>> type(c)
    <type 'complex'>
    >>> '%.3g' % (fimag(c))
    '2.94'
    >>> '%.3g' % (freal(c))
    '6.35'
    >>> '%.3g' % (dimag(c))
    '2.94'
    >>> '%.3g' % (dreal(c))
    '6.35'
    >>> '%.3g' % (dreal(3))
    '3'
    >>> '%.3g' % (dreal(3L))
    '3'
    >>> '%.3g' % (dreal(3.))
    '3'
    >>> '%.3g' % (freal(3))
    '3'
    >>> '%.3g' % (freal(3L))
    '3'
    >>> '%.3g' % (freal(3.))
    '3'

'''
#'

def assert_integer_expected(err):
  """Handle a common error report which appears differently in Python 1.5.x and 2.0"""
  assert isinstance(err, TypeError)
  message = str(err)
  assert (message == "illegal argument type for built-in operation"
          or message == "an integer is required")

import string
import re
import sys

def run(args = None):
    if args is not None:
        sys.argv = args
    import doctest, comprehensive
    return doctest.testmod(comprehensive)
    
if __name__ == '__main__':
    sys.exit(run()[0])
