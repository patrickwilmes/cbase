/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#ifndef LEXER_H
#define LEXER_H

#include "ds/stack.h"

enum token_type {
    create,
    table,
    string_literal,
    open_brace,
    close_brace,
    comma,
    semicolon,
    primary,
    key,
    not,
    null,
    data_type,
};

typedef struct token {
    enum token_type type;
    char *value;
} token_t;

token_t* token_create(enum token_type type, char *value);

void token_destroy(token_t *t);
void token_explain(token_t *token);

stack_t* tokenize(const char* source);

#endif //LEXER_H
