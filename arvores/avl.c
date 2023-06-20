#include "avl.h"

AVL *avl_criar()
{
    AVL *arvore = malloc(sizeof(AVL));
    arvore->raiz = NULL;

    return arvore;
}

int avl_vazia(AVL *arvore)
{
    return arvore->raiz == NULL;
}

No_avl *criar_no(int valor)
{
    No_avl *no = malloc(sizeof(No_avl));
    no->pai = NULL;
    no->direita = NULL;
    no->esquerda = NULL;
    no->valor = valor;
    no->altura = 0;
    return no;
}

int altura_no(No_avl *no)
{
    int esquerda = 0, direita = 0;

    if(no->esquerda != NULL)
        esquerda = no->esquerda->altura + 1;

    if(no->direita != NULL)
        direita = no->direita->altura + 1;
    
    return esquerda > direita ? esquerda : direita;
}

int altura(No_avl* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(No_avl* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura_no(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura_no(no->direita) + 1;
    }
  
    return esquerda - direita;
}

No_avl* rse(AVL* arvore, No_avl* no) {
    No_avl* pai = no->pai;
    No_avl* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

No_avl* rsd(AVL* arvore, No_avl* no) {
    No_avl* pai = no->pai;
    No_avl* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

No_avl* rde(AVL* arvore, No_avl* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

No_avl* rdd(AVL* arvore, No_avl* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

void balanceamento(AVL *arvore, No_avl *no)
{
    int fator = 0;
    while (no != NULL)
    {
        fator = fb(no);
        printf("%d\n", fator);

        if (fator > 1)
        {
            // Rotação para a direita
            if (fb(no->esquerda) > 0)
            {
                printf("RSD(%d)\n", no->valor);
                rsd(arvore, no); // rotação simples a direita, pois o FB do filho tem sinal igual
            }
            else
            {
                printf("RDD(%d)\n", no->valor);
                rdd(arvore, no); // rotação dupla a direita, pois o FB do filho tem sinal diferente
            }
        }
        else if (fator < -1)
        {
            // rotação para a esquerda
            if (fb(no->direita) < 0)
            {
                printf("RSE(%d)\n", no->valor);
                rse(arvore, no); // rotação simples a esquerda, pois o FB do filho tem sinal igual
            }
            else
            {
                printf("RDE(%d)\n", no->valor);
                rde(arvore, no); // rotação dupla a esquerda, pois o FB do filho tem sinal diferente
            }
        }

        no = no->pai;
    }
}

void adicionar_no_arvore_vazia(AVL *arvore, No_avl *no)
{
    printf("NO %d ADICIONADO NA RAIZ DA ARVORE(AVL)\n", no->valor);
    arvore->raiz = no;
}

void adicionar_no_arvore_n_vazia(AVL *arvore, No_avl *no)
{
    No_avl *no_aux = arvore->raiz;
    while (no_aux)
    {
        if (no->valor > no_aux->valor)
        {
            if (no_aux->direita == NULL && no->valor > no_aux->valor)
            {
                no->pai = no_aux;
                no_aux->direita = no;
                printf("NO %d ADICIONADO A DIREITA DE %d\n", no->valor, no->pai->valor);
                break;
            }
            else if (no_aux->esquerda == NULL && no->valor < no_aux->valor)
            {
                no->pai = no_aux;
                no_aux->esquerda = no;
                printf("NO %d ADICIONADO A ESQUERDA DE %d\n", no->valor, no->pai->valor);
                break;
            }

            printf("PERCORRE A DIREITA\n");
            no_aux = no_aux->direita;
        }

        if (no->valor < no_aux->valor)
        {
            if (no_aux->direita == NULL && no->valor > no_aux->valor)
            {
                no->pai = no_aux;
                no_aux->direita = no;
                printf("NO %d ADICIONADO A DIREITA DE %d\n", no->valor, no->pai->valor);
                break;
            }
            else if (no_aux->esquerda == NULL && no->valor < no_aux->valor)
            {
                no->pai = no_aux;
                no_aux->esquerda = no;
                printf("NO %d ADICIONADO A ESQUERDA DE %d\n", no->valor, no->pai->valor);
                break;
            }

            printf("PERCORRE A ESQUERDA\n");
            no_aux = no_aux->esquerda;
        }
    }
}

void percorrer(No_avl *no)
{
    if (no)
    {
        printf("%d\n", no->valor);
        percorrer(no->esquerda);
        percorrer(no->direita);
    }
}

No_avl *avl_adicionar(AVL *arvore, int valor)
{
    No_avl *no = criar_no(valor);

    if (avl_vazia(arvore))
        adicionar_no_arvore_vazia(arvore, no);
    else
        adicionar_no_arvore_n_vazia(arvore, no);

    balanceamento(arvore, no);
    return no;
}


No_avl* remover_no_folha(No_avl *no){
    No_avl *pai = no->pai;

    if(pai == NULL)
        free(no);
    else{
        if(pai->esquerda == no){
            free(no);
            pai->esquerda = NULL;
        }else if(pai->direita == no){
            free(no);
            pai->direita = NULL;
        }
    }

    return pai;
}

No_avl* remover_no_1_filho(AVL *arvore, No_avl *no){
    No_avl *pai = no->pai;
    
    if(pai == NULL){
        if(no->esquerda != NULL){
            arvore->raiz = no->esquerda;
            free(no);
        }else{
            arvore->raiz = no->direita;
            free(no);
        }
    }else{
        if(pai->esquerda == no){
            if(no->esquerda != NULL){
                pai->esquerda = no->esquerda;
                no->esquerda->pai = pai;
                free(no);
                return pai->esquerda;
            }else if(no->direita != NULL){
                pai->esquerda = no->direita;
                no->direita->pai = pai;
                free(no);
                return pai->esquerda;
            }
        }else if(pai->direita == no){
            if(no->esquerda != NULL){
                pai->direita = no->esquerda;
                no->esquerda->pai = pai;
                free(no);
                return pai->direita;
            }else if(no->direita != NULL){
                pai->direita = no->direita;
                no->direita->pai = pai;
                free(no);
                return pai->direita;
            } 
        }

    }

}

No_avl* remover_no_2_filhos(No_avl *no, int valor){
    No_avl *no_aux = no->esquerda;
    No_avl *pai;

    while (no_aux->direita != NULL)
        no_aux = no_aux->direita;
    
    no->valor = no_aux->valor;
    no_aux->valor = valor;
    pai = no_aux->pai;

    remover_no_folha(no_aux);
}

No_avl* arvore_remover_no(AVL *arvore, No_avl *no, int valor){
    No_avl *no_aux = no;

    while(no_aux){
        if(valor == no_aux->valor){
            if(no_aux->esquerda == NULL && no_aux->direita == NULL)
                return remover_no_folha(no_aux);
            else{
                if(no_aux->esquerda != NULL && no_aux->direita != NULL)
                   return remover_no_2_filhos(no_aux, valor);
                else
                    return remover_no_1_filho(arvore, no_aux);
            }
        }else{
            if(valor < no_aux->valor)
                no_aux = no_aux->esquerda;
            else
                no_aux = no_aux->direita;
        }
    }
}

void avl_remover_no(AVL *arvore, int valor){
    No_avl *no_aux =  arvore_remover_no(arvore, arvore->raiz, valor);
    balanceamento(arvore, no_aux);
}

No_avl* remover_no(No_avl *no){
    if(no == NULL)
        return NULL;
    remover_no(no->esquerda);
    remover_no(no->direita);

    free(no);
    return NULL;
}

AVL* avl_remover(AVL *arvore){
    remover_no(arvore->raiz);
    free(arvore);
    return NULL;
}