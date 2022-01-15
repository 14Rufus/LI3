#ifndef __user_h_
#define __user_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

typedef struct userInfo* User;

User createUser(char* id, char* name, char* friends);

User getUser(Catalogo userCat, char* id);

char* getIdUser(User user);

char* getUserName(User user);

void freeUser(User user);

#endif