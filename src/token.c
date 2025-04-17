#include "../include/token.h"
#include <stdlib.h>
#include <string.h>

Token* create_token(int type, int data, int line, const char* str) {
    Token* tok = malloc(sizeof(Token));
    if (!tok) return NULL;
    tok->type = type;
    tok->data = data;
    tok->line = line;
    if (str) {
        tok->str = strdup(str);
    } else {
        tok->str = NULL;
    }
    return tok;
}

void destroy_token(Token* tok) {
    if (tok->str) free(tok->str);
    free(tok);
}

void add_token_list(Tokenlist* list, Token* tok) {
    if (list->ptr >= list->size) {
        list->size = (list->size == 0) ? 8 : list->size * 2;
        list->data = realloc(list->data, sizeof(Token*) * list->size);
    }
    list->data[list->ptr++] = tok;
}

Token* get_token_list(Tokenlist* list, int index) {
    if (index < 0 || index >= list->ptr) return NULL;
    return list->data[index];
}
