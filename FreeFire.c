#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define STRING_SIZE 50

#define MAX_ITEM 10 // quantidade maxima de itens na mochila
int itemCount = 0;  // iniciar em 0 para ser incrementado a cada adição à mochila

typedef struct Item
{
    char name[STRING_SIZE];
    char type[STRING_SIZE];
    int quantity;

} Item;

struct Item *playerBag; // guarda os itens aqui dentro

void showBag();
void showMenu();
struct Item addItem(); // create bag and populate with itens

void clearInput();

int main()
{

    // Menu principal com opções:
    // 1. Adicionar um item
    while (1)
    {
        showMenu();
    }

    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    free(playerBag);
    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}
// return Item
struct Item addItem()
{
    struct Item p;
    char iName[STRING_SIZE];
    char iType[STRING_SIZE];
    int iQuantity;

    printf("--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf("%s", iName);
    clearInput();
    printf("Tipo do item: ");
    scanf("%s", iType);
    clearInput();
    printf("Quantidade: ");
    scanf("%d", &iQuantity);
    clearInput();

    strcpy(p.name, iName);
    // exit(1);
    strcpy(p.type, iType);
    p.quantity = iQuantity;

    return p;
}

// recebe Item , aloca espaço na memoria, adiciona Item pra mochila
void addItemToBag(struct Item p)
{
    itemCount++;
    playerBag = realloc(playerBag, itemCount * sizeof(struct Item));
    if (playerBag == NULL)
    {
        exit(1);
    }

    playerBag[itemCount - 1] = p;

    // printf("aqui: %s\n", bag[0].name);
    // printf("aqui: %s\n", bag[0].type);
    // printf("aqui: %d\n", bag[0].quantity);
}

void removeItemFromBag(char iName[])
{

    struct Item *transitionBag = NULL;
    int transitionBagSize = 0;

    for (int i = 0; i < itemCount; i++)
    {
        if (strcmp(playerBag[i].name, iName) == 0)
        {
            printf("%s foi deletado...\n", iName);
        }
        else
        {

            transitionBagSize++;

            transitionBag = realloc(transitionBag, transitionBagSize * sizeof(struct Item));
            transitionBag[transitionBagSize - 1] = playerBag[i];
        }
    }

    

    itemCount = 0;

    for (int i = 0; i < transitionBagSize; i++)
    {
        addItemToBag(transitionBag[i]);

    }
    free(transitionBag);
    printf("\n\nPressione enter para voltar...\n");
    getchar();
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

void showMenu()
{
    int response;
    printf("===============================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("===============================================\n");
    printf("Itens na Mochila: %d/%d \n\n", itemCount, MAX_ITEM);

    printf("1. Adicionar Item(Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("0 - Sair\n");
    printf("--------------------------------------\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &response);
    clearInput();
    switch (response)
    {
    case 0:
        printf("Saindo........\n");
        exit(0);
        break;
    case 1:
        // pŕimeiro checar se bag esta full
        if (itemCount == 10)
        {
            printf("A Mochila esta cheia!\n");
        }
        else
        {
            addItemToBag(addItem());
        }
        break;

    case 2:
        printf("Digite o nome do item a ser deletado: ");
        char iName[STRING_SIZE];
        scanf("%s", iName);
        clearInput();
        removeItemFromBag(iName);

        break;

    case 3:

        showBag();

    default:
        break;
    }
}

void showBag()
{

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", itemCount, MAX_ITEM);
    printf("-------------------------------------------------\n");
    printf("%-15s| %-15s| %-15s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < itemCount; i++)
    {
        printf("%-15s| %-15s| %-15d\n", playerBag[i].name, playerBag[i].type, playerBag[i].quantity);
        printf("-------------------------------------------------\n");
    }

    printf("\n\nPressione enter para voltar...\n");
    getchar();
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

void clearInput()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}