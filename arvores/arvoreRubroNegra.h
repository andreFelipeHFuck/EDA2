#include <stdlib.h>
#include <stdio.h>
#include <time.h>


enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} No;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} Arvore;

No* criarNo(Arvore *arvore, No *no, int valor);
void balancear(Arvore *arvore, No *no);
Arvore* criar();
int vazia(Arvore *arvore);
No* adicionar(Arvore *arvore, int valor);
No* adicionarNo(Arvore *arvore, No *no, int valor);
No* localizar(Arvore *arvore, int valor);
void balancear(Arvore *arvore, No *no);
void rotacionarEsquerda(Arvore *arvore, No *no);
void rotacionarDireita(Arvore *arvore, No *no);
void deleteTree(Arvore *arvore, struct no *no);
No *deletarNo(Arvore *arvore, No *no);
void *deletar(Arvore *arvore, int valor);
void buscaEmLargura(Arvore *arvore, int valor);
void appendData(char acao, int iteracao, int dado);
void geraDados(Arvore *arvore, int maxIteracoes);
void initARN(int maxIteracoes);