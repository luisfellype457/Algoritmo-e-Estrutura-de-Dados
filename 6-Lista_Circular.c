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
    return (!lc);
}

int tam(LISTA_CIRCULAR lc){
    if (!lc)
        return 0;
    else {
        NODO *aux;
        int t = 1;
        for(aux = lc->next; aux != lc; t++)
            aux = aux->next;
        return t;
    }
}

void ins(LISTA_CIRCULAR *lc, int val, int pos){
    if (pos < 1 || pos > tam(*lc)+1){
        printf("\n\tinvalid position!\n");
        exit(1);
    }
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    novo->inf = val;
    if (!*lc){
        *lc = novo;
        novo->next = novo;
    } else {
        NODO *aux = *lc;
        if (pos == tam(*lc)+1)
            *lc = novo;
        else
            for(; pos > 1; pos--, aux = aux->next);
        novo->next = aux->next;
        aux->next = novo;
    }
}
