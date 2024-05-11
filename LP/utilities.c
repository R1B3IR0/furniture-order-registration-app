#include <stdio.h>
#include <string.h>
#include "utilities.h"

void cleanBuffer() {
    char ch;
    while ((ch = (char) getchar()) != '\n' && ch != EOF);
}

char readChar(char *msg) {
    char valor;
    printf("%s", msg);
    valor = (char) getchar();
    cleanBuffer();
    return valor;
}

int readInteger(int minValor, int maxValor, const char *msg) {
    int valor;
    printf("%s", msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(INVALID_VALUE);
        cleanBuffer();
        printf("%s", msg);
    }
    cleanBuffer();
    return valor;
}

float readFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf("%s", msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(INVALID_VALUE);
        cleanBuffer();
        printf("%s", msg);
    }
    cleanBuffer();
    return valor;
}

void readString(char *string, int tamanho, char *msg) {
    printf("%s", msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanBuffer();
        }
    }
}

