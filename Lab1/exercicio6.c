#include <stdio.h>

int main(){
    int inteiro;
    printf("Digite um valor inteiro:");
    scanf("%d",&inteiro);
    if (inteiro % 5 == 0){
        printf("O número é múltiplo de 5\n");
    } else {
        printf("O número não é múltiplo de 5\n");
    }
    return 0;
}