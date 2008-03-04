boost_add_library(
  boost_filesystem
  exception.cpp operations.cpp path.cpp portability.cpp utf8_codecvt_facet.cpp
  SHARED_COMPILE_FLAGS "-DBOOST_FILESYSTEM_DYN_LINK=1"
  )

