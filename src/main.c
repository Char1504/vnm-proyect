#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[64];
    int x, y;
    int lenght;
    int angle;
} Vector;

#define MAX_VECTORS 128

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

    Vector vectors[MAX_VECTORS];
    int vector_count = 0;

    if (status == SUCCESS) {
        for (int i = 0; i < tokens.ptr; i++) {
            Token* tok = get_token_list(&tokens, i);

            // vtr::def "name" (x, y) , lenght, angle ;
            if (tok->type == DEFINE && i + 11 < tokens.ptr) {
                Token* name = get_token_list(&tokens, i + 1);
                Token* lparen = get_token_list(&tokens, i + 2);
                Token* x = get_token_list(&tokens, i + 3);
                Token* comma1 = get_token_list(&tokens, i + 4);
                Token* y = get_token_list(&tokens, i + 5);
                Token* rparen = get_token_list(&tokens, i + 6);
                Token* comma2 = get_token_list(&tokens, i + 7);
                Token* lenght = get_token_list(&tokens, i + 8);
                Token* comma3 = get_token_list(&tokens, i + 9);
                Token* angle = get_token_list(&tokens, i + 10);
                Token* delimiter = get_token_list(&tokens, i + 11);

                if (name && name->type == STRING &&
                    lparen && lparen->type == LPAREN &&
                    x && x->type == INT &&
                    comma1 && comma1->type == COMMA &&
                    y && y->type == INT &&
                    rparen && rparen->type == RPAREN &&
                    comma2 && comma2->type == COMMA &&
                    lenght && lenght->type == INT &&
                    comma3 && comma3->type == COMMA &&
                    angle && angle->type == INT &&
                    delimiter && delimiter->type == DELIMITER && delimiter->data == ';') {

                    Vector v;
                    strncpy(v.name, name->str, 63);
                    v.name[63] = '\0';
                    v.x = x->data;
                    v.y = y->data;
                    v.lenght = lenght->data;
                    v.angle = angle->data;
                    vectors[vector_count++] = v;
                    i += 11;
                }
            }

            // vtr::show "name" ;
            else if (tok->type == SHOW && i + 2 < tokens.ptr) {
                Token* name = get_token_list(&tokens, i + 1);
                Token* delimiter = get_token_list(&tokens, i + 2);

                if (name && name->type == STRING &&
                    delimiter && delimiter->type == DELIMITER && delimiter->data == ';') {
                    // Buscar vector
                    for (int j = 0; j < vector_count; j++) {
                        if (strcmp(vectors[j].name, name->str) == 0) {
                            printf("vector \"%s\" showing\n", vectors[j].name);
                        }
                    }
                    i += 2;
                }
            }

            // vtr::show "name" origin ;
            else if (tok->type == SHOW && i + 3 < tokens.ptr) {
                Token* name = get_token_list(&tokens, i + 1);
                Token* what = get_token_list(&tokens, i + 2);
                Token* delimiter = get_token_list(&tokens, i + 3);

                if (name && name->type == STRING &&
                    what && (what->type == ORIGIN || what->type == LENGHT || what->type == ANGLE) &&
                    delimiter && delimiter->type == DELIMITER && delimiter->data == ';') {
                    for (int j = 0; j < vector_count; j++) {
                        if (strcmp(vectors[j].name, name->str) == 0) {
                            if (what->type == ORIGIN)
                                printf("vector \"%s\" showing origin: %d, %d\n", vectors[j].name, vectors[j].x, vectors[j].y);
                            else if (what->type == LENGHT)
                                printf("vector \"%s\" showing lenght: %d\n", vectors[j].name, vectors[j].lenght);
                            else if (what->type == ANGLE)
                                printf("vector \"%s\" showing angle: %d degrees\n", vectors[j].name, vectors[j].angle);
                        }
                    }
                    i += 3;
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
