#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int N;
    int INICIO;
    int FIM;
    int val[MAX];
}FILA_SEQ;

void criar_fila(FILA_SEQ *f){
    f->N = f->INICIO = 0;
    f->FIM = -1;
}

int eh_vazia_f(FILA_SEQ *f){
    return !f->N;
}

int tam(FILA_SEQ *f){
    return f->N;
}

void ins(FILA_SEQ *f, int v){
    if (f->N == MAX)
        return;
    f->FIM = (f->FIM+1) % MAX;
    f->val[f->FIM] = v;
    f->N++;
}

int cons(FILA_SEQ *f){
    if (eh_vazia_f(f))
        return;
    return f->val[f->INICIO];
}

void ret(FILA_SEQ *f){
    if (eh_vazia_f(f))
        return;
    f->INICIO = (f->INICIO+1) % MAX;
    f->N--;
}

int cons_ret(FILA_SEQ *f){
    if (eh_vazia_f(f))
        return;
    else {
        int v = f->val[f->INICIO];
        f->INICIO = (f->INICIO+1) % MAX;
        f->N--;
        return v;
    }
}

void gera_fila(FILA_SEQ *f, int m, int n){
    if (m > n)
        return;
    if (m == n){
        criar_fila(f);
        ins(f, m);
    } else {
        gera_fila(f, m, n-1);
        ins(f, n);
    }
}
