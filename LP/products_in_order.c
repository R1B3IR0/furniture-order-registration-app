#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "products_in_order.h"

int readProductToOrder(OrdersArray *ptr_OrderArray, ProductsArray *ptr_ProductsArray, int i) {

    char productCode[7]; //Produto
    int productQuantity; //Quantidade de Produtos
    int itemCost = 0; //custo do artigo
    int j;

    listProducts(ptr_ProductsArray); //listagem de todos os produtos

    cleanBuffer();

    readString(productCode, 7, INSERT_PRODUCT_CODE);

    for (j = 0; j < ptr_ProductsArray->count; j++) {
        if (strcmp(ptr_ProductsArray->product[j].code, productCode) == 0) {
            printf(CODE_FOUND);

            productQuantity = readInteger(1, 1000, INSERT_QUANTITY_SIZE); //Insira a quantidade do Produto

            itemCost = ptr_ProductsArray->product[j].price * productQuantity;
            ptr_OrderArray->order[j].orderProductsArray->productInOrder[i].productTotal = itemCost;

            strcpy(ptr_OrderArray->order->orderProductsArray->productInOrder[i].code, productCode);
            ptr_OrderArray->order->orderProductsArray->productInOrder[i].quantity = productQuantity;
            ptr_OrderArray->order[j].orderTotal += ptr_OrderArray->order->orderProductsArray->productInOrder[i].productTotal;

            printf("Numero de artigos: %d\n", productQuantity);
            printf("Custo total do artigo: %d\n",
                    ptr_OrderArray->order[j].orderProductsArray->productInOrder[i].productTotal);
            printf("Custo total da encomenda: %d\n", ptr_OrderArray->order[j].orderTotal);
        } else
            return 1;

    }

    ptr_OrderArray->order->orderProductsArray->count++;

    return 0;
}
void expandOrderProductArray(OrdersArray *ptr_OrdersArray) {

    ptr_OrdersArray->order->orderProductsArray->size *= 2;

    ptr_OrdersArray->order->orderProductsArray = (OrderProductsArray *)
            realloc(ptr_OrdersArray->order->orderProductsArray,
                    ptr_OrdersArray->order->orderProductsArray->size * sizeof(ProductMaterialsArray));

    if (ptr_OrdersArray->order->orderProductsArray == NULL) {
        perror("Not allocated112\n");
        exit(EXIT_FAILURE);
    }

    for (int j = ptr_OrdersArray->order->orderProductsArray->count;
         j < ptr_OrdersArray->order->orderProductsArray->size; j++) {
        strcpy(ptr_OrdersArray->order->orderProductsArray[j].productInOrder->code, "");
        ptr_OrdersArray->order->orderProductsArray[j].productInOrder->productTotal = 0.0f;
        ptr_OrdersArray->order->orderProductsArray[j].productInOrder->quantity = 0;
    }
}

int addProductToOrder(OrdersArray *ptr_OrdersArray, ProductsArray *ptr_ProductsArray, int i) {
    // Check if the materialInProduct field is null
    if (ptr_OrdersArray->order[i].orderProductsArray == NULL) {
        // Return 0 if it is
        return 0;
    }

    //verifica se o contador do array de produtos nas orders chega ao seu tamanho máximo
    if (ptr_OrdersArray->order[i].orderProductsArray->count == ptr_OrdersArray->order[i].orderProductsArray->size) {
        // Expande o tamanho do array e aloca mais memória para novos produtos
        expandOrderProductArray(ptr_OrdersArray);
    }

    // Lê os produtos e adiciona ao array
    if (readProductToOrder(ptr_OrdersArray, ptr_ProductsArray, ptr_OrdersArray->order[i].orderProductsArray->count) !=
        1) {
    }

    /*Incrementa o campo de contagem da estrutura productMaterialsArray para controlar o número de materiais no array*/
    ptr_OrdersArray->order->orderProductsArray->count++;

    // Retorna 1 para indicar que a operação foi bem sucedida
    return 1;
}

OrderProductsArray *allocMemoryOrderProducts(int size) {

    OrderProductsArray *ptr_ProductOrderArray = (OrderProductsArray *)
            malloc(sizeof(OrderProductsArray));
    if (ptr_ProductOrderArray == NULL) {
        return NULL;
    }

    ptr_ProductOrderArray->count = 0;
    ptr_ProductOrderArray->size = size;

    ptr_ProductOrderArray->productInOrder = (ProductInOrder *)
            calloc(ptr_ProductOrderArray->size, sizeof(ProductInOrder));
    if (ptr_ProductOrderArray->productInOrder == NULL) {
        return NULL;
    }

    return ptr_ProductOrderArray;
}

void freeMemoryOrderProducts(OrderProductsArray *ptr_OrderProductsArray) {
    free(ptr_OrderProductsArray->productInOrder);
    free(ptr_OrderProductsArray);
}

