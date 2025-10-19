#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node *left;
    struct node *right;
    struct node *father;
} NODE;

typedef NODE * ARV_BIN_ENC;

void maketree(ARV_BIN_ENC *t, int x){
    *t = (NODE*) malloc(sizeof(NODE));
    if (!*t)
        return;
    (*t)->info = x;
    (*t)->father = NULL;
    (*t)->left = NULL;
    (*t)->right = NULL;
}

void setleft(ARV_BIN_ENC t, int x){
    t->left = (NODE*) malloc(sizeof(NODE));
    if (!t->left)
        return;
    t->left->info = x;
    t->left->father = t;
    t->left->left = NULL;
    t->left->right = NULL;
}

void setright(ARV_BIN_ENC t, int x){
    t->right = (NODE*) malloc(sizeof(NODE));
    if (!t->right)
        return;
    t->right->info = x;
    t->right->father = t;
    t->right->left = NULL;
    t->right->right = NULL;
}

int info(ARV_BIN_ENC t){
    return t->info;
}

ARV_BIN_ENC left(ARV_BIN_ENC t){
    return t->left;
}

ARV_BIN_ENC right(ARV_BIN_ENC t){
    return t->right;
}

ARV_BIN_ENC father(ARV_BIN_ENC t){
    return t->father;
}

ARV_BIN_ENC brother(ARV_BIN_ENC t){
    if (t->father)
        if (isleft(t))
            return t->father->right;
        else
            return t->father->left;
    else
        return NULL;
}

int isleft(ARV_BIN_ENC t){
    NODE *q = t->father;
    if (!q)
        return 0;
    if (q->left == t)
        return 1;
    return 0;
}

int isright(ARV_BIN_ENC t){
    if (t->father)
        return !isleft(t);
    return 0;
}
