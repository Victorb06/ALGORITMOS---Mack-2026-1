#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sortear() {
    return rand() % 100 + 1;
}

int validar(int palpite) {
    while (palpite < 1 || palpite > 100) {
        printf("Número inválido! Digite um número entre 1 e 100: ");
        scanf("%d", &palpite);
    }
    return palpite;
}

int verificar(int palpite, int numero) {
    if (palpite == numero) {
        printf("Parabéns!!! Você acertou!\n");
        return 1;
    }
    else if (palpite < numero) {
        printf("Você chutou muito baixo!\n");
    }
    else {
        printf("Você chutou muito alto!\n");
    }
    return 0;
}

int main() {
    int numero, palpite;
    int tentativas = 0;
    int acertou = 0;

    srand(time(NULL));
    numero = sortear();

    while (tentativas < 5 && acertou == 0) {

        printf("Tentativa %d de 5\n", tentativas + 1);
        printf("Digite um número entre 1 e 100: ");
        scanf("%d", &palpite);

        palpite = validar(palpite);
        tentativas++;

        acertou = verificar(palpite, numero);
    }

    if (acertou == 0) {
        printf("Você excedeu o número máximo de tentativas.\n");
        printf("O número sorteado era: %d\n", numero);
    }

    return 0;
}