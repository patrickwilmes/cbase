/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include <CUnit/CUnit.h>
#include "hello_test.h"
#include "hello.h"

void test_hello(void) {
    CU_ASSERT(give_me_two() == 2);  // Replace with actual test logic
}
