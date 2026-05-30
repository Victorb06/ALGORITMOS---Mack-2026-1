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
    while (i < max && fscanf(f, "%d; %49[^\n]", &pIdsC[i], descs[i]) == 2) i++; //Lê ate 49 caracteres ou até enter
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
        if (ids[meio] == id){
            return meio; //Verifica se encontrou 
        }
        if (ids[meio] > id) {
            fim = meio - 1; //Se valor do meio for maior está na parte da esquerda

        }else {
            ini = meio + 1; // Se o valor for menor está na parte da direita 
        }
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

//Separa em pivôs e se repete com recursão
void quickSortPorId(int ids[], int pIds[], int quants[], float precos[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = ids[fim], i = inicio - 1; //Escolhe o último elemento como pivô e i controla a posição dos elementos menores
        for (int j = inicio; j < fim; j++) {
            if (ids[j] <= pivo) { //Se o elemento for menor ou igual ao pivô ele fica antes do pivô
                i++; 
                trocarDados(ids, pIds, quants, precos, i, j); // troca os elementos para manter os menores antes do pivô
            }
        }
        trocarDados(ids, pIds, quants, precos, i + 1, fim);//Coloca o pivô na posição certa
        int p = i + 1; // posição final do pivô
        quickSortPorId(ids, pIds, quants, precos, inicio, p - 1); //Ordena a parte esquerda
        quickSortPorId(ids, pIds, quants, precos, p + 1, fim); //Ordena a parte direita 
    }
}

//Junta duas partes já ordenadas do vetor
void merge(int ids[], int pIds[], int quants[], float precos[],int inicio, int meio, int fim) {
    //Calcula o tamanho das duas metades
    int tam1 = meio - inicio + 1;
    int tam2 = fim - meio;

    //Vetores da parte esquerda
    int idsEsq[tam1], pIdsEsq[tam1], quantsEsq[tam1];
    float precosEsq[tam1];

    //Vetores da parte direita
    int idsDir[tam2], pIdsDir[tam2], quantsDir[tam2];
    float precosDir[tam2];

    //Copia os dados da esquerda para os vetores
    for (int i = 0; i < tam1; i++) {
        idsEsq[i] = ids[inicio + i];
        pIdsEsq[i] = pIds[inicio + i];
        quantsEsq[i] = quants[inicio + i];
        precosEsq[i] = precos[inicio + i];
    }

    //Copia os dados da parte direita para os vetores
    for (int i = 0; i < tam2; i++) {
        idsDir[i] = ids[meio + 1 + i];
        pIdsDir[i] = pIds[meio + 1 + i];
        quantsDir[i] = quants[meio + 1 + i];
        precosDir[i] = precos[meio + 1 + i];
    }

    int i = 0; //metade esquerda
    int j = 0; //metade direita
    int k = inicio; //vetor original

    while (i < tam1 && j < tam2) { //Compara os menores elementos de cada metade

        //Se o elemento da esquerda for menor ele volta primeiro para o vetor original
        if (idsEsq[i] <= idsDir[j]) {
            ids[k] = idsEsq[i];
            pIds[k] = pIdsEsq[i];
            quants[k] = quantsEsq[i];
            precos[k] = precosEsq[i];
            i++;
            //Se o elemento da direita for menor ele volta primeiro para o vetor original
        } else {
            ids[k] = idsDir[j];
            pIds[k] = pIdsDir[j];
            quants[k] = quantsDir[j];
            precos[k] = precosDir[j];
            j++;
        }

        k++;
    }

    //Se sobraram elementos na esquerda eles são copiados para o vetor original
    while (i < tam1) {
        ids[k] = idsEsq[i];
        pIds[k] = pIdsEsq[i];
        quants[k] = quantsEsq[i];
        precos[k] = precosEsq[i];

        i++;
        k++;
    }
    
    //Se sobraram elementos na direita eles são copiados para o vetor original
    while (j < tam2) {
        ids[k] = idsDir[j];
        pIds[k] = pIdsDir[j];
        quants[k] = quantsDir[j];
        precos[k] = precosDir[j];

        j++;
        k++;
    }
}

//Divide o vetor em partes menores até apenas sobrar um elemento e depois junta novamente usando a função merge
void mergeSortPorId(int ids[], int pIds[], int quants[], float precos[], int inicio, int fim) {
     if (inicio < fim) { //Divide enquanto ainda houver mais de um elemento
        int meio = (inicio + fim) / 2; //Calcula o meio do vetor

        mergeSortPorId(ids, pIds, quants, precos, inicio, meio); //Ordena a parte da esquerda

        mergeSortPorId(ids, pIds, quants, precos, meio + 1, fim); //Ordena a parte da direita

        merge(ids, pIds, quants, precos, inicio, meio, fim); //Junta as duas partes ordenadas
    }
}

//Calcula o faturamento total das vendas
float calcularFaturamentoTotal(int quants[], float prs[], int n) {
    float total = 0; //variavel acumuladora
    for (int i = 0; i < n; i++) { //percorre todas as vendas
        total += quants[i] * prs[i];
    }
    return total; //retorna o faturamento total
}

//Encontra o produto com a maior qunatidade total de vendas
int encontrarProdutoMaisVendido(int pIds[], int quants[], int n) {
    int maxQ = -1, idMaisVendido = -1; //Guarda a maior quantidade encontrada e o ID correspondente
    for (int i = 0; i < n; i++) {
        int soma = 0;
        for (int j = 0; j < n; j++) {
            if (pIds[j] == pIds[i]){ // se o ID do produto for igual soma sua quantidade vendida
                soma += quants[j];
            }
        }
        if (soma > maxQ || (soma == maxQ && pIds[i] < idMaisVendido)) { //Atualiza o mais vendido se encontrou maior quantidade ou se houve empate e o ID atual é menor
            maxQ = soma; idMaisVendido = pIds[i];
        }
    }
    return idMaisVendido; //retorna o ID do produto mais vendido
}

//Função principal
int main() {
    //Arrays paralelos
    int ids[MAX], produtoIds[MAX], quantidades[MAX];
    float precos[MAX];
    //Arrays para armazenar os dados dos produtos
    int pIdsCatalogo[MAX];
    char descricoes[MAX][50];

    int nVendas = carregarVendas("vendas.txt", ids, produtoIds, quantidades, precos, MAX); //Carrega os dados do arquivo txt
    int nProdutos = carregarProdutos("produtos.csv", pIdsCatalogo, descricoes, MAX); //Carrega os produtos do arquivo csv

    if (nVendas == -1 || nProdutos == -1) { //Verifica se houve algum erro ao abrir algum dos arquivos
        if (nVendas == -1) printf("Erro ao abrir o arquivo vendas.txt.\n"); //Verifica se foi especificadamente no txt
        if (nProdutos == -1) printf("Erro ao abrir o arquivo produtos.csv.\n"); //Verifica se foi especificadamente no csv
        printf("Encerrando o programa.\n");
        return 1; //Encerra o programa
    }

    int opcao, algOrd = 0, algBusca, idBusca, idx, idMaisVendido; //Variaveis de controle do sistema (opção,algoritmo de ordenação,busca,ID,indice e mais vendido)
    bool ordenado = false; //Verifica se o vetor já foi ordenado

    //Loop Principal
    do {
        printf("\n===== SISTEMA DE ANALISE DE VENDAS =====\n");
        printf("1. Mostrar vendas ordenadas por ID\n");
        printf("2. Buscar venda por ID\n");
        printf("3. Calcular faturamento total\n");
        printf("4. Identificar produto mais vendido\n");
        printf("5. Sair da aplicação\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!ordenado) { //Se ainda não estiver ordenado pede para o usuário escolher um algoritmo de ordenação
                    printf("Escolha o algoritmo de ordenacao:\n1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n4. Quick Sort\n5. Merge Sort\nOpcao: ");
                    scanf("%d", &algOrd);
                    //Executa o algoritmo escolhido pelo usuário
                    if (algOrd == 1) bubbleSortVendaPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 2) insertionSortVendaPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 3) selectionSortPorId(ids, produtoIds, quantidades, precos, nVendas);
                    else if (algOrd == 4) quickSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1);
                    else if (algOrd == 5) mergeSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1);
                    else{
                        printf("Opção Inválida\n");//Caso o usuário digite algo diferente do que é pedido
                        break;
                    }
                    ordenado = true;
                }
                
                printf("\nVendas ordenadas por ID:\nID Venda | Produto | Descricao       | Qtd | Preço | Total\n"); //exibe o cabeçalho da tabela
                for (int i = 0; i < nVendas; i++) { // Percorre todas as vendas
                    int pIdx = -1; //Guarda a posição da descrição do produto
                    for(int j=0; j<nProdutos; j++){ //Procura o prdouto atual no catalogo de produtos
                     if(pIdsCatalogo[j] == produtoIds[i]){
                         pIdx = j; //Se encontrou o mesmo ID salva a sua posição
                         break;
                        }
                    }
                        char *descricao; //ponteiro para guardar o texto que será usado
                        if(pIdx != -1){ //verifica se o produto foi encontrado no catálogo
                            descricao = descricoes[pIdx];//Se encontrou armazena a descrição
                        }else{
                            descricao = "N/A"; //Se não encontrou retorna N/A
                        }
                    //Exibe os dados da venda
                    printf("%-8d | %-7d | %-15s | %-3d | %-5.2f | %.2f\n", ids[i], produtoIds[i],descricao, quantidades[i], precos[i], quantidades[i] * precos[i]);
                }
                break;
            case 2:
                printf("Digite o ID da venda: ");
                scanf("%d", &idBusca);
                //Permite Escolher o algoritmo de busca
                printf("Escolha o algoritmo de busca:\n");
                printf("1. Busca Linear\n");
                printf("2. Busca Binária\n");
                printf("Opção:");
                scanf("%d", &algBusca);
                if (algBusca == 2) { //Busca Binária
                    if (!ordenado) { quickSortPorId(ids, produtoIds, quantidades, precos, 0, nVendas - 1); ordenado = true; } //Se não estiver ordenado ordena automáticamente
                    idx = buscaBinaria(ids, nVendas, idBusca); //Executa busca binária
                }else if (algBusca == 1){ //Busca Linear
                    idx = buscaLinear(ids, nVendas, idBusca); //Executa busca Linear
                } else{
                    printf("Opção Inválida\n"); // Caso o usuário digite algo diferente de 1 ou 2
                    break;
                }
                
                if (idx != -1) { //Verifica se encontrou a venda
                    int pIdx = -1; //guarda a posição do produto
                    for(int j=0; j<nProdutos; j++){
                         if(pIdsCatalogo[j] == produtoIds[idx]){
                            pIdx = j; //procura a descrição do produto
                            break;
                        }
                    }
                        char *descricao; //ponteiro para armazenar o texto
                        if (pIdx != -1) { //Verifica se o produto foi encontrado
                            descricao = descricoes[pIdx]; //Se encontrou, usa a descrição do array
                        } else {
                            descricao = "N/A"; //Caso não encontrou retorna N/A
                        }

                    printf("\nVenda encontrada:\n");
                    printf("ID Venda: %d\n", ids[idx]);
                    printf("Produto: %d\n", produtoIds[idx]);
                    printf("Descricao: %s\n", descricao);
                    printf("Quantidade: %d\n", quantidades[idx]);
                    printf("Preco unitario: %.2f\n", precos[idx]);
                    printf("Total da venda: %.2f\n", quantidades[idx] * precos[idx]); //Calcula o total da venda
                } else printf("Venda nao encontrada.\n"); //Caso não encontre nada mostra que a venda não foi encontrada
                break;
            case 3:
                printf("Faturamento total: R$ %.2f\n", calcularFaturamentoTotal(quantidades, precos, nVendas));//percorre todas as vendas e soma
                break;
            case 4: {
                idMaisVendido = encontrarProdutoMaisVendido(produtoIds, quantidades, nVendas);//chama a função para encontrar o produto com maior quantidade vendida
                int pIdx = -1; //guarda a posição do produto encontrado dentro do catálogo
                for(int j=0; j<nProdutos; j++){ //Procura o produto no catálogo usando o ID encontrado
                    if(pIdsCatalogo[j] == idMaisVendido){
                        pIdx = j; //se encontra esse mesmo ID salva a sua posição
                        break;
                    }
                }
                int totalQ = 0; //Armazena a quantidade total vendida do produto
                for(int i=0; i<nVendas; i++){ //Percorre todas as vendas procurando ocorrencias do produto mais vendido
                    if(produtoIds[i] == idMaisVendido){
                        totalQ += quantidades[i]; //Caso o produto da venda atual for igual ao mais vendido soma a sua quantidade
                    }
                }

                char *descricao; //Ponteiro que armazena a descrição do produto
                if (pIdx != -1) { //Verifica se encontrou o produto no catálogo
                    descricao= descricoes[pIdx]; //Guarda a descrição real do produto se o encontrou
                } else {
                    descricao = "N/A"; //Se não encontrou, retorna o N/A
                }   

                printf("\nProduto mais vendido:\nProduto: %d\nDescricao: %s\nQuantidade Total Vendida: %d\n", idMaisVendido,descricao, totalQ);
                break;
            }
            case 5: printf("Encerrando o programa.\n"); break; //Encerra o programa 
            default: printf("Opcao invalida. Tente novamente.\n"); //Executada quando o usuário digita uma opção inválida
        }
    } while (opcao != 5); //Menu continua aparecendo enquanto o usuário não digita 5 para fechâ-lo
    return 0;
}