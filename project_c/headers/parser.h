#ifndef __parser_h_
#define __parser_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "user.h"
#include "business.h"
#include "review.h"
#include "stats.h"

void parseUsers(char* path, Catalogo userCat);
void parseBusiness(char* path, Catalogo businessCat, Catalogo businessStatsCat);
void parseReview(char* path, Catalogo reviewCat, Catalogo userCat, Catalogo businessCat, Catalogo userStatsCat, Catalogo cityStatsCat, Catalogo businessStatsCat);

#endif