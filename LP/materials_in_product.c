#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"
#include "materials_in_product.h"

int readMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i, int j) {
    int quantity;
    int h;
    //reuse memory
    char code[64];

    //Listar Materiais
    listMaterials(ptr_MaterialsArray);
    cleanBuffer();
    readString(code, 64, INSERT_MATERIAL_CODE); // Inserir codigo Material;
    for (h = 0; h < ptr_MaterialsArray->count; h++) {
        if (strcmp(ptr_MaterialsArray->material[h].code, code) == 0) {
        }
    }

    quantity = readInteger(0, 9999, INSERT_QUANTITY_SIZE); //Insere quantidade;

    strcpy(ptr_ProductsArray->product[j].productMaterialsArray->materialInProduct[i].code, code);
    ptr_ProductsArray->product[j].productMaterialsArray->materialInProduct[i].quantity = quantity;

    return 1;
}

int addMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i) {
    // Check if the materialInProduct field is null
    if (ptr_ProductsArray->product[i].productMaterialsArray == NULL) {
        // Return 0 if it is
        return 0;
    }

    // Check if the count of material reaches the size of the array
    if (ptr_ProductsArray->product[i].productMaterialsArray->count ==
            ptr_ProductsArray->product[i].productMaterialsArray->size) {
        // Expand the size of the array and allocate more memory for new material
        expandProductMaterialsArray(ptr_ProductsArray);
    }

    // Read the material from some input source and add them to the array
    if (readMaterialsToProduct(ptr_MaterialsArray, ptr_ProductsArray,
            ptr_ProductsArray->product[i].productMaterialsArray->count, i) != 1) {
        return 0;
    }

    // Increment the count field of the productMaterialsArray struct to keep track of the number of material in the array
    ptr_ProductsArray->product[i].productMaterialsArray->count++;

    // Return 1 to indicate that the operation was successful
    return 1;
}

void expandProductMaterialsArray(ProductsArray *ptr_ProductsArray) {
    int new_size;

    new_size = ptr_ProductsArray->product->productMaterialsArray->size * 2;

    ptr_ProductsArray->product->productMaterialsArray->materialInProduct = (MaterialInProduct *)
            realloc(ptr_ProductsArray->product->productMaterialsArray->materialInProduct,
            new_size * sizeof (MaterialInProduct));

    if (ptr_ProductsArray->product->productMaterialsArray->materialInProduct == NULL) {
        printf("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_ProductsArray->product->productMaterialsArray->size = new_size;

    for (int i = ptr_ProductsArray->product->productMaterialsArray->count; i < new_size; i++) {
        ptr_ProductsArray->product->productMaterialsArray->materialInProduct[i].quantity = 0;
    }
}

ProductMaterialsArray *allocMemoryProductMaterials(int size) {

    ProductMaterialsArray *ptr_ProductMaterialsArray = (ProductMaterialsArray *)
            malloc(sizeof (ProductMaterialsArray));
    if (ptr_ProductMaterialsArray == NULL) {
        return NULL;
    }

    ptr_ProductMaterialsArray->count = 0;
    ptr_ProductMaterialsArray->size = size;

    ptr_ProductMaterialsArray->materialInProduct = (MaterialInProduct *)
            calloc(ptr_ProductMaterialsArray->size, sizeof (MaterialInProduct));

    if (ptr_ProductMaterialsArray->materialInProduct == NULL) {
        return NULL;
    }

    return ptr_ProductMaterialsArray;
}

void freeMemoryProductMaterials(ProductMaterialsArray *ptr_ProductMaterialsArray) {
    free(ptr_ProductMaterialsArray->materialInProduct);
    free(ptr_ProductMaterialsArray);
}
