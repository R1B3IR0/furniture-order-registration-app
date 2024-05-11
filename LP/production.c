#include "production.h"
#include "stdio.h"
#include "string.h"

void getOrdersByDate(OrdersArray *OrderArray, ProductsArray *products) {
    int day, month, year;
    int newDay, newMonth, newYear;
    OrdersArray *order;
    int pQuantity;
    char pCode[7];

    day = readInteger(1, 31, INSERT_ORDER_DAY);
    month = readInteger(1, 12, INSERT_ORDER_MONTH);
    year = readInteger(2020, 3000, INSERT_ORDER_YEAR);

    newDay = day;
    newMonth = month;
    newYear = year;
    do {


        if (newMonth == 1 || newMonth == 3 || newMonth == 5 || newMonth == 7 || newMonth == 8 || newMonth == 10 ||
                newMonth == 12) {
            if (newDay > 31) {
                newMonth++;
                newDay = newDay - 31;
            }
        } else if (newMonth == 2) {
            if (newDay > 28) {
                newMonth++;
                newDay = newDay - 28;
            }
        } else {
            if (newDay > 30) {
                newMonth++;
                newDay = newDay - 30;
            }
        }

        if (newMonth > 12) {
            newMonth = 1;
            newYear++;
        }

        for (int i = 0; i < OrderArray->count; i++) {
            if (OrderArray->order[i].deliveryDate.day == newDay &&
                    OrderArray->order[i].deliveryDate.month == newMonth &&
                    OrderArray->order[i].deliveryDate.year == newYear) {
                order->order[order->count] = OrderArray->order[i];
                order->count++;
            }
        }
        newDay++;
    } while (newDay - 7 <= day);


    for (int i = 0; i < order->count; i++) {
        for (int j = 0; j < order->order->orderProductsArray->count; j++) {
            pQuantity = order->order[i].orderProductsArray->productInOrder[j].quantity;
            strcpy(pCode, order->order[i].orderProductsArray->productInOrder[j].code);
            for (int k = 0; k < products->count; k++) {
                if (strcmp(pCode, products->product[k].code) == 0) {
                    for (int l = 0; l < products->product[k].productMaterialsArray->count; l++) {
                        printf("Material: %s\t Quantidade: %d\n",
                                products->product[k].productMaterialsArray->materialInProduct[l].code,
                                products->product[k].productMaterialsArray->materialInProduct[l].quantity * pQuantity);
                    }
                }

            }
        }
    }
}
