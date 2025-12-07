// HASHING ABERTO

#include <stdio.h>
#include <stdlib.h>

#define tam 8

typedef struct _Hash{
    int chave;
    struct _Hash * prox;
}Hash;

typedef Hash *TADTabelaHash[tam];

void inicializarHash(TADTabelaHash tabela){
    int i;
    for (i=0; i < tam; ++i)
        tabela[i] = NULL;
}

int funcaoHashing(int n){
    return n % tam;
}

void inserirHash(TADTabelaHash tabela, int n){
    int pos = funcaoHashing(n);
    Hash *novo;
    novo = (Hash*) malloc(sizeof(Hash));
    if (!novo)
        return;
    novo->chave = n;
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

void mostrarHash(TADTabelaHash tabela){
    int i;
    Hash *atual;
    for (i=0; i < tam; ++i)
        if (tabela[i]){
            printf("[%d]", tabela[i]->chave);
            atual = tabela[i]->prox;
            while (atual){
                printf(" -> [%d]", atual->chave);
                atual = atual->prox;
            }
            printf("\n");
        } else {
            printf("[ ]\n");
        }
}

Hash* localizarHash(TADTabelaHash tabela, int num){
    int pos = funcaoHashing(num);
    if (tabela[pos])
        if (tabela[pos]->chave == num)
            return tabela[pos];
        else {
            Hash* aux = tabela[pos]->prox;
            while (aux && aux->chave != num)
                aux = aux->prox;
            return aux;
        }
    else
        return NULL;
}

void excluirHash(TADTabelaHash tabela, int num){
    int pos = funcaoHashing(num);
    Hash* aux;
    if (tabela[pos])
        if (tabela[pos]->chave == num){
            aux = tabela[pos];
            tabela[pos] = aux->prox;
            free(aux);
        } else {
            Hash* ant;
            aux = tabela[pos]->prox;
            while (aux && aux->chave != num){
                ant = aux;
                aux = aux->prox;
            }
            if (aux){
                ant->prox = aux->prox;
                free(aux);
            }
        }
    return;
}

void liberarMemoria(TADTabelaHash tabela){
    int i;
    for (i=0; i < tam; ++i)
        while (tabela[i]){
            free(tabela[i]);
            tabela[i] = tabela[i]->prox;
        }
}

// HASHING FECHADO

typedef struct{
    int chave;
    char livre;
}HashF;

typedef HashF TabelaF[tam];

void inicializarTabelaF(TabelaF tabela){
    int i;
    for (i=0; i < tam; ++i)
        tabela[i].livre = 'L';
}

void inserirHashF(TabelaF tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].livre == 'O')
        i = i+1;
    if (i < tam){
        tabela[(pos+i)%tam].livre = 'O';
        tabela[(pos+i)%tam].chave = n;
    } else {
        return;
    }
}

int buscarChave(TabelaF tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].chave != n && 
    tabela[(pos+i)%tam].livre != 'L');
        i = i+1;
    if (i < tam && tabela[(pos+i)%tam].livre == 'O')
        return (pos+i)%tam;
    else
        return tam;
}

void mostrarHashF(TabelaF tabela){
    int i;
    for (i=0; i < tam; ++i)
        if (tabela[i].livre == 'L')
            printf("[ ] L\n");
        else {
            if (tabela[i].livre == 'O')
                printf("[%d] O\n", tabela[i].chave);
            else
                printf("[%d] R\n", tabela[i].chave);
        }
}

void removerChave(TabelaF tabela, int n){
    int pos = buscarChave(tabela, n);
    if (pos < tam)
        tabela[pos].livre = 'R';
    else
        return;
}

// HASHING FECHADO TENTATIVA QUADRÁTICA

void inserirHashQ(TabelaF tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[pos].livre == 'O'){
        pos = (pos+i)%tam;
        i = i+1;
    }
    if (i < tam){
        tabela[pos].livre = 'O';
        tabela[pos].chave = n;
    } else
        return;
}

int buscarChaveQ(TabelaF tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[pos].chave != n &&
    tabela[pos].livre != 'L'){
        pos = (pos+i)%tam;
        i = i+1;
    }
    if (i < tam && tabela[pos].livre == 'O' && tabela[pos].chave == n)
        return pos;
    else
        return tam;
}

void removerChaveQ(TabelaF tabela, int n){
    int pos = buscarChave(tabela, n);
    if (pos < tam)
        tabela[pos].livre = 'R';
    else
        return;
}

// GRAFOS

#define MAXNODES 10

int adj[MAXNODES][MAXNODES];

void ligar(int adj[][MAXNODES], int node1, int node2){
    adj[node1][node2] = 1;
}

void remover(int adj[][MAXNODES], int node1, int node2){
    adj[node1][node2] = 0;
}

int adjacente(int adj[][MAXNODES], int node1, int node2){
    return adj[node1][node2];
}

int procurarCaminho(int adj[][MAXNODES], int k, int a, int b){
    int c;
    if (k == 1)
        return adjacente(adj, a, b);
    for (c=0; c < n; ++c)
        if (adjacente(adj, a, c) && procurarCaminho(adj, k-1, c, b))
            return 1;
    return 0;
}

// REPRESENTAÇÃO ESTÁTICA

typedef struct nodetype{
    int info;
    int point;
    int next;
    char livre;
}tipoNodo;

typedef tipoNodo listaDeNodos[MAXNODES];

void jointwt(listaDeNodos node, int p, int q, int wt){
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
        exit(1);
    node[r].info = wt;
    node[r].next = -1;
    node[r].point = q;
    node[r].livre = 0;
    if (r2 < 0)
        node[p].point = r;
    else
        node[r2].next = r;
}

int getnode(listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        if (node[i].livre == 1)
            return i;
    return -1;
}

void inicializaGrafo(int *grafo, listaDeNodos node){
    int i;
    for (i=0; i < MAXNODES; ++i)
        node[i].livre = 1;
    *grafo = -1;
}

// GRAFOS COM LISTA DE NODOS VAZIOS

void criaListaDeNodosVazios(int *listaDeNodosVazios, listaDeNodos node){
    int i;
    for (i=1; i < MAXNODES; ++i)
        node[i-1].next = i;
    node[i-1].next = -1;
    *listaDeNodosVazios = 0;
}

int getnodeLista(int *listaDeNodosVazios, listaDeNodos node){
    int i = *listaDeNodosVazios;
    if (i != -1){
        *listaDeNodosVazios = node[i].next;
        return i;
    }
    printf("out of memory!\n");
    exit(1);
}

void joinwtLNV(listaDeNodos node, int *listaDeNodosVazios, int p, int q, int wt){
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
    r = getnodeLista(*listaDeNodosVazios, node);
    node[r].info = wt;
    node[r].next = -1;
    node[r].point = q;
}

void join(listaDeNodos node, int *LDNV, int p, int q){
    int r, r2;
    r2 = -1;
    r = node[p].point;
    while (r >= 0 && node[r].point != q){
        r2 = r;
        r = node[r].next;
    }
    if (r < 0){
        r = getnodeLista(node, *LDNV);
        node[r].point = q;
        node[r].next = -1;
        if (r2 < 0)
            node[p].point = r;
        else
            node[r2].next = r;
    }
}

// remv sem wt
void remv(listaDeNodos node, int *LDNV, int p, int q){
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
        freenode(LDNV, node, r);
    }
}

void freenode(int *listaDeNodosVazios, listaDeNodos node, int r){
    node[r].next = *listaDeNodosVazios;
    *listaDeNodosVazios = r;
}

// remv com wt (mesma coisa)
void remvwt(listaDeNodos node, int *LDNV, int p, int q){
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
        freenode(LDNV, node, r);
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

int addnode(listaDeNodos node, int *ldnv, int *pgraph, int x){
    int p = getnodeLista(ldnv, node);
    node[p].info = x;
    node[p].point = -1;
    node[p].next = *pgraph;
    *pgraph = p;
    return p;
}

int remvnode(listaDeNodos node, int *ldnv, int *graph, int p){
    int anterior, atual, retorno=0;
    atual = anterior = *graph;
    while (atual >= 0){
        if (atual == p){
            int aux, aux2;
            if (atual == *graph)
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