#include "arvores/arvore_b.h"

int main(){
    ArvoreB *arvore_b = arvore_B_criar(4);
    
    for(int i=0; i<10000; i++){
        arvore_B_adicionar(arvore_b, i);
    }

}

