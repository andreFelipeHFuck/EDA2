#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct no{
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
    int valor;
    int altura;
}No_avl;

typedef struct arvore{
    struct no *raiz;
}AVL;

int altura_no(No_avl *no);

AVL* avl_criar();
No_avl*  avl_adicionar(AVL *arvore, int valor);
No_avl*  avl_remover_no(AVL *arvore, int valor);

void balanceamento(AVL *arvore, No_avl *no);
No_avl *rsd(AVL *arvore, No_avl *no_avl);
No_avl *rse(AVL *arvore, No_avl *no_avl);
No_avl *rdd(AVL *arvore, No_avl *no_avl);
No_avl *rde(AVL *arvore, No_avl *no_avl);

void percorrer(No_avl* no);

