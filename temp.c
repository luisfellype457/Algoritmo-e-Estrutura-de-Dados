#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int N;
    int val[MAX];
}LISTA;

void criar_lista(LISTA *l){
    l->N = 0;
}

int eh_vazia(LISTA *l){
    return !l->N; //l->N == 0;
}

int tam(LISTA *l){
    return l->N;
}

void ins(LISTA *l, int v, int k){
    int i = l->N;
    if (k < 1 || k > l->N+1){
        printf("safada");
        exit(1); 
    }
    if (l->N == MAX){
        printf("safada2");
        exit(2);
    }
    for (; i >= k; i--){
        l->val[i] = l->val[i-1];
    }
    l->val[i] = v;
    l->N++;
}

int recup(LISTA *l, int k){
    if (k < 1 || k > l->N){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    return l->val[k-1];
}

void ret(LISTA *l, int k){
    if (k < 1 || k > l->N){
        printf("\n\tinvalid position!\n");
        exit(3);
    }
    l->N--;
    for (k--; k < l->N; k++)
        l->val[k] = l->val[k+1];

}

// LISTA_ENCADEADA

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef NODO *LISTA_ENC;

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

// LISTA_ENCADEADA_NC

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef NODO* LISTA_ENC_NC;

void criar_lista(LISTA_ENC_NC *l){
    *l = (NODO*) malloc(sizeof(NODO));
    if (!*l){
        return;
    }
    (*l)->inf = 0;
    (*l)->next = NULL;
}

int eh_vazia(LISTA_ENC_NC l){
    return !l->inf;
}

int tam(LISTA_ENC_NC l){
    return l->inf;
}

void ins(LISTA_ENC_NC l, int v, int k){
    NODO *aux, *novo;
    if (k < 1 || k > l->inf+1)
        return;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    for (aux = l; k < 1; k--, aux = aux->next);
    novo->next = aux->next;
    aux->next = novo;
    l->inf++;
}

int recup(LISTA_ENC_NC l, int k){
    if (k < 1 || k > l->inf)
        return;
    for (; k < 0; k--, l = l->next);
    return l->inf;
}

void ret(LISTA_ENC_NC l, int k){
    NODO *aux2;
    if (k < 1 || k > l->inf)
        return;
    l->inf--;
    for (; k > 1; k--, l = l->next);
    aux2 = l->next;
    l->next = aux2->next;
    free(aux2);
}

void destruir(LISTA_ENC_NC l){
    NODO *aux;
    while (l){
        aux = l;
        l = l->next;
        free(aux);
    }
}

// LISTA_CIRCULAR

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef NODO *LISTA_CIRC;

void criar_lista(LISTA_CIRC *l){
    *l = NULL;
}

int eh_vazia(LISTA_CIRC l){
    return !l;
}

int tam(LISTA_CIRC l){
    if (!l)
        return 0;
    else {
        int tam=1;
        NODO *aux;
        for (aux = l->next; aux != l; tam++)
            aux = aux->next;
        return tam;
    }
}

void ins(LISTA_CIRC *l, int v, int k){
    NODO *novo;
    int tamanho = tam(*l);
    if (k < 1 || k > tamanho+1)
        return;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    if (!tamanho){
        novo->next = novo;
        *l = novo;
    } else {
        NODO *aux = *l;
        if (k == tamanho+1)
            *l = novo;
        else 
            for (; k > 1; k--, aux = aux->next);
        novo->next = aux->next;
        aux->next = novo;
    }
}

int recup(LISTA_CIRC l, int k){
    if (k < 1 || k > tam(l))
        return;
    for (; k > 1; k--, l = l->next);
    return l->inf;
}

void ret(LISTA_CIRC *l, int k){
    int tamanho = tam(*l);
    if (k < 1 || k > tamanho)
        return;
    if (tamanho == 1){
        free(*l);
        *l = NULL;
    } else {
        NODO *aux, *aux2;
        int i = k;
        for (aux = *l; k > 1; k--, aux = aux->next);
        aux2 = aux->next;
        aux->next = aux2->next;
        if (i == tamanho)
            *l = aux;
        free(aux2);
    }
}

void destruir(LISTA_CIRC l){
    if (l){
        NODO *aux;
        for (aux = l->next; aux != l; aux = aux->next)
            free(aux);
        free(aux);
    }
}

// LISTA_DUPLAMENTE_ENCADEADA

typedef struct nodo{
    int inf;
    struct nodo *prox;
    struct nodo *ant;
}NODO;

typedef NODO *LISTA_DUP_ENC;

void criar_lista(LISTA_DUP_ENC *l){
    *l = NULL;
}

int eh_vazia(LISTA_DUP_ENC l){
    return !l;
}

int tam(LISTA_DUP_ENC l){
    int tam;
    for (tam=0; l; l = l->prox, tam++);
    return tam;
}

void ins(LISTA_DUP_ENC *l, int v, int k){
    NODO *novo;
    if (k < 1 || k > tam(*l)+1)
        return;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    if (k == 1){
        novo->ant = NULL;
        novo->prox = *l;
        *l = novo;
        if (novo->prox)
            novo->prox->ant = novo;
    } else {
        NODO *aux;
        for (aux = *l; k > 2; k--, aux = aux->prox);
        novo->prox = aux->prox;
        aux->prox = novo;
        novo->ant = aux;
        if (novo->prox)
            novo->prox->ant = novo;
    }
}

int recup(LISTA_DUP_ENC l, int k){
    if (k < 1 || k > tam(l))
        return;
    for (; k > 1; k--, l = l->prox);
    return l->inf;
}

void ret(LISTA_DUP_ENC *l, int k){
    NODO *aux = *l;
    if (k < 1 || k > tam(*l))
        return;
    if (k == 1){
        *l = aux->prox;
        if (aux->prox)
            aux->prox->ant = NULL;
        free(aux);
    } else {
        for (; k > 1; k--, aux = aux->prox);
        aux->ant->prox = aux->prox;
        if (aux->prox)
            aux->prox->ant = aux->ant;
        free(aux);
    }
}

void destruir(LISTA_DUP_ENC l){
    NODO *aux;
    while (l){
        aux = l;
        l = l->prox;
        free(aux);
    }
}

void inverter_lista(LISTA_DUP_ENC *l){
    NODO *aux = *l;
    while (aux){
        aux = (*l)->prox;
        (*l)->prox = (*l)->ant;
        (*l)->ant = aux;
        if
    }
}
