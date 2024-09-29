/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#ifndef STACK_H
#define STACK_H

typedef struct stack {
    void **data;
    int top;
    int capacity;
} stack_t;

stack_t *stack_create(int initial_capacity);

void stack_push(stack_t *stack, void *element);

void *stack_pop(stack_t *stack);

void stack_destroy(stack_t *stack);

int stack_is_empty(const stack_t *stack);

#endif //STACK_H
