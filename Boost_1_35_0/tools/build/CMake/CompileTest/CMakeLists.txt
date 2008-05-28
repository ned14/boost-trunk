cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

project(CompileTest)
string(REPLACE ":" ";" INCLUDE_PATHS ${INCLUDES})
separate_arguments(INCLUDE_PATHS)
include_directories (${INCLUDE_PATHS})
add_library(compile STATIC "${SOURCE}")
