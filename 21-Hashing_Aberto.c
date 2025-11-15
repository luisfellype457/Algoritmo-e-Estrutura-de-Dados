#include <stdio.h>
#include <stdlib.h>

#define numEntradas 8

typedef struct _Hash{
    int chave;
    struct _Hash *prox;
}Hash;

typedef Hash *TADTabelaHash[numEntradas];

void inicializarHash(TADTabelaHash tabela){
    int i;
    for (i=0; i < numEntradas; i++)
        tabela[i] = NULL;
}

int funcaoHashing(int num){
    return num % numEntradas;
}

void inserirHash(TADTabelaHash tabela, int num){
    Hash* novo;
    int pos = funcaoHashing(num);
    novo = (Hash*) malloc(sizeof(Hash));
    if (!novo)
        return;
    novo->chave = num;
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

void mostrarHash(TADTabelaHash tabela){
    int i;
    Hash* atual;
    for (i = 0; i < numEntradas; i++){
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
    Hash* aux;
    int pos = funcaoHashing(num);
    if (tabela[pos])
        if (tabela[pos]->chave == num)
            return tabela[pos];
        else {
            aux = tabela[pos]->prox;
            while (aux && aux->chave != num)
                aux = aux->prox;
            return aux;
        }
    return NULL;
}

void excluirHash(TADTabelaHash tabela, int num){
    Hash* aux;
    int pos = funcaoHashing(num);
    if (tabela[pos])
        if (tabela[pos]->chave == num){
            aux = tabela[pos];
            tabela[pos]->prox = aux->prox;
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
    else {
        return;
    }
}

void liberarMemoria(TADTabelaHash tabela){
    int i;
    Hash* aux;
    for (i = 0; i < numEntradas; i++){
        while (tabela[i]){
            aux = tabela[i];
            tabela[i] = aux->prox;                
            free(aux);
        }
    }
}
