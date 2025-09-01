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
}
