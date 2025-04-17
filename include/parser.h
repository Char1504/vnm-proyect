#ifndef PARSER_H
#define PARSER_H

#include "token.h"

typedef enum {
    SUCCESS,
    TOKEN_ERROR,
    SINTAX_ERROR
} P_status;

P_status start_parser(Tokenlist* list, const char* source);

#endif
