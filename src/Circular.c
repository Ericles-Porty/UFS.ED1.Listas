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
    int quant;
} tipoLista;

void criaLista(tipoLista *listaCirc)
{
    listaCirc->fim = NULL;
    listaCirc->quant = 0;
}

int insereNoFimDaLista(tipoLista *listaCirc, int num)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (listaCirc->fim == NULL)
        inserirElementoEmListaVazia(listaCirc, num);
    else
    {
        novoNo->dado = num;
        novoNo->proxNo = listaCirc->fim->proxNo;
        listaCirc->fim->proxNo = novoNo;
        listaCirc->fim = novoNo;
        listaCirc->quant++;
        return 0;
    }
}

int inserirNoInicioDaLista(tipoLista *listaCirc, int num)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (listaCirc->fim == NULL)
        inserirElementoEmListaVazia(listaCirc, num);
    else
    {
        novoNo->dado = num;
        novoNo->proxNo = listaCirc->fim->proxNo;
        listaCirc->fim->proxNo = novoNo;
        listaCirc->quant++;
        return 0;
    }
}
int inserirElementoEmListaVazia(tipoLista *listaCirc, int num)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    novoNo->dado = num;
    novoNo->proxNo = novoNo;
    listaCirc->fim = novoNo;
    listaCirc->quant++;
    return 1;
}

void removerElementoDoInicio(tipoLista *listaCirc)
{
    tipoNo *aux;
    
        aux = listaCirc->fim->proxNo;
        listaCirc->fim->proxNo = aux->proxNo;
        if (listaCirc->quant == 1)
            listaCirc->fim == NULL;
        listaCirc->quant--;
        free(aux);
    
    return;
}

int zerarLista(tipoLista *listaCirc)
{
    tipoNo *aux;
    while (listaCirc->quant > 0)
    {
        aux = listaCirc->fim->proxNo;
        listaCirc->fim->proxNo = aux->proxNo;
        if (listaCirc->quant == 1)
            listaCirc->fim == NULL;
        listaCirc->quant--;
        free(aux);
    }
    return 1;
}

void printaLista(tipoLista *listaCirc)
{
    if (listaCirc->quant == 0)
    {
        printf("Não existe elementos.");
        return;
    }

    tipoNo *atual;
    atual = listaCirc->fim->proxNo;
    printf("\n%d", atual->dado);
    while (atual != listaCirc->fim)
    {
        atual = atual->proxNo;
        printf(" - %d ", atual->dado);
    }
    printf("\n");
}
int pesquisarElemento(tipoLista *listaCirc, int num)
{
    int contador = 0;
    tipoNo *atual;
    atual = listaCirc->fim->proxNo;
    while (atual != listaCirc->fim)
    {
        if (atual->dado == num && contador != 0)
        {
            return contador;
        }
        atual = atual->proxNo;
        contador++;
    }
    if (atual->dado == num && contador != 0)
        return contador;

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