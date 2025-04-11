#include "../include/util.h"

char* read_ascii_file(const char* path) {

    FILE* file =fopen(path, "r");

    if(!file) {
        printf("couldnt open file'%s'\n", path);
        return NULL;
    }

    fseek(file,0,SEEK_END);
    int sizeF = ftell(file);
    fseek(file,0,SEEK_SET);

    char* buf =(char*) malloc(sizeof(char)* sizeF + 1);
    if (!buf) {
        printf("couldn't asign memory for file \n");
        return NULL;
    }
    fread(buf, 1, sizeF, file);
    buf[sizeF] = '\0';
    fclose(file);

    return buf;
}