#include "sgr.h"

struct table{
    char* header;
    char** info;
    char*** list;
    int col;
    int line;
};

struct sgr
{
    Catalogo users;
    Catalogo business;
    Catalogo review;
    Catalogo userStats;
    Catalogo cityStats;
    Catalogo businessStats;
};

// TABLE
/**
 * @brief Retorna o número de linhas de uma table
 * @param t Table pretendida
 * @return Número de linhas de uma table
 */
int getLine(TABLE t) {
    return t->line;
}

/**
 * @brief Retorna o número de colunas de uma table
 * @param t Table pretendida
 * @return Número de colunas de uma table
 */
int getCol(TABLE t) {
    return t->col;
}

/**
 * @brief Retorna um elemento da list na linha line e coluna col
 * @param t Table pretendida
 * @param line Linha pretendida
 * @param col Coluna pretendida
 * @return Elemento da list pretendido
 */
char* getList(TABLE t, int line, int col) {
    return t->list[line][col];
}

/**
 * @brief Retorna o header da table
 * @param t Table pretendida
 * @return header da table
 */
char* getHeader(TABLE t) {
    return t->header;
}
/**
 * @brief Retorna a info da table
 * @param t Table pretendida
 * @param i Coluna que pretendemos
 * @return Info da table
 */
char* getInfo(TABLE t, int i) {
    return t->info[i];
}
/**
 * @brief Liberta a memória pela table
 * @param t Table a ser libertada
 */
void freeTable(TABLE t) {
    for(int i=0; i<t->line; i++) {
        for (int j = 0; j < t->col; j++)
            free(t->list[i][j]);
        free(t->info[i]);
    }

    free(t->header);
    free(t->info);
    free(t);
}

/**
 * @brief Inicializa um sgr
 * @return sgr incializado
 */
SGR init_sgr()
{
    SGR new = malloc(sizeof(struct sgr));
    new->users = initTable();
    new->business = initTable();
    new->review = initTable();
    new->userStats = initTable();
    new->cityStats = initTable();
    new->businessStats = initTable();
    return new;
}

/**
 * @brief Carrega o sgr com os ficheiros pretendidos
 * @param users Path do ficheiro de Users
 * @param businesses Path do ficheiro de Businesses
 * @param reviews Path do ficheiro de Reviews
 * @return Sgr carregado com os ficheiros pretendidos
 */
SGR load_sgr(char *users, char *businesses, char *reviews)
{
    SGR sgr = init_sgr();

    parseUsers(users, sgr->users);
    parseBusiness(businesses, sgr->business, sgr->businessStats);
    parseReview(reviews, sgr->review, sgr->users, sgr->business, sgr->userStats, sgr->cityStats, sgr->businessStats);

    return sgr;
}

/**
 * @brief Liberta a memória alocada pelo sgr
 * @param sgr Sgr cuja memória pretendemos libertar
 */
void free_sgr(SGR sgr)
{
    freeCatalogo(sgr->users, (void (*)(void *)) freeUser);
    freeCatalogo(sgr->business, (void (*)(void *)) freeBusiness);
    freeCatalogo(sgr->review, (void (*)(void *)) freeReview);
    freeCatalogo(sgr->userStats, (void (*)(void *)) freeUserStats);
    freeCatalogo(sgr->cityStats, (void (*)(void *)) freeCityStats);
    freeCatalogo(sgr->businessStats, (void (*)(void *)) freeBusinessStats);
    free(sgr);
}

/**
 * @brief Inicializa uma table
 * @param col Número de colunas que pretendemos ter na table
 * @return Table inicializada
 */
TABLE newTable(int col) {
    TABLE t = calloc(1, sizeof(struct table));
    t->col = col;
    t->line = 0;
    t->info = malloc(sizeof(char*) * col);
    return t;
}

/**
 * @brief Retorna uma table para a indexação
 * @param t table pretendida
 * @param i
 * @param j
 * @return Table para a indexação
 */
TABLE newIndex(TABLE t, int i, int j) {
    TABLE new = newTable(1);
    new->col = 1;
    new->line = 1;
    new->list = malloc(sizeof(char**));
    new->list[0] = malloc(sizeof(char*));
    new->list[0][0] = strdup(t->list[i][j]);
    new->info[0] = strdup(t->info[j]);
    new->header = "";
    return new;
}

/**
 * @brief Adiciona uma  nova coluna a uma table
 * @param t Tabela onde pretendemos adicionar a coluna
 * @param j Coluna que queremos adicionar
 * @return Table com uma nova coluna
 */
TABLE newCollumn(TABLE t, int j) {
    TABLE new = newTable(1);
    new->col = 1;
    new->line = getLine(t);
    new->list = malloc(sizeof(char**) * new->line);
    for(int i=0; i<new->line; i++){
        new->list[i] = malloc(sizeof(char*));
        new->list[i][0] = strdup(t->list[i][j]);
    }
    new->info[0] = strdup(t->info[j]);
    new->header = "";
    return new;
}

/**
 * @brief Retorna uma nova table para escrever bo csv
 * @param line Número de linhas pretendido
 * @param col Número de colunas pretendido
 * @param info Info da table
 * @param list Matriz da table
 * @return Table pretendida
 */
TABLE newCSV(int line, int col, char** info, char*** list) {
    TABLE new = newTable(col);
    new->line = line;

    for(int i=0; i<col; i++) {
        new->info[i] = strdup(info[i]);
        free(info[i]);
    }
    free(info);

    new->list = malloc(sizeof(char**) * line);
    for(int i=0; i<line; i++) {
        new->list[i] = malloc(sizeof(char*) * col);
        for (int j = 0; j < col; j++) {
            new->list[i][j] = strdup(list[i][j]);
            free(list[i][j]);
        }
        free(list[i]);
    }
    free(list);

    new->header = "";

    return new;
}

/**
 * @brief Adiciona a uma table um negócio cujo name inicia pelo char letter
 * @param n Árvore onde estão armazenados os businesses
 * @param letter Letra pretendida
 * @param t Table a que se adiciona o Business
 */
void addBusinessTable(Node n, char letter, TABLE t) {
    if(!n)
        return;

    Business b = getCont(n);
    char* name = getBusinessName(b);
    if(name[0]==letter) {
        t->list = realloc(t->list, sizeof(char **) * (t->line + 1));
        t->list[t->line] = malloc(sizeof(char *) * t->col);
        t->list[t->line][0] = strdup(name);
        t->line++;
    }

    addBusinessTable(getLeft(n), letter, t);
    addBusinessTable(getRight(n), letter, t);
}

/**
 * @brief Query 2
 * @param sgr Sgr pretendido
 * @param letter Letra pretendida
 * @return Table com os negócios pretendidos
 */
TABLE businesses_started_by_letter(SGR sgr, char letter) {
    TABLE table = newTable(1);
    char* buffer = malloc(sizeof(char)*128), buffer2[128];
    buffer[0] = '\0';

    for(int i=0; i<HSIZE; i++)
        addBusinessTable(getNode(getAVLIndex(sgr->business, i)), letter, table);

    table->info[0] = strdup("Name");

    strcpy(buffer, "Número de negócios começados pela letra: ");
    sprintf(buffer2, "%d", table->line);
    table->header = strcat(buffer, buffer2);

    return table;
}

/**
 * @brief Query 3
 * @param sgr Sgr pretendido
 * @param business_id Id do Business pretendido
 * @return Informação do Business pretendida
 */
TABLE business_info(SGR sgr, char *business_id) {
    TABLE t = newTable(5);
    BusinessStats bs = getBusinessStats(sgr->businessStats, business_id);
    char buffer[1024];

    t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
    t->list[t->line] = malloc(sizeof(char*) * t->col);
    t->list[t->line][0] = strdup(getBusinessStatsName(bs));
    t->list[t->line][1] = strdup(getBusinessStatsCity(bs));
    t->list[t->line][2] = strdup(getBusinessStatsState(bs));
    sprintf(buffer, "%f", getBusinessStatsStars(bs));
    t->list[t->line][3] = strdup(buffer);
    sprintf(buffer, "%d", getBusinessStatsNumStars(bs));
    t->list[t->line][4] = strdup(buffer);
    t->line++;

    t->info[0] = strdup("Nome");
    t->info[1] = strdup("Cidade");
    t->info[2] = strdup("Estado");
    t->info[3] = strdup("Estrelas");
    t->info[4] = strdup("Reviews");

    t->header = strdup("Informação de um negócio");

    return t;
}

/**
 * @brief Adiciona oo id dos Businesses que tiveram uma Review de um User
 * @param review Árvore de reviews
 * @param sgr Sgr pretendida
 * @param user_id Id do User pretendido
 * @param t table a que pretendemos adicionar o User
 */
void calculaNegocios(Node review, SGR sgr, char* user_id, TABLE t) {
    if(review == NULL)
        return;

    Review r = getCont(review);
    if(strcmp(getReviewUserId(r), user_id)==0) {
        char* business_id = getReviewBusinessId(r);

        t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
        t->list[t->line] = malloc(sizeof(char*) * t->col);
        t->list[t->line][0] = strdup(business_id);
        t->list[t->line][1] = strdup(getBusinessName(getBusiness(sgr->business, business_id)));
        t->line++;
    }

    calculaNegocios(getLeft(review),sgr, user_id, t);
    calculaNegocios(getRight(review),sgr, user_id, t);
}
/**
 * @brief Query 4
 * @param sgr Sgtr pretendido
 * @param user_id Id do User pretendido
 * @return Table de Businesses que tiveram Review do User
 */
TABLE businesses_reviewed(SGR sgr, char *user_id) {
    TABLE table = newTable(2);
    char* buffer = malloc(sizeof(char)*128), buffer2[128];

    for(int i=0; i<HSIZE; i++)
        calculaNegocios(getNode(getAVLIndex(sgr->review, i)),sgr, user_id, table);

    table->info[0] = strdup("Id");
    table->info[1] = strdup("Nome");

    strcpy(buffer, "Negócios com reviews: ");
    sprintf(buffer2, "%d", table->line);
    table->header = strcat(buffer, buffer2);

    return table;
}

/**
 * @brief Query 5
 * @param sgr Sgr pretendido
 * @param stars Número de stars pretendido
 * @param city Cidade pretendida
 * @return Table de Businesses com um número igual ou maior ao pretendido
 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city){
    TABLE t = newTable(2);

    CityStats cs = getEstruturaCatalogo(sgr->cityStats, city);

    for(int i=0; i<getCityStatsSize(cs); i++) {
        if(getCityStatsStars(cs, i) >= stars) {
            t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
            t->list[t->line] = malloc(sizeof(char*) * t->col);
            t->list[t->line][0] = strdup(getCityStatsId(cs, i));
            t->list[t->line][1] = strdup(getCityStatsName(cs, i));
            t->line++;
        }
    }

    t->info[0] = strdup("Id");
    t->info[1] = strdup("Nome");
    t->header = strdup("Negócios com numero de estrelas igual ou superior a n");

    return t;
}

/**
 * @brief Adiciona os top Businesses a uma table
 * @param cityStats Árvore de cityStats
 * @param top Número pretendido para o top
 * @param t table que pretendemos adicionar os Businesses
 */
void calculaNegociosCidade(Node cityStats, int top, TABLE t) {
    if(!cityStats)
        return;

    char buffer[128];

    CityStats cs = getCont(cityStats);
    int size = getCityStatsSize(cs);
    size = size > top ? top : size;

    for(int i=0; i<size; i++){
        t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
        t->list[t->line] = malloc(sizeof(char*) * t->col);
        t->list[t->line][0] = strdup(getCityStatsCity(cs));
        sprintf(buffer, "%d", (i+1));
        t->list[t->line][1] = strdup(buffer);
        t->list[t->line][2] = strdup(getCityStatsId(cs, i));
        t->list[t->line][3] = strdup(getCityStatsName(cs, i));
        sprintf(buffer, "%f", getCityStatsStars(cs, i));
        t->list[t->line][4] = strdup(buffer);
        t->line++;
    }

    calculaNegociosCidade(getLeft(cityStats), top, t);
    calculaNegociosCidade(getRight(cityStats), top, t);
}
/**
 * @brief Query 6
 * @param sgr Sgr pretendido
 * @param top Número pretendido
 * @return Table com os top top Businesses
 */
TABLE top_businesses_by_city(SGR sgr, int top) {
    TABLE table = newTable(5);

    for(int i=0; i<HSIZE; i++)
        calculaNegociosCidade(getNode(getAVLIndex(sgr->cityStats, i)), top, table);

    table->info[0] = strdup("Cidade");
    table->info[1] = strdup("Rank");
    table->info[2] = strdup("Id");
    table->info[3] = strdup("Nome");
    table->info[4] = strdup("Estrelas");

    table->header = strdup("Top negócios por cidade");

    return table;
}

//////////////////// QUERY 7 ////////////////////
void calculaInternational(Node userStats, TABLE t){
    if(userStats == NULL)
        return;

    UserStats us = getCont(userStats);
    if(getNumStates(us) > 1) {
        t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
        t->list[t->line] = malloc(sizeof(char*) * t->col);
        t->list[t->line][0] = strdup(getUserStatsId(us));
        t->line++;
    }

    calculaInternational(getLeft(userStats), t);
    calculaInternational(getRight(userStats), t);
}

TABLE international_users(SGR sgr) {
    TABLE table = newTable(1);
    char* buffer = malloc(sizeof(char)*128), buffer2[128];

    for(int i=0; i<HSIZE; i++) {
        calculaInternational(getNode(getAVLIndex(sgr->userStats, i)), table);
    }

    table->info[0] = strdup("Id");

    strcpy(buffer, "Utilizadores internacionais: ");
    sprintf(buffer2, "%d", table->line);
    table->header = strcat(buffer, buffer2);

    return table;
}

//////////////////// QUERY 8 ////////////////////
typedef struct q8 {
    char* business_id;
    char* name;
    float stars;
}*Q8;

int compareq8(const void* a, const void* b) {
    Q8 aux = *((Q8*) a);
    Q8 aux2 = *((Q8*) b);

    float dif = aux2->stars - aux->stars;

    return dif==0 ? 0 : (dif<0) ? -1 : 1;
}

void calculaEstrelasNegocio(Node business, char* category, Q8** aux, int *size) {
    if(business == NULL)
        return;

    BusinessStats bs = getCont(business);
    if(pertenceCategoria(bs, category)){
        *aux = realloc(*aux, sizeof(Q8) * ((*size)+1));
        (*aux)[*size] = malloc(sizeof(struct q8));
        (*aux)[*size]->business_id = strdup(getBusinessStatsId(bs));
        (*aux)[*size]->name = strdup(getBusinessStatsName(bs));
        (*aux)[*size]->stars = getBusinessStatsStars(bs);
        (*size)++;
    }

    calculaEstrelasNegocio(getLeft(business), category, aux, size);
    calculaEstrelasNegocio(getRight(business), category, aux, size);
}

TABLE top_businesses_with_category(SGR sgr, int top, char *category) {
    TABLE table = newTable(3);

    Q8* aux = NULL;
    int size = 0;
    char buffer[128];

    for(int i=0; i<HSIZE; i++) {
        calculaEstrelasNegocio(getNode(getAVLIndex(sgr->businessStats, i)), category, &aux, &size);
    }

    qsort(aux, size, sizeof(Q8), compareq8);

    size = size>top ? top : size;

    table->list = malloc(sizeof(char**) * size);
    for(int i=0; i<size; i++) {
        table->list[i] = malloc(sizeof(char*) * table->col);
        table->list[i][0] = strdup(aux[i]->business_id);
        table->list[i][1] = strdup(aux[i]->name);
        sprintf(buffer, "%f", aux[i]->stars);
        table->list[i][2] = strdup(buffer);

        free(aux[i]->business_id);
        free(aux[i]->name);
    }
    free(aux);

    table->line = size;

    table->info[0] = strdup("Id");
    table->info[1] = strdup("Nome");
    table->info[2] = strdup("Estrelas");

    table->header = strdup("Top negócios de uma categoria");

    return table;
}

//////////////////// QUERY 9 ////////////////////
void verificaPalavra(Node review, char* word, TABLE t) {
    if(review == NULL)
        return;

    Review r = getCont(review);
    if(wordInText(r, word)) {
        t->list = realloc(t->list, sizeof (char**) * (t->line + 1));
        t->list[t->line] = malloc(sizeof(char*) * t->col);
        t->list[t->line][0] = strdup(getIdReview(r));
        t->line++;
    }

    verificaPalavra(getLeft(review), word, t);
    verificaPalavra(getRight(review), word, t);
}

TABLE reviews_with_word(SGR sgr, int top, char *word) {
    TABLE table = newTable(1);

    for(int i=0; i<HSIZE; i++) {
        verificaPalavra(getNode(getAVLIndex(sgr->review, i)), word, table);
    }

    table->info[0] = strdup("Id");
    table->header = strdup("Reviews com comentário que utilizam uma palavra");

    return table;
}
