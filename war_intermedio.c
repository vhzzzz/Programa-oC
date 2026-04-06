#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
int escolherTerritorio(Territorio* mapa, int quantidade, const char* mensagem, int corAtacante);
void exibirMenu();

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    int quantidade;
    Territorio* mapa;
    
    printf("========================================\n");
    printf("  MAPA MUNDIAL DE RISCO - TERRITÓRIOS\n");
    printf("========================================\n");
        
    // Solicita o número de territórios
    printf("Digite o número de territórios a serem cadastrados: ");
    scanf("%d", &quantidade);
    getchar(); // Limpa o buffer
    
    // Alocação dinâmica de memória para os territórios
    mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);
    
    // Exibe todos os territórios cadastrados
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n");
    exibirTerritorios(mapa, quantidade);
    
    // Loop principal de ataques
    int opcao;
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1: {
                // Realizar ataque
                printf("\n=== REALIZAR ATAQUE ===\n");
                
                // Escolher território atacante
                int indiceAtacante = escolherTerritorio(mapa, quantidade, 
                    "Escolha o território ATACANTE (pelo índice): ", -1);
                
                if (indiceAtacante == -1) {
                    printf("Território inválido!\n");
                    break;
                }
                
                // Escolher território defensor (não pode ser da mesma cor)
                int indiceDefensor = escolherTerritorio(mapa, quantidade, 
                    "Escolha o território DEFENSOR (pelo índice): ", indiceAtacante);
                
                if (indiceDefensor == -1) {
                    printf("Território inválido ou da mesma cor!\n");
                    break;
                }
                
                // Verifica se o atacante tem tropas suficientes
                if (mapa[indiceAtacante].tropas <= 1) {
                    printf("Território atacante não tem tropas suficientes para atacar!\n");
                    break;
                }
                
                printf("\n--- INICIANDO BATALHA ---\n");
                printf("Atacante: %s (%s) - Tropas: %d\n", 
                    mapa[indiceAtacante].nome, mapa[indiceAtacante].cor, mapa[indiceAtacante].tropas);
                printf("Defensor: %s (%s) - Tropas: %d\n", 
                    mapa[indiceDefensor].nome, mapa[indiceDefensor].cor, mapa[indiceDefensor].tropas);
                
                // Realiza o ataque
                atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
                
                // Exibe o resultado da batalha
                printf("\n--- RESULTADO PÓS-ATAQUE ---\n");
                printf("Atacante: %s (%s) - Tropas: %d\n", 
                    mapa[indiceAtacante].nome, mapa[indiceAtacante].cor, mapa[indiceAtacante].tropas);
                printf("Defensor: %s (%s) - Tropas: %d\n", 
                    mapa[indiceDefensor].nome, mapa[indiceDefensor].cor, mapa[indiceDefensor].tropas);
                
                break;
            }
            case 2:
                // Exibir todos os territórios
                printf("\n=== TERRITÓRIOS CADASTRADOS ===\n");
                exibirTerritorios(mapa, quantidade);
                break;
            case 3:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        
    } while(opcao != 3);
    
    // Libera a memória alocada
    liberarMemoria(mapa);
    
    return 0;
}

//Função para cadastrar os territórios

void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== CADASTRO DE TERRITÓRIOS ===\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);
        
        printf("  Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o \n
        
        printf("  Cor do exército (Ex: Vermelho, Azul, Verde): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
        
        printf("  Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer
    }
}

//Função para exibir todos os territórios

void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\nÍndice | Nome                     | Cor       | Tropas\n");
    printf("-------|--------------------------|-----------|-------\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("  %2d   | %-24s | %-9s | %5d\n", 
            i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Função que simula um ataque entre dois territórios

void atacar(Territorio* atacante, Territorio* defensor) {
    // Simula rolagem de dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("\nRolando dados...\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // Atacante venceu
        printf("\n>>> ATACANTE VENCEU A BATALHA! <<<\n");
        
        // Transfere a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);
        
        // Calcula metade das tropas do atacante (mínimo 1)
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;
        
        // Atualiza as tropas
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("O território %s agora pertence ao exército %s!\n", 
            defensor->nome, defensor->cor);
        printf("%d tropas foram transferidas para o território defensor.\n", 
            tropasTransferidas);
            
    } else if (dadoAtacante < dadoDefensor) {
        // Defensor venceu
        printf("\n>>> DEFENSOR VENCEU A BATALHA! <<<\n");
        
        // Atacante perde uma tropa
        atacante->tropas--;
        printf("O atacante perdeu uma tropa!\n");
        
    } else {
        // Empate
        printf("\n>>> EMPATE! <<<\n");
        printf("Ambos os lados perdem uma tropa.\n");
        
        atacante->tropas--;
        defensor->tropas--;
        
        // Garante que as tropas não fiquem negativas
        if (atacante->tropas < 0) atacante->tropas = 0;
        if (defensor->tropas < 0) defensor->tropas = 0;
    }
}

 //Função para liberar a memória alocada dinamicamente

void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}


 // Função para escolher um território pelo índice
int escolherTerritorio(Territorio* mapa, int quantidade, const char* mensagem, int corAtacante) {
    int indice;
    
    printf("%s", mensagem);
    scanf("%d", &indice);
    getchar();
    
    // Valida se o índice está dentro dos limites
    if (indice < 0 || indice >= quantidade) {
        return -1;
    }
    
    // Se for para escolher defensor, verifica se não é da mesma cor do atacante
    if (corAtacante != -1 && strcmp(mapa[indice].cor, mapa[corAtacante].cor) == 0) {
        printf("Não é possível atacar um território da mesma cor!\n");
        return -1;
    }
    
    return indice;
}

/**
 * Função para exibir o menu principal
 */
void exibirMenu() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Realizar ataque\n");
    printf("2 - Exibir territórios\n");
    printf("3 - Sair\n");
}