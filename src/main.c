#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/util.h"
#include "../include/token.h"
#include "../include/parser.h"



int main(int argc,char** argv){
    if (argc <2){

        printf("not enough arguments\n");
        return 1;
    }

    if(strcmp(argv[1], "compile") == 0) {

        char* source = read_ascii_file(argv[2]);
        printf("%s\n",source);
        Tokenlist tokens;
        start_parser(&tokens, source);
        

        //free(tokens);
        free(source);
    }
    return 0;
}