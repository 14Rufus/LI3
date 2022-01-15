#include "view.h"

void menuPath() {
    printf("\n---------------------------\n");
    printf(" Escolha o path a utilizar\n");
    printf("---------------------------\n");
    printf(" 1 | Path default\n");
    printf(" 2 | Path personalizado\n");
    printf("---------------------------\n");
}

void printLerInt(int min, int max) {
    printf("Introduza um número entre %d e %d:\n", min, max);
}

void printTable(TABLE t, int page, int max, int maxpage, int size){
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("                                       Página %d/%d\n", page+1, maxpage+1);
    printf("%s\n", getHeader(t));
    printf("------------------------------------------------------------------------------------------------------\n");

    for(int i=0; i<getCol(t); i++)
        printf("%s ", getInfo(t, i));
    printf("\n");
    for (int i = max * page; i < (max * (page + 1)) && i < size; i += max) {
        for(int j=i; (j<i+max) && (j<size); j++) {
            for (int k = 0; k < getCol(t); k++)
                printf("%s ", getList(t, j, k));
            printf("\n");
        }
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    printf("      [N] Next Page | [P] Previous Page | [F] First Page | [L] Last Page | [#] Page | [Q] Quit        \n");
    printf("------------------------------------------------------------------------------------------------------\n");
}

void printInsert(){
    printf(">> ");
}

void printTime(clock_t start, clock_t end) {
    printf("\nTempo de carregamento dos ficheiros: %.6f s\n", (double) (end - start) / CLOCKS_PER_SEC);
}


void printUsersPath() {
    printf("Introduza o path para o ficheiro dos Users:\n");
}

void printBusinessPath() {
    printf("Introduza o path para o ficheiro dos Businesses:\n");
}

void printReviewPath() {
    printf("Introduza o path para o ficheiro das Reviews:\n");
}

void printQuerieExecutada() {
    printf("Querie Executada\n");
}

void printSair() {
    printf("A fechar o programa");
}

void printProjecaoExecutada() {
    printf("Projeção Executada\n");
}

void printIndexacaoExecutada() {
    printf("Indexação Executada\n");
}

void printErro() {
    printf("Comando inválido\n");
}

void printLoadFromCSV() {
    printf("Loaded from CSV\n");
}

void printLoadToCSV() {
    printf("Loaded to CSV\n");
}