#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/util.h"
#include "../include/token.h"
#include "../include/parser.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: ./vmf compile <archivo.vmf>\n");
        return 1;
    }

    if (strcmp(argv[1], "compile") == 0) {
        // Leer archivo fuente
        char* source = read_ascii_file(argv[2]);
        if (!source) return 1;
        
        // Inicializar lista de tokens
        Tokenlist* tokens = malloc(sizeof(Tokenlist));
        tokens->data = malloc(sizeof(Token*) * 128); // Capacidad inicial
        tokens->ptr = 0;
        tokens->size = 128;

        // Procesar fuente
        P_status status = start_parser(tokens, source);
        
        if (status == SUCCESS) {
            printf("\nTokens generados (%d):\n", tokens->ptr);
            for (int i = 0; i < tokens->ptr; i++) {
                Token* tok = get_token_list(tokens, i);
                printf("[L%d] Tipo: %d - Valor: %d\n", 
                      tok->line, tok->type, tok->data);
            }
        } else {
            printf("\nError durante el parsing (Código: %d)\n", status);
        }

        // Liberar memoria
        for (int i = 0; i < tokens->ptr; i++) {
            destroy_token(tokens->data[i]);
        }
        free(tokens->data);
        free(tokens);
        free(source);
    }
    return 0;
}
