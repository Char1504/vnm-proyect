#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo.vmf\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        printf("No se pudo abrir el archivo: %s\n", argv[1]);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* source = malloc(size + 1);
    fread(source, 1, size, f);
    source[size] = '\0';
    fclose(f);

    Tokenlist tokens = {NULL, 0, 0};
    P_status status = start_parser(&tokens, source);

    if (status == SUCCESS) {
        for (int i = 0; i < tokens.ptr; i++) {
            Token* tok = get_token_list(&tokens, i);
            if (tok->type == SHOW && i + 2 < tokens.ptr) {
                Token* next = get_token_list(&tokens, i + 1);
                Token* delim = get_token_list(&tokens, i + 2);
                if (next && next->type == STRING && delim && delim->type == DELIMITER && delim->data == ';') {
                    printf("vector \"%s\" showing\n", next->str);
                }
            }
        }
    } else {
        printf("Error de parsing\n");
    }

    // Liberar memoria
    for (int i = 0; i < tokens.ptr; i++) {
        destroy_token(tokens.data[i]);
    }
    free(tokens.data);
    free(source);

    return 0;
}
