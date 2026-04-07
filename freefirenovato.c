#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Definicao da struct Item
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Prototipos das funcoes
void cadastrarItem(Item mochila[], int *totalItens);
void removerItem(Item mochila[], int *totalItens);
void listarItens(Item mochila[], int totalItens);
void buscarItem(Item mochila[], int totalItens);
void exibirMenu();
void limparBuffer();

int main() {
    Item mochila[MAX_ITENS];  // Vetor de structs com capacidade para 10 itens
    int totalItens = 0;       // Contador de itens cadastrados
    int opcao;
    
    printf("========================================\n");
    printf("   SISTEMA DE INVENTARIO - MOCHILA\n");
    printf("========================================\n\n");
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 5:
                printf("\nSaindo do sistema de inventario...\n");
                printf("Boa sorte na sua jornada!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 5 && opcao >= 1 && opcao <= 4) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
        
    } while(opcao != 5);
    
    return 0;
}

//Funcao para exibir o menu principal

void exibirMenu() {
    printf("\n----------------------------------------\n");
    printf("            MENU PRINCIPAL\n");
    printf("----------------------------------------\n");
    printf("1 - Cadastrar item na mochila\n");
    printf("2 - Remover item da mochila\n");
    printf("3 - Listar todos os itens\n");
    printf("4 - Buscar item pelo nome\n");
    printf("5 - Sair\n");
    printf("----------------------------------------\n");
}

//Funcao para limpar o buffer do teclado

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Funcao para cadastrar um novo item na mochila

void cadastrarItem(Item mochila[], int *totalItens) {
    printf("\n--- CADASTRO DE ITEM ---\n");
    
    // Verifica se a mochila esta cheia
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Capacidade maxima de %d itens atingida.\n", MAX_ITENS);
        printf("Remova algum item antes de cadastrar um novo.\n");
        return;
    }
    
    // Leitura do nome do item
    printf("Nome do item: ");
    fgets(mochila[*totalItens].nome, MAX_NOME, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';
    
    // Validacao de nome vazio
    if (strlen(mochila[*totalItens].nome) == 0) {
        printf("Nome invalido! Item nao cadastrado.\n");
        return;
    }
    
    // Leitura do tipo do item
    printf("Tipo do item (arma/municao/cura/ferramenta): ");
    fgets(mochila[*totalItens].tipo, MAX_TIPO, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';
    
    // Leitura da quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    limparBuffer();
    
    // Validacao de quantidade
    if (mochila[*totalItens].quantidade <= 0) {
        printf("Quantidade invalida! Deve ser maior que zero.\n");
        return;
    }
    
    (*totalItens)++;
    printf("\nItem cadastrado com sucesso!\n");
    
    // Lista os itens apos cada operacao
    listarItens(mochila, *totalItens);
}

//Funcao para remover um item da mochila

void removerItem(Item mochila[], int *totalItens) {
    char nomeBusca[MAX_NOME];
    int indiceEncontrado = -1;
    
    printf("\n--- REMOCAO DE ITEM ---\n");
    
    if (*totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }
    
    // Lista os itens atuais
    listarItens(mochila, *totalItens);
    
    // Leitura do nome do item a ser removido
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial pelo item
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }
    
    if (indiceEncontrado == -1) {
        printf("Item '%s' nao encontrado na mochila!\n", nomeBusca);
        return;
    }
    
    // Remove o item deslocando os elementos seguintes
    for (int i = indiceEncontrado; i < *totalItens - 1; i++) {
        strcpy(mochila[i].nome, mochila[i + 1].nome);
        strcpy(mochila[i].tipo, mochila[i + 1].tipo);
        mochila[i].quantidade = mochila[i + 1].quantidade;
    }
    
    (*totalItens)--;
    printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
    
    // Lista os itens apos cada operacao
    if (*totalItens > 0) {
        listarItens(mochila, *totalItens);
    } else {
        printf("\nMochila agora esta vazia.\n");
    }
}

//Funcao para listar todos os itens da mochila

void listarItens(Item mochila[], int totalItens) {
    printf("\n--- LISTA DE ITENS NA MOCHILA ---\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }
    
    printf("\n");
    printf("+----+--------------------------+--------------------+----------+\n");
    printf("| No | Nome                     | Tipo               | Quantidade |\n");
    printf("+----+--------------------------+--------------------+----------+\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("| %2d | %-24s | %-18s | %8d |\n", 
               i + 1, 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    
    printf("+----+--------------------------+--------------------+----------+\n");
    printf("Total de itens: %d de %d\n", totalItens, MAX_ITENS);
}

//Funcao para buscar um item pelo nome (busca sequencial)
void buscarItem(Item mochila[], int totalItens) {
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    
    printf("\n--- BUSCA DE ITEM ---\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }
    
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    printf("\n--- RESULTADO DA BUSCA ---\n");
    
    // Busca sequencial
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            printf("  Posicao na mochila: %d\n", i + 1);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila!\n", nomeBusca);
    }
}