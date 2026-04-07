#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// ==================== ESTRUTURAS ====================

// Struct Item (comum para ambas estruturas)
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Struct No para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== VARIÁVEIS GLOBAIS PARA CONTADORES ====================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==================== PROTÓTIPOS DAS FUNÇÕES ====================

// Funções para o VETOR
void inserirItemVetor(Item mochila[], int *totalItens);
void removerItemVetor(Item mochila[], int *totalItens);
void listarItensVetor(Item mochila[], int totalItens);
int buscarSequencialVetor(Item mochila[], int totalItens, char nomeBusca[]);
void ordenarVetor(Item mochila[], int totalItens);
int buscarBinariaVetor(Item mochila[], int totalItens, char nomeBusca[]);

// Funções para a LISTA ENCADEADA
void inserirItemLista(No **cabeca);
void removerItemLista(No **cabeca);
void listarItensLista(No *cabeca);
int buscarSequencialLista(No *cabeca, char nomeBusca[]);
void liberarLista(No **cabeca);

// Funções gerais
void exibirMenu();
void limparBuffer();
void exibirComparacoes();

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    int opcaoEstrutura;
    int opcao;
    
    // Estruturas para o VETOR
    Item mochilaVetor[MAX_ITENS];
    int totalItensVetor = 0;
    
    // Estruturas para a LISTA ENCADEADA
    No *cabecaLista = NULL;
    
    printf("==========================================================\n");
    printf("   SISTEMA DE MOCHILA - COMPARACAO VETOR vs LISTA\n");
    printf("==========================================================\n\n");
    
    do {
        printf("\n----------------------------------------\n");
        printf("Escolha qual estrutura deseja utilizar:\n");
        printf("----------------------------------------\n");
        printf("1 - Mochila com VETOR (lista sequencial)\n");
        printf("2 - Mochila com LISTA ENCADEADA\n");
        printf("3 - Sair\n");
        printf("----------------------------------------\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcaoEstrutura);
        limparBuffer();
        
        if (opcaoEstrutura == 1) {
            // ==================== VETOR ====================
            printf("\n========== MOCHILA COM VETOR ==========\n");
            
            do {
                exibirMenu();
                printf("Digite sua opcao: ");
                scanf("%d", &opcao);
                limparBuffer();
                
                switch(opcao) {
                    case 1:
                        inserirItemVetor(mochilaVetor, &totalItensVetor);
                        break;
                    case 2:
                        removerItemVetor(mochilaVetor, &totalItensVetor);
                        break;
                    case 3:
                        listarItensVetor(mochilaVetor, totalItensVetor);
                        break;
                    case 4: {
                        char nomeBusca[MAX_NOME];
                        printf("\n--- BUSCA SEQUENCIAL (VETOR) ---\n");
                        printf("Digite o nome do item: ");
                        fgets(nomeBusca, MAX_NOME, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        
                        comparacoesSequencial = 0;
                        int pos = buscarSequencialVetor(mochilaVetor, totalItensVetor, nomeBusca);
                        
                        if (pos != -1) {
                            printf("\nItem encontrado na posicao %d!\n", pos + 1);
                            printf("  Nome: %s\n", mochilaVetor[pos].nome);
                            printf("  Tipo: %s\n", mochilaVetor[pos].tipo);
                            printf("  Quantidade: %d\n", mochilaVetor[pos].quantidade);
                        } else {
                            printf("\nItem nao encontrado!\n");
                        }
                        printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
                        break;
                    }
                    case 5: {
                        if (totalItensVetor == 0) {
                            printf("\nNenhum item para ordenar!\n");
                            break;
                        }
                        printf("\n--- ORDENACAO DO VETOR ---\n");
                        ordenarVetor(mochilaVetor, totalItensVetor);
                        printf("Vetor ordenado por nome com sucesso!\n");
                        listarItensVetor(mochilaVetor, totalItensVetor);
                        break;
                    }
                    case 6: {
                        if (totalItensVetor == 0) {
                            printf("\nNenhum item para buscar!\n");
                            break;
                        }
                        char nomeBusca[MAX_NOME];
                        printf("\n--- BUSCA BINARIA (VETOR ORDENADO) ---\n");
                        printf("ATENCAO: A busca binaria requer que o vetor esteja ordenado!\n");
                        printf("Digite o nome do item: ");
                        fgets(nomeBusca, MAX_NOME, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        
                        comparacoesBinaria = 0;
                        int pos = buscarBinariaVetor(mochilaVetor, totalItensVetor, nomeBusca);
                        
                        if (pos != -1) {
                            printf("\nItem encontrado na posicao %d!\n", pos + 1);
                            printf("  Nome: %s\n", mochilaVetor[pos].nome);
                            printf("  Tipo: %s\n", mochilaVetor[pos].tipo);
                            printf("  Quantidade: %d\n", mochilaVetor[pos].quantidade);
                        } else {
                            printf("\nItem nao encontrado!\n");
                        }
                        printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
                        break;
                    }
                    case 7:
                        printf("\nVoltando ao menu principal...\n");
                        break;
                    default:
                        printf("\nOpcao invalida!\n");
                }
                
                if (opcao != 7 && opcao >= 1 && opcao <= 6) {
                    printf("\nPressione Enter para continuar...");
                    getchar();
                }
                
            } while(opcao != 7);
            
        } else if (opcaoEstrutura == 2) {
            // ==================== LISTA ENCADEADA ====================
            printf("\n========== MOCHILA COM LISTA ENCADEADA ==========\n");
            
            do {
                exibirMenu();
                printf("Digite sua opcao: ");
                scanf("%d", &opcao);
                limparBuffer();
                
                switch(opcao) {
                    case 1:
                        inserirItemLista(&cabecaLista);
                        break;
                    case 2:
                        removerItemLista(&cabecaLista);
                        break;
                    case 3:
                        listarItensLista(cabecaLista);
                        break;
                    case 4: {
                        char nomeBusca[MAX_NOME];
                        printf("\n--- BUSCA SEQUENCIAL (LISTA) ---\n");
                        printf("Digite o nome do item: ");
                        fgets(nomeBusca, MAX_NOME, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        
                        comparacoesSequencial = 0;
                        int encontrado = buscarSequencialLista(cabecaLista, nomeBusca);
                        
                        if (!encontrado) {
                            printf("\nItem nao encontrado!\n");
                        }
                        printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
                        break;
                    }
                    case 5:
                        printf("\nA lista encadeada NAO requer ordenacao manual!\n");
                        printf("Os itens sao organizados dinamicamente na memoria.\n");
                        break;
                    case 6:
                        printf("\nA busca binaria NAO pode ser aplicada em lista encadeada!\n");
                        printf("Listas encadeadas nao permitem acesso aleatorio aos elementos.\n");
                        break;
                    case 7:
                        printf("\nVoltando ao menu principal...\n");
                        break;
                    default:
                        printf("\nOpcao invalida!\n");
                }
                
                if (opcao != 7 && opcao >= 1 && opcao <= 6) {
                    printf("\nPressione Enter para continuar...");
                    getchar();
                }
                
            } while(opcao != 7);
            
        } else if (opcaoEstrutura == 3) {
            printf("\nEncerrando o programa...\n");
            printf("Liberando memoria alocada...\n");
            liberarLista(&cabecaLista);
            printf("Programa finalizado!\n");
        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
        
    } while(opcaoEstrutura != 3);
    
    return 0;
}

// ==================== FUNÇÕES GERAIS ====================

void exibirMenu() {
    printf("\n----------------------------------------\n");
    printf("            MENU DE OPERACOES\n");
    printf("----------------------------------------\n");
    printf("1 - Inserir novo item\n");
    printf("2 - Remover item por nome\n");
    printf("3 - Listar todos os itens\n");
    printf("4 - Buscar item por nome (busca sequencial)\n");
    printf("5 - Ordenar itens por nome (apenas VETOR)\n");
    printf("6 - Busca binaria (apenas VETOR ordenado)\n");
    printf("7 - Voltar ao menu anterior\n");
    printf("----------------------------------------\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==================== FUNÇÕES PARA VETOR ====================

void inserirItemVetor(Item mochila[], int *totalItens) {
    printf("\n--- INSERIR ITEM (VETOR) ---\n");
    
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Capacidade maxima de %d itens.\n", MAX_ITENS);
        return;
    }
    
    printf("Nome do item: ");
    fgets(mochila[*totalItens].nome, MAX_NOME, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';
    
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    fgets(mochila[*totalItens].tipo, MAX_TIPO, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();
    
    if (mochila[*totalItens].quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    
    (*totalItens)++;
    printf("Item inserido com sucesso!\n");
    listarItensVetor(mochila, *totalItens);
}

void removerItemVetor(Item mochila[], int *totalItens) {
    char nomeBusca[MAX_NOME];
    int indiceEncontrado = -1;
    
    printf("\n--- REMOVER ITEM (VETOR) ---\n");
    
    if (*totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }
    
    if (indiceEncontrado == -1) {
        printf("Item nao encontrado!\n");
        return;
    }
    
    for (int i = indiceEncontrado; i < *totalItens - 1; i++) {
        strcpy(mochila[i].nome, mochila[i + 1].nome);
        strcpy(mochila[i].tipo, mochila[i + 1].tipo);
        mochila[i].quantidade = mochila[i + 1].quantidade;
    }
    
    (*totalItens)--;
    printf("Item removido com sucesso!\n");
    listarItensVetor(mochila, *totalItens);
}

void listarItensVetor(Item mochila[], int totalItens) {
    printf("\n--- LISTA DE ITENS (VETOR) ---\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("\n+----+--------------------------+--------------------+----------+\n");
    printf("| No | Nome                     | Tipo               | Quantidade |\n");
    printf("+----+--------------------------+--------------------+----------+\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("| %2d | %-24s | %-18s | %8d |\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("+----+--------------------------+--------------------+----------+\n");
    printf("Total: %d de %d itens\n", totalItens, MAX_ITENS);
}

int buscarSequencialVetor(Item mochila[], int totalItens, char nomeBusca[]) {
    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item mochila[], int totalItens) {
    Item temp;
    // Bubble Sort
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item mochila[], int totalItens, char nomeBusca[]) {
    int esquerda = 0;
    int direita = totalItens - 1;
    
    while (esquerda <= direita) {
        comparacoesBinaria++;
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            return meio;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

// ==================== FUNÇÕES PARA LISTA ENCADEADA ====================

void inserirItemLista(No **cabeca) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return;
    }
    
    printf("\n--- INSERIR ITEM (LISTA) ---\n");
    
    printf("Nome do item: ");
    fgets(novo->dados.nome, MAX_NOME, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    fgets(novo->dados.tipo, MAX_TIPO, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();
    
    if (novo->dados.quantidade <= 0) {
        printf("Quantidade invalida!\n");
        free(novo);
        return;
    }
    
    // Insere no inicio da lista
    novo->proximo = *cabeca;
    *cabeca = novo;
    
    printf("Item inserido com sucesso!\n");
    listarItensLista(*cabeca);
}

void removerItemLista(No **cabeca) {
    char nomeBusca[MAX_NOME];
    No *atual = *cabeca;
    No *anterior = NULL;
    
    printf("\n--- REMOVER ITEM (LISTA) ---\n");
    
    if (*cabeca == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }
    
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    printf("Item removido com sucesso!\n");
    listarItensLista(*cabeca);
}

void listarItensLista(No *cabeca) {
    No *atual = cabeca;
    int contador = 1;
    
    printf("\n--- LISTA DE ITENS (LISTA ENCADEADA) ---\n");
    
    if (cabeca == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    
    printf("\n+----+--------------------------+--------------------+----------+\n");
    printf("| No | Nome                     | Tipo               | Quantidade |\n");
    printf("+----+--------------------------+--------------------+----------+\n");
    
    while (atual != NULL) {
        printf("| %2d | %-24s | %-18s | %8d |\n", 
               contador++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("+----+--------------------------+--------------------+----------+\n");
}

int buscarSequencialLista(No *cabeca, char nomeBusca[]) {
    No *atual = cabeca;
    int posicao = 1;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("  Posicao: %d\n", posicao);
            printf("  Nome: %s\n", atual->dados.nome);
            printf("  Tipo: %s\n", atual->dados.tipo);
            printf("  Quantidade: %d\n", atual->dados.quantidade);
            return 1;
        }
        atual = atual->proximo;
        posicao++;
    }
    return 0;
}

void liberarLista(No **cabeca) {
    No *atual = *cabeca;
    No *proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}