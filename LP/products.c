#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "products.h"

#define LINE_SIZE 256

Product *findProductByCode(ProductsArray *ptr_ProductsArray, const char code[]) {
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].code == code) {
            return &ptr_ProductsArray->product[i];
        }
    }
    return NULL;
}

int readProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i) {
    char code[10];
    char dimensions[11];
    char name[256];
    char option;
    int price;


    readString(code, 6, CODE_INPUT_PRODUCT);
    if (findProductByCode(ptr_ProductsArray, code)) {
        printf(CODE_EXISTS);
        return 0;
    }

    readString(name, 30, INSERT_PRODUCT_NAME);
    readString(dimensions, 11, INSERT_PRODUCT_DIMENSIONS); //TAM(Exemplo: 999x999x999) 11 casas
    price = readInteger(0, 100000, INSERT_PRICE_PRODUCT);

    strcpy(ptr_ProductsArray->product[i].code, code);
    strcpy(ptr_ProductsArray->product[i].name, name);
    strcpy(ptr_ProductsArray->product[i].dimensions, dimensions);
    ptr_ProductsArray->product[i].price = price;


    addMaterialsToProduct(ptr_MaterialsArray, ptr_ProductsArray, i);

    do {
        printf("\nDeseja inserir outro material ao seu produto? Y/N:  ");
        scanf(" %c", &option);
        switch (option) {
            case 'Y':
            case 'y':
                addMaterialsToProduct(ptr_MaterialsArray, ptr_ProductsArray, i);
                break;
            case 'N':
            case 'n':
                return 1;
            default:
                printf("Insira uma opcao válida!!");
        }
    } while (option != ('n' | 'N'));

    return 1;
}

void expandProductsArray(ProductsArray *ptr_ProductsArray) {
    int new_size;

    new_size = ptr_ProductsArray->size * 2;

    ptr_ProductsArray->product = (Product *) realloc(ptr_ProductsArray->product, new_size * sizeof(Product));
    if (ptr_ProductsArray->product == NULL) {
        printf("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_ProductsArray->size = new_size; //Para Produtos

    for (int i = ptr_ProductsArray->count; i < new_size; i++) {
        strcpy(ptr_ProductsArray->product[i].code, "");
        strcpy(ptr_ProductsArray->product[i].name, "");
        strcpy(ptr_ProductsArray->product[i].dimensions, "");
        ptr_ProductsArray->product[i].price = 0;
    }
}

ProductsArray *allocMemoryProducts(int size) {
    ProductsArray *ptr_ProductsArray;
    ptr_ProductsArray = (ProductsArray *) malloc(sizeof(ProductsArray));
    if (ptr_ProductsArray == NULL) {
        perror("Erro ao alocar memoria para ProductsArray");
        return NULL;
    }

    ptr_ProductsArray->count = 0;
    ptr_ProductsArray->size = size;

    ptr_ProductsArray->product = (Product *) calloc(ptr_ProductsArray->size, sizeof(Product));
    if (ptr_ProductsArray->product == NULL) {
        perror("Erro ao alocar memoria para Product");
        return NULL;
    }
    for (int i = 0; i < ptr_ProductsArray->size; i++) {
        ptr_ProductsArray->product[i].productMaterialsArray = allocMemoryProductMaterials(size);
        if (ptr_ProductsArray->product[i].productMaterialsArray == NULL) {
            return NULL;
        }
    }
    return ptr_ProductsArray;
}

ProductsArray *importProducts(char *filename) {

    ProductsArray *ptr_ProductsArray;

    FILE *file;
    char buffer[LINE_SIZE];
    char *field;
    char *delim = ";";
    char code[7];
    char name[128];
    char dimensions[11];
    int price, quantity;
    int fileSize;
    int countPmaterial = 0;
    int countProduct = -1;

    file = openFile(filename, "r");
    fileSize = getFileSize(file);

    ptr_ProductsArray = allocMemoryProducts(fileSize * 2);
    rewind(file);

    while (fgets(buffer, LINE_SIZE, file)) {


        field = strtok(buffer, delim);
        strcpy(code, field);


        if (code[0] == 'P') {

            countProduct++;
            countPmaterial = 0;

            field = strtok(NULL, delim);
            strcpy(name, field);

            field = strtok(NULL, delim);
            strcpy(dimensions, field);

            field = strtok(NULL, delim);
            price = strtol(field,0,10);


            strcpy(ptr_ProductsArray->product[countProduct].code, code);

            strcpy(ptr_ProductsArray->product[countProduct].name, name);

            strcpy(ptr_ProductsArray->product[countProduct].dimensions, dimensions);

            ptr_ProductsArray->product[countProduct].price = price;

        } else {


            field = strtok(NULL, delim);
            quantity = strtol(field,0,10);


            strcpy(ptr_ProductsArray->product[countProduct].
                    productMaterialsArray->materialInProduct[countPmaterial].code, code);

            ptr_ProductsArray->product[countProduct].productMaterialsArray
                    ->materialInProduct[countPmaterial].quantity = quantity;


            countPmaterial++;
        }

    }
    ptr_ProductsArray->count = countProduct + 1;
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        ptr_ProductsArray->product[i].productMaterialsArray->count = countPmaterial;
    }
    fclose(file);

    return ptr_ProductsArray;
}

void freeMemoryProducts(ProductsArray *ptr_ProductsArray) {
    free(ptr_ProductsArray->product);
    free(ptr_ProductsArray);
}

int addProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray) {

    if (ptr_ProductsArray == NULL) {
        return 0;
    }

    if (ptr_ProductsArray->count == ptr_ProductsArray->size) {
        expandProductsArray(ptr_ProductsArray);
    }

    if (readProduct(ptr_MaterialsArray, ptr_ProductsArray, ptr_ProductsArray->count) != 1) {
        return 0;
    }

    ptr_ProductsArray->count++;

    return 1;
}

int removeProduct(ProductsArray *ptr_ProductsArray, const char code[]) {
    int position = -1;

    if (ptr_ProductsArray == NULL) {
        printf("O apontador do ProductsArray é NULL");
        return -1;
    }
    if (ptr_ProductsArray->count == 0) {
        printf("ProductsArray is empty.\n");
        return 0;
    }

    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].code == code) {
            position = i;
        }
    }
    if (position == -1) {
        printf("erro ao encontrar code");
        return 1;
    }

    for (int i = position; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].code == code) {
            ptr_ProductsArray->product[i].removed = 1;
            printf(INACTIVE_PRODUCT);
        } else
            printf(FAILED_OPERATION);
    }

    return 0;
}

int updateProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, char code[]) {

    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (findProductByCode(ptr_ProductsArray, code)) {
            readProduct(ptr_MaterialsArray, ptr_ProductsArray, i);
            printf(SUCESS_OPERATION);
            return 0;

        }
    }
    printf(FAILED_OPERATION);
    return 1;
}

void listProducts(ProductsArray *ptr_ProductsArray) {
    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        printProducts(&ptr_ProductsArray->product[i]);
    }
}

void printProducts(const Product *ptr_Product) {
    printf("\n----\n");
    printf("Código do Produto: %s\n", ptr_Product->code);
    printf("Nome do Produto: %s\n", ptr_Product->name);
    printf("Dimensoes do produto: %s\n", ptr_Product->dimensions);
    printf("Preço do Produto %d\n", ptr_Product->price);

    if (ptr_Product->removed == 1) {
        printf(INACTIVE_PRODUCT);
    }

    for (int j = 0; j < ptr_Product->productMaterialsArray->count; j++) {
        printf("\n----");
        printf("\nCódigo do Material: %s", ptr_Product->productMaterialsArray->materialInProduct[j].code);
        printf("\nQuantidade :%d", ptr_Product->productMaterialsArray->materialInProduct[j].quantity);
        printf("\n----");
    }
}

void productsListCanceled(ProductsArray *ptr_ProductsArray) {
    if (ptr_ProductsArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_ProductsArray->count; i++) {
        if (ptr_ProductsArray->product[i].removed == 1) {
            printProducts(&ptr_ProductsArray->product[i]);
        }
    }
}

void exportProducts(char *filename, ProductsArray *ptr_products) {
    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < ptr_products->count; i++) {
        fprintf(file, "%s;%s;%s;%d;\n",
                ptr_products->product[i].code,
                ptr_products->product[i].name,
                ptr_products->product[i].dimensions,
                ptr_products->product[i].price
        );
        for (int j = 0; j < ptr_products->product[i].productMaterialsArray->count; j++) {
            fprintf(file, "%s;%d;\n",
                    ptr_products->product[i].productMaterialsArray->materialInProduct[j].code,
                    ptr_products->product[i].productMaterialsArray->materialInProduct[j].quantity
            );
        }
    }
    fclose(file);
}
