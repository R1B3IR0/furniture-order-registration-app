#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "orders.h"

/**
 * Obtém os materiais necessários para a produção de uma dada semana.
 * @param ptr_OrdersArray, products
 */
void getOrdersByDate(OrdersArray *OrderArray, ProductsArray *products);


#endif /* PRODUCTION_H */

