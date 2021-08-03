#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *antNo;
    struct no *proxNo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

void exibeLista(tipoLista *listaEnc)
{
    tipoNo *atual; /*Variável que será usada para percorrer a lista*/
    atual = listaEnc->inicio;
    printf("\nLista encadeada: ");
    while (atual != NULL)
    {
        printf("\nValor : %8d", atual->dado);
        if (atual->antNo != NULL)
            printf("\nAnterior: %8d", atual->antNo->dado);
        if (atual->proxNo != NULL)
            printf("\nProximo: %8d", atual->proxNo->dado);
        atual = atual->proxNo;
    }
}

void inicializa(tipoLista *listaEnc)
{
    listaEnc->inicio = NULL;
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
}

int insereListaVazia(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    novoNo->antNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNaFrente(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = listaEnc->inicio;
        novoNo->antNo = NULL;
        listaEnc->inicio = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

int insereNoFim(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(novoNo));
        if (novoNo == NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = NULL;
        novoNo->antNo = listaEnc->fim;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
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
        //printf("\n4 - Remove da frente");
        //printf("\n5 - Remove do fim");
        //printf("\n6 - Insere no em determinada posicao");
        // printf("\n7 -  Busca posicao de elemento");
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
        /*case 4:
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
            if (aux2 = buscaDado(&lista, aux))
                printf("Dado encontrado na posicao %d", aux2);
            else
                printf("\nDado nao encontrado");
            break;*/
        case 9:
            exibeLista(&lista);
            break;
        case 0:
            printf("\nEncerrando programa");
            //destruirLista(&lista);
            break;
        default:
            printf("\nOpcao invalida!");
        }
    } while (op != 0);
}