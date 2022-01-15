#ifndef __sgr_h_ //if not defined
#define __sgr_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "parser.h"
#include "review.h"
#include "stats.h"

typedef struct sgr *SGR;
typedef struct table *TABLE;

TABLE newTable(int col);

TABLE newIndex(TABLE t, int i, int j);

TABLE newCollumn(TABLE t, int j);

TABLE newCSV(int line, int col, char** info, char*** list);

SGR init_sgr();

void free_sgr(SGR sgr);

int getLine(TABLE t);

int getCol(TABLE t);

char* getInfo(TABLE t, int i);

char* getHeader(TABLE t);

void freeTable(TABLE t);

char* getList(TABLE t, int line, int col);

/* query 1 */
SGR load_sgr(char *users, char *businesses, char *reviews);

/* query 2 */
TABLE businesses_started_by_letter(SGR sgr, char letter);

/* query 3 */
TABLE business_info(SGR sgr, char *business_id);

/* query 4 */
TABLE businesses_reviewed(SGR sgr, char *user_id);

/* query 5 */
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);

/* query 6 */
TABLE top_businesses_by_city(SGR sgr, int top);

/* query 7 */
TABLE international_users(SGR sgr);

/* query 8 */
TABLE top_businesses_with_category(SGR sgr, int top, char *category);

/* query 9 */
TABLE reviews_with_word(SGR sgr, int top, char *word);

#endif