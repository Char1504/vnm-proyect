#include "../include/parser.h"

void start_parser( Tokenlist* list,const char* source) {

    char lex[256];
    int lexi =0;
    int i = 0;
    int line = 1;

    while (1){

        memset(lex, 0, 256);
        
        while(source[i] != ' '&& source[i] != '\n' && source[i] != '\0') {

            lex[lexi++] =source[i++];
        }
        lex[lexi]= '\0';

        if(strncmp(lex, "int ", 4) == 0){
            //this is an integer

            int integ = parser_get_int(lex);
            add_token_list(list, create_token(INTEGER, integ, line));
        }
        
        else {
            //its an instruccion
            int instr = parser_get_instruction(lex);
            add_token_list(list, create_token(INST, instr, line));
        }

        if(source[i]== '\n') {
            line++;
        }

        lexi =0;
        i++;
    }
}