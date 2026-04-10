#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_PISTA 200

// ==================== ESTRUTURAS ====================

// Struct que representa uma sala da mansao (arvore binaria do mapa)
typedef struct Sala {
    char nome[MAX_NOME];
    char pista[MAX_PISTA];          // Pista encontrada nesta sala
    struct Sala* esquerda;          // Ponteiro para a sala a esquerda
    struct Sala* direita;           // Ponteiro para a sala a direita
} Sala;

// Struct que representa um no da arvore BST de pistas
typedef struct PistaNode {
    char pista[MAX_PISTA];
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// ==================== PROTOTIPOS DAS FUNCOES ====================

// Funcoes para o mapa (arvore binaria)
Sala* criarSala(const char* nome, const char* pista);
void explorarSalasComPistas(Sala* salaAtual, PistaNode** raizPistas);
void liberarMapa(Sala* raiz);

// Funcoes para a BST de pistas
PistaNode* criarNoPista(const char* pista);
void inserirPista(PistaNode** raiz, const char* pista);
void exibirPistas(PistaNode* raiz);
void liberarArvorePistas(PistaNode* raiz);

// Funcoes auxiliares
void limparBuffer();
void exibirPistasColetadas(PistaNode* raiz);

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    printf("==========================================================\n");
    printf("   DETECTIVE QUEST - COLETA DE PISTAS\n");
    printf("   Sistema de Exploracao da Mansion com Pistas\n");
    printf("==========================================================\n\n");
    
    // ========== CONSTRUCAO MANUAL DO MAPA (ARVORE BINARIA) ==========
    
    // Nivel 0 - Raiz (Hall de entrada)
    Sala* hall = criarSala("Hall de Entrada", 
                           "Uma pegada misteriosa no chao parece levar para o lado esquerdo.");
    
    // Nivel 1 - Salas do primeiro andar
    Sala* salaEstar = criarSala("Sala de Estar", 
                                "Um bilhete esquecido embaixo do sofa: 'A verdade esta na biblioteca'");
    Sala* cozinha = criarSala("Cozinha", 
                              "Uma faca ensanguentada foi encontrada na pia. Pista importante!");
    
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    // Nivel 2 - Salas do segundo andar (a partir da Sala de Estar)
    Sala* biblioteca = criarSala("Biblioteca", 
                                 "Um livro com marcas de dedo na pagina 47. Alguem procurou algo escondido.");
    Sala* jardimInverno = criarSala("Jardim de Inverno", 
                                    "Plantas pisoteadas perto do muro dos fundos. Alguem fugiu por aqui.");
    
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardimInverno;
    
    // Nivel 2 - Salas do segundo andar (a partir da Cozinha)
    Sala* despensa = criarSala("Despensa", 
                               "Uma carta rasgada foi encontrada: 'Encontre-me no escritorio as 21h'");
    Sala* areaServico = criarSala("Area de Servico", 
                                  "Pegadas de lama no chao. Alguem entrou pela area dos fundos.");
    
    cozinha->esquerda = despensa;
    cozinha->direita = areaServico;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Biblioteca)
    Sala* escritorio = criarSala("Escritorio", 
                                 "Documentos financeiros suspeitos. O mordomo estava desviando dinheiro!");
    Sala* salaMapas = criarSala("Sala de Mapas", 
                                "Um mapa com um X marcado no jardim. Um tesouro ou uma pista falsa?");
    
    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaMapas;
    
    // Nivel 3 - Salas do terceiro andar (a partir do Jardim de Inverno)
    Sala* estufa = criarSala("Estufa", 
                             "Uma luva de jardinagem ensanguentada. O jardineiro pode estar envolvido.");
    Sala* salaCha = criarSala("Sala de Cha", 
                              "Conversa gravada: 'Precisamos nos livrar do detetive antes que ele descubra'");
    
    jardimInverno->esquerda = estufa;
    jardimInverno->direita = salaCha;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Despensa)
    Sala* adega = criarSala("Adega", 
                            "Gritos gravados em um celular esquecido. Alguem estava em perigo aqui.");
    Sala* deposito = criarSala("Deposito", 
                               "Uma caixa com fotos antigas da familia. Segredos do passado.");
    
    despensa->esquerda = adega;
    despensa->direita = deposito;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Area de Servico)
    Sala* lavanderia = criarSala("Lavanderia", 
                                 "Uniforme do mordomo com manchas de sangue. A prova mais forte ate agora!");
    Sala* quartoEmpregados = criarSala("Quarto dos Empregados", 
                                       "Diario da empregada: 'O patrao estava muito nervoso hoje. Ouvi uma discussao'");
    
    areaServico->esquerda = lavanderia;
    areaServico->direita = quartoEmpregados;
    
    // Inicializa a arvore BST de pistas (vazia no inicio)
    PistaNode* raizPistas = NULL;
    
    // Exibe o inicio da exploracao
    printf("Bem-vindo, detetive!\n");
    printf("Voce esta no Hall de Entrada da mansao misteriosa.\n");
    printf("Sua missao: explorar os comodos e coletar TODAS as pistas!\n");
    printf("Cada sala pode conter uma pista importante para resolver o caso.\n");
    printf("Ao final, todas as pistas serao exibidas em ordem alfabetica.\n\n");
    
    // Inicia a exploracao a partir do Hall de entrada
    explorarSalasComPistas(hall, &raizPistas);
    
    // Exibe todas as pistas coletadas em ordem alfabetica
    exibirPistasColetadas(raizPistas);
    
    // Libera a memoria alocada
    liberarMapa(hall);
    liberarArvorePistas(raizPistas);
    
    printf("\n==========================================================\n");
    printf("   Fim da investigacao. Obrigado por jogar Detective Quest!\n");
    printf("==========================================================\n");
    
    return 0;
}

// ==================== FUNCOES DO MAPA (ARVORE BINARIA) ====================

//Cria uma nova sala (no da arvore binaria) com alocacao dinamica
Sala* criarSala(const char* nome, const char* pista) {
    // Aloca memoria para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocacao foi bem sucedida
    if (novaSala == NULL) {
        printf("Erro na alocacao de memoria para a sala %s!\n", nome);
        exit(1);
    }
    
    // Copia o nome da sala
    strcpy(novaSala->nome, nome);
    
    // Copia a pista (se houver)
    if (pista != NULL && strlen(pista) > 0) {
        strcpy(novaSala->pista, pista);
    } else {
        strcpy(novaSala->pista, "");  // Sem pista
    }
    
    // Inicializa os ponteiros para os filhos como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

//Permite ao jogador explorar as salas e coletar pistas
void explorarSalasComPistas(Sala* salaAtual, PistaNode** raizPistas) {
    char opcao;
    
    printf("\n==========================================================\n");
    printf("Voce esta em: %s\n", salaAtual->nome);
    printf("==========================================================\n");
    
    // Verifica se ha pista nesta sala
    if (strlen(salaAtual->pista) > 0) {
        printf("\n[!] PISTA ENCONTRADA!\n");
        printf("    %s\n", salaAtual->pista);
        
        // Insere a pista na arvore BST
        inserirPista(raizPistas, salaAtual->pista);
        printf("\n[+] Pista adicionada ao seu diario de investigacao!\n");
    } else {
        printf("\n[-] Nenhuma pista encontrada nesta sala.\n");
    }
    
    // Verifica se a sala atual tem caminhos disponiveis
    int temEsquerda = (salaAtual->esquerda != NULL);
    int temDireita = (salaAtual->direita != NULL);
    
    // Se nao tem caminhos, nao pode prosseguir
    if (!temEsquerda && !temDireita) {
        printf("\n[!] Esta sala nao possui saidas para outros comodos.\n");
        printf("[!] Voce deve voltar pelo caminho que veio.\n");
        return;
    }
    
    // Exibe as opcoes disponiveis
    printf("\n--- Caminhos disponiveis ---\n");
    if (temEsquerda) {
        printf("  [e] - Ir para ESQUERDA -> %s\n", salaAtual->esquerda->nome);
    }
    if (temDireita) {
        printf("  [d] - Ir para DIREITA -> %s\n", salaAtual->direita->nome);
    }
    printf("  [s] - Sair da exploracao (encerrar investigacao)\n");
    
    // Loop para escolher o caminho
    do {
        printf("\nEscolha seu caminho (e/d/s): ");
        scanf(" %c", &opcao);
        limparBuffer();
        
        // Converte para minusculo
        if (opcao >= 'A' && opcao <= 'Z') {
            opcao = opcao + 32;
        }
        
        if (opcao == 'e' && temEsquerda) {
            printf("\n>> Voce seguiu para a ESQUERDA...\n");
            explorarSalasComPistas(salaAtual->esquerda, raizPistas);
            return;
        } 
        else if (opcao == 'd' && temDireita) {
            printf("\n>> Voce seguiu para a DIREITA...\n");
            explorarSalasComPistas(salaAtual->direita, raizPistas);
            return;
        }
        else if (opcao == 's') {
            printf("\n>> Voce decidiu encerrar a investigacao.\n");
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

//Libera toda a memoria alocada para o mapa (arvore binaria)
void liberarMapa(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Primeiro libera os filhos (pos-ordem)
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
    
    // Depois libera o no atual
    free(raiz);
}

// ==================== FUNCOES DA BST DE PISTAS ====================

//Cria um novo no para a arvore BST de pistas
PistaNode* criarNoPista(const char* pista) {
    PistaNode* novoNo = (PistaNode*)malloc(sizeof(PistaNode));
    
    if (novoNo == NULL) {
        printf("Erro na alocacao de memoria para pista!\n");
        exit(1);
    }
    
    strcpy(novoNo->pista, pista);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    
    return novoNo;
}

//Insere uma nova pista na arvore BST (ordem alfabetica)
void inserirPista(PistaNode** raiz, const char* pista) {
    // Caso base: arvore vazia
    if (*raiz == NULL) {
        *raiz = criarNoPista(pista);
        return;
    }
    
    // Compara as pistas para decidir onde inserir
    int comparacao = strcmp(pista, (*raiz)->pista);
    
    if (comparacao < 0) {
        // Pista menor vai para a esquerda
        inserirPista(&((*raiz)->esquerda), pista);
    } else if (comparacao > 0) {
        // Pista maior vai para a direita
        inserirPista(&((*raiz)->direita), pista);
    } else {
        // Pista duplicada (nao insere novamente)
        printf("   [*] Esta pista ja foi coletada anteriormente!\n");
    }
}

//Exibe todas as pistas em ordem alfabetica (percurso em-ordem)
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Percurso em-ordem (esquerda -> raiz -> direita)
    exibirPistas(raiz->esquerda);
    printf("   - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

//Libera a memoria alocada para a arvore BST de pistas
void liberarArvorePistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberarArvorePistas(raiz->esquerda);
    liberarArvorePistas(raiz->direita);
    free(raiz);
}

// ==================== FUNCOES AUXILIARES ====================

//Exibe o resumo final com todas as pistas coletadas
void exibirPistasColetadas(PistaNode* raiz) {
    printf("\n==========================================================\n");
    printf("   DIARIO DE INVESTIGACAO - PISTAS COLETADAS\n");
    printf("==========================================================\n");
    
    if (raiz == NULL) {
        printf("\nNenhuma pista foi coletada durante a investigacao!\n");
        printf("Tente explorar mais salas na proxima vez.\n");
    } else {
        printf("\nPistas em ordem alfabetica:\n\n");
        exibirPistas(raiz);
        printf("\nTotal de pistas coletadas: Contagem nao disponivel (arvore BST)\n");
    }
    printf("==========================================================\n");
}

//Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}