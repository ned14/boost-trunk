macro(spirit_run TESTNAME)
  parse_arguments(SPIRIT_RUN "COMPILE_FLAGS" "" ${ARGN})

  if (SPIRIT_RUN_DEFAULT_ARGS)
    set(SPIRIT_RUN_SOURCES ${SPIRIT_RUN_DEFAULT_ARGS})
  else (SPIRIT_RUN_DEFAULT_ARGS)
    set(SPIRIT_RUN_SOURCES "${TESTNAME}.cpp")
  endif (SPIRIT_RUN_DEFAULT_ARGS)

  boost_test_run(${TESTNAME} 
    ${SPIRIT_RUN_SOURCES}
    COMPILE_FLAGS "${SPIRIT_RUN_COMPILE_FLAGS}"
    )
  boost_test_run(${TESTNAME}_debug 
    ${SPIRIT_RUN_SOURCES}
    COMPILE_FLAGS "-DBOOST_SPIRIT_DEBUG=1 ${SPIRIT_RUN_COMPILE_FLAGS}"
    )
endmacro(spirit_run)

if(MSVC)
  # For Visual C++, turn on optimizations
  set(OPT_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
else(MSVC)
  set(OPT_FLAGS "")
endif(MSVC)

# spirit.core.kernel
spirit_run(match_tests)

# spirit.core.scanner
spirit_run(scanner_tests)
spirit_run(scanner_value_type_tests)

# spirit.core.primitive
spirit_run(primitives_tests)
spirit_run(char_strings_test)
boost_test_compile_fail(char_strings_test_fail)
spirit_run(numerics_tests COMPILE_FLAGS "${OPT_FLAGS}")

# spirit.core.composite
spirit_run(epsilon_tests)
spirit_run(negated_eps_p_test)
spirit_run(operators_tests)
spirit_run(directives_tests)
spirit_run(shortest_alternative_tests)

# spirit.core.non_terminal
spirit_run(rule_tests)
spirit_run(owi_st_tests)
spirit_run(grammar_tests COMPILE_FLAGS "${OPT_FLAGS}")
spirit_run(grammar_multi_instance_tst COMPILE_FLAGS "${OPT_FLAGS}")
spirit_run(subrule_tests)
# TODO: [        run owi_mt_tests.cpp : : : $(multi-threading) ]
# TODO: [        run grammar_mt_tests.cpp : : : $(multi-threading) ]
spirit_run(parser_context_test)

# spirit.meta
spirit_run(fundamental_tests)
spirit_run(parser_traits_tests)
spirit_run(traverse_tests)

# spirit.attribute
spirit_run(closure_tests COMPILE_FLAGS "${OPT_FLAGS}")
# [        run bug_000008.cpp : : : $(multi-threading) ]
spirit_run(parametric_tests)

# spirit.error_handling
spirit_run(exception_tests)

# spirit.tree
spirit_run(ast_calc_tests)
spirit_run(group_match_bug)
spirit_run(repeat_ast_tests)
boost_test_compile(mix_and_match_trees)

# temporarily removed from the test suite. tree_tests are not finished, yet.
#         spirit_run(tree_tests)

# spirit.dynamic
boost_test_compile(if_p_as_parser_tests)
boost_test_compile(while_p_as_parser_tests)
boost_test_compile(for_p_as_parser_tests)
spirit_run(if_tests)
spirit_run(if_p_int_as_condition_test)
spirit_run(for_tests)
spirit_run(while_tests)
spirit_run(lazy_tests)
spirit_run(switch_tests_eps_default)
spirit_run(switch_tests_general_def)
spirit_run(switch_tests_wo_default)
spirit_run(switch_tests_single)
spirit_run(switch_problem)
spirit_run(select_p_with_rule)

# spirit.utility.parsers
spirit_run(chset_tests)
spirit_run(confix_tests)
spirit_run(loops_tests)
spirit_run(symbols_tests)
spirit_run(symbols_add_null)
spirit_run(symbols_find_null)
spirit_run(escape_char_parser_tests COMPILE_FLAGS "${OPT_FLAGS}")
spirit_run(distinct_tests)
spirit_run(grammar_def_test)

# spirit.utility.support
# This test doesn't actually use multiple threads
#   spirit_run(scoped_lock_tests : : : $(multi-threading) ]

# spirit.iterator
spirit_run(fixed_size_queue_tests)
boost_test_compile_fail(fixed_size_queue_fail_tests)
spirit_run(file_iterator_tests)
spirit_run(multi_pass_tests COMPILE_FLAGS "${OPT_FLAGS}")
spirit_run(sf_bug_720917 COMPILE_FLAGS "${OPT_FLAGS}")
spirit_run(position_iterator_tests COMPILE_FLAGS "${OPT_FLAGS}")
boost_test_compile(multi_pass_compile_tests)

# spirit.small_bug_fixes
spirit_run(bug_fixes)

add_subdirectory(actor)
add_subdirectory(typeof_support)
