#include <stdio.h>

int main(){
    int torre = 1, bispo = 1, rainha = 1, cavalo1 = 1, cavalo2 = 1;

    // Torre
    printf("Movimentos da Torre:\n");
    
    for (torre = 1; torre <= 5; torre++)
    {
        printf("Direita\n", torre);
    }
    
    // Bispo
    printf("Movimentos do Bispo:\n");

    for (bispo = 1; bispo <= 5; bispo++) {
        printf("Cima, Direita\n", bispo);
    }

    // Rainha
    printf("Movimentos da Rainha:\n");

    for (rainha; rainha <= 8; rainha++){
        printf("Esquerda\n", rainha);
    }

    // Cavalo
    printf("Movimentos do Cavalo:\n");
    for (cavalo1; cavalo1 <= 1; cavalo1++){
        for(cavalo2; cavalo2 <= 2; cavalo2++){
            printf("Baixo\n", cavalo2);
        }
        printf("Esquerda\n", cavalo1);
    }
    return 0;
}