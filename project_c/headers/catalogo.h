#ifndef _catalogo_h_
#define _catalogo_h_

#include "avl.h"

#define HSIZE 38

typedef struct catalogo *Catalogo;

Catalogo initTable();

int hash(char key);

void insere_Catalogo(Catalogo cat, char *key, void* content);

void update_Catalogo(Catalogo cat, char *key, void* content);

int lookUpCatalogo(Catalogo cat, char* key);

void *getEstruturaCatalogo(Catalogo catalogo, char *key);

AVL getAVLKey(Catalogo catalogo, char* key);

AVL getAVLIndex(Catalogo catalogo, int index);

void freeCatalogo(Catalogo catalogo, Funcao f);

#endif