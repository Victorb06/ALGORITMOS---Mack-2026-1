#include <stdio.h>

int getmax(int v[], int n){
    int max = v[0];

    for(int i = 1; i < n; i++){
        if(v[i] > max)
            max = v[i];
    }
    return max;
}

void bubblesort(int v[], int n, int exp){

    for(int i = 0; i < n - 1; i++){

        for(int j = 0; j < n - 1 - i; j++){

            int digito1 = (v[j] / exp) % 10;
            int digito2 = (v[j + 1] / exp) % 10;

            if(digito1 > digito2){

                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void radixsort(int v[], int n){

    int max = getmax(v, n);

    for(int exp = 1; max / exp > 0; exp *= 10){

        bubblesort(v, n, exp);
    }
}

int main(){

    int v[] = {329, 457, 657, 839, 436, 720, 355};

    int n = sizeof(v) / sizeof(v[0]);

    printf("Vetor Original:\n");

    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }

    printf("\n");

    radixsort(v, n);

    printf("Vetor Ordenado:\n");

    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }

    printf("\n");

    return 0;
}