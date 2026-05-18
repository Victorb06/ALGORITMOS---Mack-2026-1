#include <stdio.h>

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int vetor[], int tamanho, int raiz) {
    int maior = raiz;
    int esquerda = 2 * raiz + 1;
    int direita = 2 * raiz + 2;

    if (esquerda < tamanho && vetor[esquerda] > vetor[maior]) {
        maior = esquerda;
    }

    if (direita < tamanho && vetor[direita] > vetor[maior]) {
        maior = direita;
    }

    if (maior != raiz) {
        trocar(&vetor[raiz], &vetor[maior]);

        heapify(vetor, tamanho, maior);
    }
}

void heapsort(int vetor[], int tamanho) {

    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(vetor, tamanho, i);
    }

    for (int i = tamanho - 1; i > 0; i--) {

        trocar(&vetor[0], &vetor[i]);

        heapify(vetor, i, 0);
    }
}

int main() {

    int vetor[] = {2,3,4,1,6,5,10,8,9,7};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d",vetor[i]);
    }
    printf("\n");

    heapsort(vetor, tamanho);

    printf("Vetor ordenado:\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d",vetor[i]);
    }
    printf("\n");
    return 0;
}