#include <stdio.h>
#include <stdlib.h>

#define MAXNODES 10;

// TAD FILA

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef struct{
    NODO *INICIO;
    NODO *FIM;
}DESCRITOR;

typedef DESCRITOR *FILA_ENC;

void cria_fila(FILA_ENC *f){
    *f = (NODO*) malloc(sizeof(DESCRITOR));
    if (!*f)
        return;
    (*f)->INICIO = (*f)->FIM = NULL;
}

int eh_vazia(FILA_ENC f){
    return !f->INICIO;
}

void ins(FILA_ENC f, int v){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = v;
    if (!f->INICIO)
        f->INICIO = novo;
    else
        f->FIM->next = novo;
    f->FIM = novo;
}

int cons(FILA_ENC f){
    if (eh_vazia(f))
        return;
    return f->INICIO->inf;
}

void ret(FILA_ENC f){
    if (eh_vazia(f))
        return;
    else {
        NODO *aux = f->INICIO;
        f->INICIO = aux->next;
        if (!f->INICIO)
            f->FIM = NULL;
        free(aux);
    }
}

int cons_ret(FILA_ENC f){
    if (eh_vazia(f))
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

// TAD GRAFO ENCADEADO EM VETOR

#define MAXNODES 10

typedef struct{
    int info;
    int point;
    int next;
    char cor;
    int d;
    int pai;
    int f;
}tipoNodo;

typedef tipoNodo listaDeNodos[MAXNODES];

void inicializaGrafo(listaDeNodos node){
    int i;
    for (i=1; i < MAXNODES; ++i)
        node[i-1].next = i;
    node[i-1].next = -1;
}

void criaListaDeNodosVazios(int *ldnv, listaDeNodos node){
    *ldnv = 0;
}

int getnode(int *ldnv, listaDeNodos node){
    int i = *ldnv;
    if (i != -1){
        *ldnv = node[i].next;
        return i;
    }
    printf("sem armazenamento!\n");
    exit(1);
}

void freenode(int *ldnv, listaDeNodos node, int p){
    node[p].next = *ldnv;
    *ldnv = p;
}

void joinwt(listaDeNodos node, int *ldnv, int p, int q, int wt){
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
    r = getnode(ldnv, node);
    node[r].point = q;
    node[r].info = wt;
    node[r].next = -1;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

void join(listaDeNodos node, int *ldnv, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r < 0){
        r = getnode(ldnv, node);
        node[r].point = q;
        node[r].next = -1;
        if (r2 < 0)
            node[p].point = r;
        else
            node[r2].next = r;
    }
}

void remv(listaDeNodos node, int *ldnv, int p, int q){
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
            node[r2].point = node[r].next;
        freenode(ldnv, node, r);
    }
}

void remvwt(listaDeNodos node, int *ldnv, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r >= 0){
        if (r2 < 0)
            node[r].point = node[r].next;
        else
            node[r2].next = node[r].next;
        freenode(ldnv, node, r);
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

int addnode(listaDeNodos node, int *ldnv, int *graph, int x){
    int p = getnode(ldnv, node);
    node[p].info = x;
    node[p].point = -1;
    node[p].next = *graph;
    *graph = p;
    return p;
}

int remvnode(listaDeNodos node, int *ldnv, int *graph, int p){
    int anterior, atual, retorno=0;
    anterior = atual = *graph;
    while (atual >= 0){
        if (atual == p){
            int aux, aux2;
            if (atual == anterior)
                *graph = node[atual].next;
            else
                node[anterior].next = node[atual].next;
            aux = node[atual].point;
            while (aux >= 0){
                aux2 = aux;
                aux = node[aux].next;
                freenode(ldnv, node, aux2);
            }
            anterior = atual;
            atual = node[atual].next;
            freenode(ldnv, node, p);
            retorno = 1;
        } else {
            int aux, aux2, auxNode;
            aux = aux2 = node[atual].point;
            while (aux >= 0){
                if (node[aux].point == p){
                    if (aux == aux2)
                        node[atual].point = node[aux].next;
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

// BUSCA EM LARGURA

void buscaEmLargura(listaDeNodos node, int G, int s){
    int u, v, ind;
    FILA_ENC Q;
    u = G;
    while (u >= 0){
        if (u != s){
            node[u].cor = 'B';
            node[u].d = -1;
            node[u].pai = -1;
        } else {
            node[u].cor = 'C';
            node[u].d = 0;
            node[u].pai = -1;
        }
        u = node[u].next;
    }
    cria_fila(&Q);
    ins(Q, s);
    while (!eh_vazia(Q)){
        u = cons_ret(Q);
        v = node[u].point;
        while (v >= 0){
            if (node[node[v].point].cor == 'B'){
                node[node[v].point].cor = 'C';
                node[node[v].point].d = node[u].d + 1;
                node[node[v].point].pai = u;
                ins(Q, node[v].point);
            }
            v = node[v].next;
        }
        node[u].cor = 'P';
    }
}

// MENOR CAMINHO

void imprimirCaminho(listaDeNodos node, int s, int v){
    if (v == s)
        printf("%c ", node[s].info);
    else
        if (node[v].pai == -1)
            printf("no way to v\n");
        else {
            imprimirCaminho(node, s, node[v].pai);
            printf("%c ", node[v].info);
        }
}

// BUSCA EM PROFUNDIDADE

int tempo;

void buscaEmProfundidade(listaDeNodos node, int G){
    int u = G;
    while (u >= 0){
        node[u].cor = 'B';
        node[u].pai = -1;
        u = node[u].next;
    }
    tempo = 0;
    u = G;
    while (u >= 0){
        if (node[u].cor == 'B')
            visitaBuscaEmProfundidade(node, u);
        u = node[u].next;
    }
}

void visitaBuscaEmProfundidade(listaDeNodos node, int u){
    int v;
    node[u].cor = 'C';
    tempo++;
    node[u].d = tempo;
    v = node[u].point;
    while (v >= 0){
        if (node[node[v].point].cor == 'B'){
            node[node[v].point].pai = u;
            visitaBuscaEmProfundidade(node, node[v].point);
        }
        v = node[v].next;
    }
    node[u].cor = 'P';
    node[u].f = ++tempo;
}
