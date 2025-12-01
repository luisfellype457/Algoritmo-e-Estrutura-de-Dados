#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 10

void ligar(int adj[][MAXNODES], int node1, int node2){
    adj[node1][node2] = 1;
}

void remover(int adj[][MAXNODES], int node1, int node2){
    adj[node1][node2] = 0;
}

int adjacente(int adj[][MAXNODES], int node1, int node2){
    return adj[node1][node2];
}

// GRAFOS PONDERADOS

typedef struct arc{
    int adj;
    int peso;
};

void ligarP(struct arc adj[][MAXNODES], int node1, int node2, int p){
    adj[node1][node2].adj = 1;
    adj[node1][node2].peso = p;
}

void removerP(struct arc adj[][MAXNODES], int node1, int node2){
    adj[node1][node2].adj = 0;
}

int adjacenteP(struct arc adj[][MAXNODES], int node1, int node2){
    return adj[node1][node2].adj;
}

// GRAFOS - APLICAÇÃO

int procurarCaminho(int adj[][MAXNODES], int k, int a, int b){
    int c;
    if (k == 1)
        return adjacente(adj, a, b);
    for (c=0; c < n; ++c)
        if (adjacente(adj, a, c) && procurarCaminho(adj, k-1, c, b))
            return 1;
    return 0;
}

int main(){
    int i, j, n, a, b, city1, city2, nr, **adj;
    scanf("%d %d %d %d", &n, &a, &b, &nr);
    **adj = (int**) malloc(n * sizeof(int*));
    if (!**adj)
        return 1;
    for (i=0; i < n; ++i)
        adj[i] = (int*) malloc(n * sizeof(int));
    for (i=0; i < n; ++i)
        for (j=0; j < n; ++j)
            adj[i][j] = 0;
    do{
        scanf("%d %d", &city1, &city2);
        if (city1 > -1 && city2 > -1)
            ligar(adj, city1, city2);
    }while (city1 > -1 && city2 > -1);
    printf("\t%s\n\n", procurarCaminho(adj, nr, a, b) ? "confirmado" : "nop");
    return 0;
}

typedef struct nodetype{
    int info;
    int point;
    int next;
    char livre; // add
}tipoNodo;

typedef tipoNodo listaDeNodos[MAXNODES];

typedef struct nodetype{
    int info;
    struct nodetype *point;
    struct nodetype *next;
};

struct nodetype *nodeptr;

int getnode(listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        if (node[i].livre == 1)
            return i;
    return -1;
}

void joinwt(listaDeNodos node, int p, int q, int wt){
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
        printf("lista cheia\n");
    else{
        node[r].info = wt;
        node[r].livre = 0;
        node[r].point = q;
        node[r].next = -1;
        if (r2 < 0)
            node[p].point = r;
        else
            node[r2].next = r;
    }
}

//

void inicializarGrafo(int *grafo, listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        node[i].livre = 1;
    *grafo = -1;
}

void criarListaDeNodos(int *listaDeNodosVazios, listaDeNodos node){
    int i;
    for (i=1; i < MAXNODES; ++i)
        node[i-1].next = i;
    node[i-1].next = -1;
    *listaDeNodosVazios = 0;
}

int getnode2(int *listaDeNodosVazios, listaDeNodos node){
    int i = *listaDeNodosVazios;
    if (i != -1){
        *listaDeNodosVazios = node[i].next;
        return i;
    } else {
        printf("sem armazenamento\n");
        exit(1);
    }
}

void joinwt2(listaDeNodos node, int *listaDeNodosVazios, int p, int q, int wt){
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
    r = getnode2(*listaDeNodosVazios, node);
    node[r].info = wt;
    node[r].point = q;
    node[r].next = -1;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

//

void join(listaDeNodos node, int *listaDeNodosVazios, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0)
        return;
    r = getnode2(*listaDeNodosVazios, node);
    node[r].point = q;
    node[r].next = -1;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

void remv(listaDeNodos node, int p, int q){
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
        freenode(listaDeNodosVazios, node, r);
    }
}
