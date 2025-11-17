#include <stdio.h>
#include <stdlib.h>

#define tam 8

typedef struct{
    int chave;
    char livre;
}Hash;

typedef Hash Tabela[tam];

int funcaoHashing(int n){
    return n % tam;
}

void inicializarTabela(Tabela tabela){
    int i;
    for (i=0; i < tam; i++)
        tabela[i].livre = 'L';
}

void mostrarHash(Tabela tabela) {
    int i;
    int valor;
    for (i = 0; i < tam; i++) {
        valor = (tabela[i].livre == 'L') ? -1 : tabela[i].chave;
        printf("[%d] %c\n", valor, tabela[i].livre);
    }
}

void inserirChave(Tabela tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[pos].livre == 'O'){
        pos = (pos+i)%tam;
        i = i+1;
    }
    if (i < tam){
        tabela[pos].livre = 'O';
        tabela[pos].chave = n;
    } else {
        return;
    }
}

int buscarChave(Tabela tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[pos].livre != 'L' && tabela[pos].chave != n){
        pos = (pos+i)%tam;
        i = i+1;
    }
    if (i < tam && tabela[pos].chave == n && tabela[pos].livre == 'O')
        return pos;
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
