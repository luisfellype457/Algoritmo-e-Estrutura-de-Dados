// CÓDIGO SOBRE LISTAS CIRCULARES DUPLAMENTE ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *prox;
    struct nodo *ant;
}NODO;

typedef NODO *LISTA_CIRC_DUPL_ENCAD_COM_NC;

void criar_lista(LISTA_CIRC_DUPL_ENCAD_COM_NC *pl){
    *pl = (NODO*) malloc(sizeof(NODO));
    if (!*pl){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    (*pl)->inf = 0;
    (*pl)->ant = (*pl)->prox = *pl;
}

int eh_vazia(LISTA_CIRC_DUPL_ENCAD_COM_NC pl){
    return (!pl->inf);
}

int tam(LISTA_CIRC_DUPL_ENCAD_COM_NC pl){
    return pl->inf;
}

void ins(LISTA_CIRC_DUPL_ENCAD_COM_NC pl, int val, int pos){
    if (pos < 1 || pos > tam(pl)+1){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    NODO *aux, *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(3);
    }
    novo->inf = val;
    for (aux = pl; pos > 1; pos--, aux = aux->prox);
    novo->prox = aux->prox;
    novo->ant = aux;
    aux->prox = novo;
    novo->prox->ant = novo;
    pl->inf++;
}

int recup(LISTA_CIRC_DUPL_ENCAD_COM_NC pl, int pos){
    if (pos < 1 || pos > tam(pl)){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    for (; pos > 0; pos--, pl = pl->prox);
    return pl->inf;
}

void ret(LISTA_CIRC_DUPL_ENCAD_COM_NC pl, int pos){
    if (pos < 1 || pos > tam(pl)){
        printf("\n\tinvalid position!\n");
        exit(5);
    }
    pl->inf--;
    for(; pos > 0; pos--, pl = pl->prox);
    pl->ant->prox = pl->prox;
    pl->prox->ant = pl->ant;
    free(pl);
}

void destruir(LISTA_CIRC_DUPL_ENCAD_COM_NC pl){
    NODO *aux;
    int tamanho = pl->inf;
    do{
        aux = pl;
        pl = pl->prox;
        free(aux);
        tamanho--;
    }while(tamanho);
}
