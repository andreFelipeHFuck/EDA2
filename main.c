#include "arvores/arvore_b.h"

int main(){
    ArvoreB *arvore_b = arvore_B_criar(4);
    
    arvore_B_adicionar(arvore_b, 8);
    arvore_B_adicionar(arvore_b, 9);
    arvore_B_adicionar(arvore_b, 10);
    arvore_B_adicionar(arvore_b, 11);
    arvore_B_adicionar(arvore_b, 15);
    arvore_B_adicionar(arvore_b, 16);
    arvore_B_adicionar(arvore_b, 17);
    arvore_B_adicionar(arvore_b, 18);
    arvore_B_adicionar(arvore_b, 20);
    arvore_B_adicionar(arvore_b, 23);

    arvore_B_percorre(arvore_b->raiz);
}

