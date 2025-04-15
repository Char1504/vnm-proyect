#include "../include/parser.h"

P_status start_parser( Tokenlist* list,const char* source) {

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

            int integ = parser_get_num(lex);
            add_token_list(list, create_token(INT, integ, line));
        }
        
        else if(strncmp(lex, "def", 3) == 0) {
            //its defining something
            int instr = parser_get_instruction(lex);
            if(instr >= 0)
                add_token_list(list, create_token(DEFINE, instr, line));
            else
                printf("Syntax Error: no such intruction '%s'\n",lex );
                return SINTAX_ERROR;
        }
        else if(strncmp(lex, "::vtr", 5) == 0) {
            //its a vector
            int instr = parser_get_type(lex);
            if(instr >= 0)
                add_token_list(list, create_token(DEFINE, instr, line));
            else
                printf("Syntax Error: no such type '%s'\n",lex );
                return SINTAX_ERROR;
        }

        if(source[i]== ';') {
            //its the end of a command

            line++;
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
return SUCCESS;
}

int parser_get_int(const char* buf){

    

}
TokenInst parser_get_instruction(const char* buf){

    

}
TokenInst parser_get_type(const char* buf) {


}