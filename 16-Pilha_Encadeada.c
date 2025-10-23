// CÓDIGO SOBRE PILHA ENCADEADA

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
}NODO;

typedef NODO * PILHA_ENC;

void create(PILHA_ENC *p){
    *p = NULL;
}

int is_empty(PILHA_ENC p){
    return !p;
}

void push(PILHA_ENC *p, int v){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    novo->next = *p;
    *p = novo;
}

int top(PILHA_ENC p){
    if (eh_vazia(p))
        return;
    return p->inf;
}

void pop(PILHA_ENC *p){
    if (!*p)
        return;
    else {
        NODO *aux = *p;
        *p = aux->next;
        free(aux);
    }
}

int top_pop(PILHA_ENC *p){
    if (!*p)
        return;
    else {
        NODO *aux = *p;
        int v = aux->inf;
        *p = aux->next;
        free(aux);
        return v;
    }
}

void destroy(PILHA_ENC p){
    NODO *aux;
    while (p){
        aux = p;
        p = p->next;
        free(aux);
    }
}
