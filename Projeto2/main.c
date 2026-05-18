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
#include <stdbool.h>

#define MAX 1000

//Trocar os dados de duas posições de arrays paralelos 
void trocarDados(int ids[], int pIds[], int quants[], float precos[], int i, int j) {
    int tId = ids[i]; ids[i] = ids[j]; ids[j] = tId; //Variavel temporaria para armazenar o ID e trocar entre as posições
    int tPId = pIds[i]; pIds[i] = pIds[j]; pIds[j] = tPId; //Variavel temporaria para para o produto ID e troca-los
    int tQ = quants[i]; quants[i] = quants[j]; quants[j] = tQ; //Variavel temporaria para quantidade e troca-las
    float tPr = precos[i]; precos[i] = precos[j]; precos[j] = tPr; //Variavel temporaria para o preco e troca-los
}

//Lê o arquivo txt 
int carregarVendas(const char nome[], int ids[], int pIds[], int quants[], float precos[], int max) {
    FILE *f = fopen(nome, "r"); //Abre o arquivo
    if (!f) return -1; //verifica se houve algum erro na hora de abrir 
    int i = 0;
    while (i < max && fscanf(f, "%d %d %d %f", &ids[i], &pIds[i], &quants[i], &precos[i]) == 4) i++; // Vai ler o arquvio até os valores estarem correctos 
    fclose(f);
    return i; //Retorna o número de registradores que foram carregados
}

//Carrega os produtos do arquivo csv
int carregarProdutos(const char nome[], int pIdsC[], char descs[][50], int max) {
    FILE *f = fopen(nome, "r"); //Abre o arquivo
    if (!f) return -1; //verifica se houve algum erro na hora de abrir
    int i = 0;
    while (i < max && fscanf(f, "%d;%49[^\n]", &pIdsC[i], descs[i]) == 2) i++; //Lê ate 49 caracteres ou até enter
    fclose(f);
    return i; // Retorna a quantidade carregada 
}

//Percorre todo o array até procurar om ID desejado 
int buscaLinear(int ids[], int n, int id) {
    for (int i = 0; i < n; i++) //Percorre todo o vetor
    if (ids[i] == id) return i; //Verifica se encontrou e retorna
    return -1; //Retorna -1 caso não tenha encontrado
}

//Procuar o ID desejado de forma mais rápida porem funciona apenas com o vetor já ordenado 
int buscaBinaria(int ids[], int n, int id) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2; //Calcula a posição do meio
        if (ids[meio] == id) return meio; //Verifica se encontrou 
        if (ids[meio] > id) fim = meio - 1; //Se valor do meio for maior está na parte da esquerda
        else ini = meio + 1; // Se o valor for menor está na parte da direita 
    }
    return -1; // Não encontrou
}

//Compara os elementos vizinhos e os maiores valores vão sendo jogados para o final
void bubbleSortVendaPorId(int ids[], int pIds[], int quants[], float precos[], int n) {
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            if (ids[j] > ids[j + 1]){
                trocarDados(ids, pIds, quants, precos, j, j + 1); // Se estiver fora de ordem troca
            }
        }
    }
}

//Procuar o menor elemento e o coloca na posição correcta
void selectionSortPorId(int ids[], int pIds[], int quants[], float precos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i; //Assume o menor como atual 
        for (int j = i + 1; j < n; j++){ //Procura um menor no restante do vetor
            if (ids[j] < ids[min]){ 
                min = j;
            }
        }
        if (min != i){ //Se encontrou um menor troca
           trocarDados(ids, pIds, quants, precos, i, min);
        }
    }
}

//Insere o elemento na posição certa dentro da parte já ordenada do vetor
void insertionSortVendaPorId(int ids[], int pIds[], int quants[], float precos[], int n) {
    for (int i = 1; i < n; i++) { //começa a partir do segundo elemento
        int idKey = ids[i], pidKey = pIds[i], qKey = quants[i]; float prKey = precos[i]; //guarda os valores atuais
        int j = i - 1; //Compara com os anteriores
        while (j >= 0 && ids[j] > idKey) {
            ids[j+1] = ids[j]; pIds[j+1] = pIds[j]; quants[j+1] = quants[j]; precos[j+1] = precos[j]; //Move os elementos para frente
            j--;
        }
        ids[j+1] = idKey; pIds[j+1] = pidKey; quants[j+1] = qKey; precos[j+1] = prKey; //Insere eles na posição certa
    }
}

//
void quickSortPorId(int ids[], int pIds[], int quants[], float precos[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = ids[fim], i = inicio - 1;
        for (int j = inicio; j < fim; j++) {
            if (ids[j] <= pivo) { i++; trocarDados(ids, pIds, quants, precos, i, j); }
        }
        trocarDados(ids, pIds, quants, precos, i + 1, fim);
        int p = i + 1;
        quickSortPorId(ids, pIds, quants, precos, inicio, p - 1);
        quickSortPorId(ids, pIds, quants, precos, p + 1, fim);
    }
}

void merge(int ids[], int pIds[], int quants[], float precos[],int inicio, int meio, int fim) {
    int tam1 = meio - inicio + 1;
    int tam2 = fim - meio;

    int idsEsq[tam1], pIdsEsq[tam1], quantsEsq[tam1];
    float precosEsq[tam1];

    int idsDir[tam2], pIdsDir[tam2], quantsDir[tam2];
    float precosDir[tam2];

    for (int i = 0; i < tam1; i++) {
        idsEsq[i] = ids[inicio + i];
        pIdsEsq[i] = pIds[inicio + i];
        quantsEsq[i] = quants[inicio + i];
        precosEsq[i] = precos[inicio + i];
    }

    for (int i = 0; i < tam2; i++) {
        idsDir[i] = ids[meio + 1 + i];
        pIdsDir[i] = pIds[meio + 1 + i];
        quantsDir[i] = quants[meio + 1 + i];
        precosDir[i] = precos[meio + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = inicio;

    while (i < tam1 && j < tam2) {

        if (idsEsq[i] <= idsDir[j]) {
            ids[k] = idsEsq[i];
            pIds[k] = pIdsEsq[i];
            quants[k] = quantsEsq[i];
            precos[k] = precosEsq[i];
            i++;
        } else {
            ids[k] = idsDir[j];
            pIds[k] = pIdsDir[j];
            quants[k] = quantsDir[j];
            precos[k] = precosDir[j];
            j++;
        }

        k++;
    }

    while (i < tam1) {
        ids[k] = idsEsq[i];
        pIds[k] = pIdsEsq[i];
        quants[k] = quantsEsq[i];
        precos[k] = precosEsq[i];

        i++;
        k++;
    }

    while (j < tam2) {
        ids[k] = idsDir[j];
        pIds[k] = pIdsDir[j];
        quants[k] = quantsDir[j];
        precos[k] = precosDir[j];

        j++;
        k++;
    }
}

void mergeSortPorId(int ids[], int pIds[], int quants[], float precos[], int inicio, int fim) {
     if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSortPorId(ids, pIds, quants, precos, inicio, meio);

        mergeSortPorId(ids, pIds, quants, precos, meio + 1, fim);

        merge(ids, pIds, quants, precos, inicio, meio, fim);
    }
}

float calcularFaturamentoTotal(int quants[], float prs[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) total += quants[i] * prs[i];
    return total;
}

int encontrarProdutoMaisVendido(int pIds[], int quants[], int n) {
    int maxQ = -1, idMaisVendido = -1;
    for (int i = 0; i < n; i++) {
        int soma = 0;
        for (int j = 0; j < n; j++) if (pIds[j] == pIds[i]) soma += quants[j];
        if (soma > maxQ || (soma == maxQ && pIds[i] < idMaisVendido)) {
            maxQ = soma; idMaisVendido = pIds[i];
        }
    }
    return idMaisVendido;
}

int main() {
    int ids[MAX], produtoIds[MAX], quantidades[MAX];
    float precos[MAX];
    int pIdsCatalogo[MAX];
    char descricoes[MAX][50];

    int nVendas = carregarVendas("vendas.txt", ids, produtoIds, quantidades, precos, MAX);
    int nProdutos = carregarProdutos("produtos.csv", pIdsCatalogo, descricoes, MAX);

    if (nVendas == -1 || nProdutos == -1) {
        if (nVendas == -1) printf("Erro ao abrir o arquivo vendas.txt.\n");
        if (nProdutos == -1) printf("Erro ao abrir o arquivo produtos.csv.\n");
        printf("Encerrando o programa.\n");
        return 1;
    }

    int opcao, algOrd = 0, algBusca, idBusca, idx, idMaisVendido;
    bool ordenado = false;

    do {
        printf("\n===== SISTEMA DE ANALISE DE VENDAS =====\n");
        printf("1. Mostrar vendas ordenadas por ID\n");
        printf("2. Buscar venda por ID\n");
        printf("3. Calcular faturamento total\n");
        printf("4. Identificar produto mais vendido\n");
        printf("5. Sair da aplicacao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!ordenado) {
                    printf("Escolha o algoritmo de ordenacao:\n1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n5. Merge Sort\nOpcao: ");
                    scanf("%d", &algOrd);
                    if (algOrd == 1) bubbleSortVendaPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 2) insertionSortVendaPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 3) selectionSortPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 4) quickSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1);
                    else if (algOrd == 5) mergeSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1);
                    ordenado = true;
                }
                printf("\nVendas ordenadas por ID:\nID Venda | Produto | Descricao | Qtd | Preco | Total\n");
                for (int i = 0; i < nVendas; i++) {
                    int pIdx = -1;
                    for(int j=0; j<nProdutos; j++) if(pIdsCatalogo[j] == produtoIds[i]) pIdx = j;
                    printf("%-8d | %-7d | %-15s | %-3d | %-5.2f | %.2f\n", ids[i], produtoIds[i], (pIdx != -1 ? descricoes[pIdx] : "N/A"), quantidades[i], precos[i], quantidades[i] * precos[i]);
                }
                break;
            case 2:
                printf("Digite o ID da venda: ");
                scanf("%d", &idBusca);
                printf("Escolha o algoritmo (1. Linear, 2. Binaria): ");
                scanf("%d", &algBusca);
                if (algBusca == 2) {
                    if (!ordenado) { quickSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1); ordenado = true; }
                    idx = buscaBinaria(ids, nVendas, idBusca);
                } else idx = buscaLinear(ids, nVendas, idBusca);
                
                if (idx != -1) {
                    int pIdx = -1;
                    for(int j=0; j<nProdutos; j++) if(pIdsCatalogo[j] == produtoIds[idx]) pIdx = j;
                    printf("\nVenda encontrada:\n");
                    printf("ID Venda: %d\n", ids[idx]);
                    printf("Produto: %d\n", produtoIds[idx]);
                    printf("Descricao: %s\n", (pIdx != -1 ? descricoes[pIdx] : "N/A"));
                    printf("Quantidade: %d\n", quantidades[idx]);
                    printf("Preco unitario: %.2f\n", precos[idx]);
                    printf("Total da venda: %.2f\n", quantidades[idx] * precos[idx]);
                } else printf("Venda nao encontrada.\n");
                break;
            case 3:
                printf("Faturamento total: R$ %.2f\n", calcularFaturamentoTotal(quantidades, precos, nVendas));
                break;
            case 4: {
                idMaisVendido = encontrarProdutoMaisVendido(produtoIds, quantidades, nVendas);
                int pIdx = -1;
                for(int j=0; j<nProdutos; j++) if(pIdsCatalogo[j] == idMaisVendido) pIdx = j;
                int totalQ = 0;
                for(int i=0; i<nVendas; i++) if(produtoIds[i] == idMaisVendido) totalQ += quantidades[i];
                printf("\nProduto mais vendido:\nID: %d\nDescricao: %s\nTotal Vendido: %d\n", idMaisVendido, (pIdx != -1 ? descricoes[pIdx] : "N/A"), totalQ);
                break;
            }
            case 5: printf("Encerrando o programa.\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
    return 0;
}