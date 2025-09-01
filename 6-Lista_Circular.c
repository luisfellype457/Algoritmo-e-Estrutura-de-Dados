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
    NODO *aux = lc->next;
    int t=1;
    while(aux != lc){
        aux = aux->next;
        t++;
    }
    return t;
}

void ins(LISTA_CIRCULAR *lc, int val, int pos){
    int tamanho = tam(*lc);
    if (pos < 1 || pos > tamanho+1){
        printf("\n\tinvalid position!\n");
        exit(1);
    }
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(2);
    }
    novo->inf = val;
    if (!*lc){
        *lc = novo;
        novo->next = novo;
    } else {
        NODO *aux = *lc;
        if (pos == tamanho+1)
            *lc = novo;
        for(; pos > 1; pos--, aux = aux->next);
        novo->next = aux->next;
        aux->next = novo;
    }
}

int recup(LISTA_CIRCULAR lc, int pos){
    if (pos < 1 || pos > tam(lc)){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    for (; pos > 0; pos--, lc=lc->next);
    return lc->inf;
}

void ret(LISTA_CIRCULAR *lc, int pos){
    int tamanho = tam(*lc);
    if (pos < 1 || pos > tamanho){
        printf("\n\tinvalid position!\n");
        exit(5);
    }
    if (tamanho == 1){
        free(*lc);
        *lc = NULL;
    } else {
        NODO *aux = *lc, *aux2;
        for (int i=pos; i > 1; i--, aux = aux->next);
        if (pos == tamanho)
            *lc = aux;
        aux2 = aux->next;
        aux->next = aux2->next;
        free(aux2);
    }
}

void destruir(LISTA_CIRCULAR *lc){
    if (*lc){
        NODO *aux = (*lc)->next, *aux2;
        while(aux != *lc){
            aux2 = aux->next;
            free(aux);
            aux = aux2;
        }
        free(aux);
        *lc = NULL;
    }
}
