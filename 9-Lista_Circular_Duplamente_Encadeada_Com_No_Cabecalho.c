// CÓDIGO SOBRE LISTAS CIRCULARES DUPLAMENTE ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *prox;
    struct nodo *ant;
}NODO;

typedef NODO * LISTA_CIR_DUP_ENC_NC;

void criar_lista(LISTA_CIR_DUP_ENC_NC *l){
    *l = (NODO*) malloc(sizeof(NODO));
    if (!*l){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    (*l)->prox = *l;
    (*l)->ant = *l;
    (*l)->inf = 0;
}

int eh_vazia(LISTA_CIR_DUP_ENC_NC l){
    return !l->inf;
}

int tam(LISTA_CIR_DUP_ENC_NC l){
    return l->inf;
}

void ins(LISTA_CIR_DUP_ENC_NC l, int v, int k){
    if (k < 1 || k > l->inf+1){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    NODO *aux, *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(3);
    }
    novo->inf = v;
    for (aux = l; k > 1; k--, aux = aux->prox);
    novo->prox = aux->prox;
    aux->prox = novo;
    novo->prox->ant = novo;
    novo->ant = aux;
    l->inf++;
}

int recup(LISTA_CIR_DUP_ENC_NC l, int k){
    if (k < 1 || k > l->inf){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    for (; k > 0; l = l->prox);
    return l->inf;
}

void ret(LISTA_CIR_DUP_ENC_NC l, int k){
    if (k < 1 || k > l->inf){
        printf("\n\tinvalid position!\n");
        exit(5);
    }
    l->inf--;
    for (; k > 0; k--, l = l->prox);
    l->ant->prox = l->prox;
    l->prox->ant = l->ant;
    free(l);
}

void destruir(LISTA_CIR_DUP_ENC_NC l){
    NODO *aux;
    int tam = l->inf;
    do{
        aux = l;
        l = l->prox;
        free(aux);
    } while(tam--);
}

void inverter_lista(LISTA_CIR_DUP_ENC_NC l){
    int tam = l->inf;
    NODO *aux;
    while(tam>=0){
        aux = l->prox;
        l->prox = l->ant;
        l->ant = aux;
        l = aux;
        tam--;
    }
}
