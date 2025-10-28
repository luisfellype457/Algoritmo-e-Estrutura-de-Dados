#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int num, alte, altd;
    struct nodo *dir, *esq;
}NODO;

typedef NODO * ARVORE_AVL;

void rotacao_direita(ARVORE_AVL *arvore){
    ARVORE_AVL aux1, aux2;
    aux1 = (*arvore)->esq;
    aux2 = aux1->dir;
    (*arvore)->esq = aux2;
    aux1->dir = *arvore;
    if (!aux2)
        (*arvore)->alte = 0;
    else
        if (aux2->alte > aux2->altd)
            (*arvore)->alte = aux2->alte + 1;
        else
            (*arvore)->alte = aux2->altd + 1;
    if ((*arvore)->alte > (*arvore)->altd)
        aux1->altd = (*arvore)->alte + 1;
    else
        aux1->altd = (*arvore)->altd + 1;
    *arvore = aux1;
}

void rotacao_esquerda(ARVORE_AVL *arvore){
    ARVORE_AVL aux1, aux2;
    aux1 = (*arvore)->dir;
    aux2 = aux1->esq;
    (*arvore)->dir = aux2;
    aux1->esq = *arvore;
    if (!aux2)
        (*arvore)->altd = 0;
    else
        if (aux2->alte > aux2->altd)
            (*arvore)->altd = aux2->alte + 1;
        else
            (*arvore)->altd = aux2->altd + 1;
    if ((*arvore)->alte > (*arvore)->altd)
        aux1->altd = (*arvore)->alte + 1;
    else
        aux1->altd = (*arvore)->altd + 1;
}

void balanceamento(ARVORE_AVL *arvore){
    int FBpai, FBfilho;
    FBpai = (*arvore)->altd - (*arvore)->alte;
    if (FBpai == 2){
        FBfilho = (*arvore)->dir->altd - (*arvore)->dir->alte;
        if (FBfilho >= 0)
            rotacao_esquerda(arvore);
        else {
            rotacao_direita(&(*arvore)->dir);
            rotacao_esquerda(arvore);
        }
    } else {
        if (FBpai == -2){
            FBfilho = (*arvore)->esq->altd - (*arvore)->esq->alte;
            if (FBfilho <= 0)
                rotacao_direita(arvore);
            else {
                rotacao_esquerda(&(*arvore)->esq);
                rotacao_direita(arvore);
            }
        }
    }
}
