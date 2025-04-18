#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static int is_identifier(const char* lex) {
    return strcmp(lex, "origin") == 0 || strcmp(lex, "lenght") == 0 || strcmp(lex, "angle") == 0;
}

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

        // Strings
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

        // Parentheses and delimiters
        if (source[i] == '(') {
            add_token_list(list, create_token(LPAREN, 0, line, NULL));
            i++;
            continue;
        }
        if (source[i] == ')') {
            add_token_list(list, create_token(RPAREN, 0, line, NULL));
            i++;
            continue;
        }
        if (source[i] == ',') {
            add_token_list(list, create_token(COMMA, 0, line, NULL));
            i++;
            continue;
        }
        if (source[i] == ';') {
            add_token_list(list, create_token(DELIMITER, ';', line, NULL));
            i++;
            continue;
        }

        // Identifiers and numbers
        while (!strchr(" \t\n\0(),;\"", source[i])) {
            if (lexi < 255) lex[lexi++] = source[i++];
            else return TOKEN_ERROR;
        }
        lex[lexi] = '\0';

        if (lex[0] == '\0') {
            if (source[i] == '\n') line++;
            if (source[i] != '\0') i++;
            continue;
        }

        if (strcmp(lex, "vtr::def") == 0) {
            add_token_list(list, create_token(DEFINE, 0, line, NULL));
        }
        else if (strcmp(lex, "vtr::show") == 0) {
            add_token_list(list, create_token(SHOW, 0, line, NULL));
        }
        else if (isdigit(lex[0]) || (lex[0] == '-' && isdigit(lex[1]))) {
            add_token_list(list, create_token(INT, atoi(lex), line, NULL));
        }
        else if (is_identifier(lex)) {
            if (strcmp(lex, "origin") == 0)
                add_token_list(list, create_token(ORIGIN, 0, line, NULL));
            else if (strcmp(lex, "lenght") == 0)
                add_token_list(list, create_token(LENGHT, 0, line, NULL));
            else if (strcmp(lex, "angle") == 0)
                add_token_list(list, create_token(ANGLE, 0, line, NULL));
        }
        else {
            printf("Error: Token desconocido '%s'\n", lex);
            return SINTAX_ERROR;
        }

        if (source[i] == '\n') line++;
        if (source[i] != '\0') i++;
    }
    return SUCCESS;
}
