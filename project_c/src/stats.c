/**
 * @file stats.c
 * @brief módulo responsável pelas relações entre os 3 principais modelos, proporcionando
 *        acesso mais rápido a dados e resultados pedidos nas queries do programa
 */
#include "stats.h"

////////// USER STATS //////////
/**
 * @brief estrutura de armazenamento das stats do utilizador
 */
struct userStats {
    char* user_id;
    char* name;
    char** states;
    int numStates;
};

/**
 * @brief função responsável pela criação das stats do utilizador
 * @param id identificador do user
 * @param name nome do user
 * @return estrutura das stats do utilizador
 */
UserStats createUserStats(char* id, char* name) {
    UserStats new = calloc(1, sizeof(struct userStats));
    new->user_id = strdup(id);
    new->name = strdup(name);

    new->states = malloc(sizeof(char*));
    new->numStates = 0;

    return new;
}
/**
 * @brief função responsável pela atualização das stats do utilizador
 * @param us estrtutura das stats do utilizador
 * @param state estado a atualizar
 */
void updateUserStats(UserStats us, char* state) {
    us->states = realloc(us->states, sizeof(char*) * (us->numStates + 1));
    us->states[us->numStates] = strdup(state);
    us->numStates++;
}

/**
 * @brief função que liberta o espaço de memória ocupado pela estrutura UserStats
 * @param us estrtura das stats do utilizador
 */
void freeUserStats(UserStats us) {
    free(us->user_id);
    free(us->name);
    for(int i=0; i<us->numStates; i++)
        free(us->states[i]);
    free(us);
}

/**
 * @brief função que devolve o identificador de uma estrutura UserStats
 * @param us estrutura UserStats
 * @return identificador da estrutura
 */
char *getUserStatsId(UserStats us) {
    return us->user_id;
}

/**
 * @brief função que devolve o nome de uma estrutura UserStats
 * @param us estrutura UserStats
 * @return nome da estrutura
 */
char *getUserStatsName(UserStats us) {
    return us->user_id;
}

/**
 * @brief função que devolve o número de estados de uma estrutura UserStats
 * @param us estrutura UserStats
 * @return número de estador da estrutura
 */
int getNumStates(UserStats us) {
    return us->numStates;
}

////////// CITYSTATS //////////

/**
 * @brief estrutura responsável pelas informações das stars do negocio
 */
struct businessStars {
    char* business_id;
    char* name;
    float stars;
    int numStars;
};

/**
 * @brief estrutura responsável pelas informações das stats da cidade
 */
struct cityStats {
    char* city;
    struct businessStars *list;
    int size;
};

/**
 * @brief função responsavel pela criação das estatisticas da cidade
 * @param city cidade
 * @return estatisticas da cidade
 */
CityStats createCityStats(char* city) {
    CityStats new = calloc(1, sizeof(struct cityStats));
    new->city = strdup(city);
    new->size = 0;

    return new;
}

/**
 * @brief comparador de negocio
 * @param a 1º argumento
 * @param b 2º argumento
 * @return inteiro de comparação
 */
int compare(const void* a, const void* b) {
    struct businessStars aux = *((struct businessStars*) a);
    struct businessStars aux2 = *((struct businessStars*) b);

    float dif = (aux2.stars / aux2.numStars) - (aux.stars / aux.numStars);

    return dif==0 ? 0 : (dif<0) ? -1 : 1;
}

void sortCityStats(CityStats cs) {
    qsort(cs->list, cs->size, sizeof(struct businessStars), compare);
}

/**
 * @brief função que devolve o identificador das stats de uma cidade
 * @param cs estrutura citystats
 * @param i
 * @return identificador
 */
char* getCityStatsId(CityStats cs, int i) {
    return cs->list[i].business_id;
}

/**
 * 
 * @param bs
 * @param business_id
 * @param name
 * @param stars
 */
void updateCityStats(CityStats bs, char* business_id, char* name, float stars) {
    int inArray = 0, i;

    for(i=0; i<bs->size && !inArray; i++){
        if(strcmp(getCityStatsId(bs, i), business_id)==0)
            inArray = 1;
    }

    if(!inArray){
        bs->list = realloc(bs->list, sizeof(struct businessStars) * (bs->size + 1));
        bs->list[bs->size].business_id = strdup(business_id);
        bs->list[bs->size].name = strdup(name);
        bs->list[bs->size].stars = stars;
        bs->list[bs->size].numStars = 1;
        bs->size++;
    } else {
        bs->list[i-1].stars += stars;
        bs->list[i-1].numStars += 1;
    }
}

void freeCityStats(CityStats bs){
    free(bs->city);

    for(int i=0; i<bs->size; i++){
        free(bs->list[i].business_id);
        free(bs->list[i].name);
    }

    free(bs);
}

char *getCityStatsCity(CityStats bs) {
    return bs->city;
}

int getCityStatsSize(CityStats cs) {
    return cs->size;
}

float getCityStatsStars(CityStats cs, int i) {
    return (cs->list[i].stars / cs->list[i].numStars);
}

char* getCityStatsName(CityStats cs, int i) {
    return cs->list[i].name;
}

////////// BUSINESSSTATS //////////

struct businessStats {
    char* business_id;
    char* name;
    char* city;
    char* state;
    float stars;
    int numStars;
    char** categories;
    int numCategories;
};

BusinessStats createBusinessStats(char* business_id, char* name, char* city, char* state) {
    BusinessStats new = calloc(1, sizeof(struct businessStats));
    new->business_id = strdup(business_id);
    new->name = strdup(name);
    new->city = strdup(city);
    new->state = strdup(state);

    new->stars = 0;
    new->numStars = 0;

    return new;
}

void updateBusinessStats(BusinessStats bs, float stars, char** categories, int numCategories) {
    bs->stars += stars;
    bs->numStars += 1;

    bs->categories = malloc(sizeof(char*) * numCategories);
    for(int i=0; i<numCategories; i++) {
        bs->categories[i] = strdup(categories[i]);
    }
    bs->numCategories = numCategories;
}

void freeBusinessStats(BusinessStats bs) {
    free(bs->business_id);
    free(bs->name);

    for(int i=0; i<bs->numCategories; i++)
        free(bs->categories[i]);

    free(bs->categories);
    free(bs);
}

BusinessStats getBusinessStats(Catalogo businessStatsCat, char* id) {
    return getEstruturaCatalogo(businessStatsCat, id);
}

char *getBusinessStatsId(BusinessStats bs) {
    return bs->business_id;
}

char *getBusinessStatsName(BusinessStats bs) {
    return bs->name;
}

char *getBusinessStatsCity(BusinessStats bs) {
    return bs->city;
}

char *getBusinessStatsState(BusinessStats bs) {
    return bs->state;
}

float getBusinessStatsStars(BusinessStats bs) {
    return bs->numStars == 0 ? bs->stars : (bs->stars) / (bs->numStars);
}

int getBusinessStatsNumStars(BusinessStats bs) {
    return bs->numStars;
}

int pertenceCategoria(BusinessStats b, char* category) {
    int flag = 0;

    for(int i=0; i<b->numCategories && !flag; i++)
        if(strcmp(category, b->categories[i])==0)
            flag=1;

    return flag;
}