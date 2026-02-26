#include <stdio.h>

int func(float media,int freq){
    if (freq < 75){
        printf("REPROVADO");
    }else if (freq >= 75 && media >= 7.5){
        printf("APROVADO");
    }else if (freq >= 75 && media < 7.5){
        printf("DE EXAME");
    }
}

int main(){
    float media;
    int freq;
    printf("Entre com a sua média:");
    scanf("%f",&media);
    printf("Entre com a sua porcentagem de frequência:");
    scanf("%d",&freq);
    func(media,freq);
    return 0;
}