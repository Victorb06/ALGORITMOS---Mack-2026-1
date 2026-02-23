#include <stdio.h>

int main(){
    float largura,comprimento;
    printf("Largura do terreno:");
    scanf("%f",&largura);
    printf("Comprimento do terreno:");
    scanf("%f",&comprimento);
    float area = largura * comprimento;
    printf("A área do terreno é de: %.2f\n",area);
    return 0;
}
