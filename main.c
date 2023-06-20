#include "arvores/avl.h"

int main(){
    AVL *avl = avl_criar();
    int n = 8;
    int v[8] = {583, 245, 731, 123, 389, 684, 893, 278};
    int i = 0;

    // do {
    //     v[i] = rand() % (n * 10);
    //     int tem = 0;

    //     for (int j = 0; j < i; j++) {
    //         if (v[j] == v[i]) {
    //             tem = 1;
    //             break;
    //         }
    //     }

    //     if (!tem) {
    //         i++;
    //     }
    // } while (i < n);



    for (int i = 0; i < n; i++) {
        // printf("%d\n", v[i]);
        avl_adicionar(avl, v[i]);
    }

    percorrer(avl->raiz);

    avl_remover_no(avl, 245);
    printf("\n");
    percorrer(avl->raiz);

    avl = avl_remover(avl);

}

