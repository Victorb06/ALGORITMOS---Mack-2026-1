#include <stdio.h>
#include <stdlib.h>

void merge(double v[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;

    double *temp = (double *)malloc((fim - inicio + 1) * sizeof(double));

    while (i <= meio && j <= fim) {
        if (v[i] < v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
        }
    }

    while (i <= meio) {
        temp[k++] = v[i++];
    }

    while (j <= fim) {
        temp[k++] = v[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = temp[k];
    }

    free(temp);
}

void mergeSort(double v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

int buscaBinaria(double v[], int inicio, int fim, double valor) {
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (v[meio] == valor) {
            return meio;
        }

        if (v[meio] < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

int existeSomaONLogN(double v[], int n, double x) {
    mergeSort(v, 0, n - 1);

    for (int i = 0; i < n; i++) {
        double procurado = x - v[i];

        int pos = buscaBinaria(v, i + 1, n - 1, procurado);

        if (pos != -1) {
            return 1;
        }
    }

    return 0;
}


//B
int existeSomaLinear(double v[], int n, double x) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda < direita) {
        double soma = v[esquerda] + v[direita];

        if (soma == x) {
            return 1;
        }

        if (soma < x) {
            esquerda++;
        } else {
            direita--;
        }
    }

    return 0;
}