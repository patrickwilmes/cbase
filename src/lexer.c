/*
* Copyright (c) 2024, Patrick Wilmes <p.wilmes89@gmail.com>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause
*/
#include "lexer.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CURRENT_TOKEN_BUF_SIZE 1024

typedef struct {
    const char *token;
    enum token_type type;
} token_map;

token_map token_maps[] = {
    {"(", open_brace},
    {")", close_brace},
    {",", comma},
    {"create", create},
    {"table", table},
    {"key", key},
    {"primary", primary},
    {"not", not},
    {"null", null},
    {"integer", data_type},
    {"text", data_type},
    {"insert", insert},
    {"into", into},
    {"values", values},
    {";", semicolon},
};

static void consume(stack_t *stack, enum token_type type, char *value, int *current_token_ptr,
                    char *current_token) {
    token_t *token = token_create(type, value);
    stack_push(stack, token);
    *current_token_ptr = -1;
    memset(current_token, 0, CURRENT_TOKEN_BUF_SIZE);
}

/*
 * For string literals, numbers and identifiers, we put the actual value into the
 * token type. As the value is only tracked inside the function scope, we need
 * to allocate memory and copy the current value over.
 */
static char* alloc_string(const char *current_value, const size_t size) {
    // ReSharper disable once CppDFAMemoryLeak
    // this is properly freed via token destructor - checked with valgrind
    char *value = calloc(size, sizeof(char));
    strcpy(value, current_value);
    return value;
}

stack_t *tokenize(const char *source) {
    stack_t *tokens = stack_create(10);

    int source_ptr = 0;

    char current_token[CURRENT_TOKEN_BUF_SIZE] = {0};
    int current_token_ptr = -1;
    do {
        if (source[source_ptr] == ' ' || source[source_ptr] == '\n') {
            source_ptr++;
            continue;
        }
        current_token_ptr++;
        current_token[current_token_ptr] = source[source_ptr];
        // consume a number
        if (isdigit(source[source_ptr])) {
            current_token_ptr = 0;
            memset(current_token, 0, CURRENT_TOKEN_BUF_SIZE);
            do {
                current_token[current_token_ptr] = source[source_ptr];
                current_token_ptr++;
                source_ptr++;
            } while (isdigit(source[source_ptr]));
            char *value = alloc_string(current_token, CURRENT_TOKEN_BUF_SIZE);
            consume(tokens, number, value, &current_token_ptr, current_token);
            continue;
        }
        // consume a string literal
        if (source[source_ptr] == '"') {
            current_token_ptr = 0;
            memset(current_token, 0, CURRENT_TOKEN_BUF_SIZE);
            source_ptr++;
            do {
                current_token[current_token_ptr] = source[source_ptr];
                current_token_ptr++;
                source_ptr++;
            } while (source[source_ptr] != '"');
            source_ptr++;
            char *value = alloc_string(current_token, CURRENT_TOKEN_BUF_SIZE);
            consume(tokens, string_literal, value, &current_token_ptr, current_token);
            continue;
        }
        for (int i = 0; token_maps[i].token != NULL; ++i) {
            if (strcmp(token_maps[i].token, current_token) == 0) {
                if (token_maps[i].type == data_type) {
                    char *value = alloc_string(current_token, CURRENT_TOKEN_BUF_SIZE);
                    consume(tokens, token_maps[i].type, value, &current_token_ptr, current_token);
                } else {
                    consume(tokens, token_maps[i].type, NULL, &current_token_ptr, current_token);
                }
            }
        }
        if (source[source_ptr + 1] == ' ' || source[source_ptr + 1] == ')' || source[source_ptr + 1] == ',') {
            if (strcmp(current_token, "") != 0) {
                char *value = alloc_string(current_token, CURRENT_TOKEN_BUF_SIZE);
                consume(tokens, identifier, value, &current_token_ptr, current_token);
            }
        }
        source_ptr++;
    } while (source[source_ptr] != '\0');

    assert(tokens->top != -1);
    // ReSharper disable once CppDFAMemoryLeak
    // this is properly freed via token destructor - checked with valgrind
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

token_t *token_create(enum token_type type, char *value) {
    token_t *token = malloc(sizeof(token_t));
    token->type = type;
    token->value = NULL;
    token->value = value;
    return token;
}

void token_explain(const token_t *token) {
    printf("Token: ");
    switch (token->type) {
        case create:
            printf("create");
            break;
        case table:
            printf("table");
            break;
        case identifier:
            printf("identifier: %s", token->value);
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
        case data_type:
            printf("data_type: %s", token->value);
            break;
        case insert:
            printf("insert");
            break;
        case into:
            printf("into");
            break;
        case values:
            printf("values");
            break;
        case string_literal:
            printf("string_literal: %s", token->value);
            break;
        case number:
            printf("number: %s", token->value);
            break;
    }
    printf("\n");
}
