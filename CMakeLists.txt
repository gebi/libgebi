project(libgebi)

#set(TEST_DIRS test_invsqrt)
#file(GLOB TEST_DIRS test_*)
#foreach(i ${TEST_DIRS})
#    add_subdirectory(${i})
#endforeach(i)

#add_subdirectory(invsqrt)
enable_testing()
set_source_files_properties(invsqrt.cpp PROPERTIES
    COMPILE_FLAGS "-O0")
add_library(gebi-static STATIC invsqrt.cpp)
set_target_properties(gebi-static PROPERTIES
    OUTPUT_NAME "gebi"
    CLEAN_DIRECT_OUTPUT 1)

add_subdirectory(tests)
