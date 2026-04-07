#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

// ==================== ESTRUTURA ====================

// Struct Componente
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

// Funções de ordenação
void bubbleSortPorNome(Componente lista[], int total, int *comparacoes, double *tempo);
void insertionSortPorTipo(Componente lista[], int total, int *comparacoes, double *tempo);
void selectionSortPorPrioridade(Componente lista[], int total, int *comparacoes, double *tempo);

// Funções de busca
int buscaBinariaPorNome(Componente lista[], int total, char nomeBusca[], int *comparacoes);

// Funções auxiliares
void cadastrarComponentes(Componente componentes[], int *total);
void exibirComponentes(Componente lista[], int total, char titulo[]);
void copiarLista(Componente origem[], Componente destino[], int total);
void exibirMenu();
void limparBuffer();
void exibirCabecalhoOrdenacao(char algoritmo[], char criterio[]);

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    Componente componentes[MAX_COMPONENTES];
    Componente listaTrabalho[MAX_COMPONENTES];
    int totalComponentes = 0;
    int opcao;
    int comparacoes;
    double tempo;
    
    printf("==========================================================\n");
    printf("   TORRE DE FUGA - SISTEMA DE PRIORIZACAO DE COMPONENTES\n");
    printf("==========================================================\n\n");
    
    // Cadastro dos componentes
    cadastrarComponentes(componentes, &totalComponentes);
    
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado! Encerrando programa.\n");
        return 0;
    }
    
    do {
        exibirMenu();
        printf("Escolha sua estrategia de ordenacao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                // Bubble Sort - Ordenar por Nome
                copiarLista(componentes, listaTrabalho, totalComponentes);
                exibirCabecalhoOrdenacao("BUBBLE SORT", "NOME (strings)");
                
                bubbleSortPorNome(listaTrabalho, totalComponentes, &comparacoes, &tempo);
                
                printf("\n--- RESULTADO DA ORDENACAO ---\n");
                exibirComponentes(listaTrabalho, totalComponentes, "Componentes ordenados por NOME");
                printf("\n--- ESTATISTICAS DE DESEMPENHO ---\n");
                printf("Algoritmo: Bubble Sort\n");
                printf("Criterio: Nome (ordem alfabetica)\n");
                printf("Numero de comparacoes: %d\n", comparacoes);
                printf("Tempo de execucao: %.6f segundos\n", tempo);
                break;
                
            case 2:
                // Insertion Sort - Ordenar por Tipo
                copiarLista(componentes, listaTrabalho, totalComponentes);
                exibirCabecalhoOrdenacao("INSERTION SORT", "TIPO (strings)");
                
                insertionSortPorTipo(listaTrabalho, totalComponentes, &comparacoes, &tempo);
                
                printf("\n--- RESULTADO DA ORDENACAO ---\n");
                exibirComponentes(listaTrabalho, totalComponentes, "Componentes ordenados por TIPO");
                printf("\n--- ESTATISTICAS DE DESEMPENHO ---\n");
                printf("Algoritmo: Insertion Sort\n");
                printf("Criterio: Tipo (ordem alfabetica)\n");
                printf("Numero de comparacoes: %d\n", comparacoes);
                printf("Tempo de execucao: %.6f segundos\n", tempo);
                break;
                
            case 3:
                // Selection Sort - Ordenar por Prioridade
                copiarLista(componentes, listaTrabalho, totalComponentes);
                exibirCabecalhoOrdenacao("SELECTION SORT", "PRIORIDADE (inteiros)");
                
                selectionSortPorPrioridade(listaTrabalho, totalComponentes, &comparacoes, &tempo);
                
                printf("\n--- RESULTADO DA ORDENACAO ---\n");
                exibirComponentes(listaTrabalho, totalComponentes, "Componentes ordenados por PRIORIDADE");
                printf("\n--- ESTATISTICAS DE DESEMPENHO ---\n");
                printf("Algoritmo: Selection Sort\n");
                printf("Criterio: Prioridade (1 a 10, crescente)\n");
                printf("Numero de comparacoes: %d\n", comparacoes);
                printf("Tempo de execucao: %.6f segundos\n", tempo);
                break;
                
            case 4: {
                // Busca Binária (requer ordenação por nome primeiro)
                printf("\n==========================================================\n");
                printf("   BUSCA BINARIA - COMPONENTE CHAVE PARA ATIVACAO\n");
                printf("==========================================================\n");
                
                // Primeiro ordena por nome
                copiarLista(componentes, listaTrabalho, totalComponentes);
                printf("\nPreparando para busca binaria...\n");
                printf("Ordenando componentes por NOME primeiro...\n");
                
                int comparacoesOrdenacao;
                double tempoOrdenacao;
                bubbleSortPorNome(listaTrabalho, totalComponentes, &comparacoesOrdenacao, &tempoOrdenacao);
                printf("Ordenacao concluida! (%d comparacoes em %.6f segundos)\n", 
                       comparacoesOrdenacao, tempoOrdenacao);
                
                exibirComponentes(listaTrabalho, totalComponentes, "Lista ordenada por NOME");
                
                char componenteChave[MAX_NOME];
                printf("\nDigite o nome do componente-chave para ativar a torre: ");
                fgets(componenteChave, MAX_NOME, stdin);
                componenteChave[strcspn(componenteChave, "\n")] = '\0';
                
                int comparacoesBusca = 0;
                int posicao = buscaBinariaPorNome(listaTrabalho, totalComponentes, componenteChave, &comparacoesBusca);
                
                printf("\n--- RESULTADO DA BUSCA ---\n");
                printf("Componente buscado: %s\n", componenteChave);
                printf("Comparacoes realizadas: %d\n", comparacoesBusca);
                
                if (posicao != -1) {
                    printf("\n==========================================================\n");
                    printf("   SUCESSO! COMPONENTE ENCONTRADO!\n");
                    printf("==========================================================\n");
                    printf("O componente '%s' esta na posicao %d da lista ordenada.\n", 
                           componenteChave, posicao + 1);
                    printf("Detalhes do componente:\n");
                    printf("  Nome: %s\n", listaTrabalho[posicao].nome);
                    printf("  Tipo: %s\n", listaTrabalho[posicao].tipo);
                    printf("  Prioridade: %d\n", listaTrabalho[posicao].prioridade);
                    printf("\nTORRE DE FUGA ATIVADA COM SUCESSO!\n");
                    printf("Parabens! Voce escapou da ilha!\n");
                } else {
                    printf("\n==========================================================\n");
                    printf("   COMPONENTE NAO ENCONTRADO!\n");
                    printf("==========================================================\n");
                    printf("O componente '%s' nao esta na lista de componentes.\n", componenteChave);
                    printf("Verifique o nome digitado ou cadastre o componente necessario.\n");
                }
                break;
            }
            
            case 5:
                // Exibir componentes originais
                exibirComponentes(componentes, totalComponentes, "COMPONENTES CADASTRADOS (ORDEM ORIGINAL)");
                break;
                
            case 6:
                printf("\nEncerrando o programa...\n");
                printf("Obrigado por jogar! Ate a proxima aventura!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 6 && opcao >= 1 && opcao <= 5) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while(opcao != 6);
    
    return 0;
}

// ==================== FUNÇÕES DE ORDENAÇÃO ====================

//Bubble Sort - Ordena por nome (ordem alfabética)

void bubbleSortPorNome(Componente lista[], int total, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    *comparacoes = 0;
    
    Componente temp;
    
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                // Troca os elementos
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Insertion Sort - Ordena por tipo (ordem alfabética)

void insertionSortPorTipo(Componente lista[], int total, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    *comparacoes = 0;
    
    Componente chave;
    int j;
    
    for (int i = 1; i < total; i++) {
        chave = lista[i];
        j = i - 1;
        
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(lista[j].tipo, chave.tipo) > 0) {
                lista[j + 1] = lista[j];
                j--;
            } else {
                break;
            }
        }
        lista[j + 1] = chave;
    }
    
    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

//Selection Sort - Ordena por prioridade (crescente)

void selectionSortPorPrioridade(Componente lista[], int total, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    *comparacoes = 0;
    
    int indiceMinimo;
    Componente temp;
    
    for (int i = 0; i < total - 1; i++) {
        indiceMinimo = i;
        for (int j = i + 1; j < total; j++) {
            (*comparacoes)++;
            if (lista[j].prioridade < lista[indiceMinimo].prioridade) {
                indiceMinimo = j;
            }
        }
        if (indiceMinimo != i) {
            temp = lista[i];
            lista[i] = lista[indiceMinimo];
            lista[indiceMinimo] = temp;
        }
    }
    
    clock_t fim = clock();
    *tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ==================== FUNÇÕES DE BUSCA ====================

//Busca Binária - Procura componente por nome (lista deve estar ordenada)

int buscaBinariaPorNome(Componente lista[], int total, char nomeBusca[], int *comparacoes) {
    int esquerda = 0;
    int direita = total - 1;
    *comparacoes = 0;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        (*comparacoes)++;
        
        int resultado = strcmp(lista[meio].nome, nomeBusca);
        
        if (resultado == 0) {
            return meio;  // Componente encontrado
        } else if (resultado < 0) {
            esquerda = meio + 1;  // Buscar na metade direita
        } else {
            direita = meio - 1;  // Buscar na metade esquerda
        }
    }
    
    return -1;  // Componente não encontrado
}

// ==================== FUNÇÕES AUXILIARES ====================

//Cadastra os componentes da torre

void cadastrarComponentes(Componente componentes[], int *total) {
    int quantidade;
    
    printf("--- CADASTRO DE COMPONENTES DA TORRE ---\n");
    printf("Quantos componentes deseja cadastrar (maximo %d)? ", MAX_COMPONENTES);
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade > MAX_COMPONENTES) {
        printf("Limite maximo de %d componentes. Cadastrando apenas %d.\n", MAX_COMPONENTES, MAX_COMPONENTES);
        quantidade = MAX_COMPONENTES;
    }
    
    printf("\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Componente %d:\n", i + 1);
        
        printf("  Nome: ");
        fgets(componentes[i].nome, MAX_NOME, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';
        
        printf("  Tipo (controle/suporte/propulsao/energia/estrutura): ");
        fgets(componentes[i].tipo, MAX_TIPO, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';
        
        printf("  Prioridade (1 a 10, sendo 10 mais urgente): ");
        scanf("%d", &componentes[i].prioridade);
        limparBuffer();
        
        if (componentes[i].prioridade < 1) componentes[i].prioridade = 1;
        if (componentes[i].prioridade > 10) componentes[i].prioridade = 10;
        
        printf("\n");
    }
    
    *total = quantidade;
    printf("Total de componentes cadastrados: %d\n", *total);
}

//Exibe todos os componentes em formato de tabela

void exibirComponentes(Componente lista[], int total, char titulo[]) {
    printf("\n=== %s ===\n", titulo);
    
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    printf("\n");
    printf("+----+--------------------------+--------------------+------------+\n");
    printf("| No | Nome                     | Tipo               | Prioridade |\n");
    printf("+----+--------------------------+--------------------+------------+\n");
    
    for (int i = 0; i < total; i++) {
        printf("| %2d | %-24s | %-18s |     %2d     |\n", 
               i + 1, 
               lista[i].nome, 
               lista[i].tipo, 
               lista[i].prioridade);
    }
    printf("+----+--------------------------+--------------------+------------+\n");
    printf("Total de componentes: %d\n", total);
}

//Copia uma lista de componentes para outra

void copiarLista(Componente origem[], Componente destino[], int total) {
    for (int i = 0; i < total; i++) {
        strcpy(destino[i].nome, origem[i].nome);
        strcpy(destino[i].tipo, origem[i].tipo);
        destino[i].prioridade = origem[i].prioridade;
    }
}

/**
 * Exibe o menu principal
 */
void exibirMenu() {
    printf("\n==========================================================\n");
    printf("   ESTRATEGIAS DE MONTAGEM DA TORRE DE FUGA\n");
    printf("==========================================================\n");
    printf("1 - Bubble Sort    (Ordenar por NOME)\n");
    printf("2 - Insertion Sort (Ordenar por TIPO)\n");
    printf("3 - Selection Sort (Ordenar por PRIORIDADE)\n");
    printf("4 - Busca Binaria  (Buscar componente-chave por NOME)\n");
    printf("5 - Exibir componentes cadastrados\n");
    printf("6 - Sair\n");
    printf("==========================================================\n");
}

/**
 * Limpa o buffer do teclado
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Exibe cabeçalho da ordenação
 */
void exibirCabecalhoOrdenacao(char algoritmo[], char criterio[]) {
    printf("\n==========================================================\n");
    printf("   EXECUTANDO %s\n", algoritmo);
    printf("   Criterio de ordenacao: %s\n", criterio);
    printf("==========================================================\n");
}