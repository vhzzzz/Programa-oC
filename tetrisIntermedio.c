#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5      // Tamanho fixo da fila de pecas
#define TAMANHO_PILHA 3     // Capacidade maxima da pilha de reserva

// ==================== ESTRUTURAS ====================

// Struct que representa uma peca do Tetris
typedef struct {
    char nome;     // Tipo da peca: 'I', 'O', 'T', 'L', 'S', 'Z', 'J'
    int id;        // Identificador unico da peca
} Peca;

// ==================== PROTOTIPOS DAS FUNCOES ====================

// Funcoes da Fila Circular
void inicializarFila(Peca fila[], int *inicio, int *fim, int *total);
void enqueue(Peca fila[], int *inicio, int *fim, int *total, Peca novaPeca);
Peca dequeue(Peca fila[], int *inicio, int *fim, int *total);
int filaVazia(int total);
int filaCheia(int total);

// Funcoes da Pilha
void inicializarPilha(Peca pilha[], int *topo);
void push(Peca pilha[], int *topo, Peca novaPeca);
Peca pop(Peca pilha[], int *topo);
int pilhaVazia(int topo);
int pilhaCheia(int topo);

// Funcoes Gerais
Peca gerarPeca(int id);
void exibirEstado(Peca fila[], int inicio, int totalFila, Peca pilha[], int topo);
void exibirMenu();
void limparBuffer();

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    // Estruturas para a Fila Circular
    Peca fila[TAMANHO_FILA];
    int inicio = 0;
    int fim = 0;
    int totalFila = 0;
    
    // Estruturas para a Pilha de Reserva
    Peca pilha[TAMANHO_PILHA];
    int topo = -1;  // Indice do topo da pilha (-1 = vazia)
    
    int opcao;
    int proximoId = 0;      // Controla o ID unico das pecas geradas
    int pecasGeradas = 0;   // Contador total de pecas geradas
    
    printf("==========================================================\n");
    printf("   TETRIS STACK - SISTEMA DE FILA E PILHA DE PECAS\n");
    printf("==========================================================\n\n");
    
    // Inicializa a semente para numeros aleatorios
    srand(time(NULL));
    
    // Inicializa as estruturas
    inicializarFila(fila, &inicio, &fim, &totalFila);
    inicializarPilha(pilha, &topo);
    
    // Preenche a fila com 5 pecas iniciais
    printf("Gerando pecas iniciais para a fila...\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca(proximoId++);
        enqueue(fila, &inicio, &fim, &totalFila, novaPeca);
        pecasGeradas++;
    }
    
    // Exibe o estado inicial
    exibirEstado(fila, inicio, totalFila, pilha, topo);
    
    // Loop principal do programa
    do {
        exibirMenu();
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:  // Jogar peca (remover da fila)
                if (filaVazia(totalFila)) {
                    printf("\n[ERRO] Nao ha pecas na fila!\n");
                } else {
                    // Remove a peca do inicio da fila
                    Peca pecaJogada = dequeue(fila, &inicio, &fim, &totalFila);
                    printf("\n--- PECA JOGADA ---\n");
                    printf("Voce jogou a peca: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
                    printf("-------------------\n");
                    
                    // Gera uma nova peca e adiciona ao final da fila
                    Peca novaPeca = gerarPeca(proximoId++);
                    enqueue(fila, &inicio, &fim, &totalFila, novaPeca);
                    printf("Nova peca gerada e adicionada a fila: [%c %d]\n", 
                           novaPeca.nome, novaPeca.id);
                    pecasGeradas++;
                }
                break;
                
            case 2:  // Reservar peca (mover da fila para a pilha)
                if (filaVazia(totalFila)) {
                    printf("\n[ERRO] Nao ha pecas na fila para reservar!\n");
                } else if (pilhaCheia(topo)) {
                    printf("\n[ERRO] Pilha de reserva cheia! (Maximo %d pecas)\n", TAMANHO_PILHA);
                    printf("Use uma peca reservada antes de reservar outra.\n");
                } else {
                    // Remove a peca do inicio da fila
                    Peca pecaReservada = dequeue(fila, &inicio, &fim, &totalFila);
                    
                    // Adiciona a peca ao topo da pilha
                    push(pilha, &topo, pecaReservada);
                    
                    printf("\n--- PECA RESERVADA ---\n");
                    printf("Peca [%c %d] movida para a pilha de reserva!\n", 
                           pecaReservada.nome, pecaReservada.id);
                    printf("----------------------\n");
                    
                    // Gera uma nova peca e adiciona ao final da fila
                    Peca novaPeca = gerarPeca(proximoId++);
                    enqueue(fila, &inicio, &fim, &totalFila, novaPeca);
                    printf("Nova peca gerada e adicionada a fila: [%c %d]\n", 
                           novaPeca.nome, novaPeca.id);
                    pecasGeradas++;
                }
                break;
                
            case 3:  // Usar peca reservada (remover da pilha)
                if (pilhaVazia(topo)) {
                    printf("\n[ERRO] Pilha de reserva vazia! Nenhuma peca reservada.\n");
                    printf("Reserve uma peca antes de usar a reserva.\n");
                } else {
                    // Remove a peca do topo da pilha
                    Peca pecaUsada = pop(pilha, &topo);
                    printf("\n--- PECA USADA DA RESERVA ---\n");
                    printf("Voce usou a peca reservada: [%c %d]\n", 
                           pecaUsada.nome, pecaUsada.id);
                           
                    // Verifica se ha espaco na pilha para possivel reposicao
                    if (!pilhaCheia(topo)) {
                        printf("Agora ha %d espaco(s) livre(s) na pilha de reserva.\n", 
                               TAMANHO_PILHA - (topo + 1));
                    }
                    printf("----------------------------\n");
                }
                break;
                
            case 0:  // Sair
                printf("\n==========================================================\n");
                printf("Encerrando o jogo...\n");
                printf("Total de pecas geradas durante a partida: %d\n", pecasGeradas);
                printf("Obrigado por jogar Tetris Stack!\n");
                printf("==========================================================\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
        
        // Exibe o estado atual apos cada acao (exceto ao sair)
        if (opcao != 0) {
            printf("\n");
            exibirEstado(fila, inicio, totalFila, pilha, topo);
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
        printf("[ERRO] Fila cheia! Nao foi possivel adicionar a peca.\n");
        return;
    }
    
    fila[*fim] = novaPeca;
    *fim = (*fim + 1) % TAMANHO_FILA;  // Movimenta o fim circularmente
    (*total)++;
}

//Remove e retorna a peca do inicio da fila (dequeue)
Peca dequeue(Peca fila[], int *inicio, int *fim, int *total) {
    if (*total == 0) {
        printf("[ERRO] Fila vazia! Nao foi possivel remover a peca.\n");
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

// ==================== FUNCOES DA PILHA ====================

//Inicializa a pilha com valores padrao
void inicializarPilha(Peca pilha[], int *topo) {
    *topo = -1;  // Pilha vazia
}

//Adiciona uma peca ao topo da pilha (push)
void push(Peca pilha[], int *topo, Peca novaPeca) {
    if (*topo >= TAMANHO_PILHA - 1) {
        printf("[ERRO] Pilha cheia! Nao foi possivel reservar a peca.\n");
        return;
    }
    
    (*topo)++;
    pilha[*topo] = novaPeca;
}

//Remove e retorna a peca do topo da pilha (pop)
Peca pop(Peca pilha[], int *topo) {
    if (*topo == -1) {
        printf("[ERRO] Pilha vazia! Nao foi possivel usar a peca reservada.\n");
        Peca pecaVazia = {'?', -1};
        return pecaVazia;
    }
    
    Peca pecaRemovida = pilha[*topo];
    (*topo)--;
    
    return pecaRemovida;
}

//Verifica se a pilha esta vazia
int pilhaVazia(int topo) {
    return topo == -1;
}

//Verifica se a pilha esta cheia
int pilhaCheia(int topo) {
    return topo >= TAMANHO_PILHA - 1;
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

//Exibe o estado atual da fila e da pilha de pecas
void exibirEstado(Peca fila[], int inicio, int totalFila, Peca pilha[], int topo) {
    printf("==========================================================\n");
    printf("                   ESTADO ATUAL DO JOGO\n");
    printf("==========================================================\n");
    
    // Exibe a FILA de pecas
    printf("\n[ FILA DE PECAS ]\n");
    printf("(Proxima a jogar -> Ultima a chegar)\n");
    printf("  ");
    
    if (filaVazia(totalFila)) {
        printf("[ FILA VAZIA ]");
    } else {
        for (int i = 0; i < totalFila; i++) {
            int indice = (inicio + i) % TAMANHO_FILA;
            printf("[%c %d] ", fila[indice].nome, fila[indice].id);
        }
    }
    
    printf("\n\n");
    
    // Exibe a PILHA de reserva
    printf("[ PILHA DE RESERVA ]\n");
    printf("(Topo -> Base)\n");
    printf("  ");
    
    if (pilhaVazia(topo)) {
        printf("[ PILHA VAZIA ]");
    } else {
        // Exibe do topo para a base
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }
    
    printf("\n");
    printf("==========================================================\n");
    
    // Informacoes adicionais sobre capacidades
    printf("Capacidade: Fila (%d/%d) | Pilha (%d/%d)\n", 
           totalFila, TAMANHO_FILA, 
           topo + 1, TAMANHO_PILHA);
    printf("==========================================================\n");
}


//Exibe o menu de opcoes para o jogador
void exibirMenu() {
    printf("\n==========================================================\n");
    printf("                     MENU DE ACOES\n");
    printf("==========================================================\n");
    printf("  CODIGO | ACAO\n");
    printf("  -------|---------------------------------------------\n");
    printf("    1    | Jogar peca (remover do inicio da fila)\n");
    printf("    2    | Reservar peca (mover da fila para a pilha)\n");
    printf("    3    | Usar peca reservada (remover do topo da pilha)\n");
    printf("    0    | Sair\n");
    printf("==========================================================\n");
}

//Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}