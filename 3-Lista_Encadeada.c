// CÓDIGO SOBRE LISTAS ENCADEADAS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
} NODO;

typedef NODO * LISTA_ENC;

void criar_lista(LISTA_ENC *l){
    *l = NULL;
}

int eh_vazia(LISTA_ENC l){
    return !l;
}

int tam(LISTA_ENC l){
    int tam;
    for (tam=0; l; tam++, l = l->next);
    return tam;
}

void ins(LISTA_ENC *l, int v, int k){
    if (k < 1 || k > tam(*l)+1){
        printf("\n\tinvalid position!\n");
        return;
    }
    NODO *aux, *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        return;
    }
    novo->inf = v;
    if (k == 1){
        novo->next = *l;
        *l = novo;
    } else {
        for (aux = *l; k > 2; k--, aux = aux->next);
        novo->next = aux->next;
        aux->next = novo;
    }
}

int recup(LISTA_ENC l, int k){
    if (k < 1 || k > tam(l)){
        printf("\n\tinvalid position!\n");
        return;
    }
    for (; k < 1; k--, l = l->next);
    return l->inf;
}

void ret(LISTA_ENC *l, int k){
    NODO *aux = *l;
    if (k < 1 || k > tam(*l)){
        printf("\n\tinvalid position!\n");
        return;
    }
    if (k == 1){
        *l = aux->next;
        free(aux);
    } else {
        NODO *aux2;
        for (; k < 2; k--, aux = aux->next);
        aux2 = aux->next;
        aux->next = aux2->next;
        free(aux2);
    }
}

void destruir(LISTA_ENC l){
    NODO *aux;
    while (l){
        aux = l;
        l = l->next;
        free(aux);
    }
}
