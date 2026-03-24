#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da estrutura Território
typedef struct {
    char nome[100];
    char cor[100];
    int tropas;
} territorio;

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal
int main() {
    printf("========================================\n");
    printf("  MAPA MUNDIAL DE RISCO - TERRITÓRIOS\n");
    printf("========================================\n");
    printf("\nVamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
    territorio territ[5];
    
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Território %d ---\n", i + 1);
        printf("Nome do território: ");
        fgets(territ[i].nome, sizeof(territ[i].nome), stdin);
        // Remove o caractere de nova linha do final da string
        territ[i].nome[strcspn(territ[i].nome, "\n")] = '\0';

        printf("Cor do território: ");
        fgets(territ[i].cor, sizeof(territ[i].cor), stdin);
        // Remove o caractere de nova linha do final da string
        territ[i].cor[strcspn(territ[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &territ[i].tropas);
        limparBuffer(); // Limpa o buffer após ler um número
    }

    // Exibindo os dados dos territórios
    printf("\n========================================\n");
    printf("     MAPA MUNDIAL ESTADO ATUAL\n");
    printf("========================================\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf("-Nome: %s\n", territ[i].nome);
        printf("-Cor: %s\n", territ[i].cor);
        printf("-Número de tropas: %d\n", territ[i].tropas);
    }
    return 0;
}