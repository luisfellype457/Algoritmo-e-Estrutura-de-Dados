// CÓDIGO SOBRE LISTAS ENCADEADAS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
} NODO;

typedef NODO * LISTA_ENC;

void criar_lista(LISTA_ENC *lista){
    *lista = NULL;
}

int eh_vazia(LISTA_ENC lista){
    return (!lista);
}

int tam(LISTA_ENC lista){
    int i;
    for (i=0; lista; i++)
        lista = lista->next;
    return i;
}

void ins(LISTA_ENC *lista, int valor, int posicao){
    if (posicao < 1 || posicao > tam(*lista)+1){
        printf("\n\tinvalid position!\n");
        exit(1);
    }

    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(2);
    }
    novo->inf = valor;

    if (posicao == 1){
        
        novo->next = *lista;
        *lista = novo;
    } else {
        
        LISTA_ENC aux = *lista;
        for (posicao; posicao > 2; posicao--)
            aux = aux->next;
        novo->next = aux->next;
        aux->next = novo;
    }

}

int recup(LISTA_ENC lista, int posicao){
    if (posicao < 1 || posicao > tam(lista)){
        printf("\n\tinvalid position!\n");
        exit(3);
    }
    for (posicao; posicao > 1; posicao--)
        lista = lista->next;
    return lista->inf;
}

void ret(LISTA_ENC *lista, int posicao){
    if (posicao < 1 || posicao > tam(*lista)){
        printf("\n\tinvalid position!\n");
        exit(4);
    }
    NODO *aux = *lista;
    if (posicao == 1){
        *lista = aux->next;
        free(aux);
    } else {
        NODO *aux2;
        for (posicao; posicao > 2; posicao--)
            aux = aux->next;
        aux2 = aux->next;
        aux->next = aux2->next;
        free(aux2);
    }
}

void destruir(LISTA_ENC lista){
    NODO *aux = lista;
    while (lista){
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}
