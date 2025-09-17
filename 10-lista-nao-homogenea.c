#include <stdio.h>
#include <stdlib.h>

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

