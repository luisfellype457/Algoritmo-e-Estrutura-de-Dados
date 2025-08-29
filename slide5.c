// CÓDIGO SOBRE LISTAS ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
}NODO;

typedef NODO * LISTA_ENC_NC;

void criar_lista(LISTA_ENC_NC *lista){
   *lista = (LISTA_ENC_NC) malloc (sizeof(NODO));

   if (!(*lista)){
    printf("\n\tallocation error!\n");
    exit(1);
   }
   (*lista)->inf = 0;
   (*lista)->next = NULL;
}

int eh_vazia(LISTA_ENC_NC lista){
    if (!lista->inf)
        return 1;
    return 0;
}

int tam(LISTA_ENC_NC lista){
    return lista->inf;
}

void ins(LISTA_ENC_NC lista, int valor, int posicao){
    if (posicao < 1 || posicao > tam(lista)+1){
        printf("\n\tinvalid postition!\n");
        exit(2);
    } else {
        NODO *novo, *aux = lista;
        novo = (NODO*) malloc (sizeof(NODO));
        if (!novo){
            printf("\n\tallocation error!\n");
            exit(3);
        }
        novo->inf = valor;

        for(posicao; posicao > 1; posicao--)
            lista = lista->next;
        novo->next = aux->next;
        aux->next = novo;
        lista->inf++;
    }
}

int recup(LISTA_ENC_NC lista, int posicao){
    if (posicao < 1 || posicao > lista->inf){

    }
    for (; posicao > 0; posicao--)
        lista = lista->next;
    return lista->inf;
}

void ret(LISTA_ENC_NC lista, int posicao){
    NODO *aux = lista, *aux2;
    for(; posicao > 1; posicao--)
        aux = aux->next;
    aux2 = aux->next;
    aux->next = aux2->next;
    free(aux2);
    lista->inf--;
}

void destruir(LISTA_ENC_NC lista){
    NODO *aux;
    while(lista){
        aux = lista;
        lista = lista->next;
        free(aux);
    }
}
