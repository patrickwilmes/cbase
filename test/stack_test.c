/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "stack_test.h"
#include <CUnit/CUnit.h>
#include "ds/stack.h"

#include <stdlib.h>

int *create_int(int value) {
    int *ptr = malloc(sizeof(int));
    *ptr = value;
    return ptr;
}

void stack_test() {
    stack_t *stack = stack_create(10);
    stack_push(stack, create_int(1));
    stack_push(stack, create_int(2));
    stack_push(stack, create_int(3));
    stack_push(stack, create_int(4));

    int *value = stack_pop(stack);
    CU_ASSERT_EQUAL(*value, 4);
    free(value);

    value = stack_pop(stack);
    CU_ASSERT_EQUAL(*value, 3);
    free(value);

    value = stack_pop(stack);
    CU_ASSERT_EQUAL(*value, 2);
    free(value);

    value = stack_pop(stack);
    CU_ASSERT_EQUAL(*value, 1);
    free(value);

    stack_destroy(stack);
}
