project(LinkTest)
include_directories (${INCLUDES})
add_executable(link ${SOURCE} COMPILE_FLAGS "${COMPILE_FLAGS}")
