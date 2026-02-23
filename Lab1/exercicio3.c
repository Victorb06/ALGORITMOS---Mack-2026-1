#include <stdio.h>

int main(){
    float nota1,nota2,nota3;
    printf("Nota 1:");
    scanf("%f",&nota1);
    printf("Nota 2:");
    scanf("%f",&nota2);
    printf("Nota 3:");
    scanf("%f",&nota3);
    float media = (nota1 + nota2 + nota3)/3;
    printf("A média entre as notas é de: %.2f\n",media);
    return 0;
}