#include "menus.h"


int main() {
    ClientsArray *ptr_ClientsArray = NULL;
    ProductsArray *ptr_ProductsArray = NULL;
    MaterialsArray *ptr_MaterialsArray = NULL;
    OrdersArray *ptr_OrdersArray = NULL;
    ProductMaterialsArray *ptr_ProductMaterialsArray = NULL;
    OrderProductsArray *ptr_OrderProductsArray = NULL;


    ptr_ClientsArray = (ClientsArray *) allocMemoryClients(50);
    if (ptr_ClientsArray == NULL) {
        free(ptr_ClientsArray);
        perror("Clients Exited\n");
        return 1;
    }

    ptr_OrdersArray = (OrdersArray *) allocMemoryOrders(50);
    if (ptr_OrdersArray == NULL) {
        free(ptr_ProductsArray);
        free(ptr_ClientsArray);
        free(ptr_OrdersArray);
        free(ptr_ProductMaterialsArray);
        perror("Orders Exited");
        return 1;
    }

    ptr_OrderProductsArray = (OrderProductsArray *) allocMemoryOrderProducts(50);
    if (ptr_OrderProductsArray == NULL) {
        free(ptr_OrderProductsArray);
        free(ptr_OrdersArray);
        perror("Order Products Exit\n");

    }

    ptr_ProductMaterialsArray = (ProductMaterialsArray *) allocMemoryProductMaterials(50);
    if (ptr_ProductMaterialsArray == NULL) {
        free(ptr_ProductMaterialsArray);
        free(ptr_MaterialsArray);
        free(ptr_ProductsArray);
        perror("Products Exit\n");
        return 1;
    }
/*
  ptr_MaterialsArray = (MaterialsArray *) allocMemoryMaterials(50);
    if (ptr_MaterialsArray == NULL) {
        free(ptr_MaterialsArray);
        perror("Materials Exited");
        return 1;
    }
*/
   /* ptr_ProductsArray = (ProductsArray *) allocMemoryProducts(50);
    if (ptr_ProductsArray == NULL) {
        free(ptr_ProductsArray);
        free(ptr_MaterialsArray);
        free(ptr_ProductMaterialsArray);
        perror("Products Exit\n");
        return 1;
    }*/
    ptr_ProductsArray = importProducts(CSVP);

   ptr_MaterialsArray= importMaterials(CSVM);


    mainMenu(ptr_ClientsArray, ptr_MaterialsArray, ptr_ProductsArray, ptr_ProductMaterialsArray, ptr_OrdersArray,
             ptr_OrderProductsArray);


    //Libertação de memória
    freeMemoryClients(ptr_ClientsArray);
    freeMemoryProducts(ptr_ProductsArray);
    freeMemoryProductMaterials(ptr_ProductMaterialsArray);
    freeMemoryMaterials(ptr_MaterialsArray);
    freeMemoryOrders(ptr_OrdersArray);
    freeMemoryOrderProducts(ptr_OrderProductsArray);

    return 0;
}