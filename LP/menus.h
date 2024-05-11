#ifndef MENUS_H
#define MENUS_H

#include "clients.h"
#include "products.h"
#include "menus_text.h"
#include "production.h"
#include "files.h"


int menusBuilder(const char *menu_msg, const char *input_msg, int min_op, int max_op);

int mainMenu(ClientsArray *ptr_ClientsArray, MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,
             ProductMaterialsArray *ptr_ProductMaterialsArray, OrdersArray *ptr_OrdersArray,
             OrderProductsArray *ptr_OrderProductsArray);

int menuAdmin(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray,
              ProductMaterialsArray *ptr_ProductMaterialsArray, OrdersArray *ptr_OrdersArray);

int clientsManagement(ClientsArray *ptr_ClientsArray, OrdersArray *ptr_OrdersArray);

int productManagement(ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray,
                      ProductMaterialsArray *ptr_ProductMaterialsArray);

int
materialManagement(MaterialsArray *ptr_MaterialsArray);

int productionManagement(MaterialsArray *ptr_MaterialsArray, OrdersArray *ptr_OrdersArray, ProductsArray *ptr_ProductsArray);

int menuClient(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, OrdersArray *ptr_OrdersArray,
               OrderProductsArray *ptr_OrderProductsArray);

int menuOrders(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray);

int menuFiles(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray);


#endif /* MENUS_H */

