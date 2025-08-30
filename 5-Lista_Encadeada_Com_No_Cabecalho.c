// CÓDIGO SOBRE LISTAS ENCADEADAS COM NÓ CABEÇALHO

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
}NODO;

typedef NODO * LISTA_ENC_NC;

// função 'invalid' criada para economizar linhas de código em erros

void invalid(){
    printf("\n\tinvalid position!\n");
    exit(2);
}

void criar_lista(LISTA_ENC_NC *lc){
    *lc = (NODO*) malloc(sizeof(NODO));
    if (!*lc){
        printf("\n\tallocation error!\n");
        exit(1);
    }
    (*lc)->inf = 0;
    (*lc)->next = NULL;
}

int eh_vazia(LISTA_ENC_NC lc){
    return !(lc->inf);
}

int tam(LISTA_ENC_NC lc){
    return lc->inf;
}

void ins(LISTA_ENC_NC lc, int val, int pos){
    if (pos < 1 || pos > lc->inf+1)
        invalid();
    NODO *aux, *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo){
        printf("\n\tallocation error!\n");
        exit(3);
    }
    novo->inf = val;
    for(aux = lc; pos > 1; pos--, aux = aux->next);
    novo->next = aux->next;
    aux->next = novo;
    lc->inf++;
}

int recup(LISTA_ENC_NC lc, int pos){
    if (pos < 1 || pos > lc->inf)
        invalid();
    for(; pos > 0; pos--, lc = lc->next);
    return lc->inf;
}

void ret(LISTA_ENC_NC lc, int pos){
    if (pos < 1 || pos > lc->inf)
        invalid();
    NODO *aux, *aux2;
    for(aux = lc; pos > 1; pos--)
        aux = aux->next;
    aux2 = aux->next;
    aux->next = aux2->next;
    free(aux2);
    lc->inf--;
}

void destruir(LISTA_ENC_NC lc){
    NODO *aux;
    while(lc){
        aux = lc->next;
        free(lc);
        lc = aux;
    }
}
