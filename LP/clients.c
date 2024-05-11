#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "clients.h"

int findClientsByCode(ClientsArray *ptr_clientsArray, int code) {
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->client[i].code == code) {
            return 1;
        }
    }

    return 0;
}

int findNif(ClientsArray *ptr_clientsArray, int nif) {
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->client[i].nif == nif) {
            return 1;
        }
    }
    return 0;
}

int readClientInfo(ClientsArray *ptr_clientsArray, int i) {
    int nif;
    int code;
    //reuse memory
    char name[256];
    char country[64];
    char address[256];

    code = readInteger(0, 9999, INSERT_CLIENT_CODE);
    if (code < 0) {
        printf("Failed to read code for new Client.\n");
        return -1;
    }

    if (findClientsByCode(ptr_clientsArray, code)) {
        printf(CODE_EXISTS"\n");
        return 0;
    }

    readString(name, 256, INSERT_CLIENT_NAME"\n");

    nif = readInteger(99999999, 999999999, INSERT_CLIENT_NIF"\n");
    if (findNif(ptr_clientsArray, nif)) {
        printf(NIF_EXISTS"\n");
        return 0;
    }
    readString(address, 256, INSERT_CLIENT_ADDRESS"\n");
    readString(country, 64, INSERT_CLIENT_COUNTRY);

    strcpy(ptr_clientsArray->client[i].name, name);
    strcpy(ptr_clientsArray->client[i].country, country);
    strcpy(ptr_clientsArray->client[i].address, address);
    ptr_clientsArray->client[i].nif = nif;
    ptr_clientsArray->client[i].code = code;


    return 1;
}

int expandClientsArray(ClientsArray *ptr_clientsArray) {
    int new_size;

    new_size = ptr_clientsArray->size * 2;

    ptr_clientsArray->client = (Client *) realloc(ptr_clientsArray->client, new_size * sizeof(Client));
    if (ptr_clientsArray->client == NULL) {
        printf("Memory allocation failed!");
        return 0;
    }

    ptr_clientsArray->size = new_size;

    for (int i = ptr_clientsArray->count; i < ptr_clientsArray->size; i++) {
        strcpy(ptr_clientsArray->client[i].name, (char *) calloc(256, sizeof(char)));
        strcpy(ptr_clientsArray->client[i].address, (char *) calloc(64, sizeof(char)));
        strcpy(ptr_clientsArray->client[i].country, (char *) calloc(64, sizeof(char)));
        ptr_clientsArray->client[i].removed = 0;
        ptr_clientsArray->client[i].code = 0;
        ptr_clientsArray->client[i].nif = 0;
    }
    return 1;
}

ClientsArray *allocMemoryClients(int size) {
    ClientsArray *ptr_clientsArray = (ClientsArray *) malloc(sizeof(ClientsArray));
    if (ptr_clientsArray == NULL) {
        printf("Memory allocation failed!");
        return NULL;
    }
    ptr_clientsArray->count = 0;
    ptr_clientsArray->size = size;

    ptr_clientsArray->client = (Client *) calloc(ptr_clientsArray->size, sizeof(Client));
    if (ptr_clientsArray->client == NULL) {
        printf("Memory allocation failed!");
        free(ptr_clientsArray);
        return NULL;
    }

    for (int i = 0; i < ptr_clientsArray->size; i++) {
        memset(ptr_clientsArray->client[i].name, 0, sizeof(ptr_clientsArray->client[i].name));
        memset(ptr_clientsArray->client[i].address, 0, sizeof(ptr_clientsArray->client[i].address));
        memset(ptr_clientsArray->client[i].country, 0, sizeof(ptr_clientsArray->client[i].country));
    }

    return ptr_clientsArray;
}

void freeMemoryClients(ClientsArray *ptr_clientsArray) {
    if (ptr_clientsArray != NULL) {
        if (ptr_clientsArray->client != NULL) {
            for (int i = 0; i < ptr_clientsArray->count; i++) {
                memset(ptr_clientsArray->client[i].name, 0, sizeof(ptr_clientsArray->client[i].name));
                memset(ptr_clientsArray->client[i].address, 0, sizeof(ptr_clientsArray->client[i].address));
                memset(ptr_clientsArray->client[i].country, 0, sizeof(ptr_clientsArray->client[i].country));
            }
            free(ptr_clientsArray->client);
        }
        free(ptr_clientsArray);
    }
}

int addClients(ClientsArray *ptr_clientsArray) {

    if (ptr_clientsArray == NULL) {
        printf("ClientsArray pointer is NULL.\n");
        return -1;
    }

    if (ptr_clientsArray->count == ptr_clientsArray->size) {
        if (!expandClientsArray(ptr_clientsArray)) {
            printf("Failed to expand ClientsArray.\n");
            return -1;
        }
    }
    if (readClientInfo(ptr_clientsArray, ptr_clientsArray->count) != 1) {
        printf("Failed to read information for new Client.\n");
        return -1;
    }

    ptr_clientsArray->count++;

    return 1;
}

int updateClient(ClientsArray *ptr_clientsArray, int code) {
    if (ptr_clientsArray == NULL) {
        printf("ClientsArray pointer is NULL.\n");
        return -1;
    }
    if (ptr_clientsArray->count == 0) {
        printf("ClientsArray is empty.\n");
        return 0;
    }
    for (int i = 0; i < ptr_clientsArray->count; i++) {
        if (ptr_clientsArray->client[i].code == code) {
            if (readClientInfo(ptr_clientsArray, i)) {
                printf("\nAtualizado comy\n");
                return 1;
            } else {
                printf("\nUpdate failed!\n");
                return 0;
            }
        }
    }
    printf("\nClient not found!\n");
    return 0;
}

void listClients(ClientsArray *ptr_ClientsArray) {
    if (ptr_ClientsArray == NULL) {
        printf("ClientsArray pointer is NULL.\n");
        return;
    }
    if (ptr_ClientsArray->count == 0) {
        printf("ClientsArray is empty.\n");
        return;
    }
    for (int i = 0; i < ptr_ClientsArray->count; i++) {
        printClientInfo(&ptr_ClientsArray->client[i]);
    }
}

void printClientInfo(const Client *ptr_client) {
    printf("\n----\n");
    printf("Código de cliente: %d\n", ptr_client->code);
    printf("Nome do Cliente: %s\n", ptr_client->name);
    printf("Morada Cliente: %s\n", ptr_client->address);
    printf("Nif do cliente: %d\n", ptr_client->nif);
    printf("País do cliente: %s\n", ptr_client->country);
    printf("Removido: %d", ptr_client->removed);
    printf("\n----\n");
}

void exportClientsTxt(ClientsArray *ptr_ClientsArray) {
    FILE *file;
    int size = 10;
    char *str = calloc(size, sizeof(char));

    readString(str, size, FILE_NAME);

    file = fopen(str, "w");
    if (file == NULL) {
        fprintf(stderr, "Não foi possível criar o ficheiro");
        fclose(file);
        return;
    }

    for (int i = 0; i < ptr_ClientsArray->count; i++) {
        fprintf(file, "Codigo: %d;\t-Nome: %s;\t-Morada: %s;\t-NIF: %d;\t-Country: %s;\t-Removed: %d;\n",
                ptr_ClientsArray->client[i].code,
                ptr_ClientsArray->client[i].name,
                ptr_ClientsArray->client[i].address,
                ptr_ClientsArray->client[i].nif,
                ptr_ClientsArray->client[i].country,
                ptr_ClientsArray->client[i].removed
        );
    }
    fclose(file);
}
