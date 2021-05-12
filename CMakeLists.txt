cmake_minimum_required(VERSION 3.14) # CMP0083 NEW
set_property(GLOBAL PROPERTY CXX_STANDARD 17)

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE FALSE)

project(libgebi)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR})

#set(TEST_DIRS test_invsqrt)
#file(GLOB TEST_DIRS test_*)
#foreach(i ${TEST_DIRS})
#    add_subdirectory(${i})
#endforeach(i)

set_source_files_properties(invsqrt.cpp PROPERTIES
    COMPILE_FLAGS "-O0")
add_library(gebi-static STATIC invsqrt.cpp)
set_target_properties(gebi-static PROPERTIES
    OUTPUT_NAME "gebi"
    CLEAN_DIRECT_OUTPUT 1)

add_subdirectory(tests)
