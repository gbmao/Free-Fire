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

typedef struct Node
{
    int root;
    struct Item thisItem;
    struct Node *nextNode;
} Node;

Node *root = NULL; // inicia um root

struct Item *playerBag; // guarda os itens aqui dentro

void addItemToLinkedListRoot(struct Item p, struct Node *node);

void showBag();
void gameLogic(int search);
struct Item addItem(); // create bag and populate with itens

void clearInput();
int search;

int main(int argc, char *argv[])
{

    // Menu principal com opções:
    // 1. Adicionar um item
    search = atoi(argv[1]);
    printf("ei: %d\n", search);
    while (1)
    {
        gameLogic(search);
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

void binarySearch(char iName[], struct Item *bag, int start, int end)
{
    if (start > end)
    {
        printf("Item: %s nao encontrado\n", iName);
        return;
    }

    int mid = (start + end) / 2;

    int cmp = strcmp(bag[mid].name, iName);
    if (cmp == 0)
    {
        printf("%s e o item de numero: %d\n", bag[mid].name, mid);
        printf("\n\nPressione enter para voltar...\n");
        getchar();
    }
    else if (cmp < 0)
    {
        binarySearch(iName, bag, mid + 1, end); 
    }
    else
    {
        binarySearch(iName, bag, start, mid - 1); 
    }
}

// void binarySearch(char iName[], struct Item *bag)
// {
//     int half = itemCount / 2;
//     struct Item *tempBag = NULL;

//     if (strcmp(bag[half].name, iName) == 0)
//     {
//         printf("%s e o item de numero: %d\n", bag[half].name, half);
//         printf("\n\nPressione enter para voltar...\n");
//         getchar();
//         return;
//     }
//     else if (half < 2)
//     {
//         printf("Item: %s nao encontrado\n", iName);
//         printf("\n\nPressione enter para voltar...\n");
//         getchar();
//         return;
//     }
//     else if ((strcmp(bag[half].name, iName) < 0))
//     {
//         // bag half vem antes de iName
//         tempBag = malloc((itemCount - half) * sizeof(Item));
//         for (int i = half, j = 0; i < itemCount; i++, j++)
//         {
//             tempBag[j] = bag[i];
//         }
//         binarySearch(iName, tempBag);
//     }
//     else if ((strcmp(bag[half].name, iName) > 0))
//     {
//         // bag vem depois
//         tempBag = malloc(half * sizeof(Item));
//         // for (int i = 0; i < half; i++)
//         // {
//         //     tempBag[i] = bag[i];
//         // }
//         tempBag = bag;
//         binarySearch(iName, tempBag);
//     }
// }

void bubbleSort(struct Item *bag)
{
    Item temp;
    for (int j = 0; j < itemCount - 1; j++)
    {
        for (int i = 0; i < itemCount - 1; i++)
        {
            if (strcmp(bag[i].name, bag[i + 1].name) > 0)
            {
                temp = bag[i + 1];
                bag[i + 1] = bag[i];
                bag[i] = temp;
            }
        }
    }
}

// adiciona item para lista encadeada

void addItemToLinkedListRoot(struct Item p, struct Node *node)
{

    if (root == NULL)
    {

        // criar um root
        root = malloc(sizeof(Node));
        root->thisItem = p;
        root->nextNode = NULL;
        root->root = 1;
        itemCount++;
        printf("%-15s| %-15s| %-15d\n", root->thisItem.name, root->thisItem.type, root->thisItem.quantity);
        return;
    }
    else if (node->nextNode == NULL)
    {
        // cria um nextNode

        node->nextNode = malloc(sizeof(Node));

        node->nextNode->thisItem = p;

        node->nextNode->root = 0;

        node->nextNode->nextNode = NULL;
        printf("Item criado!\n");
        itemCount++;
        printf("%-15s| %-15s| %-15d\n", node->nextNode->thisItem.name, node->nextNode->thisItem.type, node->nextNode->thisItem.quantity);
    }
    else
    {
        // entra no next

        addItemToLinkedListRoot(p, node->nextNode);
    }
}

void removeLinkedListItem(char name[], struct Node *node)
{

    if (node->root == 1 && strcmp(node->thisItem.name, name) == 0)
    {
        struct Node *temp = root; // aponta para o node root, para se liberar sua memoria

        if (node->nextNode == NULL)
        {
            root = NULL;
            printf("A lista ficou vazia\n");
        }
        else
        {
            root = root->nextNode;
            root->root = 1;
            printf("%s virou o item numero 1\n", root->thisItem.name);
            free(temp);
            temp = NULL;
            itemCount--;
        }
    }
    else if (node->nextNode == NULL)
    {
        printf("Item nao existe\n");
        return;
    }
    else if (strcmp(node->nextNode->thisItem.name, name) == 0)
    {
        struct Node *temp = node->nextNode;
        if (node->nextNode->nextNode == NULL)
        {
            node->nextNode = NULL;
        }
        else
        {
            node->nextNode = node->nextNode->nextNode;
            printf("deletado\n");
            free(temp);
            temp = NULL;

            itemCount--;
        }
    }
    else
    {
        removeLinkedListItem(name, node->nextNode);
    }
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

int showMenu()
{
    int response;
    printf("===============================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("===============================================\n");
    printf("Itens na Mochila: %d/%d \n\n", itemCount, MAX_ITEM);

    printf("1. Adicionar Item(Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por nome\n");
    printf("0 - Sair\n");
    printf("--------------------------------------\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &response);
    clearInput();
    return response;
}

void gameLogic(int search)
{

    switch (showMenu())
    {
    case 0:
        printf("Saindo........\n");
        exit(0);
        break;
    case 1:

        if (itemCount == 10)
        {
            printf("A Mochila esta vazia!\n");
        }
        else
        {
            if (search == 1)
            {

                addItemToBag(addItem());
            }
            else
            {

                addItemToLinkedListRoot(addItem(), root);
            }
        }
        break;

    case 2:
        printf("Digite o nome do item a ser deletado: ");
        char iName[STRING_SIZE];
        scanf("%s", iName);
        clearInput();
        if (search == 1)
        {

            removeItemFromBag(iName);
        }
        else
        {
            removeLinkedListItem(iName, root);
        }

        break;

    case 3:
        if (search == 1)
        {
            bubbleSort(playerBag);
        }
        showBag(search); // colcoar um if para decidir
        break;

    case 4:

        // searchByName();
        printf("Digite o nome do item a ser procurado: ");
        // char iName[STRING_SIZE];
        scanf("%s", iName);
        clearInput();

        binarySearch(iName, playerBag, 0, itemCount - 1);

        break;
    default:
        break;
    }
}
// printa a linked list de forma recursiva
void printLinkedList(struct Node *node)
{

    printf("%-15s| %-15s| %-15d\n", node->thisItem.name, node->thisItem.type, node->thisItem.quantity);
    printf("-------------------------------------------------\n");

    if (node->nextNode != NULL)
    {
        printLinkedList(node->nextNode);
    }
}

void showBag(int tipoBag)
{

    printf("--- ITENS NA MOCHILA (%d/%d) ---\n", itemCount, MAX_ITEM);
    printf("-------------------------------------------------\n");
    printf("%-15s| %-15s| %-15s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-------------------------------------------------\n");

    if (tipoBag == 1)
    {
        for (int i = 0; i < itemCount; i++)
        {
            printf("%-15s| %-15s| %-15d\n", playerBag[i].name, playerBag[i].type, playerBag[i].quantity);
            printf("-------------------------------------------------\n");
        }
    }
    else if (tipoBag == 0)
    {
        if (root == NULL)
        {
            printf("Lista esta vazia\n");
        }
        else
        {

            printLinkedList(root);
        }
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