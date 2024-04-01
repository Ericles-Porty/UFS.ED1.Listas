#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *proxNo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *fim;
    int quantidade;
} tipoLista;

void criaLista(tipoLista *listaCircular)
{
    listaCircular->fim = NULL;
    listaCircular->quantidade = 0;
}

int insereNoFimDaLista(tipoLista *listaCircular, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (listaCircular->fim == NULL)
    {
        inserirElementoEmListaVazia(listaCircular, valor);
        return 1;
    }

    novoNo->dado = valor;
    novoNo->proxNo = listaCircular->fim->proxNo;

    listaCircular->fim->proxNo = novoNo;
    listaCircular->fim = novoNo;
    listaCircular->quantidade++;

    return 0;
}

int inserirNoInicioDaLista(tipoLista *listaCircular, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (listaCircular->fim == NULL)
    {
        inserirElementoEmListaVazia(listaCircular, valor);
        return 1;
    }

    novoNo->dado = valor;
    novoNo->proxNo = listaCircular->fim->proxNo;

    listaCircular->fim->proxNo = novoNo;
    listaCircular->quantidade++;

    return 0;
}
int inserirElementoEmListaVazia(tipoLista *listaCircular, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (novoNo == NULL)
        return 0;

    novoNo->dado = valor;
    novoNo->proxNo = novoNo;

    listaCircular->fim = novoNo;
    listaCircular->quantidade++;

    return 1;
}

void removerElementoDoInicio(tipoLista *listaCircular)
{
    tipoNo *aux;
    aux = listaCircular->fim->proxNo;
    listaCircular->fim->proxNo = aux->proxNo;

    if (listaCircular->quantidade == 1)
        listaCircular->fim == NULL;

    listaCircular->quantidade--;

    free(aux);

    return;
}

int zerarLista(tipoLista *listaCircular)
{
    tipoNo *aux;

    while (listaCircular->quantidade > 1)
    {
        aux = listaCircular->fim->proxNo;
        listaCircular->fim->proxNo = aux->proxNo;
        listaCircular->quantidade--;

        free(aux);
    }

    if (listaCircular->quantidade == 1)
        listaCircular->fim == NULL;

    return 1;
}

void printaLista(tipoLista *listaCircular)
{
    if (listaCircular->quantidade == 0)
    {
        printf("Não existe elementos.");
        return;
    }

    tipoNo *atual;
    atual = listaCircular->fim->proxNo;
    printf("\n%d", atual->dado);

    while (atual != listaCircular->fim)
    {
        atual = atual->proxNo;
        printf(" - %d ", atual->dado);
    }

    printf("\n");
}
int pesquisarElemento(tipoLista *listaCircular, int num)
{
    int index = 0;
    tipoNo *atual;
    atual = listaCircular->fim->proxNo;

    while (atual != listaCircular->fim)
    {
        if (atual->dado == num && index != 0)
            return index;

        atual = atual->proxNo;
        index++;
    }

    // Verifica se o último elemento é o que estamos procurando
    if (atual->dado == num && index != 0)
        return index;

    return 0;
}

int main()
{
    tipoLista lista;
    criaLista(&lista);
    int numero, dec, op;
    system("cls");
    do
    {
        printf("0 - Encerrar programa \n");
        printf("1 - Insere elemento em lista vazia \n");
        printf("2 - Insere elemento no inicio \n");
        printf("3 - Insere elemento no fim \n");
        printf("4 - Apaga elemento no inicio da lista \n");
        printf("5 - Pesquisa elemento na lista \n");
        printf("6 - Apaga primeiro elemento da lista \n");
        printf("10 - Printa lista \n");
        printf("Selecione uma opcao: ");
        scanf("%d", &op);
        system("cls");
        switch (op)
        {
        case 1:
            printf("Digite um numero: ");
            scanf("%d", &numero);
            dec = inserirElementoEmListaVazia(&lista, numero);
            if (dec == 0)
            {
                printf("Houve um erro\n");
            }
            else
            {
                printf("Inserido com sucesso\n");
            }

            break;

        case 2:
            printf("Digite um numero: ");
            scanf("%d", &numero);
            dec = inserirNoInicioDaLista(&lista, numero);
            if (dec == 1)
            {
                printf("Criamos um valor inicial\n");
            }
            else
            {
                printf("Inserido com sucesso\n");
            }
            break;

        case 3:
            printf("Digite um numero: ");
            scanf("%d", &numero);
            dec = insereNoFimDaLista(&lista, numero);
            if (dec == 1)
            {
                printf("Criamos um valor inicial\n");
            }
            else
            {
                printf("Inserido com sucesso\n");
            }
            break;
        case 4:

            dec = zerarLista(&lista);
            if (dec == 0)
            {
                printf("Houve um erro\n");
            }
            else
            {
                printf("Apagado com sucesso\n");
            }
            break;
        case 5:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &numero);
            dec = pesquisarElemento(&lista, numero);
            if (dec != 0)
                printf("Elemento achado na posicao: %d\n", dec);
            else
                printf("Nao foi possivel achar o elemento.");
            break;
        case 6:
            removerElementoDoInicio(&lista);
            break;
        default:
            break;

        case 10:
            printaLista(&lista);
            break;
        }

    } while (op != 0);
    return 0;
}