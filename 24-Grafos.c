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

int procurarCaminho(int adj[][MAXNODES], int n, int k, int a, int b){
    int c;
    if (k == 1)
        return adjacente(adj, a, b);
    for (c=0; c < n; ++c)
        if (adjacente(adj, a, c) && procurarCaminho(adj, n, k-1, c, b))
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
    printf("\t%s\n\n", procurarCaminho(adj, n, nr, a, b) ? "confirmado" : "nop");
    return 0;
}
