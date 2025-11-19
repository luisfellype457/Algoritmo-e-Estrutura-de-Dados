#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 10

typedef struct graph{
    int nodes[MAXNODES];
    int arcs[MAXNODES][MAXNODES];
};

struct graph g;

void incializar(struct graph g){
    int i, j;
    for (i=0; i < MAXNODES; i++)
        for (j=0; j < MAXNODES; j++)
            g.arcs[i][j] = 0;
}

void ligar(struct graph g, int a, int b){
    g.arcs[a][b] = 1;
}
