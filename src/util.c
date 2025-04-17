#include "../include/util.h"

char* read_ascii_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("No se pudo abrir el archivo: '%s'\n", path);
        return NULL;
    }

    // Obtener tamaño del archivo
    fseek(file, 0, SEEK_END);
    long sizeF = ftell(file);
    rewind(file);

    if (sizeF <= 0) {
        printf("Archivo vacío o inválido\n");
        fclose(file);
        return NULL;
    }

    // Reservar memoria
    char* buf = malloc(sizeF + 1);
    if (!buf) {
        printf("Error de asignación de memoria\n");
        fclose(file);
        return NULL;
    }

    // Leer contenido
    size_t read = fread(buf, 1, sizeF, file);
    if (read != sizeF) {
        printf("Error de lectura: leídos %zu/%ld bytes\n", read, sizeF);
        free(buf);
        fclose(file);
        return NULL;
    }

    buf[sizeF] = '\0';
    fclose(file);
    return buf;
}
