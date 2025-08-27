// CÓDIGO SOBRE LISTAS ENCADEADAS COM RECURSIVIDADE
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int inf;
    struct nodo *next;
}NODO;

typedef NODO *LISTA_ENC;

int tam(LISTA_ENC lista){
    if (!lista)
        return 0;
    else {
        return tam(lista->next) + 1;
    }
}

int recup(LISTA_ENC lista, int posicao){
    if (posicao < 1 || posicao > tam(lista)){
        printf("\n\tinvalid position!\n");
        exit(1);
    }
    if (posicao == 1){
        return lista->inf;
    } else {
        return recup(lista->next, posicao-1);
    }
}

void destruir(LISTA_ENC lista){
    if (lista){
        destruir(lista->next);
        free(lista);
    }
}

void ins(LISTA_ENC *lista, int valor, int posicao){
    if (posicao < 1 || posicao > tam(*lista)+1){
        printf("\n\tinvalid position!\n");
        exit(2);
    }
    if (posicao == 1){
        NODO *novo = (NODO*) malloc (sizeof(NODO));
        if (!novo){
            printf("\n\tallocation error!\n");
            exit(2);
        }
        novo->inf = valor;
        novo->next = *lista;
        *lista = novo;
    } else {
        ins(&((*lista)->next), valor, posicao-1);
    }
}

void ret(LISTA_ENC *lista, int posicao){
    if (posicao < 1 || posicao > tam(*lista)){
        printf("\n\tinvalid position!\n");
        exit(3);
    }
    if (posicao == 1){
        NODO *aux = *lista;
        *lista = (*lista)->next;
        free(aux);
    } else {
        ret(&((*lista)->next), posicao-1);
    }
}

// função "pertence" sem recursividade:

int pertence(LISTA_ENC lista, int valor){
    while(lista){
        if (lista->inf == valor)
            return 1;
        lista = lista->next;
    }
    return 0;
}

// função "pertence" com recursividade

int pertence_rec(LISTA_ENC lista, int valor){
    if (!lista)
        return 0;
    if (lista->inf == valor)
        return 1;
    return pertence_rec(lista->next, valor);
}

// função "eh_ord" sem recursividade

int eh_ord(LISTA_ENC lista){
    while(lista && lista->next){
        if (lista->inf > (lista->next)->inf)
            return 0;
        lista = lista->next;
    }
    return 1;
}

// função "eh_ord" com recursividade

int eh_ord_rec(LISTA_ENC lista){
    if (lista && lista->next){
        if (lista->inf > (lista->next)->inf){
            return 0;
        }
        return eh_ord_rec(lista->next);
    }
    return 1;
}
