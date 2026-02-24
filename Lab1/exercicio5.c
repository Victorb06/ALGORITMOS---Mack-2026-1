#include <stdio.h>

int main(){
    float salariomin,dolar;
    printf("Digite o valor do salario mínimo:");
    scanf("%f",&salariomin);
    printf("Digite o valor do dolar atualmente:");
    scanf("%f",&dolar);
    float totalreal = 10000000 * dolar;
    float casa = 150 * salariomin;
    int quantidade = totalreal/casa;
    printf("A quantidade de casas que podem ser construidas é de: %d\n",quantidade);
    return 0;
}