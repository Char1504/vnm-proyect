#ifndef PARSER_VMF_H
#define PARSER_VMF_H

#include "token.h"
#include <string.h>
 
void start_parser( Tokenlist* list,const char* source);
int parser_get_int(const char* buf);

TokenInst parser_get_instruction(const char* buf);

#endif