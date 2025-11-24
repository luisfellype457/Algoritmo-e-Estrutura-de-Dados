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
