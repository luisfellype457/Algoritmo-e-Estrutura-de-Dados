// CÓDIGO SOBRE FILA ENCADEADA COM NÚMERO DE ELEMENTOS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo * next;
}NODO;

typedef struct{
    int ne;
    NODO *INICIO;
    NODO *FIM;
}DESCRITOR;

typedef DESCRITOR *FILA_ENC;

void criar_fila(FILA_ENC *f){
    *f = (FILA_ENC) malloc(sizeof(DESCRITOR));
    if (!*f)
        return;
    (*f)->FIM = (*f)->INICIO = NULL;
    (*f)->ne = 0;
}

int eh_vazia(FILA_ENC f){
    return !f->ne;
}

void ins(FILA_ENC f, int v){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    novo->next = NULL;
    if (!f->ne)
        f->INICIO = novo;
    else
        f->FIM->next = novo;
    f->FIM = novo;
    f->ne++;
}

int cons(FILA_ENC f){
    if (!f->ne)
        return;
    return f->INICIO->inf;
}

void ret(FILA_ENC f){
    if (!f->ne)
        return;
    else {
        NODO *aux = f->INICIO;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
        f->ne--;
    }
}

int cons_ret(FILA_ENC f){
    if (!f->ne)
        return;
    else {
        NODO *aux = f->INICIO;
        int v = aux->inf;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
        return v;
        f->ne--;
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
