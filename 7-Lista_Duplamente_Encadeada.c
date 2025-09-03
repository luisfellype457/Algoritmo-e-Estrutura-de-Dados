// CÓDIGO SOBRE LISTAS DUPLAMENTE ENCADEADAS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *ant;
    struct nodo *prox;
}NODO;

typedef NODO *LISTA_DUP_ENC;

void criar_lista(LISTA_DUP_ENC *ld){
    *ld = NULL;
}

int eh_vazia(LISTA_DUP_ENC ld){
    return !ld;
}

int tam(LISTA_DUP_ENC ld){
    int tamanho = 0;
    for(; ld; tamanho++, ld = ld->prox);
    return tamanho;
}

void ins(LISTA_DUP_ENC *ld, int val, int pos){
    int tamanho = tam(*ld);
    if (pos < 1 || pos > tamanho+1){
        printf("\n\tinvalid position!\n");
        exit(1);
    }
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if(!novo){
        printf("\n\tallocation error!\n");
        exit(2);
    }
    novo->inf = val;
    if (pos == 1){
        novo->ant = NULL;
        novo->prox = *ld;
        *ld = novo;
        if (novo->prox)
            novo->prox->ant = novo;
    } else {
        NODO *aux = *ld;
        for(; pos > 2; pos--, aux = aux->prox);
        novo->prox = aux->prox;
        aux->prox = novo;
        novo->ant = aux;
        if (novo->prox)
            novo->prox->ant = novo;
    }
}

int recup(LISTA_DUP_ENC ld, int pos){
    if (pos < 1 || pos > tam(ld)){
        printf("\n\tinvalid position!\n");
        exit(3);
    }
    for(; pos > 1; ld = ld->prox);
    return ld->inf;
}

void ret(LISTA_DUP_ENC *ld, int pos){
    int tamanho = tam(*ld);
    if (pos < 1 || pos > tamanho){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    if (*ld){
        NODO *aux = *ld;
        if (pos == 1){
            *ld = aux->prox;
            free(aux);
            if (*ld)
                (*ld)->ant = NULL;
        } else {
            for(; pos > 1; pos--, aux = aux->prox);
            aux->ant->prox = aux->prox;
            if(aux->prox)
                aux->prox->ant = aux->ant;
            free(aux);
        }
    }
}

void destruir(LISTA_DUP_ENC ld){
    NODO *aux;
    while(ld){
        aux = ld;
        ld = ld->prox;
        free(aux);
    }
    ld = NULL;
}
