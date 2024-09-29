/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "stack.h"

#include <stdlib.h>

stack_t *stack_create(const int initial_capacity) {
    stack_t *stack = malloc(sizeof(stack_t));
    stack->data = (void **) malloc(initial_capacity * sizeof(void *));
    stack->top = -1;
    stack->capacity = initial_capacity;
    return stack;
}

void stack_push(stack_t *stack, void *element) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (void **) realloc(stack->data, stack->capacity * sizeof(void *));
    }
    stack->data[++stack->top] = element;
}

void *stack_pop(stack_t *stack) {
    if (stack->top == -1) return NULL;
    return stack->data[stack->top--];
}

int stack_is_empty(const stack_t *stack) {
    return stack->top == -1;
}

stack_t* stack_reverse(stack_t *stack) {
    stack_t *aux = stack_create(stack->capacity);
    while (!stack_is_empty(stack)) {
        void *element = stack_pop(stack);
        stack_push(aux, element);
    }
    stack_destroy(stack);
    return aux;
}

void stack_destroy(stack_t *stack) {
    if (stack != NULL) {
        if (stack->data != NULL) {
            while (!stack_is_empty(stack)) {
                void *element = stack_pop(stack);
                free(element);
            }
            free(stack->data);
        }
        free(stack);
    }
}
