#include <stdio.h>

int main(){
    float hora;
    printf("Digite a hora do dia:");
    scanf("%f",&hora);
    float minutos = hora * 60;
    printf("O número de minutos que já passaram desde o começo do dia são de: %.2f\n",minutos);
    return 0;
}