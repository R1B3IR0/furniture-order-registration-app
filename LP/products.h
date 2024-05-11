#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "utilities.h"
#include "materials.h"
#include "files.h"

typedef struct {
    char code[64];        //Done
    char name[256];      //Done
    char dimensions[64]; //Pode ser alterado
    int price;         //Pode ser alterado
    int removed;         //Para alterar o estado do Produto/Inativo
    ProductMaterialsArray *productMaterialsArray;  //Lista de Materiais para cada produto
} Product;

typedef struct {
    Product *product;
    int count; // Representa o espaço total ocupado e a posição livre
    int size; // Tamanho total do array
} ProductsArray;

/**
 * @param ptr_ProductsArray
 * @param code
 * @return
 */
Product *findProductByCode(ProductsArray *ptr_ProductsArray, const char code[]);

/**
 *Função utilizada para inserir materiais num produto.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i, int j);

/**
 *Função utilizada para inserir ler as informações de um produto.
 * @param ptr_MaterialsArray,ptr_ProductsArray
 */
int readProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i);


/**
* Expande o array de Produtos.
* @param ptr_MaterialsArray
*/
void expandProductsArray(ProductsArray *ptr_ProductsArray);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
ProductsArray *allocMemoryProducts(int size);

void readFile(char *fileName, ProductsArray *productsArray, MaterialsArray *materialsArray);


ProductsArray *importProducts(char *filename);

ProductMaterialsArray *importProductMaterials(FILE *file);

/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_ProductsArray
 */
void freeMemoryProducts(ProductsArray *ptr_ProductsArray);

/**
 * Adiciona um artigo ao array de artigos.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray);

/**
 * Adiciona um maerial ao produto.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addMaterialsToProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, int i);


/**
 *Procura o artigo pelo código e remove-o.
 * @param code código do artigo.
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int removeProduct(ProductsArray *ptr_ProductsArray, const char code[6]);

/**
 * Procura o artigo pelo código e atualiza as informações do artigo.
 * @param code código do artigo.
 * @return 1 se atualizado com sucesso, caso-contrário 0.
 */
int updateProduct(MaterialsArray *ptr_MaterialsArray, ProductsArray *ptr_ProductsArray, char code[]);

/**
 *Função utilizada para imprimir toda a informação de um artigo.
 * @param Product
 */
void printProducts(const Product *ptr_Product);

/**
 * Itera o array de artigos.
 * @param ptr_ProductsArray
 */
void listProducts(ProductsArray *ptr_ProductsArray);

/**
 * Itera o array de artigos cancelados.
 * @param materialsArray
 */
void productsListCanceled(ProductsArray *ptr_ProductsArray);

///FUNÇÕES PARA MATERIAIS DO PRODUTO

/**
* Aloca memória para um array de artigos.
* @return um array de artigos.
*/
void expandProductMaterialsArray(ProductsArray *ptr_ProductsArray);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
ProductMaterialsArray *allocMemoryProductMaterials(int size);

/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_ProductsArray
 */
void freeMemoryProductMaterials(ProductMaterialsArray *ptr_ProductMaterialsArray);

/**
 * Exporta para um ficheiro de texto a lista dos produtos
 * @param filename
 * @param ptr_products
 */
void exportProducts(char *filename, ProductsArray *ptr_products);

#endif /* PRODUCTS_H */

