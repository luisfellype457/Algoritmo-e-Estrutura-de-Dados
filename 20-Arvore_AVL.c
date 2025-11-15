#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int num, alte, altd;
    struct nodo *dir, *esq;
}NODO;

typedef NODO * ARVORE_AVL;

void rotacao_direita(ARVORE_AVL *arvore){
    ARVORE_AVL aux1, aux2;
    aux1 = (*arvore)->esq;
    aux2 = aux1->dir;
    (*arvore)->esq = aux2;
    aux1->dir = *arvore;
    if (!aux2)
        (*arvore)->alte = 0;
    else
        if (aux2->alte > aux2->altd)
            (*arvore)->alte = aux2->alte + 1;
        else
            (*arvore)->alte = aux2->altd + 1;
    if ((*arvore)->alte > (*arvore)->altd)
        aux1->altd = (*arvore)->alte + 1;
    else
        aux1->altd = (*arvore)->altd + 1;
    *arvore = aux1;
}

void rotacao_esquerda(ARVORE_AVL *arvore){
    ARVORE_AVL aux1, aux2;
    aux1 = (*arvore)->dir;
    aux2 = aux1->esq;
    (*arvore)->dir = aux2;
    aux1->esq = *arvore;
    if (!aux2)
        (*arvore)->altd = 0;
    else
        if (aux2->alte > aux2->altd)
            (*arvore)->altd = aux2->alte + 1;
        else
            (*arvore)->altd = aux2->altd + 1;
    if ((*arvore)->alte > (*arvore)->altd)
        aux1->altd = (*arvore)->alte + 1;
    else
        aux1->altd = (*arvore)->altd + 1;
}

void balanceamento(ARVORE_AVL *arvore){
    int FBpai, FBfilho;
    FBpai = (*arvore)->altd - (*arvore)->alte;
    if (FBpai == 2){
        FBfilho = (*arvore)->dir->altd - (*arvore)->dir->alte;
        if (FBfilho >= 0)
            rotacao_esquerda(arvore);
        else {
            rotacao_direita(&(*arvore)->dir);
            rotacao_esquerda(arvore);
        }
    } else {
        if (FBpai == -2){
            FBfilho = (*arvore)->esq->altd - (*arvore)->esq->alte;
            if (FBfilho <= 0)
                rotacao_direita(arvore);
            else {
                rotacao_esquerda(&(*arvore)->esq);
                rotacao_direita(arvore);
            }
        }
    }
}

// Após inserir, atualiza a altura e realiza o balanceamento da árvore
void inserir(ARVORE_AVL *arvore, int valor) {
    // Caso base: se a árvore (subárvore) for NULL, cria um novo nó com o valor fornecido
    if (*arvore == NULL) {
        *arvore = (NODO*)malloc(sizeof(NODO));  // Aloca memória para um novo nó
        (*arvore)->num = valor;  // Atribui o valor ao nó
        (*arvore)->esq = (*arvore)->dir = NULL;  // O novo nó não tem filhos (subárvores)
        (*arvore)->altd = (*arvore)->alte = 0;  // Inicializa as alturas dos filhos como 0
    } else {
        // Caso recursivo: insere o valor na subárvore esquerda se o valor for menor que o nó atual
        if (valor < (*arvore)->num) {
            inserir(&((*arvore)->esq), valor);  // Insere à esquerda
        // Caso recursivo: insere o valor na subárvore direita se o valor for maior que o nó atual
        } else if (valor > (*arvore)->num) {
            inserir(&((*arvore)->dir), valor);  // Insere à direita
        } else {
            return;  // Se o valor já existir, não faz nada
        }

        // Após a inserção, atualiza as alturas do nó
        if (!(*arvore)->esq)
            (*arvore)->alte = 0;
        else
            if ((*arvore)->esq->alte > (*arvore)->esq->altd)
                (*arvore)->alte = (*arvore)->esq->alte + 1;
            else
                (*arvore)->alte = (*arvore)->esq->altd + 1;
        if (!(*arvore)->dir)
            (*arvore)->altd = 0;
        else
            if ((*arvore)->dir->alte > (*arvore)->dir->altd)
                (*arvore)->altd = (*arvore)->dir->alte + 1;
            else
                (*arvore)->altd = (*arvore)->dir->altd + 1;

        // Realiza o balanceamento da árvore
        balanceamento(arvore);
    }
}

void remover(ARVORE_AVL* arvore, int valor) {
    // Caso base: Se a árvore estiver vazia, apenas retorna
    if (*arvore == NULL) {
        return; // Valor não encontrado, nada a fazer
    }

    // Passo 1: Encontrar o nó a ser removido
    if (valor < (*arvore)->num) {
        // Se o valor a ser removido for menor que o valor do nó atual,
        // busca recursivamente na subárvore esquerda
        remover(&((*arvore)->esq), valor); // Buscar à esquerda
    } else if (valor > (*arvore)->num) {
        // Se o valor a ser removido for maior que o valor do nó atual,
        // busca recursivamente na subárvore direita
        remover(&((*arvore)->dir), valor); // Buscar à direita
    } else {
        // O nó com o valor a ser removido foi encontrado

        // Caso 1: O nó tem no máximo um filho (nó folha ou com um único filho)
        if ((*arvore)->esq == NULL || (*arvore)->dir == NULL) {
            // 'temp' recebe o único filho (ou NULL se não houver filhos)
            ARVORE_AVL temp = ((*arvore)->esq) ? (*arvore)->esq : (*arvore)->dir;
            
            // Se o nó não tiver nenhum filho (nó folha)
            if (temp == NULL) {
                // Armazena temporariamente o nó a ser removido
                temp = *arvore;
                *arvore = NULL; // Define o ponteiro da árvore como NULL, removendo o nó
            } else {
                // Se o nó tem um único filho, copia o conteúdo do filho para o nó atual
                **arvore = *temp; // Copia o conteúdo do nó apontado por temp para o nó apontado por *arvore (modifica os dados do nó, mas não altera o ponteiro).
            }
            // Libera a memória do nó removido
            free(temp);

        } else {
            // Caso 3: O nó tem dois filhos
            // Encontra o sucessor in-order (menor valor da subárvore direita)
            ARVORE_AVL temp = (*arvore)->dir;// Isso daqui é preferencia ou convenção
            while(temp->esq) 
                temp = temp->esq; // Percorre até o nó mais à esquerda da subárvore direita

            // Substitui o valor do nó a ser removido pelo valor do sucessor
            (*arvore)->num = temp->num;

            // Remove o sucessor recursivamente (ele será um nó folha ou com um único filho)
            remover(&((*arvore)->dir), temp->num); // Remove o sucessor
        }
    }

    // Se a árvore ficou vazia após a remoção (somente no caso de remoção de nó folha)
    if (*arvore == NULL) return;

    // Passo 2: Atualizar a altura do nó atual
    atualizar_altura(*arvore);

    // Passo 3: Balancear a árvore
    // A função balanceamento ajusta o ponteiro 'arvore' conforme necessário
    // para garantir que as propriedades de balanceamento da árvore AVL sejam mantidas
    balanceamento(arvore);
}
