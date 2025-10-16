#include <stdio.h>

int main(){
    int torre = 1, bispo = 1, rainha = 1;

    // Torre
    printf("Movimentos da Torre:\n");
    
    while (torre <= 5)
    {
        printf("Direita\n", torre);
        torre++;
    }
    
    // Bispo
    printf("Movimentos do Bispo:\n");
    do {
        printf("Cima, Direita\n", bispo);
        bispo++;
    } while (bispo <= 5);

    // Rainha
    printf("Movimentos da Rainha:\n");

    for (rainha; rainha <= 8; rainha++){
        printf("Esquerda\n", rainha);
    }
    return 0;
}