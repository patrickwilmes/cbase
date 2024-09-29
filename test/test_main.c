/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "hello_test.h"

void test_database_insert(void) {
    // Example test case
    CU_ASSERT(1 == 1);  // Replace with actual test logic
}

int main() {
    // Initialize the test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Create a test suite and add the test to it
    CU_pSuite pSuite = CU_add_suite("DatabaseTestSuite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_add_test(pSuite, "HelloTest", test_hello);
    // Add your test to the suite
    if ((NULL == CU_add_test(pSuite, "test_database_insert", test_database_insert))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
