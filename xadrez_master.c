#include <stdio.h>

void movimentos_torre(int torre) {
    if (torre > 0) {
        printf("Direita\n");
        movimentos_torre(torre - 1);
    }
}
void movimentos_bispo(int bispo) {
    int bispo1, bispo2;
    for (bispo1 = 1; bispo1 <= bispo; bispo1++) {
        for (bispo2 = 1; bispo2 <= 1; bispo2++) {
            printf("Direita\n", bispo2);
        }
        printf("Cima\n", bispo1);
    }
}
void movimentos_rainha(int rainha) {
    if (rainha > 0) {
        printf("Esquerda\n");
        movimentos_rainha(rainha - 1);
    }
}

int main(){
    int cavalo1 = 1, cavalo2 = 1, bispo = 5;

    // Torre
    printf("Movimentos da Torre:\n");
    movimentos_torre(5);
    
    // Bispo
    printf("Movimentos do Bispo:\n");
    movimentos_bispo(bispo);

    // Rainha
    printf("Movimentos da Rainha:\n");
    movimentos_rainha(8);

    // Cavalo
    printf("Movimentos do Cavalo:\n");
    for (cavalo1; cavalo1 <= 1; cavalo1++){
        for(cavalo2; cavalo2 <= 2; cavalo2++){
            printf("Cima\n", cavalo2);
        }
        printf("Direita\n", cavalo1);
    }
    return 0;
}