#include <stdio.h>
#include <stdlib.h>

/*Implementação de lista encadeada feita em sala*/

/*Estrutura que representa um nó da lista*/
typedef struct no
{
    int dado;
    struct no *proxNo;
} tipoNo;

/*Estrutura que guarda as informações de uma lista encadeada*/
typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

/*Função que faz a inicialização da lista encadeada*/
void inicializa(tipoLista *listaEnc)
{
    listaEnc->inicio = NULL;
    listaEnc->fim->dado = NULL;
    listaEnc->quant = 0;
}

/*Função que faz a inserção de um nó em uma lista vazia*/
int insereListaVazia(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

/*Função que percorre a lista exibindo todos os seus dados*/
void exibeLista(tipoLista *listaEnc)
{
    tipoNo *atual; /*Variável que será usada para percorrer a lista*/
    atual = listaEnc->inicio;
    printf("\nLista encadeada: ");
    while (atual != NULL)
    {
        printf("%8d", atual->dado);
        atual = atual->proxNo;
    }
}

/*Função que recebe um valor e pesquisa se ele está na lista, retornando sua posição*/
/*Obs: está sendo considerado que a primeira posição é igual a 1*/
int buscaDado(tipoLista *listaEnc, int valor)
{
    tipoNo *atual;
    int cont = 1;
    atual = listaEnc->inicio;
    while (atual != NULL)
    {
        if (atual->dado == valor)
            return cont;
        atual = atual->proxNo;
        cont++;
    }
    return 0;
}

/*Função que insere um nó na frente de uma lista encadeada*/
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
        listaEnc->inicio = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

/*Função para inserir elemento no fim da lista encadeada*/
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
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
    }
}

/*Função que remove primeiro elemento da lista encadeada*/
void removeDaFrente(tipoLista *listaEnc)
{
    tipoNo *aux;
    aux = listaEnc->inicio;
    listaEnc->inicio = listaEnc->inicio->proxNo;
    if (listaEnc->quant == 1)
        listaEnc->fim = NULL;
    listaEnc->quant--;
    free(aux);
}

/*Função que testa se a lista está vazia*/
int estaVazia(tipoLista *listaEnc)
{
    if (listaEnc->inicio == NULL)
        return 1;
    else
        return 0;
}

/*Função que destroi a lista corretamente, fazendo a liberação da memória alocada*/
void destruirLista(tipoLista *listaEnc)
{
    while (!estaVazia(listaEnc))
        removeDaFrente(listaEnc);
}

/*Função que remove o último elemento da lista*/
void removeDoFim(tipoLista *listaEnc)
{
    tipoNo *atual, *antigo;
    atual = listaEnc->inicio;
    if (atual->proxNo != NULL)
    {
        while (atual->proxNo != NULL)
        {
            antigo = atual;
            atual = atual->proxNo;
        }
        antigo->proxNo = NULL;
        listaEnc->fim = antigo;
    }
    else
    {
        listaEnc->inicio = NULL;
        listaEnc->fim = NULL;
    }
    listaEnc->quant--;
    free(atual);
}

/*Função que insere um valor na lista em posição específica recebida como parâmetro*/
/*Obs: Foi considerado que a primeira posição da lista é igual a 1*/
int insereEmPos(tipoLista *listaEnc, int pos, int valor)
{
    tipoNo *novoNo, *atual;
    int x;
    if (pos > 0 && pos <= listaEnc->quant + 1)
    {
        if (pos == 1)
            insereNaFrente(listaEnc, valor);
        else
        {
            novoNo = (tipoNo *)malloc(sizeof(tipoNo));
            if (novoNo == NULL)
                return 0;
            novoNo->dado = valor;
            atual = listaEnc->inicio;
            for (x = 1; x < pos - 1; x++)
                atual = atual->proxNo;
            novoNo->proxNo = atual->proxNo;
            atual->proxNo = novoNo;
            listaEnc->quant++;
            if (novoNo->proxNo == NULL)
                listaEnc->fim = novoNo;
        }
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
            if (aux2 = buscaDado(&lista, aux))
                printf("Dado encontrado na posicao %d", aux2);
            else
                printf("\nDado nao encontrado");
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