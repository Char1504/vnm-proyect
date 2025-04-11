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
            if(instr >= 0)
                add_token_list(list, create_token(INST, instr, line));
            else
                printf("Syntax Error: no such intruction '%s'\n",lex );
                return;
        }

        if(source[i]== '\n') {
            //new line
            line++;
        }

        else if (source[i] == '\0'){
            //end of file

            break;
            
        }
        lexi =0;
        i++;

        
}
}

int parser_get_int(const char* buf){

    

}
TokenInst parser_get_instruction(const char* buf){

    

}