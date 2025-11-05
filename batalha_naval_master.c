#include <stdio.h>
#include <stdlib.h>

#define LINHA 10
#define COLUNA 10
#define HABILIDADES 5

void exibirTabuleiro(char tabuleiro[LINHA][COLUNA]) {
    // Exibindo os índices das colunas
    printf("  ");
    for (int j = 0; j < COLUNA; j++) {
        printf("%d ", j);
    }
    printf("\n");

    // Exibindo o tabuleiro com índices
    for (int i = 0; i < LINHA; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLUNA; j++){
            if (tabuleiro[i][j] == '0')
                printf("0 "); // Água
            else if (tabuleiro[i][j] == '3')
                printf("3 "); // Navio
            else if (tabuleiro[i][j] == '5')
                printf("5 "); // Area habilidade
            else 
                printf("? "); // Desconhecido
        }
        printf("\n");
    }
}

// Habilidade 1:
void criarCone(int cone[HABILIDADES][HABILIDADES]) {
    for (int i = 0; i < HABILIDADES; i++) {
        for (int j = 0; j < HABILIDADES; j++) {
            if (j >= (HABILIDADES / 2 - i) && j <= (HABILIDADES / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Habilidade 2:
void criarCruz(int cruz[HABILIDADES][HABILIDADES]) {
    int centro = HABILIDADES / 2;
    for (int i = 0; i < HABILIDADES; i++) {
        for (int j = 0; j < HABILIDADES; j++) {
            if (i == centro || j == centro) 
                cruz[i][j] = 1;
            else 
                cruz[i][j] = 0;
        }
    }
}

// Habilidade 3:
void criarOctaedro(int octaedro[HABILIDADES][HABILIDADES]) {
    int centro = HABILIDADES / 2;
    for (int i = 0; i < HABILIDADES; i++) {
        for (int j = 0; j < HABILIDADES; j++) {
            int distX = abs(i - centro);
            int distY = abs(j - centro);
            if (distX + distY <= centro)
                octaedro[i][j] = 1;
            else 
                octaedro[i][j] = 0;
        }
    }
}

void aplicarHabilidade(char tabuleiro[LINHA][COLUNA], int habilidade[HABILIDADES][HABILIDADES], int origemX, int origemY) {
    int centro = HABILIDADES / 2;

    for (int i = 0; i < HABILIDADES; i++) {
        for (int j = 0; j < HABILIDADES; j++) {
            if (habilidade[i][j] == 1) {
                int x = origemX - centro + i;
                int y = origemY - centro + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (x >= 0 && x < LINHA && y >= 0 && y < COLUNA) {
                    if (tabuleiro[x][y] == '0') {
                        tabuleiro[x][y] = '5';
                    }
                }
            }
        }
    }
}

int main(){
    // Definindo o tabuleiro como uma matriz 10x10 de caracteres
    char tabuleiro[LINHA][COLUNA];
    int cone[HABILIDADES][HABILIDADES];
    int cruz[HABILIDADES][HABILIDADES];
    int octaedro[HABILIDADES][HABILIDADES];

    // Inicializando o tabuleiro com '0'
    for (int i = 0; i < LINHA; i++){
        for (int j = 0; j < COLUNA; j++){
            tabuleiro[i][j] = '0';
        }
    }

    // Adicionando navios ao tabuleiro
    tabuleiro[2][1] = '3';
    tabuleiro[2][2] = '3';
    tabuleiro[2][3] = '3';
    
    tabuleiro[5][5] = '3';
    tabuleiro[5][6] = '3'; 
    tabuleiro[5][7] = '3';

    tabuleiro[7][0] = '3';
    tabuleiro[8][1] = '3';
    tabuleiro[9][2] = '3';

    tabuleiro[0][6] = '3';
    tabuleiro[1][7] = '3';
    tabuleiro[2][8] = '3';

    // Criando as habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicando uma habilidade no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 1);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);

    // Exibindo o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}