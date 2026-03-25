/**
Tradutor de Código Morse
Projeto 1- Laboratório de Algoritmos e Programação II
Integrantes:
Enzo Yuri Domingues Ma
RA:10738664
Victor Esteves Gallo Birello
RA: 10737139
Willian Lima de Oliveira Pena
RA:10428678
 */

#include <stdio.h>
#include <string.h>

// Tabela com o código morse
const char* CODIGO_MORSE[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

//Vetor com o alfabeto
const char ALFABETO[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//Função traduzir (recebe código válido e imprime o correspondente)
void traduzir(const char *codigo) {
    for (int i = 0; i < 26; i++) {
        if (strcmp(codigo, CODIGO_MORSE[i]) == 0) { //Compara o código com os itens da tabela
            printf("%c", ALFABETO[i]); //Imprime a letra certa caso encontrada
            return;
        }
    }
}

//Função traduzir_corrompido (pega os códigos que terminam com *)
void traduzir_corrompido(const char *codigo) {
    char prefixo[20];
    int tam = strlen(codigo) - 1; //Calcula o tamanho sem considerar o *

    strncpy(prefixo, codigo, tam); //Copia o código tirando o *
    prefixo[tam] = '\0';

    printf("[");

    for (int i = 0; i < 26; i++) { //Percorre e procura códigos com esse começo
        if (strncmp(prefixo, CODIGO_MORSE[i], strlen(prefixo)) == 0) {
            printf("%c", ALFABETO[i]); //Imprime as letras possíveis diante do código dado
        }
    }

    printf("]");
}

//Função processar (percorre carctere por carctere))
void processar(char linha[], int pos, char codigo[], int *ind, int *espacos) {
    char c = linha[pos]; //Pega o caractere atual

    if (c == '\0' || c == '\n') { //Verifica se já chegou ao final da linha
        if (*ind > 0) {
            codigo[*ind] = '\0'; //Finaliza a string do código atual

            if (codigo[strlen(codigo) - 1] == '*') //Verifica se está corrompido
                traduzir_corrompido(codigo); //Se está chama a função
            else
                traduzir(codigo); //Se não está continua normal
        }
        return;
    }

    if (c == ' ') {
        (*espacos)++; //Se for um espaço, incrementa o contador de espaços

        if (*ind > 0) {
            codigo[*ind] = '\0';

            if (codigo[strlen(codigo) - 1] == '*')
                traduzir_corrompido(codigo);
            else
                traduzir(codigo);

            *ind = 0; //Reseta para começar uma nova letra
        }

        if (*espacos == 2) { //Separação de palavras
            printf(" ");
        }
    }
    else {
        *espacos = 0; //zera o contador de espaços

        codigo[*ind] = c; //Adiciona ao código da letra atual
        (*ind)++; //Avança o índice para o próximo caractere
    }

    processar(linha, pos + 1, codigo, ind, espacos); //Chama a função para o próximo caractere
}

//Função main (Lê a entrada)
int main() {
    char linha[200]; //Vetor da linha digitada
    char codigo[20] = ""; //Vetor do código morse de uma letra
    int ind = 0; //índice letra atual
    int espacos = 0; //contador de espaços

    printf("Digite o código Morse:\n");
    fgets(linha, sizeof(linha), stdin); //Lê a linha

    processar(linha, 0, codigo, &ind, &espacos); //Chama a função

    printf("\n");
    return 0;
}