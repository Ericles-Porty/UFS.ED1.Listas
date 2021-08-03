#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maximo = 30;
int quantidade = 0;
int ordenada = 0;
int qSort(int *vetor, int inicio, int fim);
int *criaLista()
{
    int *lista;
    lista = malloc(maximo * sizeof(int));
    if (lista)
        return lista;
    else
    {
        printf("\nAconteceu algum problema. A lista nao foi alocada.");
        exit(1);
    }
}

int buscaBinaria(int *vetor, int chave)
{
    int i = quantidade;
    int ini = 0;
    int fim = quantidade;
    int meio = trunc((ini + fim) / 2);
    while(i >= 0)
    {
        if (chave == vetor[meio])
        {
            return meio;
        }
        else if (chave > vetor[meio])
        {
            ini = meio;
        }
        else if (chave < vetor[meio])
        {
            fim = meio;
        }
        i--;
        meio = trunc((ini + fim) / 2);
    }
    return -1;
}
int insereNaoOrd(int *lista)
{
    ordenada = 1;
    if (quantidade < maximo)
    {
        printf("\nDigite um inteiro:");
        scanf("%d", &lista[quantidade++]);
        return 1;
    }

    return 0;
}

void mostraLista(int *lista)
{
    for (int x = 0; x < quantidade; x++)
    {
        printf("%5d", lista[x]);
    }
}

int pesqSequencial(int *lista, int chave)
{
    for (int x = 0; x < quantidade; x++)
        if (chave == lista[x])
            return x;
    return -1;
}

int removeNaoOrd(int *lista, int chave)
{
    int aux;
    aux = pesqSequencial(lista, chave);
    if (aux != -1)
    {
        lista[aux] = lista[quantidade - 1];
        quantidade--;
        return 1;
    }
    return 0;
}
int removeOrd(int *lista, int chave)
{
    int aux;
    aux = pesqSequencial(lista, chave);
    if (aux != -1)
    {
        while (aux < quantidade - 1)
        {
            lista[aux] = lista[aux + 1];
            aux++;
        }
        quantidade--;
        return 1;
    }
    return 0;
}
int menorSequen(int *vetor, int chave)
{
    if (chave < vetor[0])
    {
        return 0;
    }
    else
    {
        int i = 1;
        while (vetor[i] < chave && i < quantidade)
        {
            i++;
        }
        return i;
    }
}

int insereOrd(int *lista, int chave)
{
    int aux;
    int fim = quantidade;
    if (ordenada)
    {
        aux = qSort(lista, 0, quantidade - 1);
    }
    aux = menorSequen(lista, chave);
    if (aux != -1)
    {
        while (fim > aux)
        {
            lista[fim] = lista[fim - 1];
            fim--;
        }
        lista[aux] = chave;
        quantidade++;
        return 1;
    }
    return 0;
}
int qSort(int *vetor, int inicio, int fim)
{
    ordenada = 0;
    int i, j, x, aux;
    i = inicio;
    j = fim;
    x = vetor[i];
    do
    {
        while (vetor[i] < x && i < fim)
            i++;
        while (vetor[j] > x && j > inicio)
            j--;
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (inicio < j)
        qSort(vetor, inicio, j);
    if (i < fim)
        qSort(vetor, i, fim);
    return 1;
}
void main()
{
    int *vetor;
    int op, aux, resp;
    vetor = criaLista();
    do
    {
        printf("\nEscolha uma opcao:");
        printf("\n1 - Insere elemento em lista nao ordenada");
        printf("\n2 - insere elemento em lista ordenada");
        printf("\n3 - Pesquisa elemento da lista");
        printf("\n4 - Ordena os elementos da lista");
        printf("\n5 - Remocao nao ordenada");
        printf("\n6 - Remocao ordenada");
        printf("\n7 - Exibe elementos da lista");
        printf("\n8 - Pesquisa binaria dos elementos da lista");
        printf("\n0 - Sair do programa");
        printf("\nDigite sua opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            resp = insereNaoOrd(vetor);
            if (resp)
                printf("\nInsercao realizada");
            else
                printf("\nInsercao nao realizada");
            break;

        case 2:
            if (quantidade < maximo)
            {
                if (quantidade != 0)
                {

                    printf("\nDigite o elemento a ser inserido ordenadamente:");
                    scanf("%d", &aux);
                    resp = insereOrd(vetor, aux);
                }
                else
                {
                    resp = insereNaoOrd(vetor);
                }
                if (resp)
                    printf("\nInsercao realizada");
                else
                    printf("\nInsercao nao realizada");
            }
            else
            {
                printf("\nVetor cheio");
            }
            break;
        case 3:
            printf("\nDigite o elemento a ser buscado:");
            scanf("%d", &aux);
            resp = pesqSequencial(vetor, aux);
            if (resp != -1)
                printf("\nElemento encontrado na posicao %d", resp);
            else
                printf("\nElemento nao encontrado");
            break;
        case 4:
            resp = qSort(vetor, 0, quantidade - 1);
            if (resp)
                printf("\nOrdenacao realizada");
            else
                printf("\nOrdenacao nao realizada");
            break;
        case 5:
            printf("\nDigite o elemento a ser removido:");
            scanf("%d", &aux);
            resp = removeNaoOrd(vetor, aux);
            if (resp)
                printf("\nRemocao realizada");
            else
                printf("\nRemocao nao realizada");
            break;
        case 6:
            printf("\nDigite o elemento a ser removido:");
            scanf("%d", &aux);
            resp = removeOrd(vetor, aux);
            if (resp)
                printf("\nRemocao realizada");
            else
                printf("\nRemocao nao realizada");
            break;
        case 7:
            mostraLista(vetor);
            break;
        case 8:
            printf("\nDigite o elemento a ser buscado: ");
            scanf("%i", &aux);
            resp = buscaBinaria(vetor, aux);
            if (resp != -1)
                printf("\nValor encontrado na posicao: %i", resp);
            else
                printf("\nValor nao encontrado");
            break;
        case 0:
            printf("\nEncerrando programa.");
            break;
        default:
            printf("\nOpcao invalida!");
        }
    } while (op != 0);
    free(vetor);
}