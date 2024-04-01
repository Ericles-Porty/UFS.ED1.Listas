#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *anterior;
    struct no *proximo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quantidade;
} tipoLista;

void exibeLista(tipoLista *lista)
{
    tipoNo *atual;
    atual = lista->inicio;

    printf("\nLista encadeada: ");

    while (atual != NULL)
    {
        // O %8d é para formatar o valor ocupando 8 digitos
        printf("\nValor : %8d", atual->dado);

        if (atual->anterior != NULL)
            printf("\nAnterior: %8d", atual->anterior->dado);

        if (atual->proximo != NULL)
            printf("\nProximo: %8d", atual->proximo->dado);

        atual = atual->proximo;
    }
}

void inicializa(tipoLista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->quantidade = 0;
}

int insereListaVazia(tipoLista *lista, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (novoNo == NULL)
        return 0;

    novoNo->dado = valor;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->quantidade++;

    return 1;
}

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
    novoNo->anterior = NULL;

    lista->inicio = novoNo;
    lista->quantidade++;

    return 1;
}

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
    novoNo->anterior = lista->fim;

    lista->fim->proximo = novoNo;
    lista->fim = novoNo;
    lista->quantidade++;

    return 1;
}

int removeDaFrente(tipoLista *lista)
{
    if (lista->inicio == NULL)
        return 0;

    tipoNo *novoInicio;
    novoInicio = lista->inicio->proximo;

    lista->inicio->proximo->anterior = NULL;
    lista->inicio = novoInicio;
    lista->quantidade--;

    return 1;
}

int removeDoFim(tipoLista *lista)
{
    if (lista->inicio == NULL)
        return 0;

    tipoNo *novoFim;
    novoFim = lista->fim->anterior;

    novoFim->proximo = NULL;
    lista->fim = novoFim;
    lista->quantidade--;

    return 1;
}

int removeDaPosicao(tipoLista *lista, int posicao)
{
    if (lista->inicio == NULL)
        return 0;

    if (posicao < 0 || posicao > lista->quantidade)
        return 0;

    if (posicao == 0)
        return removeDaFrente(lista);

    if (posicao == lista->quantidade)
        return removeDoFim(lista);

    tipoNo *novoNo;
    novoNo = lista->inicio;

    for (int i = 0; i < posicao - 1; i++)
        novoNo = novoNo->proximo;

    novoNo->proximo->anterior = novoNo->proximo;
    lista->quantidade--;

    return 1;
}

int buscaSequencial(tipoLista *lista, int valor)
{
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

int destruiLista(tipoLista *lista)
{
    tipoNo *atual;
    tipoNo *proximo;

    atual = lista->inicio;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
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
        printf("\n7 -  Busca posicao de elemento");
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
            if (removeDaFrente(&lista))
                printf("\nDado removido com sucesso");
            else
                printf("\nLista vazia");

            break;
        case 5:
            if (removeDoFim(&lista))
                printf("\nDado removido com sucesso");
            else
                printf("\nLista vazia");

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

            aux2 = buscaSequencial(&lista, aux);

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