// CÓDIGO SOBRE LISTAS DUPLAMENTE ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *ant;
    struct nodo *prox;
}NODO;

typedef NODO * LISTA_CIR_DUP_ENC_NC;

void criar_lista(LISTA_CIR_DUP_ENC_NC *l){
    *l = (NODO*) malloc(sizeof(NODO));
    if (!*l){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    (*l)->inf = 0;
    (*l)->ant = NULL;
    (*l)->prox = NULL;
}

int eh_vazia(LISTA_CIR_DUP_ENC_NC l){
    return !l->inf;
}

int tam(LISTA_CIR_DUP_ENC_NC l){
    return l->inf;
}

void ins(LISTA_CIR_DUP_ENC_NC l, int val, int pos){
    NODO *aux, *novo = (NODO*) malloc(sizeof(NODO));
    if (pos < 1 || pos > l->inf+1){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(3);
    }
    novo->inf = val;
    if (pos <= l->inf/2){
        for (aux = l; pos > 1; pos--)
            aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
        novo->prox->ant = novo;
        novo->ant = aux;
    } else {
        for (aux = l; pos <= l->inf; pos++)
            aux = aux->ant;
        novo->prox = aux;
        aux->ant->prox = novo;
        novo->ant = aux->ant;
        aux->ant = novo;
    }
    l->inf++;
}

int recup(LISTA_CIR_DUP_ENC_NC l, int pos){
    int tamanho = l->inf;
    if (pos < 1 || pos > tamanho){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    if (pos <= tamanho/2)
        for (; pos > 0; pos--)
            l = l->prox;
    else 
        for (; pos <= tamanho; pos++)
            l = l->ant;
    return l->inf;
}

void ret(LISTA_CIR_DUP_ENC_NC l, int pos){
    int tamanho = l->inf;
    if (pos < 1 || pos > tamanho){
        printf("\n\tinvalid position!\n");
        exit(5);
    }
    l->inf--;
    if (pos <= tamanho/2)
        for (; pos > 0; pos--)
            l = l->prox;
    else
        for (; pos <= tamanho; pos++)
            l = l->ant;
    l->ant->prox = l->prox;
    l->prox->ant = l->ant;
    free(l);
}
