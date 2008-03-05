if (MSVC)
  add_definitions(/wd4511 /wd4512 /wd4701 /wd4702 /wd4244 /wd4267 /wd4800)
endif (MSVC)

boost_add_executable(quickbook
  detail/quickbook.cpp
  detail/actions.cpp
  detail/actions_class.cpp
  detail/utils.cpp
  detail/post_process.cpp
  detail/collector.cpp
  detail/template_stack.cpp
  DEPENDS boost_program_options boost_filesystem
  )  
