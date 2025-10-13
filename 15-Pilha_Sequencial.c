#include <stdio.h>
#include <stdlib.h>
#include "11-Fila_Sequencial.c"
#define MAX 100

typedef struct{
    int TOPO;
    int val[MAX];
}PILHA_SEQ;

void criar_pilha(PILHA_SEQ *p){
    p->TOPO = -1;
}

int eh_vazia(PILHA_SEQ *p){
    return p->TOPO < 0;
}

void push(PILHA_SEQ *p, int v){
    if (p->TOPO == MAX-1)
        return;
    p->val[++(p->TOPO)] = v;
}

int top(PILHA_SEQ *p){
    if (eh_vazia(p))
        return;
    return p->val[p->TOPO];
}

void pop(PILHA_SEQ *p){
    if (eh_vazia(p))
        return;
    p->TOPO--;
}

int top_pop(PILHA_SEQ *p){
    if (eh_vazia(p))
        return;
    return p->val[p->TOPO--];
}

void inverter_fila(FILA_SEQ *f){
    PILHA_SEQ p;
    criar_pilha(&p);
    while (!eh_vazia_f(f))
        push(&p, cons_ret(f));
    while(!eh_vazia(&p))
        ins(f, top_pop(&p));
}
