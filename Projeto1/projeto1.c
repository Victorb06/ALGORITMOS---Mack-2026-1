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
};

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

void processar_lin(char linha[],int pos, char codigo_letra[],int indice_letra, int contador_espacos){
    char c = linha[pos];
    if(c =="\0" || c == "\n"){
        if(indice_letra > 0){
            codigo_letra[indice_letra] = "\0";
            if(codigo_letra[strlen(codigo_letra)-1] == "*"){
                traduzir_corromp(codigo_letra);
            } else{
                trazduzir_cod(codigo_letra);
            }
        }
        return;
    }
    if(c == " "){
        contador_espacos++;
        if(indice_letra > 0){
            codigo_letra[indice_letra] = "\0";
            if(codigo_letra[strlen(codigo_letra)-1] == "*"){
                traduzir_corromp(codigo_letra);
            } else{
                trazduzir_cod(codigo_letra);
            }
            indice_letra = 0;
        }
        if(contador_espacos == 2){
            printf(" ");
        }
    }
    else{
        if(contador_espacos > 0){
            contador_espacos = 0;
        }
        codigo_letra[indice_letra] = c;
        indice_letra++;
    }
    processar_lin(linha, pos + 1,codigo_letra,indice_letra,contador_espacos);
}

int main(){
    char linha[100];
    char codigo_letra[20] = "";
    printf("Digite o Código Morse:");
    fgets(linha, sizeof(linha), stdin);
    processar_lin(linha,0,codigo_letra,0,0);
    printf("\n");
    return 0;
}
