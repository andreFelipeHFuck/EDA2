#include "arvores/arvore_b.h"

int main(){
    ArvoreB *arvore_b = arvore_B_criar(4);
    
    arvore_B_adicionar(arvore_b, 1);
    arvore_B_adicionar(arvore_b, 2);

    arvore_B_percorre(arvore_b->raiz);
}

