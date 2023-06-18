#include "arvores/avl.h"

int main(){
    AVL *avl = avl_criar();
    int n = 3;
    int v[3] = {10, 20, 30};
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
        printf("%d\n", v[i]);
        avl_adicionar(avl, v[i]);
    }

    printf("\n%d\n", avl->raiz->valor);
}

