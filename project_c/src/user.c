#include <catalogo.h>
#include "user.h"

//estruturas para inserir na AVL

struct userInfo{
    char *id;
    char *name;
    char **friends;
    int nfriends;
};



//o id  vai ser a key da avl
//a struct vai conter a informacao do content da avl
//+ funcoes de inicializacao


User createUser(char* id, char *name, char *friends) {
    User new = calloc(1, sizeof(struct userInfo));
    new->id = strdup(id);
    new->name = strdup(name);

    new->nfriends = 0;

    char* aux;
    while((aux = strsep(&friends,","))){
        new->friends = realloc(new->friends, sizeof(char*)*(new->nfriends+1));
        new->friends[new->nfriends] = strdup(aux);
        new->nfriends++;
    }

    return new;
}

User getUser(Catalogo userCat, char* id) {
    return getEstruturaCatalogo(userCat, id);
}

char* getIdUser(User user) {
    return user->id;
}

char* getUserName(User user) {
    return user->name;
}

void freeUser(User user) {
    free(user->id);
    free(user->name);
    for(int i=0; i<user->nfriends; i++)
        free(user->friends[i]);
    free(user);
}