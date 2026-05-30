/**
Projeto 2- Está Em Xeque?
Nome: Gabriel Pereira de Souza RA: 10440766
Nome: Victor Birello RA: 10737139
*/
#include <stdio.h>
#include <ctype.h>

#define N 8

//Função responsável por ler a string (Forsyth) e preencher a matriz do tabuleiro
void montarTabuleiro(char entrada[], char tab[N][N]) {
    int l = 0, c = 0; //l = linha e c = coluna

    for (int i = 0; entrada[i] != '\0'; i++) {
        char ch = entrada[i];

        if (ch == '-') { //mudança para próxima linha do tabuleiro 
            l++;
            c = 0;
        }
        else if (isdigit(ch)) { //se for um dígito númerico representa a quantidade de casas vazias
            int qtd = ch - '0'; //converte o caractere para valor inteiro

            for (int j = 0; j < qtd; j++) { //preenche para indicar espaço vazio
                tab[l][c++] = '.';
            }
        }
        else { //Caso seja uma letra representa uma peça e é colocada no tabuleiro
            tab[l][c++] = ch;
        }
    }
}

//Função para encontrar as coordenadas do rei (branco) no tabuleiro
void acharRei(char tab[N][N], int *lr, int *cr) {
    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            if (tab[l][c] == 'R') { //Verifica se a peça na posição atual é o rei
                *lr = l;
                *cr = c;
                return; //Interrompe assim que o rei é encontrado
            }
        }
    }
}

//Função que calcula o valor absoluto de um número inteiro 
int absSimples(int x) {
    if (x < 0) return -x;
    return x;
}

//Verifica se há um ataque em uma direção contínua 
int atacaLinha(char tab[N][N], int l, int c, int dl, int dc, int lr, int cr) {
    l += dl;
    c += dc;

    while (l >= 0 && l < N && c >= 0 && c < N) { // Continua avançando na direção dada enquanto estiver dentro dos limites do tabuleiro
        if (l == lr && c == cr) return 1; // Se atingiu o Rei, significa que a peça analisada está atacando-o
        if (tab[l][c] != '.') return 0; // Se encontrou qualquer outra peça pelo caminho, o ataque está bloqueado

        l += dl;
        c += dc;
    }

    return 0; // Se saiu do tabuleiro sem encontrar o Rei, não há ataque nessa direção
}

//Passa pelo tabuleiro procurando as peças pretas e verfica se alguma está atacando a posição do rei
int estaEmXeque(char tab[N][N], int lr, int cr) {
    // Vetores com as 8 combinações de movimentos possíveis para um cavalo
    int cavL[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int cavC[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int l = 0; l < N; l++) {
        for (int c = 0; c < N; c++) {
            char p = tab[l][c]; //Peça atual sendo analisada

            if (p == 'p') { //Verifica ataque de peões pretos
                if (l + 1 == lr && (c - 1 == cr || c + 1 == cr)) return 1;
            }

            else if (p == 'c') { //verficia ataques de cavalos pretos
                for (int i = 0; i < 8; i++) {
                    if (l + cavL[i] == lr && c + cavC[i] == cr) return 1;
                }
            }

            else if (p == 'r') { //Verifica ataques do rei preto
                if (absSimples(l - lr) <= 1 && absSimples(c - cr) <= 1) return 1;
            }

            else if (p == 't' || p == 'd') { //Verifica ataques da torre e dama(ortogonais)
                if (atacaLinha(tab, l, c, -1, 0, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, 1, 0, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, 0, -1, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, 0, 1, lr, cr)) return 1;
            }

            if (p == 'b' || p == 'd') { //Verifica ataques do bispo e da dama(diagonais)
                if (atacaLinha(tab, l, c, -1, -1, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, -1, 1, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, 1, -1, lr, cr)) return 1;
                if (atacaLinha(tab, l, c, 1, 1, lr, cr)) return 1;
            }
        }
    }

    return 0; // Se varreu todas as peças inimigas e nenhuma ataca o Rei, não está em xeque
}

int main() {
    char entrada[100];
    char tab[N][N] = {0};
    int linhaRei = -1;
    int colunaRei = -1;
    
    scanf("%s", entrada); //Recebe a entrada via teclado no terminal 

    // Constrói a matriz do tabuleiro e mapeia as coordenadas do Rei branco
    montarTabuleiro(entrada, tab);
    acharRei(tab, &linhaRei, &colunaRei);

    if (linhaRei == -1 || colunaRei == -1) { //Se o rei branco não foi encontrado encerra a execução 
        printf("False\n");
        return 0;
    }

    // Chama a função principal de verificação e imprime "True" se estiver em xeque e "False" caso contrário
    if (estaEmXeque(tab, linhaRei, colunaRei)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}