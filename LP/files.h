#ifndef FILES_H
#define FILES_H

#include "stdlib.h"
#include "stdio.h"
#define CSVP "..\\LP\\produtos.csv"
#define CSVM "..\\LP\\materiais.csv"



/**
 * Abre o ficheiro que é passado como parâmetro.
 * @param filename
 * @param mode
 * @return ficheiro.
 */
FILE *openFile(char *filename, char *mode);

/**
 * A função obtem o tamanho do fichiero em linhas.
 * @param file
 * @return número de linhas.
 */
int getFileSize(FILE *file);

#endif /* FILES_H */

