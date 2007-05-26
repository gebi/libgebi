project(libgebi)

file(GLOB TEST_DIRS test_*)
foreach(i ${TEST_DIRS})
    add_subdirectory(${i})
endforeach(i)

