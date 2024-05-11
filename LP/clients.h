#ifndef CLIENTS_H
#define CLIENTS_H

#include "utilities.h"

typedef struct {
    int code;
    char name[256];
    char address[256];
    int nif;
    char country[64];
    int removed;
} Client;

typedef struct {
    Client *client;
    int count;  // Representa o espaço total ocupado e a posição livre
    int size;   // Tamanho total do array
} ClientsArray;

/**
 * Procura cliente através do seu NIF.
 * @return o cliente com o NIF procurado.
 */
int findNif(ClientsArray *ptr_clientsArray, int nif);

/**
* Função utilizada usa o código inserido pelo utilizador para encontrar
* um cliente e verifica se ele existe dentro do array dos cliente.
* @param clientsArray
* @param code
* @return 1 se encontrado com sucesso, caso-contrário 0.
*/
int findClientsByCode(ClientsArray *ptr_clientsArray, int code);

 /** Aloca memória para o array de clientes.
 * @return um array de clientes.
 */
ClientsArray *allocMemoryClients(int size);

int expandClientsArray(ClientsArray *ptr_clientsArray);

/**
 * Função para libertar a memória do array de clientes.
 * @param ptr_clientsArray
 */
void freeMemoryClients(ClientsArray *ptr_clientsArray);

/**
 * Adiciona um novo cliente ao array.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addClients(ClientsArray *ptr_clientsArray);


/**
 * Procura o cliente pelo seu código e atualiza-o.
 * @param code código do cliente.
 * @return 1 se encontrado e atualizado, caso-contrário 0.
 */
int updateClient(ClientsArray *ptr_clientsArray, int code);

/**
 * Função utilizada para imprimir toda a informação de um cliente.
 * @param ptr_client
 */
void printClientInfo(const Client *ptr_client);


/**
 * Itera o array de clientes.
 * @param ptr_ClientsArray
 */
void listClients(ClientsArray *ptr_ClientsArray);

/**
 * Exporta para um ficheiro de texto a lista das encomendas
 * @param ordersArray
 */
void exportClientsTxt(ClientsArray *ptr_ClientsArray);
#endif /* CLIENTS_H */

