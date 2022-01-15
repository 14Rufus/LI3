#ifndef __view_h
#define __view_h

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "sgr.h"

void menuPath();
void printLerInt(int min, int max);
void printTable(TABLE t, int page, int max, int maxpage, int size);
void printInsert();
void printTime(clock_t start, clock_t end);
void printUsersPath();
void printBusinessPath();
void printReviewPath();
void printErro();
void printQuerieExecutada();
void printProjecaoExecutada();
void printIndexacaoExecutada();
void printSair();
void printLoadFromCSV();
void printLoadToCSV();

#endif
