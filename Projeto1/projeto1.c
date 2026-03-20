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

const char* CODIGO_MORSE[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

const char ALFABETO[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void traduzir(const char *codigo) {
    for (int i = 0; i < 26; i++) {
        if (strcmp(codigo, CODIGO_MORSE[i]) == 0) {
            printf("%c", ALFABETO[i]);
            return;
        }
    }
}

void traduzir_corrompido(const char *codigo) {
    char prefixo[20];
    int tam = strlen(codigo) - 1;

    strncpy(prefixo, codigo, tam);
    prefixo[tam] = '\0';

    printf("[");

    for (int i = 0; i < 26; i++) {
        if (strncmp(prefixo, CODIGO_MORSE[i], strlen(prefixo)) == 0) {
            printf("%c", ALFABETO[i]);
        }
    }

    printf("]");
}

void processar(char linha[], int pos, char codigo[], int *ind, int *espacos) {
    char c = linha[pos];

    if (c == '\0' || c == '\n') {
        if (*ind > 0) {
            codigo[*ind] = '\0';

            if (codigo[strlen(codigo) - 1] == '*')
                traduzir_corrompido(codigo);
            else
                traduzir(codigo);
        }
        return;
    }

    if (c == ' ') {
        (*espacos)++;

        if (*ind > 0) {
            codigo[*ind] = '\0';

            if (codigo[strlen(codigo) - 1] == '*')
                traduzir_corrompido(codigo);
            else
                traduzir(codigo);

            *ind = 0;
        }

        if (*espacos == 2) {
            printf(" ");
        }
    }
    else {
        *espacos = 0;

        codigo[*ind] = c;
        (*ind)++;
    }

    processar(linha, pos + 1, codigo, ind, espacos);
}

int main() {
    char linha[200];
    char codigo[20] = "";
    int ind = 0;
    int espacos = 0;

    printf("Digite o código Morse:\n");
    fgets(linha, sizeof(linha), stdin);

    processar(linha, 0, codigo, &ind, &espacos);

    printf("\n");
    return 0;
}