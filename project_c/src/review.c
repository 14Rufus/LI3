/**
 * @file review.c
 * @brief módulo de dados reponsável pelo armazenamento de informações relativas às review
 */
#include <catalogo.h>
#include "review.h"
#include <string.h>

/**
 * @brief parser responsável pela interpretação da data
 */
typedef struct parseData{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int seconds;
} Data;

/**
 * @brief estrtura responsável pelo armazenamento da informação relativa à review
 */
struct reviewInfo{
    char* id;
    char* user_id;
    char* business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    Data* date;
    char* text;
};

/**
 * @brief função responsável pela inicialização da data
 * @return estrtura data
 */
Data* initData(){
    Data *data = malloc(sizeof(struct parseData));
    data->day = -1;
    data->month = -1;
    data->year = -1;
    data->hour = -1;
    data->minute = -1;
    data->seconds = -1;
    return data;
}

/**
 * @brief função responsável pela conversão de um char para a data
 * @param f char a converter
 * @return estrtura Data
 */
Data* charToDate(char* f){
    Data *new = initData();
    char* hora, *data, *aux;

    data = strsep(&f, " ");
    hora = f;

    aux = strtok(data, "-");
    new->year = atoi(aux);
    aux = strtok(NULL, "-");
    new->month = atoi(aux);
    aux = strtok(NULL, "-");
    new->day = atoi(aux);

    aux = strtok(hora, ":");
    new->hour = atoi(aux);
    aux = strtok(NULL, ":");
    new->minute = atoi(aux);
    aux = strtok(NULL, ":");
    new->seconds = atoi(aux);

    return new;
}

/**
 * @brief função responsável pela conversão de uma data para um char
 * @param date estrutura Data
 * @return carater convertido
 */
char* dateToChar(Data* date) {
    return "come outro";
}

/**
 * @brief função responsável pela criação de uma Review
 * @param id identificador da review
 * @param user_id identificador do utilizador
 * @param business_id identificador do negócio
 * @param stars estrelas stribuidas pelo utilizador
 * @param useful nota 'useful' atribuida pelo utilizador
 * @param funny nota 'funny' atribuida pelo utilizador
 * @param cool nota 'cool' atribuida pelo utilizador
 * @param date data da review
 * @param text texto descritivo da experiência do utilizador
 * @return estrutura Review
 */
Review createReview(char* id, char* user_id, char* business_id, char* stars, char* useful, char* funny, char* cool, char* date, char* text) {
    Review new = calloc(1, sizeof(struct reviewInfo));

    new->id = strdup(id);
    new->user_id = strdup(user_id);
    new->business_id = strdup(business_id);
    new->stars = atof(stars);
    new->useful = atoi(useful);
    new->funny = atoi(funny);
    new->cool = atoi(cool);
    new->date = charToDate(date);
    new->text = text==NULL ? NULL : strdup(text);

    return new;
}

/**
 * @brief função que devolve o identificador de uma determinada review
 * @param review estrutura review
 * @return identificador da review em questão
 */
char* getIdReview(Review review) {
    return review->id;
}

/**
 * @brief função que devolve o identificador do user que realizou uma determinada review
 * @param review estrutura review
 * @return dentificador do user que realizou a review
 */
char* getReviewUserId(Review review) {
    return review->user_id;
}

/**
 * @brief função que devolve o identificador do negócio onde foi realizada uma determinada review
 * @param review estrutura review
 * @return identificador do negócio onde foi realizada a review
 */
char* getReviewBusinessId(Review review) {
    return review->business_id;
}

/**
 * @brief função que devolve as stars de uma determinada review
 * @param review estrutura review
 * @return número de stars atribuídas à review
 */
float getReviewStars(Review review) {
    return review->stars;
}

/**
 * @brief função que devolve a nota 'useful' de uma determinada review
 * @param review estrutura review
 * @return nota 'useful' atribuida à review
 */
int getReviewUseful(Review review) {
    return review->useful;
}

/**
 * @brief função que devolve a nota 'funny' de uma determinada review
 * @param review estrutura review
 * @return nota 'funny' atribuida à review
 */
int getReviewFunny(Review review) {
    return review->funny;
}

/**
 * @brief função que devolve a nota 'cool' de uma determinada review
 * @param review estrutura review
 * @return nota 'cool' atribuida à review
 */
int getReviewCool(Review review) {
    return review->cool;
}

/**
 * @brief função que devolve a data de uma determinada review
 * @param review estrutura review
 * @return string com a data da review
 */
char* getReviewData(Review review) {
    return dateToChar(review->date);
}

/**
 * @brief função que devolve a apreciação em texto de uma determinada review
 * @param review estrutura review
 * @return apreciação em texto de uma review
 */
char* getReviewText(Review review) {
    return review->text;
}

/**
 * @brief função responsável pela procura de uma determinada palavra na apreciação em texto de uma review
 * @param review estrutura review
 * @param s2 palavra a procurar
 * @return validação da existência ou não existência
 */
int wordInText(Review review, char* s2){
    char *s1 = review->text;
    int r=0;

    if(!s1)
        return r;

    int len = strlen(s2);
    char* x = strstr(s1,s2);

    if(!x)
        return r;

    char c1 = *(x - sizeof(char)); // char anterior à strstr
    char c2 = *(x + len*sizeof(char)); // char posterior à strstr

    if (x == s1 && !isalpha(c2) && !isdigit(c2)) //teste inicio
        r = 1;
    else if (c2 == '\0' && !isalpha(c1) && !isdigit(c1)) //teste meio
        r = 1;
    else if (!isalpha(c1) && !isdigit(c1) && !isalpha(c2) && !isdigit(c2)) //teste fim
        r = 1;

    return r;
}

/**
 * @brief função que liberta o espaço de memória ocupado pela estrutura Review
 * @param review estrutura review
 */
void freeReview(Review review) {
    free(review->id);
    free(review->user_id);
    free(review->business_id);
    free(review->date);
    free(review->text);
    free(review);
}