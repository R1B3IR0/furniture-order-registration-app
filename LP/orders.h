
#ifndef ORDER_H
#define ORDER_H

#include "time.h"
#include "clients.h"
#include "products.h"

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char code[6];   //Codigo do Produto
    int quantity;   //Quantidade de Produtos a encomendar
    int productTotal;
} ProductInOrder;

typedef struct {
    ProductInOrder *productInOrder;
    int size;
    int count;
} OrderProductsArray;  //Lista de Produtos numa encomenda

typedef struct {
    int clientCode;
    int orderCode;
    OrderProductsArray *orderProductsArray;
    Date deliveryDate;
    int orderTotal;
    int canceled;
} Order;

typedef struct {
    Order *order;
    int size;
    int count;
} OrdersArray;

/**
 *Função utilizada para  ler as informações de um produto de uma encomenda.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readProductToOrder(OrdersArray *ptr_OrderArray, ProductsArray *ptr_ProductsArray,int i);

/**
 * Expande a alocação memória para o array de produtos de uma encomenda.
 *
 */
void expandOrderProductArray(OrdersArray *ptr_OrdersArray);

/**
 * Adiciona produtos a uma encomenda.
 *
 */
int addProductToOrder(OrdersArray *ptr_OrdersArray, ProductsArray *ptr_ProductsArray, int i);

/**
 *Função utilizada para  ler as informações de uma encomenda.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readOrder(OrdersArray *ptr_OrderArray, ProductsArray *ptr_ProductsArray, ClientsArray *ptr_ClientsArray, int i);

/**
 * Expande a alocação memória para o array de encomendas.
 *
 */
void expandOrdersArray(OrdersArray *ptr_OrdersArray);

/**
 * Alloca memória para o array de produtos de uma encomenda.
 */
OrderProductsArray *allocMemoryOrderProducts(int size);

/**
 * Alloca memória para o array de encomendas.
 */
OrdersArray *allocMemoryOrders(int size);

/**
* Função para libertar a memória do array de produtos de uma encomenda.
* @param ptr_OrdersArray
*/
void freeMemoryOrderProducts(OrderProductsArray *ptr_OrderProductsArray);

/**
 * Função para libertar a memória do array de encomendas.
 * @param ptr_OrdersArray
 */
void freeMemoryOrders(OrdersArray *ptr_OrdersArray);

/**
 * Adiciona uma encomenda ao array.
 * @param orders_arr
 * @param clients_arr
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addOrder(OrdersArray *ptr_OrdersArray, ClientsArray *ptr_ClientsArray, ProductsArray *ptr_ProductsArray);

/**
 * A função pede ao utilizador o código da encomenda, percorre o array para procurar a encomenda
 * com esse código e remove.
 * @param ptr_OrdersArray
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int cancelOrder(OrdersArray *ptr_OrdersArray);

/**
 * Função utilizada para imprimir toda a informação de uma encomenda.
 * @param ptr_Order
 */
void printOrder(Order *ptr_Order);

/**
 * A função pede o código ao utilizador e mostra as encomendas
 * do utilizador com aquele código.
 * @param ptr_OrdersArray
 */
int ordersListByClient(OrdersArray *ptr_OrdersArray, ClientsArray *ClientArray);

/**
 *  * A função permite ao admin listar todas as encomendas existentes.
 * @param orders_arr
 */
void ordersList(OrdersArray *ptr_OrdersArray);

/**
 * A função permite ao admin listar todas as encomendas canceladas.
 * @param ptr_OrdersArray
 */
void ordersListCanceled(OrdersArray *ptr_OrdersArray);

/**
 * Procura o cliente pelo seu código e marca-o como removido se tiver encomendas,
 * caso contrario remove definitivamente.
 * @param clientCode ,ptr_clientsArray,ptr_OrdersArray
 * @return 1 se encontrado e marcado como removido, caso-contrário 0.
 */
int removeClientToCanceled(ClientsArray *ptr_clientsArray, OrdersArray *ptr_OrdersArray, int clientCode);


/**
 * Exporta para um ficheiro de texto a lista das encomendas
 * @param ordersArray
 */
void exportOrdersTxt(OrdersArray *ordersArray);


#endif /* ORDER_H */

