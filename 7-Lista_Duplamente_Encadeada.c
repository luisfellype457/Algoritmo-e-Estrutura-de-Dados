// CÓDIGO SOBRE LISTAS DUPLAMENTE ENCADEADAS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int inf;
    struct nodo *ant;
    struct nodo *prox;
} NODO;

typedef NODO *LISTA_DUP_ENC;

void invalid_pos()
{
    printf("\n\tinvalid position!\n");
    exit(1);
}

void criar_lista(LISTA_DUP_ENC *l)
{
    *l = NULL;
}

int eh_vazia(LISTA_DUP_ENC l)
{
    return !l;
}

int tam(LISTA_DUP_ENC l)
{
    int t = 0;
    for (; l; t++, l = l->prox)
        ;
    return t;
}

void ins(LISTA_DUP_ENC *l, int v, int k)
{
    if (k < 1 || k > tam(*l) + 1)
        invalid_pos();
    NODO *novo = (NODO *)malloc(sizeof(NODO));
    if (!novo)
    {
        printf("\n\tallocation error!\n");
        exit(2);
    }
    novo->inf = v;
    if (k == 1)
    {
        novo->prox = *l;
        novo->ant = NULL;
        *l = novo;
        if (novo->prox)
            novo->prox->ant = novo;
    }
    else
    {
        NODO *aux = *l;
        for (; k > 2; k--)
            aux = aux->prox;
        novo->prox = aux->prox;
        aux->prox = novo;
        novo->ant = aux;
        if (novo->prox)
            novo->prox->ant = novo;
    }
}

int recup(LISTA_DUP_ENC l, int k)
{
    if (k < 1 || k > tam(l))
        invalid_pos();
    for (; k > 1; k--, l = l->prox)
        ;
    return l->inf;
}

void ret(LISTA_DUP_ENC *l, int k)
{
    NODO *aux;
    if (k < 1 || k > tam(*l))
        invalid_pos();
    if (k == 1)
    {
        aux = *l;
        *l = aux->prox;
        if (aux->prox)
            aux->prox->ant = NULL;
    }
    else
    {
        aux = *l;
        for (; k > 1; k--)
            aux = aux->prox;
        aux->ant->prox = aux->prox;
        if (aux->prox)
            aux->prox->ant = aux->ant;
    }
    free(aux);
}

void destruir(LISTA_DUP_ENC l)
{
    NODO *aux;
    while (l)
    {
        aux = l;
        l = l->prox;
        free(aux);
    }
}

void inverter_lista(LISTA_DUP_ENC *l)
{
    if (*l)
    {
        NODO *aux;
        do
        {
            aux = (*l)->prox;
            (*l)->prox = (*l)->ant;
            (*l)->ant = aux;
            if (aux)
                *l = aux;
        } while (aux);
    }
}
