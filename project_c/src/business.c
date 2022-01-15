/**
 *@file business.c
 * @brief Ficheiro que contém as funções relativas ao módulo business
 */
#include "business.h"
#include "catalogo.h"
#include "avl.h"

//estruturas para inserir na AVL

struct businessInfo
{
    char *id;
    char *name;
    char *city;
    char *state;
    char **categories;
    int ncategories;
};

/**
 * @brief Estrutura responsável pelo arquivo informação realcionada com o ficheiro business
 * @param id identificador do negócio
 * @param name nome do negócio
 * @param city cidade onde o negócio se desenvolve
 * @param state estado onde o negócio se desenvolve
 * @param categories categorias implementadas por um determinado negócio
 * @return estrutura informativa do negócio
 */
Business createBusiness(char *id, char *name, char *city, char *state, char *categories)
{
    Business new = calloc(1, sizeof(struct businessInfo));
    new->id = strdup(id);
    new->name = strdup(name);
    new->city = strdup(city);
    new->state = strdup(state);

    new->ncategories = 0;
    char *aux;
    while ((aux = strsep(&categories, ",")))
    {
        new->categories = realloc(new->categories, sizeof(char *) * (new->ncategories + 1));
        new->categories[new->ncategories] = strdup(aux);
        new->ncategories++;
    }

    return new;
}

/**
 * @brief função que devolve um determinado negócio
 * @param businessCat catálogo de negócio
 * @param id identificador de negócio
 * @return Estrutura do catálogo de um determinado business
 */
Business getBusiness(Catalogo businessCat, char* id) {
    return getEstruturaCatalogo(businessCat, id);
}

/**
 * @brief função que devolve o nome de um determinado negócio
 * @param business estrutura informativa do negócio
 * @return nome do negócio em questão
 */
char* getBusinessName(Business business)
{
    return business->name;
}

/**
 * @brief função que devolve o id de um determinado negócio
 * @param business estrutura informativa do negócio
 * @return nome do negócio em questão
 */
char *getIdBusiness(Business business)
{
    return business->id;
}

/**
 * @brief função que devolve a cidade de um determinado negócio
 * @param b estrutura business a utilizar
 * @return cidade de um determinado negócio
 */
char *getBusinessCity(Business b)
{
    return b->city;
}

/**
 * @brief função que devolve o estado de um determinado negócio
 * @param b estrutura business a utilizar
 * @return estado de um determinado negócio
 */
char *getBusinessState(Business b)
{
    return b->state;
}

/**
 * @brief função que devolve as categorias de um determinado negócio
 * @param b estrutura business a utilizar
 * @return categorias de um determinado negócio
 */
char ** getCategories(Business b) {
    return b->categories;
}

/**
 * @brief função que devolve o número de categorias de um determinado negócio
 * @param b estrutura business a utilizar
 * @return número de categorias de um determinado negócio
 */
int getNumCategories(Business b) {
    return b->ncategories;
}

/**
 * @brief função que liberta o espaço de memória ocupado pela estrutura Business
 * @param business estrutura business a libertar
 */
void freeBusiness(Business business) {
    free(business->id);
    free(business->name);
    free(business->city);
    free(business->state);
    for(int i=0; i<business->ncategories; i++)
        free(business->categories[i]);
    free(business);
}