#ifndef PARSER_VMF_H
#define PARSER_VMF_H

#include "token.h"
#include <stdio.h>
#include <string.h>

enum _P_status {

    SUCCESS,
    SINTAX_ERROR

};
typedef enum _P_status P_status;
 
P_status start_parser( Tokenlist* list,const char* source);
int parser_get_num(const char* buf);
TokenInst parser_get_instruction(const char* buf);

TokenInst parser_get_type(const char* buf);

#endif