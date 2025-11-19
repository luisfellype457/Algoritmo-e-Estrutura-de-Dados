// HASHING ABERTO

#include <stdio.h>
#include <stdlib.h>

#define numEntradas 8

typedef struct _Hash{
    int chave;
    struct _Hash * prox;
}Hash;

typedef Hash *TADTabelaHash[numEntradas];

void inicializarHash(TADTabelaHash tabela){
    int i;
    for (i=0; i < numEntradas; i++)
        tabela[i] = NULL;
}

int funcaoHashing(int n){
    return n % numEntradas;
}

void inserirHash(TADTabelaHash tabela, int num){
    int pos = funcaoHashing(num);
    Hash *novo;
    novo = (Hash*) malloc(sizeof(Hash));
    if (!novo)
        return;
    novo->chave = num;
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

void mostrarHash(TADTabelaHash tabela){
    int i;
    Hash *atual;
    for (i=0; i < numEntradas; i++){
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
        return;
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
            } else {
                return;
            }
        }
    else
        return;
}

void liberarMemoria(TADTabelaHash tabela){
    int i;
    for (i=0; i < numEntradas; i++)
        while (tabela[i]){
            free(tabela[i]);
            tabela[i] = tabela[i]->prox;
        }
}

// HASHING FECHADO

#define tam 8

typedef struct{
    int chave;
    char livre;
}HashF;

typedef HashF Tabela[tam];

void inicializarHash(Tabela tabela){
    int i;
    for (i=0; i < tam; i++)
        tabela[i].livre = 'L';
}

int funcaoHashing(int n){
    return n % tam;
}

void mostrarHash(Tabela tabela){
    int i;
    for (i=0; i < tam; i++){
        if (tabela[i].livre == 'O'){
            printf("%d - [%d] O\n", i, tabela[i].chave);
        } else {
            printf("%d - [ ] %c\n", i, tabela[i].livre);
        }
    }
}

void inserirHash(Tabela tabela, int num){
    int pos = funcaoHashing(num);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].livre == 'O')
        i = i+1;
    if (i < tam){
        tabela[(pos+i)%tam].livre = 'O';
        tabela[(pos+i)%tam].chave = num;
    } else {
        return;
    }
}

int buscarChave(Tabela tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].livre != 'L' &&
    tabela[(pos+i)%tam].chave != n)
        i = i+1;
    if (i < tam && tabela[(pos+i)%tam].livre == 'O')
        return (pos+i)%tam;
    else
        return tam;
}

void removerChave(Tabela tabela, int n){
    int pos = buscarChave(tabela, n);
    if (pos < tam)
        tabela[pos].livre = 'R';
    else
        return;
}

 // HASHING FECHADO TENTATIVA QUADRÁTICA

void inserir(Tabela tabela, int n){
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

int buscarQ(Tabela tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[pos].livre != 'L' && tabela[pos].chave != n){
        pos = (pos+i)%tam;
        i = i+1;
    }
    if (i < tam && tabela[pos].livre == 'O' && tabela[pos].chave == n)
        return pos;
    else
        return tam;
}

void removerQ(Tabela tabela, int n){
    int pos = buscarQ(tabela, n);
    if (pos < tam)
        tabela[pos].livre = 'R';
    else
        return;
}
