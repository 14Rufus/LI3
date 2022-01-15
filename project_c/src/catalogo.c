/**
 * @file catalogo.c
 * @brief módulo de dados onde deverão ser guardados os utilizadores, os negócios e as reviews e todas as informações
 *        relativas aos registos válidos dos ficheiros .csv
 */

#include "catalogo.h"

/**
 * @brief estrutura catálogo
 */

struct catalogo
{
  AVL *list;
};

// INIT

/**
 * @brief função responsável pela inicialização da estrutura Table
 * @return catálogo inicializado
 */
Catalogo initTable()
{
  Catalogo new = malloc(sizeof(Catalogo));
  new->list = malloc(sizeof(AVL) * HSIZE);

  int i;
  for (i = 0; i < HSIZE; i++)
    new->list[i] = initAVL();

  return new;
}

/**
 * @brief função de hash responsável pela organização por index
 * @param key primeiro carater do id, utilizado como key da hash table
 * @return hash table organizada pelos primeiros carateres dos ids
 */

int hash(char key) {
  int index = key;
  if (key >= 'a' && key <= 'z')
    index -= 'a';
  else if (key >= 'A' && key <= 'Z')
    index -= 'A';
  else if (key >= '0' && key <= '9')
    index = index - '0' + 26;
  else if (key == '_')
    index = 36;
  else if (key == '-')
    index = 37;

  return index;
}

/**
 * @brief função responsável pela insersão no catálogo
 * @param cat estrutura do catálogo
 * @param key primeiro carater do id, utilizado como key da hash table
 * @param content informação contida na estrutura do catálogo
 */
void insere_Catalogo(Catalogo cat, char *key, void* content)
{
  int index = hash(key[0]);

  cat->list[index] = avl_insert(cat->list[index], key, content);
}

/**
 * @brief função responsável pela atualização do catálogo
 * @param cat estrutura do catálogo
 * @param key primeiro carater do id, utilizado como key da hash table
 * @param content informação contida na estrutura do catálogo
 */
void update_Catalogo(Catalogo cat, char *key, void* content) {
    int index = hash(key[0]);

    cat->list[index] = avl_update(cat->list[index], key, content);
}

/**
 * @brief função responsável pela procura num determinado catálogo
 * @param cat estrutura do catálogo
 * @param key primeiro carater do id, utilizado como key da hash table
 * @return existência de um determinado catálogo
 */
int lookUpCatalogo(Catalogo cat, char* key) {
    int index = hash(key[0]);
    return avl_lookUp(cat->list[index], key);
}

/**
 * @brief função que devolve um determinado catálogo
 * @param catalogo estrutura catálogo
 * @param key primeiro carater do id, utilizado como key da hash table
 * @return estrutura catálogo pretendida
 */
void *getEstruturaCatalogo(Catalogo catalogo, char *key){
  int index = hash(key[0]);
  return avl_getEstrutura(catalogo->list[index], key);
}

/**
 * @brief função que devolve uma determinado AVL consoante a key fornecida
 * @param catalogo estrutura catálogo
 * @param key primeiro carater do id, utilizado como key da hash table
 * @return estrutura AVL
 */
AVL getAVLKey(Catalogo catalogo, char* key){
    int index = hash(key[0]);
    return catalogo->list[index];
}

/**
 * @brief função que devolve o index de uma determinado AVL
 * @param catalogo estrutura catálogo
 * @param index posição na hash table consoante o char do id
 * @return estrutura AVL
 */
AVL getAVLIndex(Catalogo catalogo, int index){
  return catalogo->list[index];
}

/**
 * @brief função que liberta o espaço de memória ocupado pela estrutura Catalogo
 * @param catalogo estrutura catálogo
 * @param f função responsável pela libertação do conteúdo do catálogo
 */
void freeCatalogo(Catalogo catalogo, Funcao f){
  int i;

  for (i = 0; i < HSIZE; i++) {
    freeAVL(catalogo->list[i], f);
  }
}