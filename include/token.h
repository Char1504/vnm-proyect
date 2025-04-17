#ifndef TOKEN_VMF_H
#define TOKEN_VMF_H

enum _TokenType {
    VECTOR,
    MATRIX
};

typedef enum _TokenType TokenType;

enum _TokenInst {
    DEFINE,
    SHOW,
    HIDE
};

typedef enum _TokenInst TokenInst;

enum _TokenNums {
    INT,
    BOOL,
    XCORD,
    YCORD,
    STRING,
    DELIMITER
};

struct _Token {
    int type;
    int data;
    int line;
};

typedef struct _Token Token;

Token* create_token(int type, int data, int line);
void destroy_token(Token *tok);

struct _Tokenlist {
    Token** data;
    int ptr;
    int size;
};

typedef struct _Tokenlist Tokenlist;

void add_token_list(Tokenlist* list, Token* tok);
Token* get_token_list(Tokenlist* list, int index);

#endif
