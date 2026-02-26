#include <stdio.h>

int main(){
    float peso,alt;
    printf("Peso(em quilogramas):");
    scanf("%f",&peso);
    printf("Altura(em metros):");
    scanf("%f",&alt);
    float imc = peso / (alt * alt);
    printf("O IMC de uma pessoa com peso %.2f kg e altura %.2f m é igual a: %.2f\n",peso,alt,imc);
    return 0; 
}