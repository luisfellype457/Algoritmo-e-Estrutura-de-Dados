// EXTRA: CÓDIGO SOBRE LISTAS DUPLAMENTE ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *ant;
    struct nodo *prox;
}NODO;

typedef NODO * LISTA_DUP_ENC_NC;

void criar_lista(LISTA_DUP_ENC_NC *l){
    *l = (NODO*) malloc(sizeof(NODO));
    if (!*l){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    (*l)->prox = NULL;
    (*l)->ant = NULL;
    (*l)->inf = 0;
}

int eh_vazia(LISTA_DUP_ENC_NC l){
    return !l->inf;
}

int tam(LISTA_DUP_ENC_NC l){
    return l->inf;
}

void ins(LISTA_DUP_ENC_NC l, int v, int k){
    if (k < 1 || k > l->inf+1){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    NODO *aux, *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tinvalid position!\n");
        exit(3);
    }
    for (aux = l; k > 1; k--, aux = aux->prox);
    novo->prox = aux->prox;
    aux->prox = novo;
    novo->ant = aux;
    if (novo->prox)
        novo->prox->ant = novo;
    l->inf++;
}

int recup(LISTA_DUP_ENC_NC l, int k){
    if (k < 1 || k > l->inf){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    for (; k > 0; k--, l = l->prox);
    return l->inf;
}

void ret(LISTA_DUP_ENC_NC l, int k){
    if (k < 1 || k > l->inf){
        printf("\n\tinvalid position!\n");
        exit(5);
    }
    l->inf--;
    for (; k > 0; k--, l = l->prox);
    l->ant->prox = l->prox;
    if (l->prox)
        l->prox->ant = l->ant;
    free(l);
}

void destruir(LISTA_DUP_ENC_NC l){
    NODO *aux;
    while(l){
        aux = l;
        l = l->prox;
        free(aux);
    }
}
