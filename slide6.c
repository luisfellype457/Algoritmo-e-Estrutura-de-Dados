// CÓDIGO SOBRE LISTA CIRCULAR

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;
typedef NODO *LISTA_CIRCULAR;

void criar_lista(LISTA_CIRCULAR *lc){
    *lc = NULL;
}

int eh_vazia(LISTA_CIRCULAR lc){
    return (lc == NULL);
}

int tam(LISTA_CIRCULAR lc){
    if (!lc)
        return 0;
    NODO *aux = lc->next;
    int t=1;
    for(; aux != lc; aux = aux->next, t++);
    return t;
}

void ins(LISTA_CIRCULAR *lc, int val, int pos){
    if (pos < 1 || pos > tam(*lc)+1){
        printf("\n\tinvalid position!\n");
        exit(1);
    }

    NODO *new = (NODO*) malloc (sizeof(NODO));
    if (!new){
    printf("\n\tallocation error!\n");
    exit(2);
    }
    new->inf = val;

    // quando for vazia?
    // quando for o último?
    // quando tiver no meio da lista?

}
