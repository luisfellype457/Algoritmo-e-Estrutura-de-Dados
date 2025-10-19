#include <stdio.h>
#include <stdlib.h>
#define NUMNODES 100

typedef struct{
    int info;
    int father;
    int left;
    int right;
}NODE;

typedef struct{
    int root;
    int nodeFree;
    NODE nodes[NUMNODES];
}ARV_BIN_SEQ;

void maketree(ARV_BIN_SEQ *t, int x){
    int i, ind;
    for(i=0; i < NUMNODES-1; i++)
        t->nodes[i].left = i+1;
    t->nodes[i].left = -1;
    t->nodeFree = 0;
    ind = getNode(t);
    if (ind != -1){
        t->nodes[ind].father = -1;
        t->nodes[ind].left = -1;
        t->nodes[ind].right = -1;
        t->nodes[ind].info = x;
        t->root = ind;
    } else {
        return;
    }
}

int getNode(ARV_BIN_SEQ *t){
    if (t->nodeFree != -1){
        int i = t->nodeFree;
        t->nodeFree = t->nodes[i].left;
        return i;
    } else {
        return -1;
    }
}

void freeNode(ARV_BIN_SEQ *t, int node){
    t->nodes[node].left = t->nodeFree;
    t->nodeFree = node;
}

void setleft(ARV_BIN_SEQ *t, int p, int x){
    int ind = getNode(t);
    if (ind != -1){
        t->nodes[p].left = ind;
        t->nodes[ind].father = p;
        t->nodes[ind].left = -1;
        t->nodes[ind].right = -1;
        t->nodes[ind].info = x;
    } else {
        return;
    }
}

void setright(ARV_BIN_SEQ *t, int p, int x){
    int ind = getNode(t);
    if (ind != -1){
        t->nodes[p].right = ind;
        t->nodes[ind].father = p;
        t->nodes[ind].info = x;
        t->nodes[ind].left = -1;
        t->nodes[ind].right = -1;
    } else {
        return;
    }
}

int info(ARV_BIN_SEQ *t, int p){
    return t->nodes[p].info;
}

int left(ARV_BIN_SEQ *t, int p){
    return t->nodes[p].left;
}

int right(ARV_BIN_SEQ *t, int p){
    return t->nodes[p].right;
}

int father(ARV_BIN_SEQ *t, int p){
    return t->nodes[p].father;
}

int brother(ARV_BIN_SEQ *t, int p){
    if (father(t, p) != -1)
        if (isleft(t, p))
            return right(t, father(t, p));
        else
            return t->nodes[t->nodes[p].father].left;
    return -1;
}

int isleft(ARV_BIN_SEQ *t, int p){
    int q = father(t, p);
    if (q == -1)
        return 0;
    if (left(t, q) == p)
        return 1;
    return 0;
}

int isright(ARV_BIN_SEQ *t, int p){
    if (father(t, p) != -1)
        return !isleft(t, p);
    return 0;
}
