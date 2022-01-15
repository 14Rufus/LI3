#include "avl.h"
#include <string.h>

/* Estrutura de uma AVL- tree Balanceada de Procura **/
struct avl
{
    int size;
    Node tree;
};

/* Estrutura de um nodo de uma AVL com a informação necessária **/
struct node
{
    char *key;
    void *content;
    int size;
    Node left;
    Node right;
};


/**
 * @brief Inicializa uma avl
 * @return avl inicializada
 */
AVL initAVL()
{
    AVL new = malloc(sizeof(struct avl));
    new->size = 0;
    new->tree = malloc(sizeof(struct node));
    new->tree = NULL;

    return new;
}

/**
 * @brief Inicializa uma árvore balanceada
 * @param nodo Nodo a null
 * @param info String que será a key do nodo
 * @param estrutura Contéudo que será armazenado no nodo
 * @return Nodo com a key e o conteúdo dado
 */
static Node newNode(Node nodo, char* info, void *estrutura)
{
    nodo = malloc(sizeof(struct node));
    nodo->key = strdup(info);
    nodo->content = estrutura;
    nodo->size = 1;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}

/**
 * @brief Liberta a memória alocada de uma árvore
 * @param nodo Nodo que corresponde à raiz da árvore a libertar
 * @param f Função que liberta o espaço alocado pelo conteúdo de cada nodo
 */
static void tree_free(Node nodo, Funcao f)
{
    if (nodo != NULL)
    {
        tree_free(nodo->left, f);
        tree_free(nodo->right, f);
        if (nodo->content != NULL)
        {
            f(nodo->content);
        }
        free(nodo->key);
        free(nodo);
    }
}

/**
 * @brief Liberta a memória alocada de uma AVL
 * @param nodo AVL a ser libertada
 * @param f Função que liberta o conteúdo dos nodos da árvore
 */
void freeAVL(AVL nodo, Funcao f)
{
    tree_free(nodo->tree, f);
    free(nodo);
}

/**
 * @brief Calcula o maior de dois inteiros
 * @param x1 Primeiro inteiro
 * @param x2 Segundo inteiro
 * @return Maior dos dois inteiros
 */
int max(int x1, int x2)
{
    return (x1 > x2) ? x1 : x2;
}

/**
 * @brief Calcula o tamanho de uma árvore
 * @param a Nodo que corresponde à raiz da árvore pretendida
 * @return Tamanho da árvore
 */
int size(Node a)
{
    if (a == NULL)
        return 0;
    return a->size;
}

/**
 * @brief Retorna o nodo que corresponde à raiz da AVL
 * @param a Árvore que pretendemos
 * @return Nodo que corresponde à raiz da avl fornecida
 */
Node getNode(AVL a)
{
    return a->tree;
}

/**
 * @brief Retorna o nodo à esquerda do nodo dado
 * @param a Nodo que pretendemos obter a esquerda
 * @return Nodo à esquerda do nodo dado
 */
Node getLeft(Node a)
{
    return a->left;
}

/**
 * @brief Retorna o nodo à direita do nodo dado
 * @param a Nodo que pretendemos obter a direita
 * @return Nodo à direita do nodo dado
 */
Node getRight(Node a)
{
    return a->right;
}

/**
 * @brief Retorna a key de um nodo
 * @param a Nodo que pretendemos obter a key
 * @return Key do nodo dado
 */
char *getKey(Node a)
{
    return a->key;
}

/**
 * @brief Retorna a diferença de alturas entre a tree da esquerda e a tree da direita
 * @param n Nodo
 * @return Inteiro que corresponde à diferença das alturas
 */
static int getBalance(Node n)
{
    return size(n->left) - size(n->right);
}

/**
 * @brief Retorna o conteúdo associado a um nodo
 * @param n Nodo
 * @return Conteúdo do nodo
 */
void *getCont(Node n)
{
    return n->content;
}

/**
 * @brief Roda um nodo dado para a direita
 * @param y Nodo
 * @return Nodo depois de uma rotação à direita
 */
Node rightRotate(Node y)
{
    Node x = y->left;
    Node T2 = x->right;

    x->right = y;
    y->left = T2;

    y->size = max(size(y->left), size(y->right)) + 1;
    x->size = max(size(x->left), size(x->right)) + 1;

    return x;
}

/**
 * @brief Roda um nodo dado para a esquerda
 * @param y Nodo
 * @return Nodo depois de uma rotação à esquerda
 */
Node leftRotate(Node x)
{
    Node y = x->right;
    Node T2 = y->left;

    y->left = x;
    x->right = T2;

    x->size = max(size(x->left), size(x->right)) + 1;
    y->size = max(size(y->left), size(y->right)) + 1;

    return y;
}

/**
 * @brief Insere um nodo numa árvore balanceada
 * @param nodo Nodo a inserir
 * @param info key do nodo a inserir
 * @param estrutura Conteúdo do nodo a inserir
 * @return Árvore balanceada com o novo nodo inserir
 */
static Node node_insert(Node nodo, char* info, void* estrutura)
{
    int balance;

    if (nodo != NULL)
    {

        if (strcmp(info, nodo->key) < 0)
            nodo->left = node_insert(nodo->left, info, estrutura);
        else if (strcmp(info, nodo->key) > 0)
            nodo->right = node_insert(nodo->right, info, estrutura);
        else
            nodo->content = estrutura;

        /* Atualiza os pesos */
        nodo->size = max(size(nodo->left), size(nodo->right)) + 1;

        /* Verifica o balanceamento */
        balance = getBalance(nodo);

        /* Left Left Case */
        if (balance > 1 && strcmp(info, nodo->left->key) < 0)
            return rightRotate(nodo);

        /* Right Right Case */
        if (balance < -1 && strcmp(info, nodo->right->key) > 0)
            return leftRotate(nodo);

        /* Left Right Case */
        if (balance > 1 && strcmp(info, nodo->left->key) > 0)
        {
            nodo->left = leftRotate(nodo->left);
            return rightRotate(nodo);
        }
        /* Right Left Case */
        if (balance < -1 && strcmp(info, nodo->right->key) < 0)
        {
            nodo->right = rightRotate(nodo->right);
            return leftRotate(nodo);
        }
    }
    else
        nodo = newNode(nodo, info, estrutura);

    return nodo;
}

/**
 * @brief Inserir um nodo numa árvore
 * @param tree AVL onde se vai inserir o nodo
 * @param key Key do nodo a inserir
 * @param estrutura Conteeúdo do nodo a inserir
 * @return AVL com o novo nodo inserido
 */
AVL avl_insert(AVL tree, char* key, void* estrutura)
{
    tree->tree = node_insert(tree->tree, key, estrutura);
    tree->size++;
    return tree;
}

/**
 * @brief Atualiza a um nodo
 * @param nodo Nodo atualizado
 * @param info Key atualizada
 * @param estrutura Conteúdo atualizado
 * @return Nodo atualizado
 */
static Node node_update(Node nodo, char* info, void* estrutura)
{
    if (strcmp(info, nodo->key) < 0)
        nodo->left = node_insert(nodo->left, info, estrutura);
    else if (strcmp(info, nodo->key) > 0)
        nodo->right = node_insert(nodo->right, info, estrutura);
    else
        nodo->content = estrutura;

    return nodo;
}

/**
 * @brief Insere uma nova estrutura na árvore a key
 * @param tree AVL onde se insere
 * @param key Key a inserir
 * @param estrutura Conteúdo a inserir
 * @return AVL atualizada
 */
AVL avl_update(AVL tree, char* key, void* estrutura) {
    tree->tree = node_update(tree->tree, key, estrutura);
    return tree;
}

/**
 * @brief Verifica se existe um nodo, através da sua key
 * @param node Nodo a procurar
 * @param value Key a procurar
 * @return Int 1 se encontra e 0 se não
 */
static int node_lookUp(Node node, char* value)
{
    int r;
    if (node == NULL)
        return 0;
    else
    {
        r = strcmp(value, node->key);
        if (r == 0)
            return 1;
        else if (r < 0)
            return node_lookUp(node->left, value);
        else
            return node_lookUp(node->right, value);
    }
}

/**
 * @brief Verifica se existe o value na árvore
 * @param tree AVL a procurar
 * @param value Key a procurar
 * @return
 */
int avl_lookUp(AVL tree, char* value)
{
    if (tree == NULL)
        return 0;
    return node_lookUp(tree->tree, value);
}

/**
 * @brief Retorna o conteúdo de um nodo com key value
 * @param node Nodo a procurar
 * @param value Key do nodo pretendido
 * @return Conteúdo do nodo pretendido
 */
void* node_getEstrutura(Node node, char* value)
{
    int r;
    if (node == NULL)
        return NULL;
    else
    {
        r = strcmp(value, node->key);
        if (r == 0)
            return node->content;
        else if (r < 0)
            return node_getEstrutura(node->left, value);
        else
            return node_getEstrutura(node->right, value);
    }
}

/**
 * @brief Retorna o conteúdo de um nodo com key value numa AVL
 * @param node AVL a procurar
 * @param value Key do nodo pretendido
 * @return Conteúdo do nodo pretendido
 */
void* avl_getEstrutura(AVL node, char* value)
{
    if(!node)
        return NULL;
    return node_getEstrutura(node->tree, value);
}