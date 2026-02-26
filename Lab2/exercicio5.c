#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sortear(){
    return rand() % 100 + 1;
}

int advin(int palpite){
    do{
        if( palpite < 1 || palpite > 100){
        printf("Número inválido, entre com um número válido");
    }
    } while (palpite < 1 || palpite > 100);
}

int verif(int palpite,int num){
    if (palpite == num){
        printf("Parabéns!!! Você acertou!");
    } else if (palpite < num){
        printf("Você chutou muito baixo! O valor correto é %d\n",num);
    } else{
        printf("Você chutou muito alto! O valor correto é %d\n",num);
    }
}

int main(){
    int num;
    int palpite;
    num = sortear;
    printf("Digite um número entre 1 e 100:");
    scanf("%d",&num);
    advin(palpite);
    verif(palpite,num);
    return 0;
}