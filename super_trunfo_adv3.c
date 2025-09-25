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
    int atributo1, atributo2;

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
    printf("Escolha dois atributos diferentes que deseja comparar!\n");
    printf("1 - População\n");
    printf("2 - Área Territorial\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional (menor valor vence)\n");
    printf("6 - PIB per Capita\n");

    printf("Primeiro Atributo\n");
    scanf("%d", &atributo1);
    switch (atributo1){
    case 1:
        printf("2 - Área Territorial\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor valor vence)\n");
        printf("6 - PIB per Capita\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    case 2:
        printf("1 - População\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor valor vence)\n");
        printf("6 - PIB per Capita\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    case 3:
        printf("1 - População\n");
        printf("2 - Área Territorial\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor valor vence)\n");
        printf("6 - PIB per Capita\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    case 4:
        printf("1 - População\n");
        printf("2 - Área Territorial\n");
        printf("3 - PIB\n");
        printf("5 - Densidade Populacional (menor valor vence)\n");
        printf("6 - PIB per Capita\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    case 5:
        printf("1 - População\n");
        printf("2 - Área Territorial\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("6 - PIB per Capita\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    case 6:
        printf("1 - População\n");
        printf("2 - Área Territorial\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor valor vence)\n");
        printf("Segundo Atributo\n");
        scanf("%d", &atributo2);
        break;
    default:
        printf("Opção inválida!\n");
        break;
    }
    printf("---------------------------------------\n");
    if (atributo1 == atributo2) {
        printf("Os atributos escolhidos devem diferentes, por favor tente novamente.\n");
        return 0;
    }

    printf("---------------------------------------\n");

    switch (atributo1){
    case 1:
        switch (atributo2){
        case 2:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram População e Área territorial.\n");
            printf("A Área Territorial e a População de %s é %.2f km² e %d habitantes e a de %s é %.2f km² e %d habitantes\n", A, area1, pop1, B, area2, pop2);
                        (pop1 + area1 > pop2 + area2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pop2 + area2 > pop1 + area1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 3:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram População e PIB\n");
            printf("A População e o PIB de %s é %d habitantes e %.2f bilhões e a de %s é %d habitantes e %.2f bilhões\n", A, pop1, pib1 / 1000000000, B, pop2, pib2 / 1000000000);     
                        (pop1 + pib1 > pop2 + pib2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pop2 + pib2 > pop1 + pib1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 4:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram População e Pontos Turisticos\n");
            printf("A População e o número de Pontos Turisticos de %s é %d habitantes e %d pontos e a de %s é %d habitantes e %d pontos\n", A, pop1, pontos1, B, pop2, pontos2);
                        (pop1 + pontos1 > pop2 + pontos2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pop2 + pontos2 > pop1 + pontos1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 5:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram População e Densidade Populacional\n");
            printf("A População e a Densidade Populacional de %s é %d habitantes e %.2f hab/km² e a de %s é %d habitantes e %.2f hab/km²\n", A, pop1, densidade1, B, pop2, densidade2); 
                        (pop1 + densidade1 < pop2 + densidade2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pop2 + densidade2 < pop1 + densidade1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 6:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram População e PIB per Capita\n");
            printf("A População e o PIB per Capita de %s é %d habitantes e R$%.2f e a de %s é %d habitantes e R$%.2f\n", A, pop1, pibcap1, B, pop2, pibcap2);
                        (pop1 + pibcap1 > pop2 + pibcap2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pop2 + pibcap2 > pop1 + pibcap1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    case 2:
        switch (atributo2){
        case 1:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Área Territorial e População\n");
            printf("A Área Territorial e a População de %s é %.2f km² e %d habitantes e a de %s é %.2f km² e %d habitantes\n", A, area1, pop1, B, area2, pop2);
                        (area1 + pop1 > area2 + pop2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (area2 + pop2 > area1 + pop1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 3:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Área Territorial e PIB\n");
            printf("A População e o PIB de %s é %d habitantes e %.2f bilhões e a de %s é %d habitantes e %.2f bilhões\n\n", A, area1, pib1 / 1000000000, B, area2, pib2 / 1000000000);
                        (area1 + pib1 > area2 + pib2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (area2 + pib2 > area1 + pib1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 4:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Área Territorial e Pontos Turisticos\n");
            printf("A Área Territorial e o número de Pontos Turisticos de %s é %.2f km² e %d pontos e a de %s é %.2f km² e %d pontos\n", A, area1, pontos1, B, area2, pontos2);
                        (area1 + pontos1 > area2 + pontos2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (area2 + pontos2 > area1 + pontos1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n"); 
        break;
        case 5:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Área Territorial e Densidade Populacional\n");
            printf("A Área Territorial e a Densidade Populacional de %s é %.2f km² e %.2f hab/km² e a de %s é %.2f km² e %.2f hab/km²\n", A, area1, densidade1, B, area2, densidade2); 
                        (area1 + densidade1 < area2 + densidade2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (area2 + densidade2 < area1 + densidade1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 6:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Área Territorial e PIB per Capita\n");
            printf("A Área Territorial e o PIB per Capita de %s é %.2f km² e R$%.2f e a de %s é %.2f km² e R$%.2f\n", A, area1, pibcap1, B, area2, pibcap2);
                        (area1 + pibcap1 > area2 + pibcap2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (area2 + pibcap2 > area1 + pibcap1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    case 3:
        switch (atributo2){
        case 1:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB e População\n");
            printf("O PIB e a População de %s é %.2f bilhões e %d habitantes e a de %s é %.2f bilhões e %d habitantes\n", A, pib1 / 1000000000, pop1, B, pib2 / 1000000000, pop2);
                        (pib1 + pop1 > pib2 + pop2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pib2 + pop2 > pib1 + pop1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 2:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB e Área Territorial\n");
            printf("O PIB e a Área Territorial de %s é %.2f bilhões e %.2f km² e a de %s é %.2f bilhões e %.2f km²\n", A, pib1 / 1000000000, area1, B, pib2 / 1000000000, area2);
                        (pib1 + area1 > pib2 + area2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pib2 + area2 > pib1 + area1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 4:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB e Pontos Turisticos\n");
            printf("O PIB e o número de Pontos Turisticos de %s é %.2f bilhões e %d pontos e a de %s é %.2f bilhões e %d pontos\n", A, pib1 / 1000000000, pontos1, B, pib2 / 1000000000, pontos2);
                        (pib1 + pontos1 > pib2 + pontos2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pib2 + pontos2 > pib1 + pontos1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 5:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB e Densidade Populacional\n");
            printf("O PIB e a Densidade Populacional de %s é %.2f bilhões e %.2f hab/km² e a de %s é %.2f bilhões e %.2f hab/km²\n", A, pib1 / 1000000000, densidade1, B, pib2 / 1000000000, densidade2); 
                        (pib1 + densidade1 < pib2 + densidade2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pib2 + densidade2 < pib1 + densidade1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 6:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB e PIB per Capita\n");
            printf("O PIB e o PIB per Capita de %s é %.2f bilhões e R$%.2f e a de %s é %.2f bilhões e R$%.2f\n", A, pib1 / 1000000000, pibcap1, B, pib2 / 1000000000, pibcap2);
                        (pib1 + pibcap1 > pib2 + pibcap2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pib2 + pibcap2 > pib1 + pibcap1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    case 4:
        switch (atributo2){
        case 1:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Pontos Turisticos e População\n");
            printf("O número de Pontos Turisticos e a População de %s é %d pontos e %d habitantes e a de %s é %d pontos e %d habitantes\n", A, pontos1, pop1, B, pontos2, pop2);
                        (pontos1 + pop1 > pontos2 + pop2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pontos2 + pop2 > pontos1 + pop1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");    
        break;
        case 2:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Pontos Turisticos e Área Territorial\n");
            printf("O número de Pontos Turisticos e a Área Territorial de %s é %d pontos e %.2f km² e a de %s é %d pontos e %.2f km²\n", A, pontos1, area1, B, pontos2, area2);
                        (pontos1 + area1 > pontos2 + area2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pontos2 + area2 > pontos1 + area1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 3:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Pontos Turisticos e PIB\n");
            printf("O número de Pontos Turisticos e o PIB de %s é %d pontos e %.2f bilhões e a de %s é %d pontos e %.2f bilhões\n", A, pontos1, pib1 / 1000000000, B, pontos2, pib2 / 1000000000);
                        (pontos1 + pib1 > pontos2 + pib2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pontos2 + pib2 > pontos1 + pib1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 5:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Pontos Turisticos e Densidade Populacional\n");
            printf("O número de Pontos Turisticos e a Densidade Populacional de %s é %d pontos e %.2f hab/km² e a de %s é %d pontos e %.2f hab/km²\n", A, pontos1, densidade1, B, pontos2, densidade2); 
                        (pontos1 + densidade1 < pontos2 + densidade2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pontos2 + densidade2 < pontos1 + densidade1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 6:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Pontos Turisticos e PIB per Capita\n");
            printf("O número de Pontos Turisticos e o PIB per Capita de %s é %d pontos e R$%.2f e a de %s é %d pontos e R$%.2f\n", A, pontos1, pibcap1, B, pontos2, pibcap2);
                        (pontos1 + pibcap1 > pontos2 + pibcap2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pontos2 + pibcap2 > pontos1 + pibcap1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    case 5:
        switch (atributo2){
        case 1:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Densidade Populacional e População\n");
            printf("A Densidade Populacional e a População de %s é %.2f hab/km² e %d habitantes e a de %s é %.2f hab/km² e %d habitantes\n", A, densidade1, pop1, B, densidade2, pop2);
                        (densidade1 + pop1 < densidade2 + pop2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (densidade2 + pop2 < densidade1 + pop1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 2:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Densidade Populacional e Área Territorial\n");
            printf("A Densidade Populacional e a Área Territorial de %s é %.2f hab/km² e %.2f km² e a de %s é %.2f hab/km² e %.2f km²\n", A, densidade1, area1, B, densidade2, area2);
                        (densidade1 + area1 < densidade2 + area2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (densidade2 + area2 < densidade1 + area1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 3:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Densidade Populacional e PIB\n");
            printf("A Densidade Populacional e o PIB de %s é %.2f hab/km² e %.2f bilhões e a de %s é %.2f hab/km² e %.2f bilhões\n", A, densidade1, pib1 / 1000000000, B, densidade2, pib2 / 1000000000);
                        (densidade1 + pib1 < densidade2 + pib2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (densidade2 + pib2 < densidade1 + pib1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 4:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Densidade Populacional e Pontos Turisticos\n");
            printf("A Densidade Populacional e o número de Pontos Turisticos de %s é %.2f hab/km² e %d pontos e a de %s é %.2f hab/km² e %d pontos\n", A, densidade1, pontos1, B, densidade2, pontos2); 
                        (densidade1 + pontos1 < densidade2 + pontos2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (densidade2 + pontos2 < densidade1 + pontos1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 6:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram Densidade Populacional e PIB per Capita\n");
            printf("A Densidade Populacional e o PIB per Capita de %s é %.2f hab/km² e R$%.2f e a de %s é %.2f hab/km² e R$%.2f\n", A, densidade1, pibcap1, B, densidade2, pibcap2);
                        (densidade1 + pibcap1 < densidade2 + pibcap2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (densidade2 + pibcap2 < densidade1 + pibcap1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    case 6:
        switch (atributo2){
        case 1:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB per Capita e População\n");
            printf("O PIB per Capita e a População de %s é R$%.2f e %d habitantes e a de %s é R$%.2f e %d habitantes\n", A, pibcap1, pop1, B, pibcap2, pop2);
                        (pibcap1 + pop1 > pibcap2 + pop2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pibcap2 + pop2 > pibcap1 + pop1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 2:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB per Capita e Área Territorial\n");
            printf("O PIB per Capita e a Área Territorial de %s é R$%.2f e %.2f km² e a de %s é R$%.2f e %.2f km²\n", A, pibcap1, area1, B, pibcap2, area2);
                        (pibcap1 + area1 > pibcap2 + area2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pibcap2 + area2 > pibcap1 + area1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 3:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB per Capita e PIB\n");
            printf("O PIB per Capita e o PIB de %s é R$%.2f e %.2f bilhões e a de %s é R$%.2f e %.2f bilhões\n", A, pibcap1, pib1 / 1000000000, B, pibcap2, pib2 / 1000000000);
                        (pibcap1 + pib1 > pibcap2 + pib2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pibcap2 + pib2 > pibcap1 + pib1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 4:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB per Capita e Pontos Turisticos\n");
            printf("O PIB per Capita e o número de Pontos Turisticos de %s é R$%.2f e %d pontos e a de %s é R$%.2f e %d pontos\n", A, pibcap1, pontos1, B, pibcap2, pontos2); 
                        (pibcap1 + pontos1 > pibcap2 + pontos2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pibcap2 + pontos2 > pibcap1 + pontos1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        case 5:
            printf("As cidades comparadas são %s e %s\n", A, B);
            printf("Os atributos escolhidos foram PIB per Capita e Densidade Populacional\n");
            printf("O PIB per Capita e a Densidade Populacional de %s é R$%.2f e %.2f hab/km² e a de %s é R$%.2f e %.2f hab/km²\n", A, pibcap1, densidade1, B, pibcap2, densidade2); 
                        (pibcap1 + densidade1 < pibcap2 + densidade2)
                            ? printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
                            : (pibcap2 + densidade2 < pibcap1 + densidade1)
                                ? printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
                                : printf("As cartas empataram!\n");
        break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    break;
    default:
        printf("Opção inválida!\n");
        break;
    break;
    }
    
    printf("---------------------------------------\n");

    printf("RESULTADO FINAL\n");
    printf("O atributo para a comparação final é Super Poder!\n");
    printf("O Super Poder de %s: %.2f e o de %s: %.2f\n", A, superpoder1 / 1000000, B, superpoder2 / 1000000);
    (superpoder1 > superpoder2)
        ?printf("Carta 1 - %s (%s) é a vencedora!\n", A, E01)
        :(superpoder2 > superpoder1)
            ?printf("Carta 2 - %s (%s) é a vencedora!\n", B, E02)
            :printf("As cartas empataram!\n");

    return 0;
}