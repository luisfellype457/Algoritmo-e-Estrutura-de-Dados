#include <stdio.h>
#include <stdlib.h>

#define tam 8

typedef struct {
    int chave;
    char livre;
}Hash;

typedef Hash Tabela[tam];

int funcaoHashing(int n){
    return n % tam;
}

void inserir(Tabela tabela, int n){
    int pos = funcaoHashing(n);
    int i=0;
    while (i < tam && tabela[(pos+i)%tam].livre != 'L'
    && tabela[(pos+i)%tam].livre != 'R')
        i = i + 1;
    if (i < tam){
        tabela[(pos+i)%tam].livre = 'O';
        tabela[(pos+i)%tam].chave = n;
    } else {
        printf("tabela cheia!\n");
    }
}
