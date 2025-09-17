#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct
{
    int N;
    int INICIO;
    int FIM;
    int val[MAX];
} FILA_SEQ;

void criar_fila(FILA_SEQ *f)
{
    f->N = 0;
    f->INICIO = 0;
    f->FIM = -1;
}

int eh_vazia(FILA_SEQ *f)
{
    return !f->N;
}

int tam(FILA_SEQ *f){
    return f->N;
}

void ins
