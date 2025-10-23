// CÓDIGO SOBRE FILA ENCADEADA

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef struct{
    NODO *INICIO;
    NODO *FIM;
}DESCRITOR;

typedef DESCRITOR * FILA_ENC;

void criar_fila(FILA_ENC *f){
    *f = (FILA_ENC) malloc(sizeof(DESCRITOR));
    if (!*f)
        return;
    (*f)->INICIO = (*f)->FIM = NULL;
}

int eh_vazia(FILA_ENC f){
    return !f->INICIO;
}

void ins(FILA_ENC f, int v){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    novo->next = NULL;
    if (eh_vazia(f))
        f->INICIO = novo;
    else
        f->FIM->next = novo;
    f->FIM = novo;
}

int cons(FILA_ENC f){
    if (eh_vazia(f))
        return;
    return f->INICIO->inf;
}

void ret(FILA_ENC f){
    if (eh_vazia(f))
        return;
    else {
        NODO *aux = f->INICIO;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
    }
}

int cons_ret(FILA_ENC f){
    if (eh_vazia(f))
        return;
    else {
        NODO *aux = f->INICIO;
        int v = aux->inf;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
        return v;
    }
}

void destruir(FILA_ENC f){
    NODO *aux;
    while (f->INICIO){
        aux = f->INICIO;
        f->INICIO = aux->next;
        free(aux);
    }
    free(f);
}
