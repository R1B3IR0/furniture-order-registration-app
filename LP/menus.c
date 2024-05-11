#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

int menusBuilder(const char *menu_msg, const char *input_msg, int min_op, int max_op) {
    int op;

    printf("%s", menu_msg);
    op = readInteger(min_op, max_op, input_msg);

    return op;
}

int menuAdmin(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray,
        ProductMaterialsArray *ptr_ProductMaterialsArray, OrdersArray *ptr_OrdersArray) {
    int op;

    do {
        op = menusBuilder(MENU_ADMIN, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                return 0;
            case 1:
                clientsManagement(ptr_ClientsArray, ptr_OrdersArray);
                break;
            case 2:
                productManagement(ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray);
                break;
            case 3:
                materialManagement(ptr_MaterialsArray);
                break;
            case 4:
                productionManagement(ptr_MaterialsArray, ptr_OrdersArray, ptr_ProductsArray);
                break;
            case 5:
                menuOrders(ptr_OrdersArray, ptr_ClientsArray);
                break;
            case 6:
                menuFiles(ptr_MaterialsArray, ptr_ProductsArray, ptr_OrdersArray, ptr_ClientsArray);
                break;
            default:
                break;
        }

    } while (op != 0);
}

int clientsManagement(ClientsArray *ptr_ClientsArray, OrdersArray *ptr_OrdersArray) {
    int op;


    do {
        op = menusBuilder(MENU_CLIENT_MANAGEMENT, INSERT_OPTION, 0, 4);
        switch (op) {
            case 0:
                return 0;
            case 1:
                addClients(ptr_ClientsArray);
                break;
            case 2:
                updateClient(ptr_ClientsArray, readInteger(0, 9999, INSERT_CLIENT_CODE));
                break;
            case 3:
                removeClientToCanceled(ptr_ClientsArray, ptr_OrdersArray, readInteger(0, 9999, INSERT_CLIENT_CODE));
                break;
            case 4:
                listClients(ptr_ClientsArray);
                break;
            default:
                break;
        }
    } while (op != 0);
}

int productManagement(ProductsArray *ptr_ProductsArray, MaterialsArray *ptr_MaterialsArray,
        ProductMaterialsArray *ptr_ProductMaterialsArray) {
    int op;
    char *code = ptr_ProductsArray->product->code;

    do {
        op = menusBuilder(MENU_PRODUCT_MANAGEMENT, INSERT_OPTION, 0, 6);
        switch (op) {
            case 0:
                return 0;
            case 1:
                addProduct(ptr_MaterialsArray, ptr_ProductsArray);
                break;
            case 2:
                readString(code, 6, INSERT_PRODUCT_CODE);
                updateProduct(ptr_MaterialsArray, ptr_ProductsArray, code);

                break;
            case 3:
                readString(code, 6, INSERT_PRODUCT_CODE);
                removeProduct(ptr_ProductsArray, code);
                break;
            case 4:
                listProducts(ptr_ProductsArray);
                break;
            case 5:
                productsListCanceled(ptr_ProductsArray);
                break;
            case 6:
                exportProducts(CSVP, ptr_ProductsArray);
            default:
                break;
        }
    } while (op != 0);
}

int materialManagement(MaterialsArray *ptr_MaterialsArray) {
    int op;

    do {
        op = menusBuilder(MENU_MATERIAL_MANAGEMENT, INSERT_OPTION, 0, 5);
        switch (op) {
            case 0:
                return 0;
            case 1:
                addMaterial(ptr_MaterialsArray);
                break;
            case 2:
                updateMaterial(ptr_MaterialsArray);
                break;
            case 3:
                removeMaterial(ptr_MaterialsArray);
            case 4:
                listMaterials(ptr_MaterialsArray);
                break;
            case 5:
                exportMaterials(CSVM, ptr_MaterialsArray);
            default:
                break;

        }

    } while (op != 0);
}

int productionManagement(MaterialsArray *ptr_MaterialsArray, OrdersArray *ptr_OrdersArray, ProductsArray *ptr_ProductsArray) {
    int op;
    do {
        op = menusBuilder(MENU_PRODUCTION_MANAGEMENT, INSERT_OPTION, 0, 1);
        switch (op) {
            case 0:
                return 0;
            case 1:
                getOrdersByDate(ptr_OrdersArray, ptr_ProductsArray);
                break;
            default:
                break;
        }
    } while (op != 0);


}

int menuClient(ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray, OrdersArray *ptr_OrdersArray,
        OrderProductsArray *ptr_OrderProductsArray) {
    int op;

    do {
        op = menusBuilder(MENU_CLIENT, INSERT_OPTION, 0, 2);
        switch (op) {
            case 0:
                return 0;
            case 1:
                addOrder(ptr_OrdersArray, ptr_ClientsArray, ptr_ProductsArray);
                break;
            case 2:
                exportOrdersTxt(ptr_OrdersArray);
            default:
                break;
        }
    } while (op != 0);

}

int mainMenu(ClientsArray *ptr_ClientsArray, MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray,
        ProductMaterialsArray *ptr_ProductMaterialsArray, OrdersArray *ptr_OrdersArray,
        OrderProductsArray *ptr_OrderProductsArray) {
    int op;

    do {
        op = menusBuilder(MAIN_MENU, INSERT_PROFILE, 0, 2);
        switch (op) {
            case 0:
                return (EXIT_SUCCESS);
            case 1:
                menuAdmin(ptr_ClientsArray, ptr_ProductsArray, ptr_MaterialsArray, ptr_ProductMaterialsArray,
                        ptr_OrdersArray);
                break;
            case 2:
                menuClient(ptr_ClientsArray, ptr_ProductsArray, ptr_OrdersArray, ptr_OrderProductsArray);
                break;
            default:
                break;
        }

    } while (op != 0);

}

int menuOrders(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray) {
    int op;
    do {
        op = menusBuilder(MENU_ORDERS, INSERT_OPTION, 0, 3);
        switch (op) {
            case 0:
                return 0;
            case 1:
                ordersList(ptr_OrdersArray);
                break;
            case 2:
                ordersListByClient(ptr_OrdersArray, ptr_ClientsArray);
                break;
            case 3:
                ordersListCanceled(ptr_OrdersArray);
                break;
            case 4:
                cancelOrder(ptr_OrdersArray);
            default:
                break;
        }
    } while (op != 0);
}

int menuFiles(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, OrdersArray *ptr_OrdersArray,
        ClientsArray *ptr_ClientsArray) {

    int op;
    do {
        op = menusBuilder(MENU_FILES, INSERT_OPTION, 0, 4);
        switch (op) {
            case 0:
                return 0;
            case 1:
                importMaterials(CSVM);
                break;
            case 2:
                importProducts(CSVP);
                break;
            case 3:
                exportMaterials(CSVM, ptr_MaterialsArray);
                break;
            case 4:
                exportProducts(CSVP, ptr_ProductsArray);
            case 5:
                exportOrdersTxt(ptr_OrdersArray);
                break;
            case 6:
                exportClientsTxt(ptr_ClientsArray);
            default:
                break;
        }
    } while (op != 0);
}
