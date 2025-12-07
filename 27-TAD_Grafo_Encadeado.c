#include <stdio.h>
#include <stdlib.h>

typedef struct _nodetype{
    int info;
    struct _nodetype *point;
    struct _nodetype *next;
}nodetype;

typedef nodetype *TADgraph;

void inicializaGrafo(TADgraph *graph){
    *graph = NULL;
}

void joinwt(nodetype *p, nodetype *q, int wt){
    nodetype *r, *r2;
    r2 = NULL;
    r = p->point;
    while (r && r->point != q){
        r2 = r;
        r = r->next;
    }
    if (r){
        r->info = wt;
        return;
    }
    r = (nodetype*) malloc(sizeof(nodetype));
    if (!r)
        return;
    r->point = q;
    r->info = wt;
    r->next = NULL;
    if (!r2)
        p->point = r;
    else
        r2->next = r;
}

void join(nodetype *p, nodetype *q){
    nodetype *r, *r2;
    r2 = NULL;
    r = p->point;
    while (r && r->point != q){
        r2 = r;
        r = r->next;
    }
    if (r)
        return;
    r = (nodetype*) malloc(sizeof(nodetype));
    if (!r)
        return;
    r->point = q;
    r->next = NULL;
    if (!r2)
        p->point = r;
    else
        r2->next = r;
}

void remv(nodetype *p, nodetype *q){
    nodetype *r, *r2;
    r2 = NULL;
    r = p->point;
    while (r && r->point != q){
        r2 = r;
        r = r->next;
    }
    if (r){
        if (!r2)
            p->point = r->next;
        else
            r2->next = r->next;
        free(r);
    }
}

void remvwt(nodetype *p, nodetype *q){
    nodetype *r, *r2;
    r2 = NULL;
    r = p->point;
    while (r && r->point != q){
        r2 = r;
        r = r->next;
    }
    if (r){
        if (!r2)
            p->point = r->next;
        else
            r2->next = r->next;
        free(r);
    }
}

char adjacent(nodetype *p, nodetype *q){
    nodetype *r;
    r = p->point;
    while (r)
        if (r->point == q)
            return 1;
        else
            r = r->next;
    return 0;
}

nodetype* findnode(TADgraph graph, int x){
    nodetype *p;
    p = graph;
    while (p)
        if (p->info == x)
            return p;
        else
            p = p->next;
    return NULL;
}

nodetype* addnode(TADgraph *graph, int x){
    nodetype *p;
    p = (nodetype*) malloc(sizeof(nodetype));
    if (!p)
        exit(1);
    p->info = x;
    p->point = NULL;
    p->next = *graph;
    *graph = p;
    return p;
}

int remvnode(TADgraph *graph, nodetype *p){
    nodetype *anterior, *atual;
    int retorno=0;
    anterior = atual = *graph;
    while (atual){
        if (atual == p){
            nodetype *aux, *aux2;
            if (atual == *graph)
                *graph = atual->next;
            else
                anterior->next = atual->next;
            aux = atual->point;
            while (aux){
                aux2 = aux;
                aux = aux->next;
                free(aux2);
            }
            anterior = atual;
            atual = atual->next;
            free(anterior);
            retorno = 1;
        } else {
            nodetype *aux, *aux2, *auxNode;
            aux = aux2 = atual->point;
            while (aux){
                if (aux->point == p){
                    if (aux == aux2)
                        atual->point = aux->next;
                    else
                        aux2->next = aux->next;
                    auxNode = aux;
                    aux2 = aux;
                    aux = aux->next;
                    free(auxNode);
                } else {
                    aux2 = aux;
                    aux = aux->next;
                }
            }
            anterior = atual;
            atual = atual->next;
        }
    }
    return retorno;
}
