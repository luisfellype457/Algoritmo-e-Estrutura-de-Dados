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
    return (l->N == 0);
}

int tamanho(LISTA *l){
    return (l->N);
}

void inserir(LISTA *l, int valor, int posicao){
    int i = max;

    if (posicao < 1 || posicao > l->N+1){

        invalid();

    } else if (l->N == max){

        printf("Full list!");
        exit(2);

    } else {

        while (i > posicao-1){
            l->val[i] = l->val[i-1];
            i--;
        }

        l->val[i] = valor;

        l->N++;
    }
}

int recuperar(LISTA *l, int posicao){
    if (posicao < 1 || posicao > l->N){
        
        invalid();

    } else {

        return l->val[posicao-1];
    }
}

void retirar(LISTA *l, int posicao){

    if (posicao < 1 || posicao > l->N){
        
        invalid();

    } else {

        for (posicao-1; posicao < l->N-1; posicao++)

            l->val[posicao] = l->val[posicao + 1];

        l->N--;

    }
}

int pertence(LISTA *l, int v){
    int i;

    for (i=0; i <= l->N-1; i++){
        
        if (l->val[i] == v)

            return 1;
    }

    return 0;
}

int eh_ordenada(LISTA *l){
    int i;

    for (i=0; i < l->N-1; i++) {

        if (l->val[i] > l->val[i+1])
            return 0;
    }

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
