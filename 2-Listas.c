// CÓDIGO SOBRE LISTAS E SUAS OPERAÇÕES

#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct{
    int N;
    int val[max];
}LISTA;

void invalid(){
    printf("Invalid position!");
    exit(1);
}

void criar_lista(LISTA *l){
    l->N = 0;
}

int eh_vazia(LISTA *l){
    return !l->N;
}

int tamanho(LISTA *l){
    return l->N;
}

void ins(LISTA *l, int v, int k){
    int i;

    if (k < 1 || k > l->N+1)
        invalid();

    if (l->N == max){
        printf("\n\tfull list!\n");
        exit(2);
    }
    for (i = l->N; k <= i; i--)
        l->val[i] = l->val[i-1];
    
    l->val[k-1] = v;

    l->N++;
}

int recup(LISTA *l, int k){
    if (k < 1 || k > l->N)
        invalid();

    return l->val[k-1];
}

void ret(LISTA *l, int k){
    if (k < 1 || k > l->N)
        invalid();
    l->N--;
    for (k-1; k < l->N; k++)
        l->val[k+1] = l->val[k];
}

int pertence(LISTA *l, int v){
    int i;
    for (i=0; i < l->N; i++)
        if (l->val[i] == v)
            return 1;
    return 0;
}

int eh_ordenada(LISTA *l){
    int i;
    for (i=0; i < l->N-1; i++)
        if (l->val[i] > l->val[i+1])
            return 0;
    return 1;
}

void gera_lista(LISTA *l, int m, int n){

    if (m > n){

        printf("Invalid range!");
        exit(3);

    } else if (m == n){

        criar_lista(l);
        inserir(l, m, 1);

    } else {

        gera_lista(l, m+1, n);
        inserir(l, m, 1);
    }
}
