#include <stdio.h>
#include <stdlib.h>

// TAD FILA

typedef struct {
    int indMemoria;
    int indInf;
}DADOS;

typedef struct nodo{
    DADOS inf;
    struct nodo *next;
}NODO;

typedef struct{
    NODO *INICIO;
    NODO *FIM;
}DESCRITOR;

typedef DESCRITOR *FILA_ENC;

void cria_fila(FILA_ENC *fila){
    *fila = (DESCRITOR*) malloc(sizeof(DESCRITOR));
    if (!*fila)
        return;
    (*fila)->INICIO = (*fila)->FIM = NULL;
}

int eh_vazia(FILA_ENC fila){
    return !fila->INICIO;
}

void ins(FILA_ENC fila, DADOS dado){
    NODO *novo;
    novo = (NODO*) malloc(sizeof(NODO));
    if (!novo)
        return;
    novo->inf = dado;
    novo->next = NULL;
    if (!fila->FIM)
        fila->INICIO = novo;
    else
        fila->FIM->next = novo;
    fila->FIM = novo;
}

DADOS cons(FILA_ENC fila){
    if (eh_vazia(fila))
        return;
    return fila->INICIO->inf;
}

void ret(FILA_ENC fila){
    if (eh_vazia(fila))
        return;
    else {
        NODO *aux = fila->INICIO;
        fila->INICIO = aux->next;
        if (!fila->INICIO)
            fila->FIM = NULL;
        free(aux);
    }
}

DADOS cons_ret(FILA_ENC fila){
    if (eh_vazia(fila))
        return;
    else {
        NODO *aux = fila->INICIO;
        DADOS d = aux->inf;
        fila->INICIO = aux->next;
        if (!fila->INICIO)
            fila->FIM = NULL;
        free(aux);
        return d;
    }
}

// TAD GRAFO ENCADEADO EM VETOR

#define MAXNODES 10

typedef struct{
    int info;
    int point;
    int next;
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

void buscaEmLargura(listaDeNodos node, int G, int s){
    int u, *d=NULL, *pai=NULL, *vertice=NULL, numVertices=0, v, ind;
    char *cor=NULL;
    FILA_ENC Q;
    DADOS aux;
    u = G;
    while (u >= 0){
        ++numVertices;
        d = (int*) realloc(d, numVertices*sizeof(int));
        if (!d) return;
        pai = (int*) realloc(pai, numVertices*sizeof(int));
        if (!pai) return;
        vertice = (int*) realloc(vertice, numVertices*sizeof(int));
        if (!vertice) return;
        cor = (char*) realloc(cor, numVertices*sizeof(char));
        if (!cor) return;
        if (u != s){
            d[numVertices-1] = -1;
            pai[numVertices-1] = -1;
            vertice[numVertices-1] = node[u].info;
            cor[numVertices-1] = 'B';
        } else {
            ind = numVertices-1;
            d[ind] = 0;
            pai[ind] = -1;
            vertice[ind] = node[u].info;
            cor[ind] = 'C';
        }
        u = node[u].next;
    }
    cria_fila(&Q);
    aux.indInf = s;
    aux.indMemoria = ind;
    ins(Q, aux);
    while (!eh_vazia(Q)){
        aux = cons_ret(Q);
        u = aux.indInf;
        v = G;
        ind = -1;
        while (v >= 0){
            ind++;
            if (adjacent(node, u, v)){
                if (cor[ind] == 'B'){
                    DADOS aux2;
                    cor[ind] = 'C';
                    d[ind] = d[aux.indMemoria] + 1;
                    pai[ind] = u;
                    aux2.indInf = v;
                    aux2.indMemoria = ind;
                    ins(Q, aux2);
                }
            }
            v = node[v].next;
        }
        cor[aux.indMemoria] = 'P';  
    }
}
