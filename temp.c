// FILA SEQUENCIAL

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int INICIO;
    int FIM;
    int N;
    int val[MAX];
}FILA_SEQ;

void criar_fila_s(FILA_SEQ *f){
    f->N = f->INICIO = 0;
    f->FIM = -1;
}

int eh_vazia_fs(FILA_SEQ *f){
    return !f->N;
}

int tam_fs(FILA_SEQ *f){
    return f->N;
}

void ins_fs(FILA_SEQ *f, int v){
    if (f->N == MAX)
        return;
    f->FIM = (f->FIM+1) % MAX;
    f->val[f->FIM] = v;
    f->N++;
}

int cons_fs(FILA_SEQ *f){
    if (eh_vazia_fs(f))
        return;
    return f->val[f->INICIO];
}

void ret_fs(FILA_SEQ *f){
    if (eh_vazia_fs(f))
        return;
    f->INICIO = (f->INICIO+1) % MAX;
    f->N--;
}

int cons_ret_fs(FILA_SEQ *f){
    if (!f->N)
        return;
    else {
        int v = f->val[f->INICIO];
        f->INICIO = (f->INICIO+1) % MAX;
        f->N--;
        return v;
    }
}

void gera_fila(FILA_SEQ *f, int m, int n){
    if (m > n)
        return;
    if (m == n){
        criar_fila_s(f);
        ins_fs(f, m);
    } else {
        gera_fila(f, m, n-1);
        ins_fs(f, n);
    }
}

// FILA ENCADEADA

typedef struct nodo {
    int inf;
    struct nodo * next;
}NODO;

typedef struct {
    NODO * INICIO;
    NODO * FIM;
}DESCRITOR;

typedef DESCRITOR * FILA_ENC;

void criar_fila_e(FILA_ENC *f){
    *f = (FILA_ENC) malloc(sizeof(DESCRITOR));
    if (!*f)
        return;
    (*f)->INICIO = (*f)->FIM = NULL;
}

int eh_vazia_fe(FILA_ENC f){
    return !f->INICIO;
}

void ins_fe(FILA_ENC f, int v){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    novo->next = NULL;
    if (eh_vazia_fe(f))
        f->INICIO = novo;
    else
        f->FIM->next = novo;
    f->FIM = novo;
}

int cons_fe(FILA_ENC f){
    if (eh_vazia_fe(f))
        return;
    return f->INICIO->inf;
}

void ret_fe(FILA_ENC f){
    if (eh_vazia_fe(f))
        return;
    else {
        NODO *aux = f->INICIO;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
    }
}

int cons_ret_fe(FILA_ENC f){
    if (eh_vazia_fe(f))
        return;
    else {
        NODO *aux = f->INICIO;
        int v = aux->inf;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
        return v;
    }
}

void destruir_fe(FILA_ENC f){
    NODO *aux;
    while(f->INICIO){
        aux = f->INICIO;
        f->INICIO = aux->next;
        free(aux);
    }
    free(f);
}

// PILHA SEQUENCIAL

typedef struct {
    int TOPO;
    int val[MAX];
}PILHA_SEQ;

void criar_pilha_s(PILHA_SEQ *p){
    p->TOPO = -1;
}

int eh_vazia_ps(PILHA_SEQ *p){
    return p->TOPO < 0;
}

void push_ps(PILHA_SEQ *p, int v){
    if (p->TOPO == MAX-1)
        return;
    p->val[++p->TOPO] = v;
}

int top_ps(PILHA_SEQ *p){
    if (eh_vazia_ps(p))
        return;
    return p->val[p->TOPO];
}

void pop_ps(PILHA_SEQ *p){
    if (eh_vazia_ps(p))
        return;
    p->TOPO--;
}

int top_pop_ps(PILHA_SEQ *p){
    if (eh_vazia_ps(p))
        return;
    return p->val[p->TOPO--];
}

void inverter_fila(FILA_SEQ *f){
    PILHA_SEQ p;
    criar_pilha_s(&p);
    while(!eh_vazia_fs(f))
        push_ps(&p, cons_ret_fs(f));
    while(!eh_vazia_ps(&p))
        ins_fs(f, top_pop_ps(&p));
}

// PILHA ENCADEADA

typedef struct nodo{
    int inf;
    struct nodo * next;
}NODO;

typedef NODO * PILHA_ENC;

void create(PILHA_ENC *p){
    *p = NULL;
}

int is_empty(PILHA_ENC p){
    return !p;
}

void push_pe(PILHA_ENC *p, int v){
    NODO *new;
    new = (NODO*) malloc(sizeof(NODO));
    if (!new)
        return;
    new->inf = v;
    new->next = *p;
    *p = new;
}

int top_pe(PILHA_ENC p){
    if (!p)
        return;
    return p->inf;
}

void pop_pe(PILHA_ENC *p){
    if (!*p)
        return;
    else {
        NODO *aux = *p;
        *p = aux->next;
        free(aux);
    }
}

int top_pop_pe(PILHA_ENC *p){
    if (!*p)
        return;
    else {
        NODO *aux = *p;
        int v = aux->inf;
        *p = aux->next;
        free(aux);
        return v;
    }
}

// ÁRVORE BINÁRIA SEQUENCIAL

#define NUMNODES 100

typedef struct {
    int info;
    int father;
    int left;
    int right;
}NODE;

typedef struct {
    int root;
    int nodeFree;
    NODE nodes[NUMNODES];
}ARV_BIN_SEQ;

void maketree(ARV_BIN_SEQ *t, int x){
    int i, ind;
    for (i = 0; i < NUMNODES-1; i++)
        t->nodes[i].left = i+1;
    t->nodes[i].left = -1;
    t->nodeFree = 0;
    ind = getNode(t);
    if (ind != -1){
        t->nodes[ind].info = x;
        t->nodes[ind].father = -1;
        t->nodes[ind].left = -1;
        t->nodes[ind].right = -1;
        t->root = ind;
    } else {
        return;
    }
}

int getNode(ARV_BIN_SEQ *t){
    if (t->nodeFree != -1){
        int i = t->nodeFree;
        t->nodeFree = t->nodes[t->nodeFree].left;
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
        t->nodes[ind].info = x;
        t->nodes[ind].left = -1;
        t->nodes[ind].right = -1;
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

// ÁRVORE BINÁRIA ENCADEADA

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
