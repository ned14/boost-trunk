include_directories(${Boost_SOURCE_DIR}/boost/tr1/tr1)

if (BORLAND)
  # Borland's broken include mechanism needs these extra headers:
  include_directories(${Boost_SOURCE_DIR}/boost/tr1/tr1/bcc32)  
endif (BORLAND)

macro(boost_glob_test_compile path glob_par compile_flags)
  #message("boost_glob_test_compile ${path} ${glob_par} ${compile_flags}")
  list_contains(WITH_STD "WITH_STD" ${ARGN})
  file(GLOB file_list ${path}/${glob_par})
  foreach (current_file ${file_list})
    get_filename_component(file_name ${current_file} NAME_WE)
    boost_test_compile(${file_name} ${path}/${file_name}.cpp 
      COMPILE_FLAGS "${compile_flags}")
    if (WITH_STD)
      boost_test_compile(${file_name}_std ${path}/${file_name}.cpp 
        COMPILE_FLAGS "${compile_flags} -DTEST_STD_HEADERS=1")
    endif (WITH_STD)
  endforeach (current_file)
endmacro(boost_glob_test_compile)

macro(boost_glob_test_compile_fail patch glob_par compile_flags)
  #message("boost_glob_test_compile_fail ${path} ${glob_par} ${compile_flags}")
  file(GLOB file_list ${glob_par})
  foreach (current_file ${file_list})
    get_filename_component(file_name ${current_file} NAME_WE)
    boost_test_compile_fail(${file_name} ${path}/${file_name}.cpp COMPILE_FLAGS "${compile_flags}")
	  endforeach (current_file)
endmacro(boost_glob_test_compile_fail)

macro(boost_glob_test_run path glob_par compile_flags)
  list_contains(WITH_STD "WITH_STD" ${ARGN})
  file(GLOB file_list ${path}/${glob_par})
  foreach (current_file ${file_list})
    get_filename_component(file_name ${current_file} NAME_WE)
    boost_test_run(${file_name} ${path}/${file_name}.cpp COMPILE_FLAGS "${compile_flags}")
    if (WITH_STD)
      boost_test_run(${file_name}_std ${path}/${file_name}.cpp 
        COMPILE_FLAGS "${compile_flags} -DTEST_STD_HEADERS=1")
    endif (WITH_STD)
  endforeach (current_file)
endmacro(boost_glob_test_run)


boost_glob_test_compile(. test*.cpp "" WITH_STD)

boost_glob_test_run(. run*.cpp "" WITH_STD)

boost_glob_test_compile_fail(config tr1_has_tr1*fail.cpp "")

boost_glob_test_compile(config tr1_has_tr1*pass.cpp "")


message("libs/tr1/test/CMakeLists.txt: was this just cruft?  Seems to duplicate first glob_test_compile line above")

boost_glob_test_run(type_traits *.cpp "")
# previous:
#boost_glob_test_run(type_traits *.cpp "-DTEST_STD=1")
#boost_glob_test_compile(std_headers *.cpp "-DTEST_STD=1")
