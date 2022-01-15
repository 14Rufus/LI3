#ifndef __business_h_
#define __business_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "catalogo.h"

typedef struct businessInfo *Business;

Business createBusiness(char *id, char *name, char *city, char *state, char *categories);
Business getBusiness(Catalogo businessCat, char* id);

char *getBusinessName(Business business);
char *getIdBusiness(Business business);
char *getBusinessCity(Business business);
char *getBusinessState(Business business);
char ** getCategories(Business b);
int getNumCategories(Business b);
void freeBusiness(Business business);

#endif