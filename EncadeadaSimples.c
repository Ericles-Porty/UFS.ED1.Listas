#include <stdio.h>
#include <stdlib.h>

/*Implementação de lista encadeada feita em sala*/

/*Estrutura que representa um nó da lista*/
typedef struct no
{
    int dado;
    struct no *proximo;
} tipoNo;

/*Estrutura que guarda as informações de uma lista encadeada*/
typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quantidade;
} tipoLista;

/*Função que faz a inicialização da lista encadeada*/
void inicializa(tipoLista *lista)
{
    lista->inicio = NULL;
    lista->fim->dado = NULL;
    lista->quantidade = 0;
}

/*Função que faz a inserção de um nó em uma lista vazia*/
int insereListaVazia(tipoLista *lista, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (novoNo == NULL)
        return 0;

    novoNo->dado = valor;
    novoNo->proximo = NULL;

    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->quantidade++;

    return 1;
}

/*Função que percorre a lista exibindo todos os seus dados*/
void exibeLista(tipoLista *lista)
{
    tipoNo *atual; /*Variável que será usada para percorrer a lista*/
    atual = lista->inicio;

    printf("\nLista encadeada: ");

    while (atual != NULL)
    {
        printf("%8d", atual->dado);
        atual = atual->proximo;
    }
}

/*Função que recebe um valor e pesquisa se ele está na lista, retornando sua posição*/
/*Obs: está sendo considerado que a primeira posição é igual a 1*/
int buscaDado(tipoLista *lista, int valor)
{
    if (lista->inicio == NULL)
        return -1;

    tipoNo *atual;
    atual = lista->inicio;

    int index = 0;
    while (atual != NULL)
    {
        if (atual->dado == valor)
            return index;

        atual = atual->proximo;
        index++;
    }

    return -1;
}

/*Função que insere um nó na frente de uma lista encadeada*/
int insereNaFrente(tipoLista *lista, int valor)
{
    if (lista->inicio == NULL)
    {
        insereListaVazia(lista, valor);
        return 1;
    }

    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (novoNo == NULL)
        return 0;

    novoNo->dado = valor;
    novoNo->proximo = lista->inicio;

    lista->inicio = novoNo;
    lista->quantidade++;

    return 1;
}

/*Função para inserir elemento no fim da lista encadeada*/
int insereNoFim(tipoLista *lista, int valor)
{
    if (lista->inicio == NULL)
    {
        insereListaVazia(lista, valor);
        return 1;
    }

    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(novoNo));

    if (novoNo == NULL)
        return 0;

    novoNo->dado = valor;
    novoNo->proximo = NULL;

    lista->fim->proximo = novoNo;
    lista->fim = novoNo;
    lista->quantidade++;

    return 1;
}

/*Função que remove primeiro elemento da lista encadeada*/
void removeDaFrente(tipoLista *lista)
{
    tipoNo *aux;
    aux = lista->inicio;
    lista->inicio = lista->inicio->proximo;

    if (lista->quantidade == 1)
        lista->fim = NULL;

    lista->quantidade--;
    free(aux);
}

/*Função que testa se a lista está vazia*/
int estaVazia(tipoLista *lista)
{
    if (lista->inicio == NULL)
        return 1;

    return 0;
}

/*Função que destroi a lista corretamente, fazendo a liberação da memória alocada*/
void destruirLista(tipoLista *lista)
{
    while (!estaVazia(lista))
        removeDaFrente(lista);
}

/*Função que remove o último elemento da lista*/
void removeDoFim(tipoLista *lista)
{
    tipoNo *atual, *antigo;
    atual = lista->inicio;

    if (atual->proximo != NULL)
    {
        while (atual->proximo != NULL)
        {
            antigo = atual;
            atual = atual->proximo;
        }

        antigo->proximo = NULL;
        lista->fim = antigo;
    }
    else
    {
        lista->inicio = NULL;
        lista->fim = NULL;
    }

    lista->quantidade--;
    free(atual);
}

/*Função que insere um valor na lista em posição específica recebida como parâmetro*/
/*Obs: Foi considerado que a primeira posição da lista é igual a 1*/
int insereEmPos(tipoLista *lista, int pos, int valor)
{
    tipoNo *novoNo, *atual;
    int index;

    if (pos > 0 && pos <= lista->quantidade + 1)
    {
        if (pos == 1)
        {
            insereNaFrente(lista, valor);
            return 1;
        }

        novoNo = (tipoNo *)malloc(sizeof(tipoNo));

        if (novoNo == NULL)
            return 0;

        atual = lista->inicio;

        for (index = 1; index < pos - 1; index++)
            atual = atual->proximo;

        novoNo->dado = valor;
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
        lista->quantidade++;

        if (novoNo->proximo == NULL)
            lista->fim = novoNo;
    }

    return 1;
}

void main()
{
    tipoLista lista;
    int aux, aux2, op;
    inicializa(&lista);
    do
    {
        printf("\nMenu");
        printf("\n2 - Insere na frente\n3 - Insere no fim");
        printf("\n4 - Remove da frente");
        printf("\n5 - Remove do fim");
        printf("\n6 - Insere no em determinada posicao");
        printf("\n7 - Busca posicao de elemento");
        printf("\n9 - Exibe a lista");
        printf("\n0 - Sai do programa");
        printf("\nDigite sua opcao:");
        scanf("%d", &op);
        switch (op)
        {
        case 2:
            printf("\nDigite outro numero inteiro:");
            scanf("%d", &aux);

            if (insereNaFrente(&lista, aux))
                printf("\nDado inserido com sucesso");
            else
                printf("\nInsercao nao efetuada");

            break;
        case 3:
            printf("\nDigite um numero inteiro:");
            scanf("%d", &aux);

            if (insereNoFim(&lista, aux))
                printf("\nDado inserido com sucesso");
            else
                printf("\nDado nao inserido");

            break;
        case 4:
            removeDaFrente(&lista);
            break;
        case 5:
            removeDoFim(&lista);
            break;
        case 6:
            printf("\nDigite o valor a ser inserido:");
            scanf("%d", &aux);

            printf("\nDigite a posicao em que deseja inserir:");
            scanf("%d", &aux2);

            if (insereEmPos(&lista, aux2, aux))
                printf("\nNo inserido com sucesso!");
            else
                printf("\nNo nao inserido!");

            break;
        case 7:
            printf("\nDigite o elemento que deseja buscar:");
            scanf("%d", &aux);

            aux2 = buscaDado(&lista, aux);

            if (aux2 == -1)
                printf("\nDado nao encontrado");
            else
                printf("Dado encontrado na posicao %d", aux2);

            break;
        case 9:
            exibeLista(&lista);
            break;
        case 0:
            printf("\nEncerrando programa");
            destruirLista(&lista);
            break;
        default:
            printf("\nOpcao invalida!");
        }
    } while (op != 0);
}