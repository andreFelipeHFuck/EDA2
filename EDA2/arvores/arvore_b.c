#include "arvore_b.h"

int numeroComparacoes = 0;

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
        numeroComparacoes++;
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
        numeroComparacoes++;
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
        numeroComparacoes++;
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
    numeroComparacoes++;
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
        numeroComparacoes++;
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

No_B* remover_no(No_B *no){
    if(no == NULL)
        return NULL;
    for(int i=0; i<no->total; i++){
        if(no->filhos[i] == NULL)
            return NULL;
            
        remover_no(no->filhos[i]);
        free(no);
    }
    return NULL;
}

void appendData(char acao, int iteracao, int dado, char nome_arquivo[]){
    FILE *f;
    f = fopen(nome_arquivo, "a");
    if(acao == 'I') fprintf(f, "I");
    else fprintf(f, "R");
    fprintf(f, ":");
    fprintf(f, "%d", iteracao);
    fprintf(f, ":");
    fprintf(f, "%d", dado);
    fprintf(f, ";");
    fclose(f);
}

void geraDados(int numeroIteracoes) {

    int vetorDeDados[numeroIteracoes];

    int vetorMediaAdicionar1[numeroIteracoes];
    int vetorMediaAdicionar5[numeroIteracoes];
    int vetorMediaAdicionar10[numeroIteracoes];

    for(int i=0; i<numeroIteracoes; i++){
        vetorDeDados[i] = 0;
        vetorMediaAdicionar1[i] = 0;
        vetorMediaAdicionar5[i] = 0;
        vetorMediaAdicionar10[i] = 0;
    }

    
    srand(time(NULL));

    for(int i=0; i < 10; i++){
        
        ArvoreB* a1 = arvore_B_criar(1);
        ArvoreB* a5 = arvore_B_criar(5);
        ArvoreB* a10 = arvore_B_criar(10);
        
        for(int n = 1; n < numeroIteracoes+1; n++){
            numeroComparacoes = 0;

            vetorDeDados[n-1] = rand() % 10000;
            arvore_B_adicionar(a1, vetorDeDados[n-1]);
            vetorMediaAdicionar1[n-1] += numeroComparacoes;
        }

        for(int n = 1; n < numeroIteracoes+1; n++){
            numeroComparacoes = 0;

            vetorDeDados[n-1] = rand() % 10000;
            arvore_B_adicionar(a5, vetorDeDados[n-1]);
            vetorMediaAdicionar5[n-1] += numeroComparacoes;
        }

        for(int n = 1; n < numeroIteracoes+1; n++){
            numeroComparacoes = 0;

            vetorDeDados[n-1] = rand() % 10000;
            arvore_B_adicionar(a10, vetorDeDados[n-1]);
            vetorMediaAdicionar10[n-1] += numeroComparacoes;
        }
    }

    for(int n=1; n<numeroIteracoes+1; n++){
        vetorMediaAdicionar1[n-1] /= 10;
        appendData('I', n, vetorMediaAdicionar1[n-1], "../assets/arvoreB1.txt");
    }

    for(int n=1; n<numeroIteracoes+1; n++){
        vetorMediaAdicionar5[n-1] /= 10;
        appendData('I', n, vetorMediaAdicionar5[n-1], "../assets/arvoreB5.txt");
    }


    for(int n=1; n<numeroIteracoes+1; n++){
        vetorMediaAdicionar10[n-1] /= 10;
        appendData('I', n, vetorMediaAdicionar10[n-1], "../assets/arvoreB10.txt");
    }
}


//Limpa o arquivo txt e inicia o calculo de complexidade
void initAB(int maxComapacoes) {
    FILE *p1;
    p1 = fopen("../assets/arvoreB1.txt", "w");
    fprintf(p1, "");
    fclose(p1);

    FILE *p5;
    p5 = fopen("../assets/arvoreB5.txt", "w");
    fprintf(p5, "");
    fclose(p5);

    FILE *p10;
    p10 = fopen("../assets/arvoreB10.txt", "w");
    fprintf(p10, "");
    fclose(p10);

    geraDados(maxComapacoes);
}

int main(){
    initAB(10000);
}