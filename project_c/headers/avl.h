#ifndef __avl_h_
#define __avl_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct avl* AVL;
typedef struct node* Node;
typedef void (Funcao)(void *);

AVL initAVL();

AVL atualiza_avl(AVL arvore, char *value, void* estrutura);

void freeAVL(AVL nodo, Funcao f);

Node getNode(AVL a);

Node getLeft(Node a);

Node getRight(Node a);

char *getKey(Node a);

void *getCont(Node n);

int avl_size(AVL tree);

AVL avl_insert(AVL tree, char* key, void* estrutura);

AVL avl_update(AVL tree, char* key, void* estrutura);

int avl_lookUp(AVL tree, char* value);

void* node_getEstrutura(Node node, char* value);

void* avl_getEstrutura(AVL node, char* value);

#endif