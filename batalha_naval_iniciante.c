#include <stdio.h>

void matriz(char tabuleiro[10][10]) {
    // Exibindo os índices das colunas
    printf("  ");
    for (int y = 0; y < 10; y++) {
        printf("%d ", y);
    }
    printf("\n");

    // Exibindo o tabuleiro com índices
    for (int x = 0; x < 10; x++) {
        printf("%d ", x);
        for (int y = 0; y < 10; y++)
            printf("%c ", tabuleiro[x][y]);
            printf("\n");
    }
}

int main(){
    // Definindo o tabuleiro como uma matriz 10x10 de caracteres
    char tabuleiro[10][10];

    // Inicializando o tabuleiro com '0'
    for (int x = 0; x < 10; x++){
        for (int y = 0; y < 10; y++){
            tabuleiro[x][y] = '0';
        }
        printf("\n");
    }

    // Adicionando navios ao tabuleiro
    tabuleiro[2][1] = '3';
    tabuleiro[2][2] = '3';
    tabuleiro[2][3] = '3';
    
    tabuleiro[5][5] = '3';
    tabuleiro[5][6] = '3'; 
    tabuleiro[5][7] = '3';

    // Exibindo o tabuleiro
    matriz(tabuleiro);

    return 0;
}