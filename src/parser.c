#include "../include/parser.h"
#include <stdlib.h>  // Línea añadida para atoi()
#include <ctype.h>

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
            lex[lexi++] = source[i++];
            while (source[i] != '"' && source[i] != '\0') {
                if (lexi < 255) lex[lexi++] = source[i++];
                else return TOKEN_ERROR;
            }
            if (source[i] == '"') lex[lexi++] = source[i++];
            else return SINTAX_ERROR;
            
            add_token_list(list, create_token(STRING, 0, line));
            continue;
        }

        if (strchr("(),;", source[i])) {
            lex[lexi++] = source[i++];
            add_token_list(list, create_token(DELIMITER, lex[0], line));
            continue;
        }

        while (!strchr(" \t\n\0(),;", source[i])) {
            if (lexi < 255) lex[lexi++] = source[i++];
            else return TOKEN_ERROR;
        }
        lex[lexi] = '\0';

        if (strcmp(lex, "vtr::def") == 0) {
            add_token_list(list, create_token(DEFINE, VECTOR, line));
        } 
        else if (strcmp(lex, "vtr::show") == 0) {
            add_token_list(list, create_token(SHOW, 0, line));
        } 
        else if (isdigit(lex[0])) {
            add_token_list(list, create_token(INT, atoi(lex), line));
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

int parser_get_num(const char* buf) {
    return atoi(buf);
}

TokenInst parser_get_instruction(const char* buf) {
    if (strcmp(buf, "def") == 0) return DEFINE;
    if (strcmp(buf, "show") == 0) return SHOW;
    return -1;
}

TokenInst parser_get_type(const char* buf) {
    if (strcmp(buf, "vtr") == 0) return (TokenInst)VECTOR;  // Cast añadido
    return -1;  // Return añadido para todos los casos
}
