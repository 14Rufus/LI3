#ifndef __stats_h
#define __stats_h

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "catalogo.h"

typedef struct cityStats *CityStats;
typedef struct userStats *UserStats;
typedef struct businessStats *BusinessStats;

UserStats createUserStats(char* id, char* name);
void updateUserStats(UserStats us, char* state);
void freeUserStats(UserStats us);
char *getUserStatsId(UserStats us);
char *getUserStatsName(UserStats us);
int getNumStates(UserStats us);

CityStats createCityStats(char* city);
void updateCityStats(CityStats bs, char* business_id, char* name, float stars);
void freeCityStats(CityStats bs);
void sortCityStats(CityStats cs);
char *getCityStatsCity(CityStats bs);
int getCityStatsSize(CityStats cs);
float getCityStatsStars(CityStats cs, int i);
char* getCityStatsId(CityStats cs, int i);
char* getCityStatsName(CityStats cs, int i);

BusinessStats createBusinessStats(char* business_id, char* name, char* city, char* state);
void updateBusinessStats(BusinessStats bs, float stars, char** categories, int numCategories);
void freeBusinessStats(BusinessStats bs);
BusinessStats getBusinessStats(Catalogo businessStatsCat, char* id);
int pertenceCategoria(BusinessStats bs, char* category);
char *getBusinessStatsId(BusinessStats bs);
char *getBusinessStatsName(BusinessStats bs);
float getBusinessStatsStars(BusinessStats bs);
int getBusinessStatsNumStars(BusinessStats bs);
char *getBusinessStatsCity(BusinessStats bs);
char *getBusinessStatsState(BusinessStats bs);


#endif
