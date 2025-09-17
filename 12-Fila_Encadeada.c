#include <stdio.h>
int main()
{
    int valorUm, valorDois;
    printf("Digite um valor inteiro: ");
    scanf("%d", &valorUm);
    printf("Digite outro valor inteiro: ");
    scanf("%d", &valorDois);
    printf("%d+%d=%d\n", valorUm, valorDois, valorUm+valorDois);
}