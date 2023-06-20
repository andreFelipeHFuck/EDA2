#include "arvore_b.h"

No_B* criar_no(ArvoreB *arvore){
    int max = arvore->ordem * 2;
    No_B *no = malloc(sizeof(No_B));

    no->pai = NULL;

    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(No_B) * (max + 2));
    no->total = 0;

    for(int i=0; i < max + 2; i++)
        no->filhos[i] = NULL;
    
    return no;
}

ArvoreB* arvore_B_criar(int ordem){
    ArvoreB *arvore = malloc(sizeof(ArvoreB));

    arvore->ordem = ordem;
    arvore->raiz = criaNo(arvore);
}

int pesquisa_binaria(No_B *no, int chave){
    int inicio = 0, fim = no->total - 1, meio;
    while(inicio <= fim){
        meio = (inicio + fim) / 2;
        if(no->chaves[meio] == chave)
            return meio;
    }else if(no->chaves[meio] > chave)
        fim = meio - 1;
    else
        inicio = meio + 1;
    
    return inicio;
}

No_B* localiza_no(ArvoreB *arvore, int chave){
    No_B *no = arvore->raiz;

    while(no != NULL){
        int i = pesquisa_binaria(no, chave);

        if(no->filhos[i] == NULL)
            return no;
        else
            no = no->filhos;
    }
    return NULL;
}

void adiciona_chave_no(No_B *no, No_B *direita, int chave){
    int i = pesquisa_binaria(no, chave);

    for(int j = no->total - 1; j >= i; j--){
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }

    no->chaves[i] = chave;
    no->filhos[i + 1] = direita;

    no->total++;
}

int tranbordo(ArvoreB *arvore, No_B *no){
    return no->total > arvore->ordem * 2;
}

No_B* divide_no(ArvoreB *arvore, No_B *no){
    int meio = no->total / 2;
    No_B *novo = criar_no(arvore);
    novo->pai = no->pai;

    for(int i = meio + 1; i < no->total; i++){
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if(novo->filhos[novo->total] != NULL)
            novo->filhos[novo->total]->pai = novo;
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];

    if(novo->filhos[novo->total] != NULL)
        novo->filhos[novo->total]->pai = novo;
    
    no->total = meio;
    return novo;
}

void adicionar_chave(ArvoreB *arvore, int chave){
    No* no = localiza_no(arvore, chave);

    adiciona_chave_recursiva(arvore, no, NULL, chave);
}

void adicionaChaveRecursivo(ArvoreB* arvore, No_B* no, No_B* novo, int chave) {
    adicionaChaveNo(no, novo, chave);

    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem];
        No_B* novo = divideNo(arvore, no);

    if (no->pai == NULL) {
        No_B* raiz = criaNo(arvore);
        raiz->filhos[0] = no;
        adicionaChaveNo(pai, novo, promovido);

        no->pai = raiz;
        novo->pai = raiz;
        arvore->raiz = raiz;
    } else
        adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
    }
}