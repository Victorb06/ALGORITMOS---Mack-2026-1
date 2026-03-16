/**
Tradutor de Código Morse
Projeto 1- Laboratório de Algoritmos e Programação II
Integrantes:
Enzo Yuri Domingues Ma
RA:10738664
Willian Lima de Oliveira Pena
RA:10428678
Victor Esteves Gallo Birello
RA: 10737139
 */

#include <stdio.h>
#include <string.h>

const char* Codigo_Morse[26] = {
".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
"..-","...-",".--","-..-","-.--","--.."
}

const char alfabeto[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void trazduzir_cod(char codigo[]){
    for(int i = 0; i < 26; i++){
        if(strcmp(codigo, Codigo_Morse[i]) == 0){
            printf("%c",alfabeto[i]);
            return;
        }
    }
}

void traduzir_corromp(char codigo[]){
    char prefixo [20];
    int tamanho = strlen(codigo) - 1;
    strncpy(prefixo, codigo, tamanho);
    prefixo [tamanho] = "\0";
    printf("[");
    for (int i = 0; i < 26; i++){
        if(strncmp(prefixo,Codigo_Morse[i],strlen(prefixo)) == 0){
            printf("%c",alfabeto[i]);
        }
    }
    printf("]");
}

int main(){
    char linha[100];
    char codigo_letra[20];
    int indice_letra = 0;
    int contador_espaco = 0;
    printf("Digite o Código Morse:");
    fgets(linha, sizeof(linha), stdin);

    for(int i = 0; i <= strlen(linha); i++){
        
    }
}
