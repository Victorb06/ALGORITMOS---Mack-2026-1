#include <stdio.h>

int main(){
    int numero1,numero2;
    printf("Entre com um número inteiro:");
    scanf("%d",&numero1);
    printf("Entre com mais  número inteiro:");
    scanf("%d",&numero2);
    int soma = numero1 + numero2;
    int sub = numero1 - numero2;
    int mult = numero1 * numero2;
    float div = numero1 / numero2;
    printf("Soma:%d\n",soma);
    printf("Subtração:%d\n",sub);
    printf("Multiplicação:%d\n",mult);
    printf("Divisão:%.2f\n",div);
    return 0;
}