#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5  // Tamanho fixo da fila de pecas

// ==================== ESTRUTURA ====================

// Struct que representa uma peca do Tetris
typedef struct {
    char nome;     // Tipo da peca: 'I', 'O', 'T', 'L', 'S', 'Z', 'J'
    int id;        // Identificador unico da peca
} Peca;

// ==================== PROTOTIPOS DAS FUNCOES ====================

void inicializarFila(Peca fila[], int *inicio, int *fim, int *total);
void enqueue(Peca fila[], int *inicio, int *fim, int *total, Peca novaPeca);
Peca dequeue(Peca fila[], int *inicio, int *fim, int *total);
Peca gerarPeca(int id);
void exibirFila(Peca fila[], int inicio, int total);
int filaVazia(int total);
int filaCheia(int total);
void exibirMenu();

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    Peca fila[TAMANHO_FILA];  // Vetor que representa a fila circular
    int inicio = 0;            // Indice do inicio da fila
    int fim = 0;               // Indice do fim da fila
    int total = 0;             // Quantidade atual de elementos na fila
    int opcao;
    int proximoId = 0;         // Controla o ID unico das pecas geradas
    
    printf("==========================================\n");
    printf("   TETRIS STACK - SISTEMA DE FILA DE PECAS\n");
    printf("==========================================\n\n");
    
    // Inicializa a semente para numeros aleatorios
    srand(time(NULL));
    
    // Inicializa a fila com 5 pecas
    printf("Inicializando fila com %d pecas...\n\n", TAMANHO_FILA);
    inicializarFila(fila, &inicio, &fim, &total);
    
    // Gera as primeiras pecas da fila
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca(proximoId++);
        enqueue(fila, &inicio, &fim, &total, novaPeca);
    }
    
    // Exibe o estado inicial da fila
    exibirFila(fila, inicio, total);
    
    // Loop principal do programa
    do {
        exibirMenu();
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:  // Jogar peca (dequeue)
                if (filaVazia(total)) {
                    printf("\nNao ha pecas na fila! A fila esta vazia.\n");
                } else {
                    Peca pecaJogada = dequeue(fila, &inicio, &fim, &total);
                    printf("\n--- PECA JOGADA ---\n");
                    printf("Voce jogou a peca: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
                    printf("-------------------\n");
                }
                break;
                
            case 2:  // Inserir nova peca (enqueue)
                if (filaCheia(total)) {
                    printf("\nFila cheia! Nao e possivel adicionar nova peca.\n");
                    printf("Jogue uma peca antes de adicionar mais.\n");
                } else {
                    Peca novaPeca = gerarPeca(proximoId++);
                    enqueue(fila, &inicio, &fim, &total, novaPeca);
                    printf("\n--- NOVA PECA ADICIONADA ---\n");
                    printf("Peca gerada: [%c %d]\n", novaPeca.nome, novaPeca.id);
                    printf("----------------------------\n");
                }
                break;
                
            case 0:  // Sair
                printf("\nEncerrando o jogo...\n");
                printf("Obrigado por jogar Tetris Stack!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        // Exibe o estado atual da fila apos cada acao
        if (opcao != 0) {
            printf("\n");
            exibirFila(fila, inicio, total);
        }
        
    } while(opcao != 0);
    
    return 0;
}

// ==================== FUNCOES DA FILA CIRCULAR ====================

//Inicializa a fila com valores padrao
void inicializarFila(Peca fila[], int *inicio, int *fim, int *total) {
    *inicio = 0;
    *fim = 0;
    *total = 0;
}

//Adiciona uma nova peca ao final da fila (enqueue)
void enqueue(Peca fila[], int *inicio, int *fim, int *total, Peca novaPeca) {
    if (*total >= TAMANHO_FILA) {
        printf("Erro: Fila cheia! Nao foi possivel adicionar a peca.\n");
        return;
    }
    
    fila[*fim] = novaPeca;
    *fim = (*fim + 1) % TAMANHO_FILA;  // Movimenta o fim circularmente
    (*total)++;
}

//Remove e retorna a peca do inicio da fila (dequeue)
Peca dequeue(Peca fila[], int *inicio, int *fim, int *total) {
    if (*total == 0) {
        printf("Erro: Fila vazia! Nao foi possivel remover a peca.\n");
        Peca pecaVazia = {'?', -1};
        return pecaVazia;
    }
    
    Peca pecaRemovida = fila[*inicio];
    *inicio = (*inicio + 1) % TAMANHO_FILA;  // Movimenta o inicio circularmente
    (*total)--;
    
    return pecaRemovida;
}

//Verifica se a fila esta vazia
int filaVazia(int total) {
    return total == 0;
}

//Verifica se a fila esta cheia
int filaCheia(int total) {
    return total >= TAMANHO_FILA;
}

// ==================== FUNCOES DE GERACAO DE PECAS ====================

//Gera uma nova peca com tipo aleatorio e id unico
Peca gerarPeca(int id) {
    Peca novaPeca;
    
    // Lista de tipos possiveis de pecas no Tetris
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    int numTipos = sizeof(tipos) / sizeof(tipos[0]);
    
    // Escolhe um tipo aleatorio
    int indiceAleatorio = rand() % numTipos;
    novaPeca.nome = tipos[indiceAleatorio];
    novaPeca.id = id;
    
    return novaPeca;
}

// ==================== FUNCOES DE EXIBICAO ====================

//Exibe o estado atual da fila de pecas
void exibirFila(Peca fila[], int inicio, int total) {
    printf("==========================================\n");
    printf("         ESTADO ATUAL DA FILA\n");
    printf("==========================================\n");
    
    if (filaVazia(total)) {
        printf("   [ FILA VAZIA ]\n");
        printf("==========================================\n");
        return;
    }
    
    printf("Fila de pecas (INICIO -> FINAL):\n\n");
    printf("  ");
    
    // Percorre a fila circularmente
    for (int i = 0; i < total; i++) {
        int indice = (inicio + i) % TAMANHO_FILA;
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
    }
    
    printf("\n\n");
    printf("Proxima peca a jogar: [%c %d] (INICIO da fila)\n", 
           fila[inicio].nome, fila[inicio].id);
    printf("==========================================\n");
}

//Exibe o menu de opcoes para o jogador
void exibirMenu() {
    printf("\n==========================================\n");
    printf("              MENU DE ACOES\n");
    printf("==========================================\n");
    printf("  1 - Jogar peca (remover do inicio)\n");
    printf("  2 - Adicionar nova peca (ao final)\n");
    printf("  0 - Sair\n");
    printf("==========================================\n");
}