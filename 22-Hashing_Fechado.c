#include <stdio.h>
#include <stdlib.h>

#define tam 8

typedef struct{
    int chave;
    char livre;
}Hash;

typedef Hash TabelaHash[tam];

void inicializarHash(TabelaHash *tabela){
    int i;
    for (i=0; i < tam; i++)
        tabela[i]->livre = 'L';
}

int funcaoHashing(int n){
    return n % tam;
}

void mostrarHash(TabelaHash tabela){
    int i;
    for (i=0; i < tam; i++){
        if (tabela[i].livre != 'L')
            printf("[%d]\n", tabela[i].chave);
        else
            printf("[ ]\n");
    }
}

void inserirChave(TabelaHash tabela, int n){
    int i=0;
    int pos = funcaoHashing(n);
    while (i < tam && tabela[(pos+i)%tam].livre == 'O')
        i = i+1;
    if (i < tam){
        tabela[(pos+i)%tam].livre = 'O';
        tabela[(pos+i)%tam].chave = n;
    } else {
        return;
    }
}

int buscarChave(TabelaHash tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].livre != 'L' && tabela[(pos+i)%tam].chave != n)
        i = i+1;
    if (i < tam && tabela[(pos+i)%tam].livre == 'O' && tabela[(pos+i)%tam].chave == n)
        return (pos+i)%tam;
    else
        return tam;
}

void removerChave(TabelaHash tabela, int n){
    int posicao = buscarChave(tabela, n);
    if (posicao < tam)
        tabela[posicao].livre = 'R';
    else
        return;
}
