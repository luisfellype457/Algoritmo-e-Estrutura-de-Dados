#include <stdio.h>
#include <stdlib.h>
#define NUMNODES 100

typedef struct{
    int info;
    int left;
    int right;
    int father;
}NODE;

typedef struct{
    int root;
    int nodeFree;
    NODE nodes[NUMNODES];
}ARV_BIN_SEQ;

void maketree(ARV_BIN_SEQ *a, int)