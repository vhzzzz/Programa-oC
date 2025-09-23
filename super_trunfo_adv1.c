#include <stdio.h>

int main () {
    //Cidades
    char A[50], B[50];
    //Estado
    char E01[50], E02[50];
    //Codigo da carta
    char C01[50], C02[50];
    //População
    unsigned int pop1, pop2;
    //PIB
    float pib1, pib2;
    //Area territorial
    float area1, area2;
    //Pontos turisticos
    int pontos1, pontos2;
    //Densidade populacional
    float densidade1, densidade2;
    //PIB per Capita
    float pibcap1, pibcap2;
    //Super Poder
    float superpoder1, superpoder2; 
    //Comparar Dados

    //Questionando o usuario
    printf("*** INFORME OS DADOS DAS CARTAS ***\n");
    printf("*** PRIMEIRA CARTA ***\n");
    //Cidade
    printf("Nome da primera cidade: %s\n", A);
    scanf("%s", &A);
    //Estado
    printf("Estado da primera carta: %s\n", E01);
    scanf("%s", &E01);
    //Codigo da carta
    printf("O codigo da carta deve seguir o seguinte padrão: A letra do estado seguida de um número de 01 a 04 (ex: A01, B03)\n");
    printf("Codigo da primeira carta: %s\n", C01);
    scanf("%s", &C01);
    //População
    printf("Informe a população da primeira carta: %d\n", pop1);
    scanf("%d", &pop1);
    //PIB
    printf("Informe o PIB da primeira carta: %f\n", pib1);
    scanf("%f", &pib1);
    //Área
    printf("Infome a area da primeira carta em Km²: %f\n", area1);
    scanf("%f", &area1);
    //Pontos turisticos
    printf("Pontos turisticos da primeira carta: %d\n", pontos1);
    scanf("%d", &pontos1);

    printf("*** SEGUNDA CARTA ***\n");
    //Cidade
    printf("Nome da primera cidade: %s\n", B);
    scanf("%s", &B);
    //Estado
    printf("Estado da segunda carta: %s\n", E02);
    scanf("%s", &E02);
    //Codigo da carta
    printf("O codigo da carta deve seguir o seguinte padrão: A letra do estado seguida de um número de 01 a 04 (ex: A01, B03)\n");
    printf("Codigo da segunda carta: %s\n", C02);
    scanf("%s", &C02);
    //População
    printf("Informe a população da segunda carta: %d\n", pop2);
    scanf("%d", &pop2);
    //PIB
    printf("Informe o PIB da segunda carta: %f\n", pib2);
    scanf("%f", &pib2);
    //Área
    printf("Infome a area da segunda carta em Km²: %f\n", area2);
    scanf("%f", &area2);
    //Pontos turisticos
    printf("Pontos turisticos da segunda carta: %d\n", pontos2);
    scanf("%d", &pontos2);

    //Impressão dos dados
    printf("---------------------------------------\n");

    printf("CARTA 1\n"); 
    printf("Estado: %s\n", E01);
    printf("Codigo: %s\n", C01);
    printf("Nome da cidade: %s\n", A);
    printf("População: %i\n", pop1);
    printf("Área: %.2fkm²\n", area1);
    printf("PIB: %.2f bilhões\n", pib1 / 1000000000);
    printf("Numero de Pontos Turisticos: %i\n", pontos1);

    densidade1 = (float) pop1 / area1;
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);

    pibcap1 = (float) pib1 / pop1;
    printf("PIB per Capita: R$%.2f\n", pibcap1);

    superpoder1 = (double) pop1+pib1+area1+pontos1+densidade1+pibcap1;
    printf("Super Poder: %.2f\n", superpoder1 / 1000000);

    printf("---------------------------------------\n");
    
    printf("CARTA 2\n"); 
    printf("Estado: %s\n", E02);
    printf("Codigo: %s\n", C02);
    printf("Nome da cidade: %s\n", B);
    printf("População: %i\n", pop2);
    printf("Área: %.2fkm²\n", area2);
    printf("PIB: %.2f bilhões\n", pib2 / 1000000000);
    printf("Numero de Pontos Turisticos: %i\n", pontos2);

    densidade2 = (float) pop2 / area2;
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);

    pibcap2 = (float) pib2 / pop2;
    printf("PIB per Capita: R$%.2f\n", pibcap2);

    superpoder2 = (double) pop2+pib2+area2+pontos2+densidade2+pibcap2;
    printf("Super Poder: %.2f\n", superpoder2 / 1000000);

    printf("---------------------------------------\n");

    printf("COMPARAÇÃO DAS CARTAS\n");
    printf("População: %d\n", pop1 > pop2);
    printf("Área: %d\n", area1 > area2);
    printf("PIB: %d\n", pib1 > pib2);
    printf("Pontos turisticos: %d\n", pontos1 > pontos2);
    printf("Densidade Populacional: %d\n", densidade1 < densidade2);
    printf("PIB per Capita: %d\n", pibcap1 > pibcap2);
    printf("Super Poder: %d\n", superpoder1 > superpoder2);

    printf("---------------------------------------\n");

    printf("RESULTADO FINAL\n");
    if (superpoder1 > superpoder2) {
        printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01);
    } else if (superpoder2 > superpoder1) {
        printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02);
    } else {
        printf("As cartas empataram!\n");
    }

    return 0;
}