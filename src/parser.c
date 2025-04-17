#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

P_status start_parser(Tokenlist* list, const char* source) {
    char lex[256];
    int lexi = 0;
    int i = 0;
    int line = 1;

    while (source[i] != '\0') {
        memset(lex, 0, 256);
        lexi = 0;

        while (source[i] == ' ' || source[i] == '\t') i++;
        if (source[i] == '\0') break;

        if (source[i] == '"') {
            i++; // skip opening quote
            while (source[i] != '"' && source[i] != '\0') {
                if (lexi < 255) lex[lexi++] = source[i++];
                else return TOKEN_ERROR;
            }
            lex[lexi] = '\0';
            if (source[i] == '"') i++; // skip closing quote
            add_token_list(list, create_token(STRING, 0, line, lex));
            continue;
        }

        if (strchr("(),;", source[i])) {
            lex[lexi++] = source[i++];
            lex[lexi] = '\0';
            add_token_list(list, create_token(DELIMITER, lex[0], line, NULL));
            continue;
        }

        while (!strchr(" \t\n\0(),;\"", source[i])) {
            if (lexi < 255) lex[lexi++] = source[i++];
            else return TOKEN_ERROR;
        }
        lex[lexi] = '\0';

        if (strcmp(lex, "vtr::def") == 0) {
            add_token_list(list, create_token(DEFINE, 0, line, NULL));
        }
        else if (strcmp(lex, "vtr::show") == 0) {
            add_token_list(list, create_token(SHOW, 0, line, NULL));
        }
        else if (isdigit(lex[0])) {
            add_token_list(list, create_token(INT, atoi(lex), line, NULL));
        }
        else if (strcmp(lex, "vtr") == 0) {
            add_token_list(list, create_token(VECTOR, 0, line, NULL));
        }
        else if (lex[0] != '\0') {
            printf("Error: Token desconocido '%s'\n", lex);
            return SINTAX_ERROR;
        }

        if (source[i] == '\n') line++;
        if (source[i] != '\0') i++;
    }
    return SUCCESS;
}
