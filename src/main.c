/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

void process_input(const char *input);

void repl();

int main(void) {
    // process_input(
    //     "create table test (\n"
    //     "id integer primary key, \n"
    //     "name text not null, \n"
    //     "age integer, \n"
    //     ");\n"
    // );
    // printf("---------------------------------\n");
    process_input(
        "insert into test (id, name, age) values (28, \"max\", 28);"
    );
    // repl();
    return 0;
}

void repl() {
    char input[1024];
    while (1) {
        printf("cbase > ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (strncmp(input, ".exit", 5) == 0) {
                break;
            }
            process_input(input);
        }
    }
}

void process_input(const char *input) {
    stack_t *tokens = tokenize(input);
    tokens = stack_reverse(tokens);
    while (!stack_is_empty(tokens)) {
        token_t *token = stack_pop(tokens);
        token_explain(token);
        token_destroy(token);
    }
    stack_destroy(tokens);
}
