#ifndef UTILITIES_H
#define UTILITIES_H

// Ficheiro
#define EMPTY_FILE "Ficheiro Vazio"
#define FILE_NAME "Insira o nome do ficheiro:"



//Mensagem para inserir o utilizador.
#define INSERT_PROFILE "Insira o tipo de utilizador:"

//Mensagens utilizadas para avisar números repetidos.
#define INVALID_VALUE "O valor inserido é invalido."
#define CODE_EXISTS "O codigo já existe!"
#define NIF_EXISTS "O NIF introduzido ja esta essociado a outro cliente!"
#define INSERT_OPTION "Insira a opção que deseja:"
#define CODE_FOUND  "O codigo foi encontrado!"
#define FAILED_OPERATION "Operacao falhada"
#define SUCESS_OPERATION "Operacao realizada com sucesso"

//Mensagens utilizadas para os produtos.
#define INSERT_PRODUCT_CODE "Insira o codigo do produto:"
#define INSERT_PRODUCT_NAME "Insira um nome para o produto:"
#define INSERT_MATERIAL_CODE "Insira o codigo do material:"
#define INSERT_PRODUCT_DIMENSIONS "Insira as dimensoes do produto:(comprimento x altura x profundidade): "
#define INSERT_PRODUCT_TYPE "Tipo do produto: (PAR / UN / 4...): "
#define CODE_INPUT_PRODUCT "Codigo do Artigo:"
#define PRODUCT_REMOVED "O artigo foi removido!"
#define INACTIVE_PRODUCT_SUCESS "Estado do produto: Inativo \n\t\\Sucesso//\n"
#define INACTIVE_PRODUCT "\n|----ATENÇÃO-----|\n|Produto removido|\n|----------------|\n"
//Mensagens utilizadas para o cliente.
#define INSERT_CLIENT_CODE "Insira o codigo do cliente:"
#define INSERT_CLIENT_NAME "Insira o nome do cliente:"
#define INSERT_CLIENT_NIF "Insira o NIF do cliente:"
#define INSERT_CLIENT_COUNTRY "Insira o pais do cliente:"
#define INSERT_CLIENT_ADDRESS "Insira a morada do cliente:"
#define CLIENT_NOT_FOUND "Nao existe cliente associado ao codigo introduzido"

//Mensagens utilizadas para as encomendas.
#define INSERT_ORDER_DAY "Insira o dia da entrega da encomenda (1-31): "
#define INSERT_ORDER_MONTH "Insira o mes da entrega da encomenda (1-12): "
#define INSERT_ORDER_YEAR "Insira o ano da entrega da encomenda(1999-2099): "
#define INSERT_ORDER_CODE "Insira o codigo da encomenda:"
#define INSERT_QUANTITY_SIZE "Insira o quantidade do artigo: "
#define INSERT_ITEM "Deseja inserir um artigo? "
#define INSERT_PRICE_PRODUCT "Insira o preco do produto:"
#define CANCELED_ORDER "\n|----ATENÇÃO-----|\n|Encomenda cancelada|\n|----------------|\n"



void cleanBuffer();
/**
 * Função utilizada para ler caracteres.
 * @param msg
 * @return o caracter.
 */
char readChar(char *msg);

/**
 * Função utilizada para ler inteiros.
 * @param minValor
 * @param maxValor
 * @param msg
 * @return o valor inteiro.
 */
int readInteger(int minValor, int maxValor, const char *msg);

/**
 * Função utilizada para ler float.
 * @param minValor
 * @param maxValor
 * @param msg
 * @return o valor em float
 */
float readFloat(float minValor, float maxValor, char *msg);

/**
 * Função utilizada para ler um array de caracteres.
 * @param string
 * @param tamanho
 * @param msg
 */
void readString(char *string, int tamanho, char *msg);



#endif /* UTILITIES_H */

