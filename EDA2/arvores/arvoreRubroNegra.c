#include "arvoreRubroNegra.h"

int numeroComparacoes = 0;

Arvore* criar() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vazia(Arvore* arvore) {
    return arvore->raiz == NULL;
}

No* criarNo(Arvore* arvore, No* pai, int valor) {
    No* no = malloc(sizeof(No));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

No* adicionarNo(Arvore* arvore, No* no, int valor) {
    numeroComparacoes++;
    if (valor >= no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

No* adicionar(Arvore* arvore, int valor) {
    if (vazia(arvore)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        No* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
        
        return no;
    }
}

No* localizar(Arvore* arvore, int valor) {
    //Localiza e retorna o ponteiro do nó alvo
    if (!vazia(arvore)) {
        No* no = arvore->raiz;

        while (no != arvore->nulo) {
            numeroComparacoes++;
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void balancear(Arvore* arvore, No* no) {
    if(no == arvore->nulo || no == NULL)return;
    while (no->pai->cor == Vermelho) {
        numeroComparacoes++;
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarDireita(arvore, no->pai->pai); //Caso 3
                }
            }
        } else {
            No *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no); //Caso 2
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho; //Caso 3
                    rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
                }
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda(Arvore* arvore, No* no) {
    numeroComparacoes++;
    No* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(Arvore* arvore, No* no) {
    numeroComparacoes++;
    No* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}


//Funcao auxiliar que deleta a arvore inteira
void deleteTree(Arvore *a, struct no* node){
    if (node == a->nulo) return;
 
    /* first delete both subtrees */
    deleteTree(a, node->esquerda);
    deleteTree(a, node->direita);
   
    /* then delete the node */
    //printf("\n Deleting node: %d", node->valor);
    if(node != a->raiz){
        //printf("\nNao eh a raiz");
        if(node->pai->esquerda != a->nulo){
            if(node->pai->esquerda == node){
                node->pai->esquerda = a->nulo;
            }else{
                node->pai->direita = a->nulo;
            }
        }else{
            node->pai->direita = a->nulo;
        }
    }else{
        a->raiz = NULL;
    }
    free(node);
}


No *deletarNo(Arvore *arvore, No *root){
    // Se o nó alvo nao possui filho a esquerda
    if (root->esquerda == arvore->nulo) {
        // verifica se o no alvo é a raiz
        if(arvore->raiz == root){
            //verifica se a raiz é a ultima a ser removida
            if(root->direita == arvore->nulo){
                free(root);
                arvore->raiz = NULL;
                return arvore->raiz;
            }
            arvore->raiz = root->direita;
            arvore->raiz->pai = arvore->nulo;
            free(root);
            return arvore->raiz;
        }
        //Estes 2 if's verificam se o nodo alvo é maior ou menor que o pai
        if(root->pai->valor < root->valor){
            root->pai->direita = root->direita;
            if(root->direita != arvore->nulo)
                root->direita->pai = root->pai;
            No* temp = root->direita;
            free(root);
            return temp;
        }if(root->pai->valor >= root->valor) {
            root->pai->esquerda = root->direita;
            if(root->direita != arvore->nulo)
                root->direita->pai = root->pai;
            No* temp = root->direita;
            free(root);
            return temp;
        }
    }
    //Caso o nó alvo tenha filho a esquerda, cairá nesse if, que verifica se há filho a direita
    else if (root->direita == arvore->nulo) {
        //Segue a mesma logica do if anterior
        if(arvore->raiz == root){
            arvore->raiz = root->esquerda;
            arvore->raiz->pai = arvore->nulo;
            free(root);
            return arvore->raiz;
        }
        if(root->pai->valor < root->valor){
            root->pai->direita = root->esquerda;
            if(root->esquerda != arvore->nulo)
                root->esquerda->pai = root->pai;
            No* temp = root->esquerda;
            free(root);
            return temp;
        }if(root->pai->valor > root->valor) {
            root->pai->esquerda = root->esquerda;
            if(root->esquerda != arvore->nulo)
                root->esquerda->pai = root->pai;
            No* temp = root->esquerda;
            free(root);
            return temp;
        }
    }
 
    //Caso o nó não possua filhos entrará aqui
    else {
 
        // Encontr o sucessor pertindo inicialmente a direita, e segue ao nó mais a esquerda
        No* succ = root->direita;
        numeroComparacoes++;
        if(succ != arvore->nulo){
            while (succ->esquerda != arvore->nulo) {
                succ = succ->esquerda;
                numeroComparacoes++;
            }
        }
        //Encontra o No sucessor mais à esquerda a partir do No filho direito do alvo
        //Uma vez que encontra o nó mais a direita, compia-se o valor do No sucessor ao No alvo
        //E em seguida o sucessor eh removido da arvore
        if (succ != root)
            succ->esquerda = succ->direita;
        else
            succ->direita = succ->direita;      // Transfere o dado do sucessor ao nó a ser removido
            succ->direita->pai = root;                // ao inves de remover o nó por completo, apenas troca de valor com o nó folha mais a esquerda
        root->valor = succ->valor;                    // e por fim remove o nó folha que serviu de sucessor
 
        // Delete Successor and return root
        free(succ);
        return root;
    }
}

void *deletar(Arvore *arvore, int valor){
    No* no = localizar(arvore, valor);
    if(no==NULL) return 0;
    No *reposicionado = deletarNo(arvore, no);
    balancear(arvore, reposicionado);
}

//Função auxiliar para verificar a integridade da arvore
void buscaEmLargura(Arvore *arvore, int tamanho) {
    No *raiz = arvore->raiz;
    if (raiz == NULL){
        printf("\nArvore vazia!");
        return;
    }

    // Cria uma fila para armazenar os nós da árvore
    No **fila = (No **)malloc(sizeof(No *) * tamanho);
    int inicio = 0, fim = 0;

    // Adiciona a raiz na fila
    fila[fim++] = raiz;

    // Enquanto a fila não estiver vazia
    while (inicio < fim) {
        // Remove o primeiro nó da fila
        No *noAtual = fila[inicio++];

        // Imprime o valor do nó
        if(noAtual != arvore->nulo){
            printf("(Valor = %d | Cor = %d) ", noAtual->valor, noAtual->cor);
        }

        // Adiciona os nós filhos na fila, se existirem
        if (noAtual->esquerda != arvore->nulo)
            fila[fim++] = noAtual->esquerda;
        if (noAtual->direita != arvore->nulo)
            fila[fim++] = noAtual->direita;
    }

    // Libera a memória da fila
    free(fila);
    return;
}

//Concatena novos dados ao arquivo de texto
void appendData(char acao, int iteracao, int dado){
    FILE *f;
    f = fopen("arvoreRubroNegra.txt", "a");
    if(acao == 'I') fprintf(f, "I");
    else fprintf(f, "R");
    fprintf(f, ":");
    fprintf(f, "%d", iteracao);
    fprintf(f, ":");
    fprintf(f, "%d", dado);
    fprintf(f, ";");
    fclose(f);
}

//Funcao responsavel por executar os textes de complexidade da arvore
void geraDados(Arvore *a, int numeroIteracoes) {

    int mediaComparacoes = 0;
    srand(time(NULL));
    int vetorMediasInsert[(numeroIteracoes * 10)];
    int vetorMediasRemove[(numeroIteracoes * 10)];
    
    //Insere dados aleatorios na arvore e salva no vetor vetorDeDados
    
    int vetorDeDados[numeroIteracoes];
    for(int j = 0; j < 10; j++){

        for(int n = 1; n < numeroIteracoes+1; n++){
            numeroComparacoes = 0;
            vetorDeDados[n-1] = rand() % 10000;
            adicionar(a, vetorDeDados[n-1]);
        
            // appendData('I', n, numeroComparacoes);
            if(j == 0){
                vetorMediasInsert[n-1] = numeroComparacoes;
            }else{
                vetorMediasInsert[n-1] += numeroComparacoes;
            }
        }
        //Deleta os dados da arvore a partir dos valores salvos no vetor previamente
        for(int n = 1; n < numeroIteracoes + 1; n++){
            numeroComparacoes = 0;
            deletar(a, vetorDeDados[n-1]);
            // appendData('R', n, numeroComparacoes);
            if(j == 0){
                vetorMediasRemove[n-1] = numeroComparacoes;
            }else{
                vetorMediasRemove[n-1] += numeroComparacoes;
            }
        }
        a->raiz = NULL;
    }
    for(int i = 1; i < numeroIteracoes+1; i++){
        appendData('I', i, vetorMediasInsert[i-1]/10);
    }
    for(int i = 1; i < numeroIteracoes+1; i++){
        appendData('R', i, vetorMediasRemove[i-1]/10);
    }
    
    printf("%d ", a->raiz);

    //buscaEmLargura(a, numeroIteracoes);
    //printf("\n");
    //buscaEmLargura(a, numeroIteracoes);
}


//Limpa o arquivo txt e inicia o calculo de complexidade
void initARN(int maxComapacoes) {
    FILE *p;
    p = fopen("arvoreRubroNegra.txt", "w");
    fprintf(p, "");
    fclose(p);

    Arvore* a = criar();

    geraDados(a, maxComapacoes);
    
}

int main() {
    initARN(10000);
}