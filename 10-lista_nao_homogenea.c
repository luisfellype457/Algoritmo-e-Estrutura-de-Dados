#include <stdio.h>
#include <stdlib.h>
#define INTGR 1
#define FLT 2
#define STRING 3

typedef struct node{
    int etype;
    union inf{
        int ival;
        float fval;
        char sval[20];
    } element;
    struct node *prox;
    struct node *ant;
} NODE;

typedef NODE * TAD_LISTA;

void criar_lista(TAD_LISTA *l){
    *l = NULL;
}

int eh_vazia(TAD_LISTA l){
    return !l;
}

int tam(TAD_LISTA l){
    int tam;
    for (tam=0; l; l = l->prox);
    return tam;
}

int pertence(TAD_LISTA l, union inf v, int etype){
    if (!l)
        return 0;
    else {
        NODE *aux = l;
        do {
            if (etype == aux->etype && (
                (INTGR == etype && aux->element.ival == v.ival) ||
                (FLT == etype && aux->element.fval == v.fval) ||
                (STRING == etype && !strcmp(aux->element.sval, v.sval))
            ))
                return 1;
            aux = aux->prox;
        } while (aux != l);
        return 0;
    }
}

void ins(TAD_LISTA *l, int k, union inf v, int etype){
    if (k < 1 || k > tam(*l))
        return;
    if (pertence(*l, v, etype))
        printf("ja tem");
    else {
        TAD_LISTA novo;
        novo = (TAD_LISTA) malloc(sizeof(NODE));
        if (!novo)
            return;
        novo->etype = etype;
        novo->element = v;
    }
}
