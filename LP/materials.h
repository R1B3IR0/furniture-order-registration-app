#ifndef MATERIALS_H
#define MATERIALS_H

#include "utilities.h"
#include "files.h"

typedef struct {
    char code[6];    //codigo de materiais
    int quantity;   //quantidade de material

} MaterialInProduct;

typedef struct {
    MaterialInProduct *materialInProduct;
    int size;
    int count;
} ProductMaterialsArray;  //Lista de Produtos/Materiais

typedef struct {
    char code[6];
    char description[64];
    char unit[5];
} Material;

typedef struct {
    Material *material;
    int count;           // Representa o espaço total ocupado e a posição livre
    int size;            // Tamanho total do array
} MaterialsArray;

int getMaterialIndex(char *code, MaterialsArray *materialsArray);

/**
 * @param ptr_MaterialsArray
 * @param code
 * @return
 */
Material *findMaterialByCode(MaterialsArray *ptr_MaterialsArray, char code[]);

/**
 * @param ptr_MaterialsArray
 * @param i
 * @return "sucess"
 */
int readMaterial(MaterialsArray *ptr_MaterialsArray, int i);

/**
 * Aloca memória para um array de artigos.
 * @return um array de artigos.
 */
MaterialsArray *allocMemoryMaterials(int size);

MaterialsArray *importMaterials(char *filename);


/**
 * Função para libertar a memória do array de artigos.
 * @param ptr_MaterialsArray
 */
void freeMemoryMaterials(MaterialsArray *ptr_MaterialsArray);

/**
* Expande o array de Materiais.
* @param ptr_MaterialsArray
*/
void expandMaterialsArray(MaterialsArray *ptr_MaterialsArray);

/**
 * Adiciona um artigo ao array de artigos.
 * @return 1 se adicionado com sucesso, caso-contrário 0.
 */
int addMaterial(MaterialsArray *ptr_MaterialsArray);

/**
 *Procura o artigo pelo código e remove-o.
 * @param code código do artigo.
 * @return 1 se removido com sucesso, caso-contrário 0.
 */
int removeMaterial(MaterialsArray *ptr_MaterialsArray);

/**
 * Procura o artigo pelo código e atualiza as informações do artigo.
 * @param code código do artigo.
 * @return 1 se atualizado com sucesso, caso-contrário 0.
 */
int updateMaterial(MaterialsArray *ptr_MaterialsArray);

/**
 *Função utilizada para imprimir toda a informação de um material.
 * @param material
 */
void printMaterials(const Material *material);

/**
 * Itera o array de artigos.
 * @param materialsArray
 */
void listMaterials(MaterialsArray *materialsArray);

/**
 * Itera o array de artigos cancelados.
 * @param materialsArray
 */


/**
 * Exporta para um ficheiro de texto a lista dos materiais
 * @param materialsArray
 * @param filename
 */
void exportMaterials(char *filename, MaterialsArray *materialsArray);

#endif /* MATERIALS_H */

