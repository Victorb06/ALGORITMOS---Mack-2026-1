#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sortear() {
    return rand() % 100 + 1;
}

int advin(int palpite) {
    while (palpite < 1 || palpite > 100) {
        printf("Número inválido! Digite um número entre 1 e 100: ");
        scanf("%d", &palpite);
    }
    return palpite;
}

int verif(int palpite, int num) {
    if (palpite == num) {
        printf("Parabéns!!! Você acertou!\n");
        return 1;
    } 
    else if (palpite < num) {
        printf("Você chutou muito baixo!\n");
    } 
    else {
        printf("Você chutou muito alto!\n");
    }
    return 0;
}

int main() {
    int num, palpite;
    int tentativas = 0;
    int acertou = 0;

    srand(time(NULL)); 
    num = sortear();

    while (acertou == 0) {
        printf("Digite um número entre 1 e 100: ");
        scanf("%d", &palpite);

        palpite = advin(palpite);
        tentativas++;

        acertou = verif(palpite, num);
    }

    printf("Você precisou de %d tentativas.\n", tentativas);

    return 0;
}