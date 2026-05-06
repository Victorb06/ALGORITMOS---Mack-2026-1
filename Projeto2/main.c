/**
Sistema de Análise de Dados de Vendas
Projeto 2- Laboratório de Algoritmos e Programação II
Integrantes:
Enzo Yuri Domingues Ma
RA:10738664
Victor Esteves Gallo Birello
RA: 10737139
Willian Lima de Oliveira Pena
RA:10428678
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int ids[MAX];
int produtoids[MAX];
int quantidades[MAX];
float precos[MAX];
int produtosidscatalogo[MAX];
char descricoes[MAX][50];

int buscarprodutocatalogo(int idProduto, int nProdutos){
    for(int i = 0; i < nProdutos; i++){
        if (produtosidscatalogo[i] == idProduto){
            return i;
        }
    }
    return -1;
}

int carregarVendas (const char nomeArquivo[],int ids[],int produtoids[], int quantidades[], float precos[], int max){
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL){
        return -1;
    }
    int i = 0;
    while(i < max && fscanf(arq,"%d %d %d %f",&ids[i],&produtoids[i],&quantidades[i],&precos[i]) == 4){
        i++;
    }
    fclose(arq);
    return i;
}

int carregarProdutos(const char nomeArquivo[], int produtosids[], char descricoes[][50],int max){
    FILE *arq = fopen(nomeArquivo, "r");
    if( arq == NULL){
        return -1;
    }
    int i = 0;
    while(i < max && fscanf(arq, "%d %[^\n]", &produtosids[i], descricoes[i]) == 2){
        i++;
    }
    fclose(arq);
    return i;
}

int BuscaLinear(int ids[], int n, int idProcurado){
    for(int i = 0; i < n; i++){
        if (ids[i] == idProcurado){
            return i;
        }
    }
    return -1;
}

int BuscaBinaria(int ids[], int n, int idProcurado){
    int inicio = 0;
    int fim = n - 1; 

    while (inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if (ids[meio] == idProcurado){
            return meio;
        } else if (ids[meio] < idProcurado){
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
}

void trocarDados(int i, int j,
                 int ids[],
                 int produtoIds[],
                 int quantidades[],
                 float precos[]) {

    int tempInt;
    float tempFloat;

    tempInt = ids[i];
    ids[i] = ids[j];
    ids[j] = tempInt;

    tempInt = produtoIds[i];
    produtoIds[i] = produtoIds[j];
    produtoIds[j] = tempInt;

    tempInt = quantidades[i];
    quantidades[i] = quantidades[j];
    quantidades[j] = tempInt;

    tempFloat = precos[i];
    precos[i] = precos[j];
    precos[j] = tempFloat;
}


void bubbleSortVendaPorId(int ids[],
                          int produtoIds[],
                          int quantidades[],
                          float precos[],
                          int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (ids[j] > ids[j + 1]) {

                trocarDados(j, j + 1,
                            ids,
                            produtoIds,
                            quantidades,
                            precos);
            }
        }
    }
}

void insertionSortVendaPorId(int ids[],
                             int produtoIds[],
                             int quantidades[],
                             float precos[],
                             int n) {

    for (int i = 1; i < n; i++) {

        int idAtual = ids[i];
        int produtoAtual = produtoIds[i];
        int qtdAtual = quantidades[i];
        float precoAtual = precos[i];

        int j = i - 1;

        while (j >= 0 && ids[j] > idAtual) {

            ids[j + 1] = ids[j];
            produtoIds[j + 1] = produtoIds[j];
            quantidades[j + 1] = quantidades[j];
            precos[j + 1] = precos[j];

            j--;
        }

        ids[j + 1] = idAtual;
        produtoIds[j + 1] = produtoAtual;
        quantidades[j + 1] = qtdAtual;
        precos[j + 1] = precoAtual;
    }
}

void selectionSortPorId(int ids[],
                        int produtoIds[],
                        int quantidades[],
                        float precos[],
                        int n) {

    for (int i = 0; i < n - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < n; j++) {

            if (ids[j] < ids[menor]) {
                menor = j;
            }
        }

        trocarDados(i, menor,
                    ids,
                    produtoIds,
                    quantidades,
                    precos);
    }
}


int particionar(int ids[],
                int produtoIds[],
                int quantidades[],
                float precos[],
                int inicio,
                int fim) {

    int pivo = ids[fim];

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {

        if (ids[j] < pivo) {

            i++;

            trocarDados(i, j,
                        ids,
                        produtoIds,
                        quantidades,
                        precos);
        }
    }

    trocarDados(i + 1, fim,
                ids,
                produtoIds,
                quantidades,
                precos);

    return i + 1;
}

void quickSortPorId(int ids[],
                    int produtoIds[],
                    int quantidades[],
                    float precos[],
                    int inicio,
                    int fim) {

    if (inicio < fim) {

        int pivo = particionar(ids,
                               produtoIds,
                               quantidades,
                               precos,
                               inicio,
                               fim);

        quickSortPorId(ids,
                       produtoIds,
                       quantidades,
                       precos,
                       inicio,
                       pivo - 1);

        quickSortPorId(ids,
                       produtoIds,
                       quantidades,
                       precos,
                       pivo + 1,
                       fim);
    }
}

void merge(int ids[],
           int produtoIds[],
           int quantidades[],
           float precos[],
           int inicio,
           int meio,
           int fim) {

    int tam = fim - inicio + 1;

    int tempIds[MAX];
    int tempProdutos[MAX];
    int tempQtd[MAX];
    float tempPrecos[MAX];

    int i = inicio;
    int j = meio + 1;
    int k = 0;

    while (i <= meio && j <= fim) {

        if (ids[i] < ids[j]) {

            tempIds[k] = ids[i];
            tempProdutos[k] = produtoIds[i];
            tempQtd[k] = quantidades[i];
            tempPrecos[k] = precos[i];

            i++;
        }
        else {

            tempIds[k] = ids[j];
            tempProdutos[k] = produtoIds[j];
            tempQtd[k] = quantidades[j];
            tempPrecos[k] = precos[j];

            j++;
        }

        k++;
    }

    while (i <= meio) {

        tempIds[k] = ids[i];
        tempProdutos[k] = produtoIds[i];
        tempQtd[k] = quantidades[i];
        tempPrecos[k] = precos[i];

        i++;
        k++;
    }

    while (j <= fim) {

        tempIds[k] = ids[j];
        tempProdutos[k] = produtoIds[j];
        tempQtd[k] = quantidades[j];
        tempPrecos[k] = precos[j];

        j++;
        k++;
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {

        ids[i] = tempIds[k];
        produtoIds[i] = tempProdutos[k];
        quantidades[i] = tempQtd[k];
        precos[i] = tempPrecos[k];
    }
}

void mergeSortPorId(int ids[],
                    int produtoIds[],
                    int quantidades[],
                    float precos[],
                    int inicio,
                    int fim) {

    if (inicio < fim) {

        int meio = (inicio + fim) / 2;

        mergeSortPorId(ids,
                       produtoIds,
                       quantidades,
                       precos,
                       inicio,
                       meio);

        mergeSortPorId(ids,
                       produtoIds,
                       quantidades,
                       precos,
                       meio + 1,
                       fim);

        merge(ids,
              produtoIds,
              quantidades,
              precos,
              inicio,
              meio,
              fim);
    }
}

float calcularFaturamentoTotal(int quantidades[],
                               float precos[],
                               int n) {

    float total = 0;

    for (int i = 0; i < n; i++) {

        total += quantidades[i] * precos[i];
    }

    return total;
}

int encontrarProdutoMaisVendido(int produtoIds[],
                                int quantidades[],
                                int n) {

    int maiorQuantidade = 0;
    int produtoMaisVendido = produtoIds[0];

    for (int i = 0; i < n; i++) {

        int soma = 0;

        for (int j = 0; j < n; j++) {

            if (produtoIds[i] == produtoIds[j]) {
                soma += quantidades[j];
            }
        }

        if (soma > maiorQuantidade ||
           (soma == maiorQuantidade &&
            produtoIds[i] < produtoMaisVendido)) {

            maiorQuantidade = soma;
            produtoMaisVendido = produtoIds[i];
        }
    }

    return produtoMaisVendido;
}


void mostrarVendas(int nVendas, int nProdutos) {

    printf("\nVendas ordenadas por ID:\n\n");

    printf("ID Venda | Produto | Descricao              | Quantidade | Preco Unitario | Total\n");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < nVendas; i++) {

        int posProduto = buscarProdutoCatalogo(produtoIds[i], nProdutos);

        float total = quantidades[i] * precos[i];

        printf("%-9d| %-9d| %-23s| %-11d| %-16.2f| %.2f\n",
               ids[i],
               produtoIds[i],
               descricoes[posProduto],
               quantidades[i],
               precos[i],
               total);
    }
}

int main() {

    int nVendas;
    int nProdutos;

    int ordenado = 0;

    nVendas = carregarVendas("vendas.txt",
                             ids,
                             produtoIds,
                             quantidades,
                             precos,
                             MAX);

    if (nVendas == -1) {

        printf("Erro ao abrir o arquivo vendas.txt.\n");
        printf("Encerrando o programa.\n");

        return 1;
    }

    nProdutos = carregarProdutos("produtos.csv",
                                 produtoIdsCatalogo,
                                 descricoes,
                                 MAX);

    if (nProdutos == -1) {

        printf("Erro ao abrir o arquivo produtos.csv.\n");
        printf("Encerrando o programa.\n");

        return 1;
    }

    int opcao;

    do {

        printf("\n===== SISTEMA DE ANALISE DE VENDAS =====\n\n");

        printf("1. Mostrar vendas ordenadas por ID\n");
        printf("2. Buscar venda por ID\n");
        printf("3. Calcular faturamento total\n");
        printf("4. Identificar produto mais vendido\n");
        printf("5. Sair da aplicacao\n\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        if (opcao == 1) {

            if (!ordenado) {

                int algoritmo;

                printf("\nEscolha o algoritmo de ordenacao:\n\n");

                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("4. Quick Sort\n");
                printf("5. Merge Sort\n\n");

                printf("Opcao: ");
                scanf("%d", &algoritmo);

                switch (algoritmo) {

                    case 1:
                        bubbleSortVendaPorId(ids,
                                             produtoIds,
                                             quantidades,
                                             precos,
                                             nVendas);
                        break;

                    case 2:
                        insertionSortVendaPorId(ids,
                                                produtoIds,
                                                quantidades,
                                                precos,
                                                nVendas);
                        break;

                    case 3:
                        selectionSortPorId(ids,
                                           produtoIds,
                                           quantidades,
                                           precos,
                                           nVendas);
                        break;

                    case 4:
                        quickSortPorId(ids,
                                       produtoIds,
                                       quantidades,
                                       precos,
                                       0,
                                       nVendas - 1);
                        break;

                    case 5:
                        mergeSortPorId(ids,
                                       produtoIds,
                                       quantidades,
                                       precos,
                                       0,
                                       nVendas - 1);
                        break;

                    default:
                        printf("Opcao invalida.\n");
                        continue;
                }

                ordenado = 1;
            }

            mostrarVendas(nVendas, nProdutos);
        }


        else if (opcao == 2) {

            int idBusca;
            int algoritmoBusca;

            printf("\nDigite o ID da venda: ");
            scanf("%d", &idBusca);

            printf("\nEscolha o algoritmo de busca:\n\n");

            printf("1. Busca linear\n");
            printf("2. Busca binaria\n\n");

            printf("Opcao: ");
            scanf("%d", &algoritmoBusca);

            int posicao = -1;

            if (algoritmoBusca == 1) {

                posicao = buscaLinear(ids,
                                      nVendas,
                                      idBusca);
            }

            else if (algoritmoBusca == 2) {

                if (!ordenado) {

                    quickSortPorId(ids,
                                   produtoIds,
                                   quantidades,
                                   precos,
                                   0,
                                   nVendas - 1);

                    ordenado = 1;
                }

                posicao = buscaBinaria(ids,
                                       nVendas,
                                       idBusca);
            }

            else {

                printf("Opcao invalida.\n");
                continue;
            }

            if (posicao != -1) {

                int posProduto =
                    buscarProdutoCatalogo(produtoIds[posicao],
                                          nProdutos);

                printf("\nVenda encontrada:\n\n");

                printf("ID Venda: %d\n",
                       ids[posicao]);

                printf("Produto: %d\n",
                       produtoIds[posicao]);

                printf("Descricao: %s\n",
                       descricoes[posProduto]);

                printf("Quantidade: %d\n",
                       quantidades[posicao]);

                printf("Preco unitario: %.2f\n",
                       precos[posicao]);

                printf("Total da venda: %.2f\n",
                       quantidades[posicao] *
                       precos[posicao]);
            }

            else {

                printf("\nVenda nao encontrada.\n");
            }
        }


        else if (opcao == 3) {

            float faturamento =
                calcularFaturamentoTotal(quantidades,
                                         precos,
                                         nVendas);

            printf("\nFaturamento total: R$ %.2f\n",
                   faturamento);
        }


        else if (opcao == 4) {

            int produtoMaisVendido =
                encontrarProdutoMaisVendido(produtoIds,
                                            quantidades,
                                            nVendas);

            int total = 0;

            for (int i = 0; i < nVendas; i++) {

                if (produtoIds[i] == produtoMaisVendido) {

                    total += quantidades[i];
                }
            }

            int posProduto =
                buscarProdutoCatalogo(produtoMaisVendido,
                                      nProdutos);

            printf("\nProduto mais vendido:\n\n");

            printf("Produto: %d\n",
                   produtoMaisVendido);

            printf("Descricao: %s\n",
                   descricoes[posProduto]);

            printf("Quantidade total vendida: %d\n",
                   total);
        }
        else if (opcao != 5) {

            printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5);

    printf("\nEncerrando o programa.\n");

    return 0;
}