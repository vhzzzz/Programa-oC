#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para funcoes de manipulacao de caracteres

#define MAX_NOME 50

// ==================== ESTRUTURA ====================

// Struct que representa uma sala da mansao
typedef struct Sala {
    char nome[MAX_NOME];        // Nome da sala
    struct Sala* esquerda;      // Ponteiro para a sala a esquerda
    struct Sala* direita;       // Ponteiro para a sala a direita
} Sala;

// ==================== PROTOTIPOS DAS FUNCOES ====================

Sala* criarSala(const char* nome);
void explorarSalas(Sala* salaAtual);
void exibirMenu();
void limparBuffer();
void liberarArvore(Sala* raiz);

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    printf("==========================================================\n");
    printf("   DETECTIVE QUEST - MANSao MISTERIOSA\n");
    printf("   Sistema de Exploracao do Mapa\n");
    printf("==========================================================\n\n");
    
    // ========== CONSTRUCAO MANUAL DA ARVORE BINARIA ==========
    // A estrutura da mansao e criada automaticamente em codigo
    
    // Nivel 0 - Raiz (Hall de entrada)
    Sala* hall = criarSala("Hall de Entrada");
    
    // Nivel 1 - Salas do primeiro andar
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    // Nivel 2 - Salas do segundo andar (a partir da Sala de Estar)
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardimInverno = criarSala("Jardim de Inverno");
    
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardimInverno;
    
    // Nivel 2 - Salas do segundo andar (a partir da Cozinha)
    Sala* despensa = criarSala("Despensa");
    Sala* areaServico = criarSala("Area de Servico");
    
    cozinha->esquerda = despensa;
    cozinha->direita = areaServico;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Biblioteca)
    Sala* escritorio = criarSala("Escritorio");
    Sala* salaMapas = criarSala("Sala de Mapas");
    
    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaMapas;
    
    // Nivel 3 - Salas do terceiro andar (a partir do Jardim de Inverno)
    Sala* estufa = criarSala("Estufa");
    Sala* salaCha = criarSala("Sala de Cha");
    
    jardimInverno->esquerda = estufa;
    jardimInverno->direita = salaCha;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Despensa)
    Sala* adega = criarSala("Adega");
    Sala* deposito = criarSala("Deposito");
    
    despensa->esquerda = adega;
    despensa->direita = deposito;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Area de Servico)
    Sala* lavanderia = criarSala("Lavanderia");
    Sala* quartoEmpregados = criarSala("Quarto dos Empregados");
    
    areaServico->esquerda = lavanderia;
    areaServico->direita = quartoEmpregados;
    
    // Exibe o inicio da exploracao
    printf("Bem-vindo, detetive!\n");
    printf("Voce esta no Hall de Entrada da mansao misteriosa.\n");
    printf("Sua missao: explorar os comodos ate encontrar pistas sobre o culpado.\n");
    printf("Em cada sala, voce pode escolher ir para a ESQUERDA ou para a DIREITA.\n\n");
    
    // Inicia a exploracao a partir do Hall de entrada
    explorarSalas(hall);
    
    // Libera a memoria alocada para a arvore
    liberarArvore(hall);
    
    printf("\n==========================================================\n");
    printf("   Fim da exploracao. Obrigado por jogar Detective Quest!\n");
    printf("==========================================================\n");
    
    return 0;
}

// ==================== FUNCOES DA ARVORE BINARIA ====================

//Cria uma nova sala (no da arvore binaria) com alocacao dinamica
Sala* criarSala(const char* nome) {
    // Aloca memoria para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocacao foi bem sucedida
    if (novaSala == NULL) {
        printf("Erro na alocacao de memoria para a sala %s!\n", nome);
        exit(1);
    }
    
    // Copia o nome da sala
    strcpy(novaSala->nome, nome);
    
    // Inicializa os ponteiros para os filhos como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

//Permite ao jogador explorar as salas interativamente
void explorarSalas(Sala* salaAtual) {
    char opcao;
    int passos = 0;
    
    printf("\n----------------------------------------------------------\n");
    printf("Voce esta em: %s\n", salaAtual->nome);
    printf("----------------------------------------------------------\n");
    
    // Verifica se a sala atual tem caminhos disponiveis
    int temEsquerda = (salaAtual->esquerda != NULL);
    int temDireita = (salaAtual->direita != NULL);
    
    // Se nao tem caminhos, chegou ao fim (no folha)
    if (!temEsquerda && !temDireita) {
        printf("\n[!] Esta sala nao possui saidas para outros comodos.\n");
        printf("[!] Voce chegou ao fim da exploracao nesta ala da mansao.\n");
        printf("\n*** PISTA ENCONTRADA! ***\n");
        printf("Voce descobriu pistas importantes no(a) %s!\n", salaAtual->nome);
        printf("Anote em seu diario: O culpado pode estar relacionado a este local!\n");
        return;
    }
    
    // Exibe as opcoes disponiveis
    printf("\nCaminhos disponiveis:\n");
    if (temEsquerda) {
        printf("  [e] - Ir para ESQUERDA -> %s\n", salaAtual->esquerda->nome);
    }
    if (temDireita) {
        printf("  [d] - Ir para DIREITA -> %s\n", salaAtual->direita->nome);
    }
    printf("  [s] - Sair da exploracao (voltar para o menu principal)\n");
    
    // Loop para escolher o caminho
    do {
        printf("\nEscolha seu caminho (e/d/s): ");
        scanf(" %c", &opcao);
        limparBuffer();
        
        // Converte para minusculo para facilitar comparacao
        opcao = tolower(opcao);
        
        if (opcao == 'e' && temEsquerda) {
            passos++;
            printf("\n>> Voce seguiu para a ESQUERDA...\n");
            explorarSalas(salaAtual->esquerda);
            return;
        } 
        else if (opcao == 'd' && temDireita) {
            passos++;
            printf("\n>> Voce seguiu para a DIREITA...\n");
            explorarSalas(salaAtual->direita);
            return;
        }
        else if (opcao == 's') {
            printf("\n>> Voce decidiu encerrar a exploracao.\n");
            printf("Total de salas visitadas: %d\n", passos);
            return;
        }
        else {
            printf("[ERRO] Opcao invalida!\n");
            if (opcao == 'e' && !temEsquerda) {
                printf("Nao ha caminho para a ESQUERDA nesta sala!\n");
            } else if (opcao == 'd' && !temDireita) {
                printf("Nao ha caminho para a DIREITA nesta sala!\n");
            }
        }
    } while (1);
}

//Libera toda a memoria alocada para a arvore binaria
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Primeiro libera os filhos (pos-ordem)
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    
    // Depois libera o no atual
    free(raiz);
}


//Exibe o menu de opcoes (funcao auxiliar)
void exibirMenu() {
    printf("\n==========================================================\n");
    printf("   CONTROLES DE NAVEGACAO\n");
    printf("==========================================================\n");
    printf("  e - Ir para sala a ESQUERDA\n");
    printf("  d - Ir para sala a DIREITA\n");
    printf("  s - Sair da exploracao\n");
    printf("==========================================================\n");
}


//Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}