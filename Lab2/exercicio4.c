#include <stdio.h>

void analise(int a,int b, int c){
    if (a < b + c || b < a + c || c < a + b){
        printf("É um triângulo");
    } else{
        printf("Não é um triângulo");
    }
}

int main(){
    int a,b,c;
    printf("Digite o tamanho do primeiro lado do triângulo:");
    scanf("%d",&a);
    printf("Digite o tamanho do segundo lado do triângulo:");
    scanf("%d",&b);
    printf("Digite o tamanho do terceiro lado do triângulo:");
    scanf("%d",&c);
    analise(a,b,c);
    return 0;
}

