# The set of archives that we will use for testing the Serialization
# library
set(BOOST_ARCHIVE_LIST 
  "text_archive" 
  "text_warchive" 
  "binary_archive" 
  "xml_archive" 
  "xml_warchive"
  )

# The serialization_test macro declares a set of tests of the
# serialization library. For each invocation of serialization_test,
# this macro will build separate static and dynamic tests for each
# archive type listed in BOOST_ARCHIVE_LIST.
macro(serialization_test testname)
  parse_arguments(BSL_TEST "" "NO_LIBS;POLYMORPHIC" ${ARGN})

  if(NOT BSL_TEST_DEFAULT_ARGS)
    set(BSL_TEST_SOURCES "${testname}.cpp")
  else(NOT BSL_TEST_DEFAULT_ARGS)
    set(BSL_TEST_SOURCES "${BSL_TEST_DEFAULT_ARGS}")
  endif(NOT BSL_TEST_DEFAULT_ARGS)

  if (BSL_TEST_POLYMORPHIC)
    set(BSL_TEST_POLY "polymorphic_")
  elseif(BSL_TEST_POLYMORPHIC)
    set(BSL_TEST_POLY "")
  endif(BSL_TEST_POLYMORPHIC)
  
  foreach(ARCHIVE ${BOOST_ARCHIVE_LIST})
    set(BSL_TEST_LIBRARIES) 
    if(NOT BSL_NO_LIBS)
      set(BSL_TEST_LIBRARIES "boost_serialization")
      if(ARCHIVE MATCHES ".*warchive")
        set(BSL_TEST_LIBRARIES "boost_wserialization" ${BSL_TEST_LIBRARIES})
      endif(ARCHIVE MATCHES ".*warchive")
    endif(NOT BSL_NO_LIBS)

    # Tests linking against the static serialization library
    boost_test_run("${testname}_${ARCHIVE}"
      ${BSL_TEST_SOURCES}
      STATIC
      DEPENDS boost_test_exec_monitor-static ${BSL_TEST_LIBRARIES}
      COMPILE_FLAGS "-DBOOST_ARCHIVE_TEST=${BSL_TEST_POLY}${ARCHIVE}.hpp -DBOOST_LIB_DIAGNOSTIC=1")
    
    # Tests linking against the shared serialization library
    boost_test_run("${testname}_${ARCHIVE}_dll"
      ${BSL_TEST_SOURCES}
      SHARED
      DEPENDS boost_test_exec_monitor-static ${BSL_TEST_LIBRARIES}
      COMPILE_FLAGS "-DBOOST_ARCHIVE_TEST=${BSL_TEST_POLY}${ARCHIVE}.hpp -DBOOST_LIB_DIAGNOSTIC=1 -DBOOST_ALL_DYN_LINK=1")
  endforeach(ARCHIVE ${BOOST_ARCHIVE_LIST})
endmacro(serialization_test)

serialization_test(test_array)
serialization_test(test_binary)
serialization_test(test_contained_class)
serialization_test(test_cyclic_ptrs)
serialization_test(test_delete_pointer)
serialization_test(test_deque)
serialization_test(test_derived)
serialization_test(test_derived_class)
serialization_test(test_derived_class_ptr)
serialization_test(test_diamond)
serialization_test(test_exported)
serialization_test(test_class_info_save)
serialization_test(test_class_info_load)
serialization_test(test_object)
serialization_test(test_primitive)
serialization_test(test_list)
serialization_test(test_list_ptrs)
serialization_test(test_map)
serialization_test(test_mi)
serialization_test(test_multiple_ptrs)
serialization_test(test_no_rtti)
serialization_test(test_non_intrusive)
serialization_test(test_non_default_ctor)
serialization_test(test_non_default_ctor2)
serialization_test(test_null_ptr)
serialization_test(test_nvp)
serialization_test(test_recursion)
serialization_test(test_registered)
serialization_test(test_set)
serialization_test(test_simple_class)
serialization_test(test_simple_class_ptr)
serialization_test(test_split)
serialization_test(test_tracking)
serialization_test(test_unregistered)
serialization_test(test_variant)
serialization_test(test_vector)
serialization_test(test_optional)
serialization_test(test_shared_ptr)
serialization_test(test_shared_ptr_132)
serialization_test(test_polymorphic POLYMORPHIC 
  test_polymorphic.cpp test_polymorphic_A.cpp)
serialization_test(test_iterators NO_LIBS)
serialization_test(test_iterators_base64 NO_LIBS)
serialization_test(test_inclusion NO_LIBS)
serialization_test(test_private_ctor)
serialization_test(test_reset_object_address)
serialization_test(test_smart_cast NO_LIBS)
serialization_test(test_static_warning NO_LIBS)
serialization_test(test_utf8_codecvt 
  test_utf8_codecvt.cpp ../src/utf8_codecvt_facet.cpp NO_LIBS)
serialization_test(test_void_cast)
serialization_test(test_mult_archive_types)
serialization_test(test_codecvt_null 
  test_codecvt_null.cpp ../src/codecvt_null.cpp NO_LIBS)

# demos
serialization_test(test_demo)
serialization_test(test_demo_auto_ptr)
serialization_test(test_demo_exception)
serialization_test(test_demo_fast_archive)
serialization_test(test_demo_pimpl 
  ../example/demo_pimpl.cpp ../example/demo_pimpl_A.cpp)
serialization_test(test_demo_polymorphic 
  ../example/demo_polymorphic.cpp ../example/demo_polymorphic_A.cpp)
serialization_test(test_demo_portable_archive)
serialization_test(test_demo_shared_ptr)
serialization_test(test_demo_xml)
serialization_test(test_demo_xml_save)
serialization_test(test_demo_xml_load)

# should fail compilation
boost_test_compile_fail(test_not_serializable) # FIXME std:locale-support ]
boost_test_compile_fail(test_traits_fail) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_save_fail1) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_save_fail2) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_save_fail3) # FIXME std:locale-support ]
# note - library unable to detect there errors for now
#boost_test_compile_fail(test_const_save_fail1_nvp)
#boost_test_compile_fail(test_const_save_fail2_nvp)
#boost_test_compile_fail(test_const_save_fail3_nvp)
boost_test_compile_fail(test_const_load_fail1) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_load_fail2) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_load_fail3) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_load_fail1_nvp) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_load_fail2_nvp) # FIXME std:locale-support ]
boost_test_compile_fail(test_const_load_fail3_nvp) # FIXME std:locale-support ]

# should compile
boost_test_compile(test_traits_pass) # FIXME std:locale-support ]
boost_test_compile(test_const_pass) # FIXME std:locale-support ]
