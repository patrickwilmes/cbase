/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "lexer.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *tokenize(const char *source) {
    stack_t *tokens = stack_create(10);

    int source_ptr = 0;

    char current_token[1024] = {0};
    int current_token_ptr = -1;
    do {
        if (source[source_ptr] == ' ' || source[source_ptr] == '\n') {
            source_ptr++;
            continue;
        }
        current_token_ptr++;
        current_token[current_token_ptr] = source[source_ptr];

        if (strcmp(current_token, "(") == 0) {
            token_t *token = token_create(open_brace, NULL);
            stack_push(tokens, token);
            current_token_ptr = -1;
            memset(current_token, 0, sizeof(current_token));
        } else if (strcmp(current_token, ")") == 0) {
            token_t *token = token_create(close_brace, NULL);
            stack_push(tokens, token);
            current_token_ptr = -1;
            memset(current_token, 0, sizeof(current_token));
        } else if (strcmp(current_token, "create") == 0) {
            token_t *token = token_create(create, NULL);
            stack_push(tokens, token);
            current_token_ptr = -1;
            memset(current_token, 0, sizeof(current_token));
        } else if (strcmp(current_token, "table") == 0) {
            token_t *token = token_create(table, NULL);
            stack_push(tokens, token);
            current_token_ptr = -1;
            memset(current_token, 0, sizeof(current_token));
        } else if (source[source_ptr+1] == ' ') {
            if (strcmp(current_token, "") != 0) {
                // ReSharper disable once CppDFAMemoryLeak
                // this is properly freed via token destructor - checked with valgrind
                char *value = calloc(1024, sizeof(char));
                strcpy(value, current_token);
                token_t *token = token_create(string_literal, value);
                stack_push(tokens, token);
                current_token_ptr = -1;
                memset(current_token, 0, sizeof(current_token));
            }
        }
        source_ptr++;
    } while (source[source_ptr] != '\0');

    assert(tokens->top != -1);
    return tokens;
}

void token_destroy(token_t *t) {
    if (t) {
        if (t->value) {
            free(t->value);
        }
        free(t);
    }
}

token_t* token_create(enum token_type type, char *value) {
    token_t *token = malloc(sizeof(token_t));
    token->type = type;
    token->value = NULL;
    token->value = value;
    return token;
}

void token_explain(token_t *token) {
    printf("Token: ");
    switch (token->type) {
        case create:
            printf("create");
            break;
        case table:
            printf("table");
            break;
        case string_literal:
            printf("string_literal: %s", token->value);
            break;
        case open_brace:
            printf("open_brace");
            break;
        case close_brace:
            printf("close_brace");
            break;
        case comma:
            printf("comma");
            break;
        case semicolon:
            printf("semicolon");
            break;
        case primary:
            printf("primary");
            break;
        case key:
            printf("key");
            break;
        case not:
            printf("not");
            break;
        case null:
            printf("null");
            break;
    }
    printf("\n");
}
