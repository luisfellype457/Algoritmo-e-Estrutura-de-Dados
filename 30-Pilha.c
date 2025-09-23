#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct
{
    int TOPO;
    int VAL[MAX];
}PILHA_SEQ;

void criar_pilha(PILHA_SEQ *p){
    p->TOPO = -1;
}

int eh_vazia(PILHA_SEQ *p){
    return p->TOPO < 0;
}

int tam(PILHA_SEQ *p){
    return p->TOPO;
}

void push(PILHA_SEQ *p, int v){
    if (p->TOPO == MAX-1){
        printf("\n\tfull stack!\n");
        exit(1);
    }
    p->TOPO++;
    p->VAL[p->TOPO] = v;
}

int top(PILHA_SEQ *p){
    if (p->TOPO < 0){
        printf("\n\tempty stack!\n");
        exit(2);
    }
    return p->VAL[p->TOPO];
}

void pop(PILHA_SEQ *p){
    if (p->TOPO < 0){
        printf("\n\tempty stack!\n");
        exit(3);
    }
    p->TOPO--;
}

int top_pop(PILHA_SEQ *p){
    if (p->TOPO < 0){
        printf("\n\tempty stack!\n");
        exit(4);
    }
    return p->VAL[--p->TOPO];
    --p->TOPO;
}
