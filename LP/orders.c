#include "stdio.h"
#include "stdlib.h"
#include "orders.h"

int readOrder(OrdersArray *ptr_OrderArray, ProductsArray *ptr_ProductsArray, ClientsArray *ptr_ClientsArray, int i) {
    char option;
    int orderCode, op1;
    int clientCode;
    Date data;

    listClients(ptr_ClientsArray); //lista clientes

    do { //verifica códido cliente
        clientCode = readInteger(0, 9999, INSERT_CLIENT_CODE);

        if (findClientsByCode(ptr_ClientsArray, clientCode)) {
            printf("\nCódigo encontrado!");
            op1 = 1;
        } else {
            printf("\nInsira um cliente válido");
            op1 = 0;
        }
    } while (op1 != 1);

    srand(time(NULL));
    orderCode = rand() % 9999;

    printf("\nCódigo da encomenda: %d\n", orderCode);

    data.day = readInteger(1, 31, INSERT_ORDER_DAY);
    data.month = readInteger(1, 12, INSERT_ORDER_MONTH);
    data.year = readInteger(2000, 2099, INSERT_ORDER_YEAR);

    if (data.month == 1 || data.month == 3 || data.month == 5 ||
            data.month == 7 || data.month == 8 || data.month == 10 || data.month == 12) {
        if (data.day > 31) {
            data.month++;
            data.day -= 31;
        }
    } else {
        if (data.day > 30) {
            data.month++;
            data.day -= 30;
        }
    }

    if (data.day > 28 && data.month == 2) {
        data.day -= 28;
        data.month++;
    }

    if (data.month > 12) {
        data.month = 1;
        data.year++;
    }

    ptr_OrderArray->order[i].clientCode = clientCode;
    ptr_OrderArray->order[i].orderCode = orderCode;
    ptr_OrderArray->order[i].deliveryDate.day = data.day;
    ptr_OrderArray->order[i].deliveryDate.month = data.month;
    ptr_OrderArray->order[i].deliveryDate.year = data.year;

    addProductToOrder(ptr_OrderArray, ptr_ProductsArray, i);

    do {
        printf("\nDeseja inserir outro produto à sua encomenda? Y/N:  ");
        scanf(" %c", &option);
        switch (option) {
            case 'Y':
            case 'y':
                addProductToOrder(ptr_OrderArray, ptr_ProductsArray, i);
                break;
            case 'N':
            case 'n':
                break;
            default:
                printf("Insira uma opcao válida!!");

        }
    } while (option != ('n' | 'N'));

    ptr_OrderArray->count++;

    return 0;
}

void expandOrdersArray(OrdersArray *ptr_OrdersArray) {
    int new_order_size;

    new_order_size = ptr_OrdersArray->size * 2;

    ptr_OrdersArray->order = (Order *) realloc(ptr_OrdersArray->order, new_order_size * sizeof (Order));
    if (ptr_OrdersArray->order == NULL) {
        perror("Not allocated\n");
        exit(EXIT_FAILURE);
    }

    ptr_OrdersArray->size = new_order_size;

    for (int i = ptr_OrdersArray->count; i < new_order_size; i++) {
        ///fazer realloc para as o array de produtos da encomenda
        ptr_OrdersArray->order[i].orderProductsArray = (OrderProductsArray *)
                realloc(ptr_OrdersArray->order[i].orderProductsArray, new_order_size * sizeof (OrderProductsArray));
        if (ptr_OrdersArray->order[i].orderProductsArray == NULL) {
            perror("Not allocated\n");
            exit(EXIT_FAILURE);
        }
    }
}

OrdersArray *allocMemoryOrders(int size) {

    OrdersArray *ptr_OrdersArray = (OrdersArray *) malloc(sizeof (OrdersArray));
    if (ptr_OrdersArray == NULL) {
        return NULL;
    }

    ptr_OrdersArray->count = 0;
    ptr_OrdersArray->size = size;

    ptr_OrdersArray->order = (Order *) calloc(ptr_OrdersArray->size, sizeof (Order));
    if (ptr_OrdersArray->order == NULL) {
        return NULL;
    }

    for (int i = 0; i < ptr_OrdersArray->size; i++) {
        ptr_OrdersArray->order[i].orderProductsArray = allocMemoryOrderProducts(size);
        if (ptr_OrdersArray->order[i].orderProductsArray == NULL) {
            return NULL;
        }
    }
    return ptr_OrdersArray;
}

void freeMemoryOrders(OrdersArray *ptr_OrdersArray) {
    for (int i = 0; i < ptr_OrdersArray->size; i++) {
        free(ptr_OrdersArray->order[i].orderProductsArray);
    }
    free(ptr_OrdersArray->order);
    free(ptr_OrdersArray);
}

int addOrder(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray) {

    // Check if the OrdersArray field is null
    if (ptr_OrdersArray == NULL) {
        // Return 1 if it is
        return 1;
    }

    //verifica se o contador do array de produtos nas orders chega ao seu tamanho máximo
    if (ptr_OrdersArray->count == ptr_OrdersArray->size) {
        // Expande o tamanho do array e aloca mais memória para novos produtos
        expandOrdersArray(ptr_OrdersArray);
    }

    // Lê os produtos e adiciona ao array
    readOrder(ptr_OrdersArray, ptr_ProductsArray, ptr_ClientsArray, ptr_OrdersArray->count);

    //Incrementa o campo de contagem da estrutura productMaterialsArray para controlar o número de materiais no array
    ptr_OrdersArray->count++;

    // Retorna 0 para indicar que a operação foi bem sucedida
    return 0;
}

int ordersListByClient(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Sem encomendas para listar");
        return 1;
    }

    int code = readInteger(0, 9999, INSERT_CLIENT_CODE);

    for (int i = 0; i < ptr_ClientsArray->count; i++) {
        if (ptr_ClientsArray->client[i].code == code) {
            printf(CODE_FOUND);
            for (int j = 0; j < ptr_OrdersArray->count; j++) {
                if (ptr_OrdersArray->order[i].clientCode == code) {
                    printOrder(&ptr_OrdersArray->order[i]);
                    return 0;
                }
            }
        }
    }
    printf(CLIENT_NOT_FOUND);
    return 1;
}

void ordersList(OrdersArray *ptr_OrdersArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        printOrder(&ptr_OrdersArray->order[i]);

    }
}

void printOrder(Order *ptr_Order) {
    printf("\n----\n");
    printf("Código do cliente: %d\n", ptr_Order->clientCode);
    printf("Código da encomenda: %d\n", ptr_Order->orderCode);
    printf("Valor da encomenda: %d\n", ptr_Order->orderTotal);
    printf("Data de entrega: %d-%d-%d\n",
            ptr_Order->deliveryDate.day,
            ptr_Order->deliveryDate.month,
            ptr_Order->deliveryDate.year
            );
    if (ptr_Order->canceled == 1) {
        printf(CANCELED_ORDER);
    }

    for (int i = 0; i < ptr_Order->orderProductsArray->count; i++) {
        printf("\n----");
        printf("\nCódigo do Produto: %s", ptr_Order->orderProductsArray->productInOrder[i].code);
        printf("\nQuantidade :%d", ptr_Order->orderProductsArray->productInOrder[i].quantity);
        printf("\nTotal do produto: %d", ptr_Order->orderProductsArray->productInOrder[i].productTotal);
        printf("\n----");

    }
}

int cancelOrder(OrdersArray *ptr_OrdersArray) {

    int code = readInteger(0, 9999, INSERT_ORDER_CODE);
    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->order[i].orderCode == code) {
            ptr_OrdersArray->order[i].canceled = 1;
            printf(SUCESS_OPERATION);
        }
    }
    return 0;
}

void ordersListCanceled(OrdersArray *ptr_OrdersArray) {

    if (ptr_OrdersArray->count == 0) {
        printf("Vazio\n");
        return;
    }

    for (int i = 0; i < ptr_OrdersArray->count; i++) {
        if (ptr_OrdersArray->order[i].canceled == 1) {
            printOrder(&ptr_OrdersArray->order[i]);
        }
    }
}

int removeClientToCanceled(ClientsArray *ptr_clientsArray, OrdersArray *ptr_OrdersArray, int clientCode) {
    if (ptr_clientsArray == NULL) {
        printf("ClientsArray pointer is NULL.\n");
        return -1;
    }

    if (ptr_clientsArray->count == 0) {
        printf("ClientsArray is empty.\n");
        return 0;
    }

    for (int i = 0; i < ptr_OrdersArray->count; i++) {

        if (ptr_OrdersArray->order[i].clientCode ==
                clientCode) {//se encontrar o código do cliente numa encomenda faz :
            for (int j = 0; i < ptr_clientsArray->count; j++) {
                if (ptr_clientsArray->client[j].code == clientCode) {
                    ptr_clientsArray->client[j].removed = 1;
                    printf("Cliente Inativo");
                    return 0;
                }
            }
        } else
            printf("Cliente não tem encomendas");
    }
    //caso não encontreo cliente nas encomendas remove definitivamente o cliente do programa
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->client[i].code == clientCode) {
            // ajusta clientes para preencher espaço vazio
            for (int j = i; j < ptr_clientsArray->count - 1; j++) {
                ptr_clientsArray->client[j] = ptr_clientsArray->client[j + 1];
            }
            ptr_clientsArray->count--;
            printf("\nRemovido com sucesso\n");
            return 0;
        } else {
            printf("\nNão encontrado!\n");
        }
    }
    return 1;
}

void exportOrdersTxt(OrdersArray *ordersArray) {

    FILE *file;
    int size = 10;
    char *str = calloc(size, sizeof (char));

    readString(str, size, FILE_NAME);

    file = fopen(str, "w");
    if (file == NULL) {
        fprintf(stderr, "Não foi possível criar o ficheiro");
        fclose(file);
        return;
    }

    for (int i = 0; i < ordersArray->count; i++) {
        fprintf(file, "Codigo: %d;Cliente: %d;Data de entrega: %d/%d/%d;Order total:%d;\n",
                ordersArray->order[i].orderCode,
                ordersArray->order[i].clientCode,
                ordersArray->order[i].deliveryDate.day,
                ordersArray->order[i].deliveryDate.month,
                ordersArray->order[i].deliveryDate.year,
                ordersArray->order[i].orderTotal
                );
        for (int j = 0; j < ordersArray->order[i].orderProductsArray->count; j++) {
            fprintf(file, "%s;%d;%d\n",
                    ordersArray->order[i].orderProductsArray->productInOrder[j].code,
                    ordersArray->order[i].orderProductsArray->productInOrder[j].quantity,
                    ordersArray->order[i].orderProductsArray->productInOrder[j].productTotal
                    );
        }
    }


    fclose(file);
}