#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "materials.h"

#define LINE_SIZEM 64

int getMaterialIndex(char *code, MaterialsArray *materialsArray) {
    for (int i = 0; i < materialsArray->count; i++) {
        if (strcmp(code, materialsArray->material[i].code) == 0) {
            return i;
        }
    }
    return -1;
}

Material *findMaterialByCode(MaterialsArray *ptr_MaterialsArray, char code[]) {
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->material[i].code, code) == 0) {
            return &ptr_MaterialsArray->material[i];
        }
    }
    return NULL;
}

int readMaterial(MaterialsArray *ptr_MaterialsArray, int i) {
    char code[6];
    char *name = malloc(sizeof(char) * 64);
    char type[5];

    readString(code, 6, CODE_INPUT_PRODUCT);

    // Check if a Material with the same code already exists in the array
    if (findMaterialByCode(ptr_MaterialsArray, code)) {
        printf(CODE_EXISTS);
        return 0;
    }

    readString(name, 256, INSERT_PRODUCT_NAME);
    readString(type, 5, INSERT_PRODUCT_TYPE);

    // Copy the data into the appropriate elements of the MaterialsArray
    strcpy(ptr_MaterialsArray->material[i].code, code);
    strcpy(ptr_MaterialsArray->material[i].description, name);
    strcpy(ptr_MaterialsArray->material[i].unit, type);

    return 1;
}

MaterialsArray *allocMemoryMaterials(int size) {
    MaterialsArray *ptr_MaterialsArray = (MaterialsArray *) malloc(sizeof(MaterialsArray));
    if (ptr_MaterialsArray == NULL) {
        printf("Error allocating memory for MaterialsArray\n");
        return NULL;
    }

    ptr_MaterialsArray->count = 0;
    ptr_MaterialsArray->size = size;

    ptr_MaterialsArray->material = (Material *) calloc(ptr_MaterialsArray->size, sizeof(Material));
    if (ptr_MaterialsArray->material == NULL) {
        printf("Error allocating memory for material\n");
        return NULL;
    }
    for (int i = 0; i < ptr_MaterialsArray->size; i++) {
        strcpy(ptr_MaterialsArray->material[i].code, "");
        strcpy(ptr_MaterialsArray->material[i].description, "");
        strcpy(ptr_MaterialsArray->material[i].unit, "");

    }

    return ptr_MaterialsArray;
}

MaterialsArray *importMaterials(char *filename) {

    MaterialsArray *ptr_MaterialsArray;

    FILE *file;
    char buffer[LINE_SIZEM];
    char *field;
    char *delim = ";";
    char code[6];
    char description[40];
    char unit[5];
    int fileSize;

    file = openFile(filename, "r");
    fileSize = getFileSize(file);

    ptr_MaterialsArray = allocMemoryMaterials(fileSize);
    rewind(file);

    while (fgets(buffer, LINE_SIZEM, file)) {

        field = strtok(buffer, delim);
        strcpy(code, field);

        strcpy(ptr_MaterialsArray->material[ptr_MaterialsArray->count].code,
               code);

        field = strtok(NULL, delim);
        strcpy(description, field);

        strcpy(ptr_MaterialsArray->material[ptr_MaterialsArray->count].description,
               description);

        field = strtok(NULL, delim);
        strcpy(unit, field);

        strcpy(ptr_MaterialsArray->material[ptr_MaterialsArray->count].unit,
               unit);


        ptr_MaterialsArray->count++;

    }

    fclose(file);

    return
            ptr_MaterialsArray;

}

void freeMemoryMaterials(MaterialsArray *ptr_MaterialsArray) {
    if (ptr_MaterialsArray == NULL) {
        return;
    }
    free(ptr_MaterialsArray->material);
    free(ptr_MaterialsArray);
}

void expandMaterialsArray(MaterialsArray *ptr_MaterialsArray) {
    int new_size;

    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return;
    }

    new_size = ptr_MaterialsArray->size * 2;

    ptr_MaterialsArray->material = (Material *) realloc(ptr_MaterialsArray->material,
                                                        new_size * sizeof(Material));
    if (ptr_MaterialsArray->material == NULL) {
        printf("Error allocating memory for expanded material array\n");
        return;
    }

    ptr_MaterialsArray->size = new_size;

    for (int i = ptr_MaterialsArray->count; i < new_size; i++) {
        ptr_MaterialsArray->material[i].code[0] = '\0';
        ptr_MaterialsArray->material[i].description[0] = '\0';
        ptr_MaterialsArray->material[i].unit[0] = '\0';

    }
}

int addMaterial(MaterialsArray *ptr_MaterialsArray) {
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 0;
    }
    if (ptr_MaterialsArray->count == ptr_MaterialsArray->size) {
        expandMaterialsArray(ptr_MaterialsArray);
    }
    if (readMaterial(ptr_MaterialsArray, ptr_MaterialsArray->count) != 1) {
        return 0;
    }
    ptr_MaterialsArray->count++;
    return 1;
}

int removeMaterial(MaterialsArray *ptr_MaterialsArray) {
    char *code = ptr_MaterialsArray->material->code;
    int position = -1;
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 1;
    }
    readString(code, 6, INSERT_MATERIAL_CODE);
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->material[i].code, code) == 0) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        printf("Material not found\n");
        return 1;
    }

    for (int i = position; i < ptr_MaterialsArray->count - 1; i++) {
        ptr_MaterialsArray->material[i] = ptr_MaterialsArray->material[i + 1];
    }

    ptr_MaterialsArray->count--;
    printf("Material removed\n");
    return 0;
}

int updateMaterial(MaterialsArray *ptr_MaterialsArray) {
    char *code = ptr_MaterialsArray->material->code;
    if (ptr_MaterialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return 0;
    }
    readString(code, 6, INSERT_MATERIAL_CODE);
    for (int i = 0; i < ptr_MaterialsArray->count; i++) {
        if (strcmp(ptr_MaterialsArray->material[i].code, code) == 0) {
            printf("Material found\n");
            return readMaterial(ptr_MaterialsArray, i);
        }
    }
    printf("Material with code %s not found\n", code);
    return 0;
}

void printMaterials(const Material *material) {
    if (material == NULL) {
        printf("Error: Material pointer is null\n");
        return;
    }
    printf("\n----\n");
    printf("Code: %s\n", material->code);
    printf("Description: %s\n", material->description);
    printf("Type: %s\n", material->unit);
    printf("\n----\n");
}

void listMaterials(MaterialsArray *materialsArray) {
    if (materialsArray == NULL) {
        printf("Error: MaterialsArray pointer is null\n");
        return;
    }
    if (materialsArray->count == 0) {
        printf("No material to list\n");
        return;
    }
    for (int i = 0; i < materialsArray->count; i++) {
        printMaterials(&materialsArray->material[i]);
    }
}

void exportMaterials(char *filename, MaterialsArray *materialsArray) {

    FILE *file;

    file = openFile(filename, "w");


    for (int i = 0; i < materialsArray->count; i++) {
        fprintf(file, "%s;%s;%s;\n",
                materialsArray->material[i].code,
                materialsArray->material[i].description,
                materialsArray->material[i].unit
        );
    }
    fclose(file);
}

