#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_PISTA 200
#define TAMANHO_HASH 31      // Tamanho da tabela hash (numero primo para melhor distribuicao)

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

// Struct que representa um no da tabela hash (lista encadeada para colisoes)
typedef struct HashNode {
    char pista[MAX_PISTA];
    char suspeito[MAX_NOME];
    struct HashNode* proximo;
} HashNode;

// ==================== PROTOTIPOS DAS FUNCOES ====================

// Funcoes para o mapa (arvore binaria)
Sala* criarSala(const char* nome, const char* pista);
void explorarSalasComPistas(Sala* salaAtual, PistaNode** raizPistas, HashNode** tabelaHash);
void liberarMapa(Sala* raiz);

// Funcoes para a BST de pistas
PistaNode* criarNoPista(const char* pista);
void inserirPista(PistaNode** raiz, const char* pista);
void exibirPistas(PistaNode* raiz);
int contarPistas(PistaNode* raiz);
void liberarArvorePistas(PistaNode* raiz);

// Funcoes para a Tabela Hash
int funcaoHash(const char* pista);
void inicializarTabelaHash(HashNode** tabelaHash);
void inserirNaHash(HashNode** tabelaHash, const char* pista, const char* suspeito);
const char* encontrarSuspeito(HashNode** tabelaHash, const char* pista);
void liberarTabelaHash(HashNode** tabelaHash);

// Funcoes para o julgamento final
void verificarSuspeitoFinal(PistaNode* raizPistas, HashNode** tabelaHash);
void contarPistasPorSuspeito(PistaNode* raiz, HashNode** tabelaHash, int* contagemSuspeitos, char suspeitos[][MAX_NOME], int* totalSuspeitos);

// Funcoes auxiliares
void limparBuffer();
void exibirPistasColetadas(PistaNode* raiz);
void exibirMenuNavegacao();

// ==================== FUNCAO PRINCIPAL ====================

int main() {
    printf("==========================================================\n");
    printf("   DETECTIVE QUEST - CAPITULO FINAL\n");
    printf("   Sistema de Investigacao com Pistas e Suspeitos\n");
    printf("==========================================================\n\n");
    
    // ========== CONSTRUCAO MANUAL DO MAPA (ARVORE BINARIA) ==========
    
    // Nivel 0 - Raiz (Hall de entrada)
    Sala* hall = criarSala("Hall de Entrada", 
                           "Uma pegada misteriosa no chao parece levar para o lado esquerdo.");
    
    // Nivel 1 - Salas do primeiro andar
    Sala* salaEstar = criarSala("Sala de Estar", 
                                "Um bilhete esquecido: 'Sr. Smith, o pagamento esta atrasado. Ass: Silva'");
    Sala* cozinha = criarSala("Cozinha", 
                              "Uma faca ensanguentada. Pertence ao conjunto de facas do mordomo.");
    
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    // Nivel 2 - Salas do segundo andar (a partir da Sala de Estar)
    Sala* biblioteca = criarSala("Biblioteca", 
                                 "Documento encontrado: O testamento foi alterado em favor do Sr. Smith.");
    Sala* jardimInverno = criarSala("Jardim de Inverno", 
                                    "Um relogio de bolso gravado: 'Para James, com amor, Margaret'");
    
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardimInverno;
    
    // Nivel 2 - Salas do segundo andar (a partir da Cozinha)
    Sala* despensa = criarSala("Despensa", 
                               "Carta rasgada: 'Silva, voce precisa sumir com as provas'");
    Sala* areaServico = criarSala("Area de Servico", 
                                  "Pegadas de lama. O mordomo foi visto usando botas sujas ontem.");
    
    cozinha->esquerda = despensa;
    cozinha->direita = areaServico;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Biblioteca)
    Sala* escritorio = criarSala("Escritorio", 
                                 "Documentos financeiros: Transferencias suspeitas para a conta do Sr. Smith.");
    Sala* salaMapas = criarSala("Sala de Mapas", 
                                "Um mapa com anotacoes: 'Silva, o esconderijo esta aqui'");
    
    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaMapas;
    
    // Nivel 3 - Salas do terceiro andar (a partir do Jardim de Inverno)
    Sala* estufa = criarSala("Estufa", 
                             "Um diario: 'Hoje, Silva me ameacou. Preciso tomar cuidado'");
    Sala* salaCha = criarSala("Sala de Cha", 
                              "Conversa gravada: 'Smith, o detetive esta chegando perto'");
    
    jardimInverno->esquerda = estufa;
    jardimInverno->direita = salaCha;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Despensa)
    Sala* adega = criarSala("Adega", 
                            "Garrafa de veneno encontrada. O mordomo tinha acesso a esta area.");
    Sala* deposito = criarSala("Deposito", 
                               "Fotos comprometedoras de Silva com a vitima momentos antes do crime.");
    
    despensa->esquerda = adega;
    despensa->direita = deposito;
    
    // Nivel 3 - Salas do terceiro andar (a partir da Area de Servico)
    Sala* lavanderia = criarSala("Lavanderia", 
                                 "Uniforme do mordomo com manchas de sangue. Teste DNA confirma.");
    Sala* quartoEmpregados = criarSala("Quarto dos Empregados", 
                                       "Carta: 'Querido Smith, preciso de mais dinheiro para ficar quieto'");
    
    areaServico->esquerda = lavanderia;
    areaServico->direita = quartoEmpregados;
    
    // Inicializa a arvore BST de pistas (vazia no inicio)
    PistaNode* raizPistas = NULL;
    
    // Inicializa a tabela hash com as associacoes pista -> suspeito
    HashNode* tabelaHash[TAMANHO_HASH];
    inicializarTabelaHash(tabelaHash);
    
    // ========== PREENCHIMENTO DA TABELA HASH ==========
    // Associando pistas aos suspeitos (chave: pista, valor: suspeito)
    inserirNaHash(tabelaHash, "Uma pegada misteriosa no chao parece levar para o lado esquerdo.", "Desconhecido");
    inserirNaHash(tabelaHash, "Um bilhete esquecido: 'Sr. Smith, o pagamento esta atrasado. Ass: Silva'", "Silva");
    inserirNaHash(tabelaHash, "Uma faca ensanguentada. Pertence ao conjunto de facas do mordomo.", "Mordomo");
    inserirNaHash(tabelaHash, "Documento encontrado: O testamento foi alterado em favor do Sr. Smith.", "Sr. Smith");
    inserirNaHash(tabelaHash, "Um relogio de bolso gravado: 'Para James, com amor, Margaret'", "James");
    inserirNaHash(tabelaHash, "Carta rasgada: 'Silva, voce precisa sumir com as provas'", "Silva");
    inserirNaHash(tabelaHash, "Pegadas de lama. O mordomo foi visto usando botas sujas ontem.", "Mordomo");
    inserirNaHash(tabelaHash, "Documentos financeiros: Transferencias suspeitas para a conta do Sr. Smith.", "Sr. Smith");
    inserirNaHash(tabelaHash, "Um mapa com anotacoes: 'Silva, o esconderijo esta aqui'", "Silva");
    inserirNaHash(tabelaHash, "Um diario: 'Hoje, Silva me ameacou. Preciso tomar cuidado'", "Silva");
    inserirNaHash(tabelaHash, "Conversa gravada: 'Smith, o detetive esta chegando perto'", "Sr. Smith");
    inserirNaHash(tabelaHash, "Garrafa de veneno encontrada. O mordomo tinha acesso a esta area.", "Mordomo");
    inserirNaHash(tabelaHash, "Fotos comprometedoras de Silva com a vitima momentos antes do crime.", "Silva");
    inserirNaHash(tabelaHash, "Uniforme do mordomo com manchas de sangue. Teste DNA confirma.", "Mordomo");
    inserirNaHash(tabelaHash, "Carta: 'Querido Smith, preciso de mais dinheiro para ficar quieto'", "Sr. Smith");
    
    // Exibe o inicio da exploracao
    printf("Bem-vindo, detetive!\n");
    printf("Voce esta no Hall de Entrada da mansao misteriosa.\n");
    printf("Sua missao: explorar os comodos e coletar TODAS as pistas!\n");
    printf("Cada pista sera associada a um suspeito atraves da tabela hash.\n");
    printf("Ao final, voce devera acusar o culpado baseado nas pistas coletadas.\n");
    printf("(Voce precisa de pelo menos 2 pistas apontando para o mesmo suspeito)\n\n");
    
    // Inicia a exploracao a partir do Hall de entrada
    explorarSalasComPistas(hall, &raizPistas, tabelaHash);
    
    // Exibe todas as pistas coletadas em ordem alfabetica
    exibirPistasColetadas(raizPistas);
    
    // Realiza o julgamento final
    if (raizPistas != NULL) {
        verificarSuspeitoFinal(raizPistas, tabelaHash);
    } else {
        printf("\n==========================================================\n");
        printf("   NENHUMA PISTA COLETADA!\n");
        printf("==========================================================\n");
        printf("Voce nao coletou nenhuma pista durante a investigacao.\n");
        printf("Sem provas, nao e possivel fazer uma acusacao.\n");
        printf("Caso arquivado por falta de evidencias.\n");
    }
    
    // Libera a memoria alocada
    liberarMapa(hall);
    liberarArvorePistas(raizPistas);
    liberarTabelaHash(tabelaHash);
    
    printf("\n==========================================================\n");
    printf("   Fim da investigacao. Obrigado por jogar Detective Quest!\n");
    printf("==========================================================\n");
    
    return 0;
}

// ==================== FUNCOES DO MAPA (ARVORE BINARIA) ====================

//Cria uma nova sala (no da arvore binaria) com alocacao dinamica
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro na alocacao de memoria para a sala %s!\n", nome);
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    
    if (pista != NULL && strlen(pista) > 0) {
        strcpy(novaSala->pista, pista);
    } else {
        strcpy(novaSala->pista, "");
    }
    
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

//Permite ao jogador explorar as salas e coletar pistas
void explorarSalasComPistas(Sala* salaAtual, PistaNode** raizPistas, HashNode** tabelaHash) {
    char opcao;
    
    printf("\n==========================================================\n");
    printf("Voce esta em: %s\n", salaAtual->nome);
    printf("==========================================================\n");
    
    // Verifica se ha pista nesta sala
    if (strlen(salaAtual->pista) > 0) {
        printf("\n[!] PISTA ENCONTRADA!\n");
        printf("    %s\n", salaAtual->pista);
        
        // Busca o suspeito associado na tabela hash
        const char* suspeito = encontrarSuspeito(tabelaHash, salaAtual->pista);
        printf("    -> Suspeito associado: %s\n", suspeito);
        
        // Insere a pista na arvore BST
        inserirPista(raizPistas, salaAtual->pista);
        printf("\n[+] Pista adicionada ao seu diario de investigacao!\n");
    } else {
        printf("\n[-] Nenhuma pista encontrada nesta sala.\n");
    }
    
    // Verifica se a sala atual tem caminhos disponiveis
    int temEsquerda = (salaAtual->esquerda != NULL);
    int temDireita = (salaAtual->direita != NULL);
    
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
            explorarSalasComPistas(salaAtual->esquerda, raizPistas, tabelaHash);
            return;
        } 
        else if (opcao == 'd' && temDireita) {
            printf("\n>> Voce seguiu para a DIREITA...\n");
            explorarSalasComPistas(salaAtual->direita, raizPistas, tabelaHash);
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
    if (raiz == NULL) return;
    liberarMapa(raiz->esquerda);
    liberarMapa(raiz->direita);
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
    if (*raiz == NULL) {
        *raiz = criarNoPista(pista);
        return;
    }
    
    int comparacao = strcmp(pista, (*raiz)->pista);
    
    if (comparacao < 0) {
        inserirPista(&((*raiz)->esquerda), pista);
    } else if (comparacao > 0) {
        inserirPista(&((*raiz)->direita), pista);
    }
    // Se igual, nao insere duplicata
}

//Exibe todas as pistas em ordem alfabetica (percurso em-ordem)
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf("   - %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

//Conta o numero total de pistas na BST
int contarPistas(PistaNode* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarPistas(raiz->esquerda) + contarPistas(raiz->direita);
}

//Libera a memoria da arvore BST de pistas
void liberarArvorePistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    liberarArvorePistas(raiz->esquerda);
    liberarArvorePistas(raiz->direita);
    free(raiz);
}

// ==================== FUNCOES DA TABELA HASH ====================

//Funcao hash para calcular o indice baseado na pista
int funcaoHash(const char* pista) {
    unsigned long hash = 0;
    for (int i = 0; pista[i] != '\0'; i++) {
        hash = hash * 31 + pista[i];
    }
    return hash % TAMANHO_HASH;
}

//Inicializa a tabela hash com todos os valores NULL
void inicializarTabelaHash(HashNode** tabelaHash) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabelaHash[i] = NULL;
    }
}

//Insere uma associacao pista-suspeito na tabela hash
void inserirNaHash(HashNode** tabelaHash, const char* pista, const char* suspeito) {
    int indice = funcaoHash(pista);
    
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    if (novoNo == NULL) {
        printf("Erro na alocacao de memoria para hash!\n");
        exit(1);
    }
    
    strcpy(novoNo->pista, pista);
    strcpy(novoNo->suspeito, suspeito);
    novoNo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoNo;
}

//Encontra o suspeito associado a uma pista na tabela hash
const char* encontrarSuspeito(HashNode** tabelaHash, const char* pista) {
    int indice = funcaoHash(pista);
    HashNode* atual = tabelaHash[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return "Desconhecido";
}

//Libera a memoria da tabela hash
void liberarTabelaHash(HashNode** tabelaHash) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashNode* atual = tabelaHash[i];
        while (atual != NULL) {
            HashNode* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

// ==================== FUNCOES DO JULGAMENTO FINAL ====================

//Conta quantas pistas apontam para cada suspeito
void contarPistasPorSuspeito(PistaNode* raiz, HashNode** tabelaHash, 
                              int* contagemSuspeitos, char suspeitos[][MAX_NOME], 
                              int* totalSuspeitos) {
    if (raiz == NULL) return;
    
    // Processa a pista atual
    const char* suspeito = encontrarSuspeito(tabelaHash, raiz->pista);
    
    // Verifica se o suspeito ja esta no array
    int encontrado = -1;
    for (int i = 0; i < *totalSuspeitos; i++) {
        if (strcmp(suspeitos[i], suspeito) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1) {
        // Novo suspeito
        strcpy(suspeitos[*totalSuspeitos], suspeito);
        contagemSuspeitos[*totalSuspeitos] = 1;
        (*totalSuspeitos)++;
    } else {
        // Suspeito ja existente
        contagemSuspeitos[encontrado]++;
    }
    
    // Processa os filhos
    contarPistasPorSuspeito(raiz->esquerda, tabelaHash, contagemSuspeitos, suspeitos, totalSuspeitos);
    contarPistasPorSuspeito(raiz->direita, tabelaHash, contagemSuspeitos, suspeitos, totalSuspeitos);
}

//Realiza a fase final de julgamento onde o jogador acusa um suspeito
void verificarSuspeitoFinal(PistaNode* raizPistas, HashNode** tabelaHash) {
    printf("\n==========================================================\n");
    printf("   FASE DE JULGAMENTO - QUEM E O CULPADO?\n");
    printf("==========================================================\n");
    
    // Conta pistas por suspeito
    int contagemSuspeitos[20] = {0};
    char suspeitos[20][MAX_NOME];
    int totalSuspeitos = 0;
    
    contarPistasPorSuspeito(raizPistas, tabelaHash, contagemSuspeitos, suspeitos, &totalSuspeitos);
    
    // Exibe estatisticas das pistas
    printf("\n--- ANALISE DAS PISTAS COLETADAS ---\n");
    printf("Total de pistas coletadas: %d\n", contarPistas(raizPistas));
    printf("\nPistas por suspeito:\n");
    for (int i = 0; i < totalSuspeitos; i++) {
        printf("  %s: %d pista(s)\n", suspeitos[i], contagemSuspeitos[i]);
    }
    
    // Solicita a acusacao do jogador
    char acusado[MAX_NOME];
    printf("\n--- ACUSACAO FINAL ---\n");
    printf("Com base nas pistas coletadas, quem voce acusa como culpado?\n");
    printf("Suspeitos disponiveis: ");
    for (int i = 0; i < totalSuspeitos; i++) {
        printf("%s", suspeitos[i]);
        if (i < totalSuspeitos - 1) printf(", ");
    }
    printf("\nDigite o nome do suspeito: ");
    fgets(acusado, MAX_NOME, stdin);
    acusado[strcspn(acusado, "\n")] = '\0';
    limparBuffer();
    
    // Verifica a acusacao
    printf("\n==========================================================\n");
    printf("   VEREDICTO FINAL\n");
    printf("==========================================================\n");
    
    int pistasContraAcusado = 0;
    for (int i = 0; i < totalSuspeitos; i++) {
        if (strcmp(suspeitos[i], acusado) == 0) {
            pistasContraAcusado = contagemSuspeitos[i];
            break;
        }
    }
    
    if (pistasContraAcusado >= 2) {
        printf("\n✅ ACUSACAO PROCEDENTE! ✅\n");
        printf("Voce acusou %s, que tem %d pista(s) apontando contra si.\n", 
               acusado, pistasContraAcusado);
        printf("As evidencias sao suficientes para condenar o culpado!\n");
        printf("Parabens, detetive! A justica foi feita.\n");
    } else if (pistasContraAcusado == 1) {
        printf("\n⚠️ ACUSACAO FRACA ⚠️\n");
        printf("Voce acusou %s, mas apenas %d pista aponta contra esta pessoa.\n", 
               acusado, pistasContraAcusado);
        printf("As evidencias sao insuficientes para uma condenacao.\n");
        printf("O caso permanece em aberto para novas investigacoes.\n");
    } else {
        printf("\n❌ ACUSACAO IMPROCEDENTE! ❌\n");
        printf("Voce acusou %s, mas nenhuma pista aponta para esta pessoa.\n", acusado);
        printf("Voce acusou a pessoa errada! O verdadeiro culpado ainda esta solto.\n");
        printf("Continue investigando para encontrar o criminoso.\n");
    }
}

// ==================== FUNCOES AUXILIARES ====================

//Exibe o resumo final com todas as pistas coletadas
void exibirPistasColetadas(PistaNode* raiz) {
    printf("\n==========================================================\n");
    printf("   DIARIO DE INVESTIGACAO - PISTAS COLETADAS\n");
    printf("==========================================================\n");
    
    if (raiz == NULL) {
        printf("\nNenhuma pista foi coletada durante a investigacao!\n");
    } else {
        printf("\nPistas em ordem alfabetica:\n\n");
        exibirPistas(raiz);
        printf("\nTotal de pistas coletadas: %d\n", contarPistas(raiz));
    }
}

//Exibe o menu de navegacao
void exibirMenuNavegacao() {
    printf("\n==========================================================\n");
    printf("   CONTROLES DE NAVEGACAO\n");
    printf("==========================================================\n");
    printf("  e - Ir para sala a ESQUERDA\n");
    printf("  d - Ir para sala a DIREITA\n");
    printf("  s - Sair da exploracao e iniciar julgamento\n");
    printf("==========================================================\n");
}

//Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}