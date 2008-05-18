set(TESTS 
stl_byval
stl_byref
array_byval
array_byref
cstr_byval
cstr_byref
pair_byval
pair_byref
user_defined
call_once
rvalue_const
rvalue_nonconst
dependent_type)

foreach(test ${TESTS})
  boost_test_run(${test})
endforeach(test ${TESTS})

boost_test_compile(noncopyable)

