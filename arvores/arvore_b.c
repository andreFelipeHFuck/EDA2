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
    arvore->raiz = criar_no(arvore);

    return arvore;
}

int pesquisa_binaria(No_B *no, int chave){
    int inicio = 0, fim = no->total - 1, meio;
    while(inicio <= fim){
        meio = (inicio + fim) / 2;
        if(no->chaves[meio] == chave)
            return meio;
        else if(no->chaves[meio] > chave)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return inicio;
}

No_B* localiza_no_chave(ArvoreB *arvore, int chave){
    No_B *no = arvore->raiz;

    while (no != NULL)
    {
        int i = pesquisa_binaria(no, chave);

        if(i < no->total && no->chaves[i] == chave)
            return no;
        else
            no = no->filhos[i];
    }

    return NULL;
    
}

No_B* localiza_no(ArvoreB *arvore, int chave){
    No_B *no = arvore->raiz;

    while(no != NULL){
        int i = pesquisa_binaria(no, chave);

        if(no->filhos[i] == NULL)
            return no;
        else
            no = no->filhos[i];
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

int transbordo(ArvoreB *arvore, No_B *no){
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

void adicona_chave_recursivo(ArvoreB* arvore, No_B* no, No_B* novo, int chave) {
    adiciona_chave_no(no, novo, chave);

    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem];
        novo = divide_no(arvore, no);
    
        if (no->pai == NULL) {
            No_B* pai = criar_no(arvore);
            pai->filhos[0] = no;
            adiciona_chave_no(pai, novo, promovido);

            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
    } else
        adicona_chave_recursivo(arvore, no->pai, novo, promovido);
    }
}

void arvore_B_adicionar(ArvoreB* arvore, int chave){
    No_B* no = localiza_no(arvore, chave);

    adicona_chave_recursivo(arvore, no, NULL, chave);
}

void arvore_B_percorre(No_B *no){
    if(no != NULL){
        for(int i=0; i < no->total; i++){
            arvore_B_percorre(no->filhos[i]);

            printf("%d\n", no->chaves[i]);
        }

        arvore_B_percorre(no->filhos[no->total]);
    }
}

int no_folha(No_B *no){
    int cont = 0;
    for(int i=0; i<no->total; i++){
        if(no->filhos[i] == NULL)
            cont++;
    }

    return cont == no->total ? 1 : 0;
}

// /*
// A exclusão da chave não viola a propriedade do número mínimo 
// de chaves que um nó deve conter.
// */
// void remove_valor(No_B *no, int chave){
//     int pos = pesquisa_binaria(no, chave);
//     int i = pos + 1;

//     while (i <= no->total)
//     {
//         no->chaves[i - 1] = no->chaves[i];
//         no->filhos[i - 1] = no->filhos[i];
//         i++;
//     }

//     no->total--;
// }

// void copia_sucessor(No_B *no, int pos){
//     No_B *no_aux;
//     no_aux = no->filhos[pos];

//     for (; no_aux->filhos[0] != NULL;)
//     {
//         no_aux = no_aux->filhos[0];
//     }
//     no->chaves[pos] = no_aux->chaves[1];
// }

// void deslocar_direita(No_B *no, int pos){
//     No_B *no_aux = no->filhos[pos];
//     int j = no_aux->total;

//     while (j > 0){
//         no_aux->chaves[j + 1] = no_aux->chaves[j];
//         no_aux->filhos[j + 1] = no_aux->filhos[j];
//     }

//     no_aux->chaves[1] = no->chaves[pos];
//     no_aux->filhos[1] = no_aux->filhos[0];
//     no_aux->total++;

//     no_aux = no->filhos[pos - 1];
//     no->chaves[pos] = no_aux->chaves[no_aux->total];
//     no->filhos[pos] = no_aux->filhos[no_aux->total];
//     no_aux->total--;
// }

// void deslocar_esquerda(No_B *no, int pos){
//     int j = 1;
//     No_B *no_aux = no->filhos[pos - 1];

//     no_aux->total++;
//     no_aux->chaves[no_aux->total] = no->chaves[pos];
//     no_aux->filhos[no_aux->total] = no->filhos[pos]->filhos[0];

//     no_aux = no->filhos[pos];
//     no->chaves[pos] = no_aux->chaves[1];
//     no_aux->filhos[0] = no_aux->filhos[1];
//     no_aux->total--;

//     while (j <= no_aux->total)
//     {
//         no_aux->chaves[j] = no_aux->chaves[j + 1];
//         no_aux->filhos[j] = no_aux->filhos[j + 1];
//         j++;
//     }
// }

// void junta_nos(No_B *no, int pos){
//     int j = 1;

//     No_B *no_aux1 = no->filhos[pos];
//     No_B *no_aux2 = no->filhos[pos - 1];

//     no_aux2->total++;
//     no_aux2->chaves[no_aux2->total] = no->chaves[pos];
//     no_aux2->filhos[no_aux2->total] = no->filhos[0];

//     while (j <= no_aux1->total){
//         no->chaves[j] = no->chaves[j + 1];
//         no->filhos[j] = no->filhos[j + 1];
//         j++;
//     }
//     no->total--;
//     free(no_aux1);
// }

// void ajustar_nos(ArvoreB *arvore, No_B *no, int pos){
//     if(!pos){
//         if(no->filhos[1]->total > arvore->ordem)
//             deslocar_esquerda(no, 1);
//         else
//             junta_nos(no, 1);
//     }else{
//         if(no->total != pos){
//             if(no->filhos[pos - 1]->total > arvore->ordem)
//                 deslocar_direita(no, pos);
//             else{
//                 if(no->filhos[pos + 1]->total > arvore->ordem)
//                     deslocar_esquerda(no, pos + 1);
//                 else
//                     junta_nos(no, pos);
//             }
//         }else{
//             if(no->filhos[pos - 1]->total > arvore->ordem)
//                 deslocar_direita(no, pos);
//             else
//                 junta_nos(no, pos);
//         }
//     }
// }

// int deletar_valor_do_no(ArvoreB *arvore, No_B *no, int chave){
//     int pos, flag = 0;

//     if(no){
//         if(chave < no->chaves[1]){
//             pos = 0;
//             flag = 0;
//         }else{
//             for(pos = no->total; (chave < no->chaves[pos] && pos > 1); pos--);

//             if(chave == no->chaves[pos]){
//                 flag = 1;
//             }else{
//                 flag = 0;
//             }
//         }

//         if(flag){
//             printf("TESTE\n");
//             if(no->filhos[pos - 1]){
//                 copia_sucessor(no, pos);
//                 flag = deletar_valor_do_no(arvore, no->filhos[pos] ,no->chaves[pos]);

//                 if(flag == 0){
//                     printf("ITEM NAO PRESENTE NA ARVORE-B\n");
//                 }
//             }else{
//                 remove_valor(no, pos);
//             }
//         }else{
//             flag = deletar_valor_do_no(arvore, no->filhos[pos], chave);
//         }

//         if(no->filhos[pos]){
//             if(no->filhos[pos]->total < arvore->ordem)
//                 ajustar_nos(arvore, no, pos);
//         }
//     }

//     printf("FLAG %d\n", flag);
//     return flag;
// }

// void arvore_B_deletar(ArvoreB *arvore, int chave){
//     No_B *no = arvore->raiz;
//     No_B *no_aux;

//     if(!deletar_valor_do_no(arvore, no, chave)){
//         printf("Não está presente\n");
//         return;
//     }else{
//         if(no->total == 0){
//             no_aux = no;
//             no_aux = no->filhos[0];
//             free(no_aux);
//         }
//     }
//     arvore->raiz = no;
// }


void remove_valor(No_B *no, int chave){
    int pos = pesquisa_binaria(no, chave);
    int i = pos + 1;

    while (i <= no->total)
    {
        no->chaves[i - 1] = no->chaves[i];
        no->filhos[i - 1] = no->filhos[i];
        i++;
    }

    no->total--;
}

void arvore_B_deletar(ArvoreB *arvore, int chave){
    No_B *no =  localiza_no_chave(arvore, chave);

    if(no == NULL){return;}

    if(no_folha(no)){

    }
}