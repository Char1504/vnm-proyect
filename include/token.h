#ifndef TOKEN_H
#define TOKEN_H

typedef enum _TokenType {
    DEFINE,
    SHOW,
    HIDE,
    VECTOR,
    INT,
    STRING,
    DELIMITER
} TokenType;

typedef enum _TokenInst {
    INST_DEFINE,
    INST_SHOW,
    INST_VECTOR
} TokenInst;

typedef struct {
    int type;
    char* str; // Para almacenar cadenas (como "palo1")
    int data;
    int line;
} Token;

typedef struct {
    Token** data;
    int size;
    int ptr;
} Tokenlist;

Token* create_token(int type, int data, int line, const char* str);
void destroy_token(Token* tok);
void add_token_list(Tokenlist* list, Token* tok);
Token* get_token_list(Tokenlist* list, int index);

#endif
