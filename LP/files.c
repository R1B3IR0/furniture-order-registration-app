#include <stdio.h>
#include <stdlib.h>
#include "files.h"

FILE *openFile(char *filename, char *mode) {
    FILE *file;

    file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Falha ao abrir o ficheiro %s", filename);
        exit(EXIT_FAILURE);
    }

    if (ferror(file)) {
        fprintf(stderr, "Falha ao abrir o ficheiro %s, erro --> %d", filename, ferror(file));
        exit(EXIT_FAILURE);
    }

    return file;
}

int getFileSize(FILE *file) {
    int ch;
    int lines = 0;

    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            lines++;
        }
    }

    return lines;
}
