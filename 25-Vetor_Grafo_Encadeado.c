#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 10

typedef struct nodetype{
    int info;
    int point;
    int next;
    char livre;
}tipoNodo;

typedef tipoNodo listaDeNodos[MAXNODES];

void jointwt(listaDeNodos node, int p, int q, int wt){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0){
        node[r].info = wt;
        return;
    }
    r = getnode(node);
    if (r < 0)
        exit(1);
    node[r].info = wt;
    node[r].next = -1;
    node[r].point = q;
    node[r].livre = 0;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

int getnode(listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        if (node[i].livre == 1)
            return i;
    return -1;
}

void inicializaGrafo(int *grafo, listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        node[i].livre = 1;
    *grafo = -1;
}

// GRAFOS COM LISTA DE NODOS VAZIOS

void criaListaDeNodosVazios(int *listaDeNodosVazios, listaDeNodos node){
    int i;
    for (i=1; i < MAXNODES; ++i)
        node[i-1].next = i;
    node[i-1].next = -1;
    *listaDeNodosVazios = 0;
}

int getnodeLista(int *listaDeNodosVazios, listaDeNodos node){
    int i = *listaDeNodosVazios;
    if (i != -1){
        *listaDeNodosVazios = node[i].next;
        return i;
    }
    printf("out of memory!\n");
    exit(1);
}

void joinwtLNV(listaDeNodos node, int *listaDeNodosVazios, int p, int q, int wt){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0){
        node[r].info = wt;
        return;
    }
    r = getnodeLista(*listaDeNodosVazios, node);
    node[r].info = wt;
    node[r].next = -1;
    node[r].point = q;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

void join(listaDeNodos node, int *LDNV, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r < 0){
        r = getnodeLista(node, *LDNV);
        node[r].point = q;
        node[r].next = -1;
        if (r2 < 0)
            node[p].point = r;
        else
            node[r2].next = r;
    }
}

// remv sem wt
void remv(listaDeNodos node, int *LDNV, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0){
        if (r2 < 0)
            node[p].point = node[r].next;
        else
            node[r2].next = node[r].next;
        freenode(LDNV, node, r);
    }
}

void freenode(int *listaDeNodosVazios, listaDeNodos node, int r){
    node[r].next = *listaDeNodosVazios;
    *listaDeNodosVazios = r;
}

// remv com wt (mesma coisa)
void remvwt(listaDeNodos node, int *LDNV, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0){
        if (r2 < 0)
            node[p].point = node[r].next;
        else
            node[r2].next = node[r].next;
        freenode(LDNV, node, r);
    }
}

char adjacent(listaDeNodos node, int p, int q){
    int r;
    r = node[p].point;
    while (r >= 0)
        if (node[r].point == q)
            return 1;
        else
            r = node[r].next;
    return 0;
}

int findnode(listaDeNodos node, int graph, int x){
    int p = graph;
    while (p >= 0)
        if (node[p].info == x)
            return p;
        else
            p = node[p].next;
    return -1;
}

int addnode(listaDeNodos node, int *ldnv, int *pgraph, int x){
    int p = getnodeLista(ldnv, node);
    node[p].info = x;
    node[p].point = -1;
    node[p].next = *pgraph;
    *pgraph = p;
    return p;
}

int remvnode(listaDeNodos node, int *ldnv, int *graph, int p){
    int atual, anterior, retorno=0;    // atual e anterior para nodos
    atual = anterior = *graph;
    while (atual >= 0){             // existe grafo ou não terminou
        if (atual == p){            // encontrou o nó
            int aux, aux2;                 // aux(atual), aux2(anterior) para remover arcos 
            if (atual == *graph)                  // mexe no início caso seja o primeiro
                *graph = node[atual].next;
            else
                node[anterior].next = node[atual].next;
            aux = node[atual].point;                      // começo nos arcos
            while (aux >= 0){ 
                aux2 = aux;                          
                aux = node[aux].next;
                freenode(ldnv, node, aux2);              // free clássico
            }
            anterior = atual;                      // atualiza o while
            atual = node[atual].next; 
            freenode(ldnv, node, p);               // remove nodo
            retorno = 1;                      // confirma exclusão
        } else {
            int aux, aux2, auxNode;
            aux = aux2 = node[atual].point;    // acessa o primeiro arco do nodo
            while (aux >= 0){                  // enquanto houver arcos
                if (node[aux].point == p){       // encontrou um arco que aponta para p
                    if (aux == aux2)                            // se for o primeiro
                        node[atual].point = node[aux].next;     // o primeiro arco será o prox.
                    else
                        node[aux2].next = node[aux].next;       
                    auxNode = aux;
                    aux2 = aux;
                    aux = node[aux].next;
                    freenode(ldnv, node, auxNode);
                } else {
                    aux2 = aux;
                    aux = node[aux].next;
                }
            } 
            anterior = atual;
            atual = node[atual].next;
        }
    }
    return retorno;
}
