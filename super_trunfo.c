#include <stdio.h>

int main () {
    //Cidades
    char A[50] = ("Bauru");
    char B[50] = ("Fortaleza");
    char C[50] = ("Londrina");
    char D[50] = ("Rondonopolis");
    //Estado
    char E01[50] = ("SP");
    char E02[50] = ("CE");
    char E03[50] = ("PR");
    char E04[50] = ("MT");
    //Codigo da carta
    char C01[50] = ("SP01");
    char C02[50] = ("CE02");
    char C03[50] = ("PR03");
    char C04[50] = ("MT04");
    //População
    int popbauru = 391000;
    int popforta = 4284000;
    int poplondr = 577318;
    int poprondo = 260000;
    //PIB
    float pibbauru = 16700000;
    float pibforta = 73400000;
    float piblondr = 17838385;
    float pibrondo = 8137633;
    //Area territorial
    float areabaur = 673.5;
    float areafort = 313.6;
    float arealond = 1651.5;
    float arearond = 4159.2;
    //Pontos turisticos
    int pontobauru = 20;
    int pontoforta = 50;
    int pontolondr = 16;
    int pontorondo = 25;

    //Impressão dos dados
    printf("---------------------------------------\n");

    printf("CARTA 1\n");
    printf("Estado: %s\n", E01);
    printf("Codigo: %s\n", C01);
    printf("Nome da cidade: %s\n", A);
    printf("População: %i\n", popbauru);
    printf("Área: %.2fkm²\n", areabaur);
    printf("PIB: R$%.2f\n", pibbauru);
    printf("Numero de Pontos Turisticos: %i\n", pontobauru);

    printf("---------------------------------------\n");

    printf("CARTA 2\n");
    printf("Estado: %s\n", E02);
    printf("Codigo: %s\n", C02);
    printf("Nome da cidade: %s\n", B);
    printf("População: %i\n", popforta);
    printf("Área: %.2fkm²\n", areafort);
    printf("PIB: R$%.2f\n", pibforta);
    printf("Numero de Pontos Turisticos: %i\n", pontoforta);

    printf("---------------------------------------\n");

    printf("CARTA 3\n");
    printf("Estado: %s\n", E03);
    printf("Codigo: %s\n", C03);
    printf("Nome da cidade: %s\n", C);
    printf("População: %i\n", poplondr);
    printf("Área: %.2fkm²\n", arealond);
    printf("PIB: R$%.2f\n", piblondr);
    printf("Numero de Pontos Turisticos: %i\n", pontolondr);

    printf("---------------------------------------\n");

    printf("CARTA 4\n");
    printf("Estado: %s\n", E04);
    printf("Codigo: %s\n", C04);
    printf("Nome da cidade: %s\n", D);
    printf("População: %i\n", poprondo);
    printf("Área: %.2fkm²\n", arearond);
    printf("PIB: R$%.2f\n", pibrondo);
    printf("Numero de Pontos Turisticos: %i\n", pontorondo);
    
    printf("---------------------------------------\n");

    return 0;
}
