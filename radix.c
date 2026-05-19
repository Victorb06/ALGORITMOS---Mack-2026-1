#include <stdio.h>

int getmax(int v[],int n){
    int max = v[0];

    for(int i = 1; i < n; i++){
        if(v[i] > max)
           max = v[i];
    }
    return max;
}

void countingsort(int v[],int n,int exp){
    int output[n];
    int count[10] = {0};

    for(int i = 0; i < n; i++){
        count[(v[i] / exp) % 10]++;
    }

    for(int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    for(int i = n - 1; i >= 0; i--){
        int index = (v[i] / exp) % 10;
        output[count[index] - 1] = v[i];
        count[index]--;
    }

    for(int i = 0; i < n; i++){
        v[i] = output[i];
    }
}

void radixsort(int v[],int n){
    int max = getmax(v,n);
    for(int exp = 1; max / exp > 0; exp *= 10){
        countingsort(v,n,exp);
    }
}

int main(){
    int v[]={329,457,657,839,436,720,355};
    int n = sizeof(v) / sizeof(v[0]);

    printf("Vetor Original:\n");
    for(int i = 0; i < n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");

    radixsort(v,n);

    printf("Vetor Ordenado:\n");
    for(int i = 0; i < n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    return 0;
}