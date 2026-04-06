#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO 200
#define TOTAL_MISSOES 6

// Definição da struct Territorio
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Definição da struct Jogador
typedef struct {
    char missao[MAX_MISSAO];
    char cor[MAX_COR];
} Jogador;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador);
void exibirMissao(char* missao);
void liberarMemoria(Territorio* mapa, Jogador* jogadores);
void inicializarMissoes(char* missoes[]);
int escolherTerritorioAtacante(Territorio* mapa, int quantidade, char* corJogador);
int escolherTerritorioDefensor(Territorio* mapa, int quantidade, char* corJogador);

int main() {
    srand(time(NULL));
    
    int quantidadeTerritorios;
    int numJogadores;
    Territorio* mapa;
    Jogador* jogadores;
    char* listaMissoes[TOTAL_MISSOES];
    int jogoAtivo = 1;
    int turno = 1;
    int jogadorVencedor = -1;
    
    printf("=== SISTEMA DE MISSOES ESTRATEGICAS ===\n\n");
    
    // Inicializa o vetor de missoes pre-definidas
    inicializarMissoes(listaMissoes);
    
    // Solicita o numero de jogadores
    printf("Digite o numero de jogadores: ");
    scanf("%d", &numJogadores);
    getchar();
    
    // Solicita o numero de territorios
    printf("Digite o numero de territorios: ");
    scanf("%d", &quantidadeTerritorios);
    getchar();
    
    // Alocacao dinâmica para os territorios
    mapa = (Territorio*)calloc(quantidadeTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria para territorios!\n");
        return 1;
    }
    
    // Alocacao dinâmica para os jogadores
    jogadores = (Jogador*)malloc(numJogadores * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro na alocacao de memoria para jogadores!\n");
        free(mapa);
        return 1;
    }
    
    // Cadastro dos territorios
    cadastrarTerritorios(mapa, quantidadeTerritorios);
    
    // Sorteia uma missao e define uma cor para cada jogador
    printf("\n=== SORTEIO DE MISSOES ===\n");
    char cores[][10] = {"Vermelho", "Azul", "Verde", "Amarelo", "Roxo", "Laranja"};
    
    for (int i = 0; i < numJogadores; i++) {
        atribuirMissao(jogadores[i].missao, listaMissoes, TOTAL_MISSOES);
        strcpy(jogadores[i].cor, cores[i % 6]);
        printf("Jogador %d: Cor %s - Missao sorteada!\n", i + 1, jogadores[i].cor);
    }
    
    // Exibe as missoes de cada jogador (apenas uma vez no inicio)
    printf("\n=== MISSOES DOS JOGADORES ===\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("Jogador %d (%s): ", i + 1, jogadores[i].cor);
        exibirMissao(jogadores[i].missao);
    }
    
    // Exibe o mapa inicial
    printf("\n=== MAPA INICIAL ===\n");
    exibirMapa(mapa, quantidadeTerritorios);
    
    // Loop principal do jogo
    while (jogoAtivo && turno <= 50) {
        printf("\n=== TURNO %d ===\n", turno);
        
        for (int jogador = 0; jogador < numJogadores && jogoAtivo; jogador++) {
            printf("\n--- Vez do Jogador %d (%s) ---\n", jogador + 1, jogadores[jogador].cor);
            printf("Sua missao: ");
            exibirMissao(jogadores[jogador].missao);
            
            // Opcoes do jogador
            int opcao;
            int atacou = 0;
            
            do {
                printf("\nOpcoes:\n");
                printf("1 - Atacar territorio\n");
                printf("2 - Exibir mapa\n");
                printf("3 - Passar turno\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();
                
                switch(opcao) {
                    case 1: {
                        if (atacou) {
                            printf("Voce ja atacou neste turno! Apenas um ataque por turno.\n");
                            break;
                        }
                        
                        // Escolher territorio atacante (do jogador atual)
                        int indiceAtacante = escolherTerritorioAtacante(mapa, quantidadeTerritorios, jogadores[jogador].cor);
                        
                        if (indiceAtacante == -1) {
                            printf("Nenhum territorio disponivel para atacar!\n");
                            break;
                        }
                        
                        // Escolher territorio defensor
                        int indiceDefensor = escolherTerritorioDefensor(mapa, quantidadeTerritorios, jogadores[jogador].cor);
                        
                        if (indiceDefensor == -1) {
                            printf("Nenhum territorio inimigo disponivel!\n");
                            break;
                        }
                        
                        // Verifica tropas suficientes
                        if (mapa[indiceAtacante].tropas <= 1) {
                            printf("Tropas insuficientes para atacar! (Minimo 2 tropas necessarias)\n");
                            break;
                        }
                        
                        // Realiza o ataque
                        printf("\n=== BATALHA ENTRE %s e %s ===\n", 
                               mapa[indiceAtacante].nome, mapa[indiceDefensor].nome);
                        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
                        
                        // Exibe resultado
                        printf("\nResultado apos batalha:\n");
                        printf("Atacante (%s): %d tropas\n", mapa[indiceAtacante].nome, mapa[indiceAtacante].tropas);
                        printf("Defensor (%s): %d tropas (Cor: %s)\n", 
                               mapa[indiceDefensor].nome, mapa[indiceDefensor].tropas, mapa[indiceDefensor].cor);
                        
                        atacou = 1;
                        break;
                    }
                    case 2:
                        exibirMapa(mapa, quantidadeTerritorios);
                        break;
                    case 3:
                        printf("Turno passado!\n");
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
            } while(opcao != 3);
            
            // Verifica se o jogador atual cumpriu sua missao
            if (verificarMissao(jogadores[jogador].missao, mapa, quantidadeTerritorios, jogadores[jogador].cor)) {
                printf("\n========================================\n");
                printf("PARABENS JOGADOR %d (%s)!\n", jogador + 1, jogadores[jogador].cor);
                printf("Voce cumpriu sua missao: ");
                exibirMissao(jogadores[jogador].missao);
                printf("========================================\n");
                jogoAtivo = 0;
                jogadorVencedor = jogador;
                break;
            }
        }
        
        turno++;
    }
    
    if (turno > 50 && jogadorVencedor == -1) {
        printf("\nLimite de turnos atingido! Jogo encerrado sem vencedor.\n");
    } else if (jogadorVencedor != -1) {
        printf("\nJOGADOR %d (%s) E O GRANDE VENCEDOR!\n", jogadorVencedor + 1, jogadores[jogadorVencedor].cor);
    }
    
    // Libera toda a memoria alocada
    liberarMemoria(mapa, jogadores);
    
    return 0;
}

/**
 * Inicializa o vetor de missoes pre-definidas
 */
void inicializarMissoes(char* missoes[]) {
    missoes[0] = "Conquistar 3 territorios inimigos";
    missoes[1] = "Eliminar todas as tropas da cor vermelha";
    missoes[2] = "Controlar pelo menos 5 territorios";
    missoes[3] = "Ter um exercito com mais de 50 tropas no total";
    missoes[4] = "Conquistar um territorio com ataque perfeito (6 contra 1)";
    missoes[5] = "Controlar 80%% dos territorios do mapa";
}

/**
 * Funcao para cadastrar os territorios
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("  Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        
        printf("  Cor do exercito (Vermelho/Azul/Verde/Amarelo/Roxo/Laranja): ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        printf("  Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

/**
 * Funcao para exibir o mapa de todos os territorios
 */
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n");
    printf("+--------+----------------------+------------+--------+\n");
    printf("| Indice | Nome                 | Cor        | Tropas |\n");
    printf("+--------+----------------------+------------+--------+\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("|   %2d   | %-20s | %-10s |  %3d   |\n", 
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("+--------+----------------------+------------+--------+\n\n");
}

/**
 * Funcao que simula um ataque entre dois territorios
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("\nROLANDO DADOS...\n");
    printf("   Atacante rolou: %d\n", dadoAtacante);
    printf("   Defensor rolou: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("\nATACANTE VENCEU A BATALHA!\n");
        
        // Transfere a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do atacante (minimo 1)
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;
        
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("   %s agora pertence ao exercito %s!\n", 
               defensor->nome, defensor->cor);
        printf("   %d tropas foram transferidas para a defesa.\n", tropasTransferidas);
        
    } else if (dadoAtacante < dadoDefensor) {
        printf("\nDEFENSOR VENCEU A BATALHA!\n");
        atacante->tropas--;
        printf("   %s perdeu 1 tropa. Tropas restantes: %d\n", 
               atacante->nome, atacante->tropas);
        
    } else {
        printf("\nEMPATE!\n");
        atacante->tropas--;
        defensor->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
        if (defensor->tropas < 0) defensor->tropas = 0;
        printf("   Ambos perderam 1 tropa.\n");
        printf("   Atacante: %d tropas | Defensor: %d tropas\n", 
               atacante->tropas, defensor->tropas);
    }
}

/**
 * Sorteia uma missao e copia para o destino
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

/**
 * Verifica se a missao do jogador foi cumprida
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    // Conta quantos territorios o jogador possui
    int territoriosJogador = 0;
    int totalTropasJogador = 0;
    
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            territoriosJogador++;
            totalTropasJogador += mapa[i].tropas;
        }
    }
    
    // Verifica o tipo de missao
    if (strstr(missao, "Conquistar 3 territorios inimigos") != NULL) {
        return territoriosJogador >= 3;
    }
    
    if (strstr(missao, "Eliminar todas as tropas da cor vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) {
                return 0; // Ainda existe tropa vermelha
            }
        }
        return 1; // Todas as tropas vermelhas foram eliminadas
    }
    
    if (strstr(missao, "Controlar pelo menos 5 territorios") != NULL) {
        return territoriosJogador >= 5;
    }
    
    if (strstr(missao, "mais de 50 tropas no total") != NULL) {
        return totalTropasJogador > 50;
    }
    
    if (strstr(missao, "Conquistar um territorio com ataque perfeito") != NULL) {
        // Esta missao seria verificada durante um ataque especifico
        // Implementacao simplificada: retorna falso
        return 0;
    }
    
    if (strstr(missao, "80%") != NULL || strstr(missao, "80%%") != NULL) {
        int totalTerritorios = tamanho;
        int percentual = (territoriosJogador * 100) / totalTerritorios;
        return percentual >= 80;
    }
    
    return 0;
}

/**
 * Exibe a missao do jogador
 */
void exibirMissao(char* missao) {
    printf("\"%s\"\n", missao);
}

/**
 * Libera toda a memoria alocada dinamicamente
 */
void liberarMemoria(Territorio* mapa, Jogador* jogadores) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria dos territorios liberada.\n");
    }
    
    if (jogadores != NULL) {
        free(jogadores);
        printf("Memoria dos jogadores liberada.\n");
    }
}

/**
 * Escolhe um territorio para atacar
 */
int escolherTerritorioAtacante(Territorio* mapa, int quantidade, char* corJogador) {
    printf("\nTerritorios disponiveis para ATACAR (seus territorios):\n");
    int territoriosDisponiveis = 0;
    
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            printf("  [%d] %s - Tropas: %d\n", i, mapa[i].nome, mapa[i].tropas);
            territoriosDisponiveis++;
        }
    }
    
    if (territoriosDisponiveis == 0) {
        printf("  Nenhum territorio encontrado!\n");
        return -1;
    }
    
    int indice;
    printf("Digite o indice do territorio atacante: ");
    scanf("%d", &indice);
    getchar();
    
    if (indice < 0 || indice >= quantidade || strcmp(mapa[indice].cor, corJogador) != 0) {
        printf("Territorio invalido ou nao pertence a voce!\n");
        return -1;
    }
    
    return indice;
}

/**
 * Escolhe um territorio para defender
 */
int escolherTerritorioDefensor(Territorio* mapa, int quantidade, char* corJogador) {
    printf("\nTerritorios disponiveis para DEFENDER (territorios inimigos):\n");
    int territoriosDisponiveis = 0;
    
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(mapa[i].cor, corJogador) != 0) {
            printf("  [%d] %s (%s) - Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
            territoriosDisponiveis++;
        }
    }
    
    if (territoriosDisponiveis == 0) {
        printf("  Nenhum territorio inimigo encontrado!\n");
        return -1;
    }
    
    int indice;
    printf("Digite o indice do territorio defensor: ");
    scanf("%d", &indice);
    getchar();
    
    if (indice < 0 || indice >= quantidade || strcmp(mapa[indice].cor, corJogador) == 0) {
        printf("Territorio invalido ou nao e inimigo!\n");
        return -1;
    }
    
    return indice;
}