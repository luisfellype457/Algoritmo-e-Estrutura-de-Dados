// CÓDIGO SOBRE LISTAS CIRCULARES

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int inf;
    struct nodo *next;
} NODO;

typedef NODO *LISTA_CIRCULAR;

void i_position()
{
    printf("\n\tinvalid position!\n");
    exit(1);
}

void criar_lista(LISTA_CIRCULAR *l)
{
    *l = NULL;
}

int eh_vazia(LISTA_CIRCULAR l)
{
    return !l;
}

int tam(LISTA_CIRCULAR l)
{
    int t = 1;
    if (!l)
        return 0;
    else
    {
        NODO *aux = l->next;
        while (l != aux)
        {
            t++;
            aux = aux->next;
        }
        return t;
    }
}

void ins(LISTA_CIRCULAR *l, int v, int k)
{
    int tamanho = tam(*l);
    if (k < 1 || k > tamanho+1)
        i_position();
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
    {
        printf("\n\tallocation error!\n");
        exit(2);
    }
    novo->inf = v;
    if (!*l)
    {
        novo->next = novo;
        *l = novo;
    }
    else
    {
        NODO *aux = *l;
        if (k == tamanho+1)
            *l = novo;
        else
            for (; k > 1; k--, aux = aux->next);
        novo->next = aux->next;
        aux->next = novo;
    }
}

int recup(LISTA_CIRCULAR l, int k)
{
    if (k < 1 || k > tam(l))
        i_position();
    for (; k > 0; k--, l = l->next);
    return l->inf;
}

void ret(LISTA_CIRCULAR *l, int k)
{
    int tamanho = tam(*l);
    if (k < 1 || k > tamanho)
        i_position();
    if (tamanho == 1)
    {
        free(*l);
        *l = NULL;
    }
    else
    {
        NODO *aux = *l, *aux2;
        int i = k;
        for (aux = *l; i > 1; i--, aux = aux->next);
        aux2 = aux->next;
        aux->next = aux2->next;
        free(aux2);
        if (k == tamanho+1)
            *l = aux;
    }
}

void destruir(LISTA_CIRCULAR l)
{
    NODO *aux, *aux2 = l;
    if (l){
        for (aux = l->next; aux != aux2;){
            l = aux->next;
            free(aux);
            aux = l;
        }
        free(aux);
    }
}
