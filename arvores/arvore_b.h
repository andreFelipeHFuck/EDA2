#include <stdlib.h>
#include <stdio.h>

typedef struct no_B {
    int total;
    int *chaves;
    struct no_B **filhos;
    struct no_B *pai;
}No_B;

typedef struct arvoreB{
    No_B *raiz;
    int ordem;
}ArvoreB;

ArvoreB* arvore_B_criar(int ordem);
void arvore_B_adicionar(ArvoreB* arvore, int chave);
void arvore_B_percorre(No_B *no);
