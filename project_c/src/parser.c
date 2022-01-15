#include "parser.h"

#define BUFFSIZE 1024

/**
 * @brief Lẽ o ficheiro de Users e coloca no catalogo
 * @param path Path do ficehiro a ler
 * @param userCat Catalogo onde serão colocados os Users
 */
void parseUsers(char* path, Catalogo userCat) {
    FILE* f = fopen(path, "r");
    int size = BUFFSIZE;
    char *buffer = malloc(sizeof(char) * size);
    char *id, *name, *friends, *aux;

    fgets(buffer, size, f);

    while(fgets(buffer, size, f)) {
        unsigned long len = strlen(buffer);
        if (len == size - 1 && buffer[len - 2] != '\n') {
            fseek(f, -len, SEEK_CUR);
            size *= 2;
            buffer = realloc(buffer, size);
            continue;
        }
        aux = buffer;

        id = strsep(&aux, ";");
        name = strsep(&aux, ";");
        friends = strsep(&aux, "\n");

        if (!getUser(userCat, id)) {
            User new = createUser(id, name, friends);
            insere_Catalogo(userCat, getIdUser(new), new);
        }
    }
    free(buffer);
}

/**
 * @brief Lẽ o ficheiro de Businesses e coloca no catalogo
 * @param path Path do ficehiro a ler
 * @param userCat Catalogo onde serão colocados os Businesses
 */
void parseBusiness(char* path, Catalogo businessCat, Catalogo businessStatsCat) {
    FILE *f = fopen(path, "r");
    int size = BUFFSIZE;
    char *buffer = malloc(sizeof(char) * size);
    char *id, *name, *city, *state, *categories, *aux;

    fgets(buffer, size, f);

    while (fgets(buffer, size, f)) {
        unsigned long len = strlen(buffer);
        if (len == size-1 && buffer[len-2] != '\n') {
            fseek(f, -len, SEEK_CUR);
            size *= 2;
            buffer = realloc(buffer, size);
            continue;
        }
        aux = buffer;

        if(!getBusiness(businessCat, id)) {
            id = strsep(&aux, ";");
            name = strsep(&aux, ";");
            city = strsep(&aux, ";");
            state = strsep(&aux, ";");
            categories = strsep(&aux, "\n");

            Business new = createBusiness(id, name, city, state, categories);
            insere_Catalogo(businessCat, getIdBusiness(new), new);

            BusinessStats bs = createBusinessStats(id, getBusinessName(new), getBusinessCity(new),
                                                   getBusinessState(new));
            insere_Catalogo(businessStatsCat, id, bs);
        }
    }

    free(buffer);
}

/**
 * @brief Organiza uma árvore de city
 * @param city Árvore de city a ser organizada
 */
void sortCity(Node city) {
    if(!city)
        return;

    sortCityStats(getCont(city));

    sortCity(getLeft(city));
    sortCity(getRight(city));
}

/**
 * @brief Lẽ o ficheiro de Businesses e coloca no catalogo
 * @param path Path onde está o ficheiro a ler
 * @param reviewCat Catalogo onde serão colocadas a Reviews
 * @param userCat Catalogo de Users
 * @param businessCat Catalogo de Businesses
 * @param userStatsCat Catalogo de Stats de Users
 * @param cityStatsCat Catalogo de Stats de City
 * @param businessStatsCat Catalogo de Stats de Businesses
 */
void parseReview(char* path, Catalogo reviewCat, Catalogo userCat, Catalogo businessCat, Catalogo userStatsCat, Catalogo cityStatsCat, Catalogo businessStatsCat) {
    FILE* f = fopen(path, "r");
    int size = BUFFSIZE;
    char* buffer = malloc(sizeof(char) * size);
    char *id, *user_id, *business_id, *stars, *useful, *funny, *cool, *date, *text, *aux;

    fgets(buffer, size, f);

    while (fgets(buffer, size, f) && buffer[0]!='\n') {
        unsigned long len = strlen(buffer);
        if (len == size-1 && buffer[len-2] != '\n') {
            fseek(f, -len, SEEK_CUR);
            size *= 2;
            buffer = realloc(buffer, size);
            continue;
        }
        aux = buffer;

        id = strsep(&aux, ";");
        user_id = strsep(&aux, ";");
        business_id = strsep(&aux, ";");
        stars = strsep(&aux, ";");
        useful = strsep(&aux, ";");
        funny = strsep(&aux, ";");
        cool = strsep(&aux, ";");
        date = strsep(&aux, ";");
        text = strsep(&aux, "\n");

        if(getUser(userCat,user_id) && getBusiness(businessCat, business_id)) {
            Review new = createReview(id, user_id, business_id, stars, useful, funny, cool, date, text);
            insere_Catalogo(reviewCat, getIdReview(new), new);

            User u = getUser(userCat, user_id);
            UserStats us = getEstruturaCatalogo(userStatsCat, user_id);
            if(!us) {
                us = createUserStats(user_id, getUserName(u));
                insere_Catalogo(userStatsCat, user_id, us);
            }
            Business b = getBusiness(businessCat, business_id);
            updateUserStats(us, getBusinessState(b));

            char *city = getBusinessCity(b);
            CityStats cs = getEstruturaCatalogo(cityStatsCat, city);
            if(!cs) {
                cs = createCityStats(city);
                insere_Catalogo(cityStatsCat, city, cs);
            }
            updateCityStats(cs, getIdBusiness(b), getBusinessName(b), atof(stars));

            BusinessStats bs = getEstruturaCatalogo(businessStatsCat, business_id);
            updateBusinessStats(bs, atof(stars), getCategories(b), getNumCategories(b));
        }
    }

    for(int i=0; i<HSIZE; i++)
        sortCity(getNode(getAVLIndex(cityStatsCat, i)));

    free(buffer);
}