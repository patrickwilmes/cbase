enable_testing()

find_library(CUNIT_LIBRARY NAMES libcunit.so libcunit.a cunit)
find_path(CUNIT_INCLUDE_DIR NAMES CUnit/Basic.h)

if (NOT CUNIT_LIBRARY OR NOT CUNIT_INCLUDE_DIR)
    message(FATAL_ERROR "CUnit library or include files not found")
endif()

SET(PROD_SOURCES
        ../src/ds/stack.c
        ../src/ds/stack.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(cbase_test
        test_main.c
        stack_test.c
        stack_test.h
        ${PROD_SOURCES}
)

target_include_directories(cbase_test PRIVATE ${CUNIT_INCLUDE_DIR})
target_link_libraries(cbase_test PRIVATE ${CUNIT_LIBRARY})

add_test(NAME DatabaseTests COMMAND cbase_test)
