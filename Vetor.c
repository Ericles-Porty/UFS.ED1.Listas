#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maximo = 30;
int quantidade = 0;
int isOrdenado = 1; // 0 - nao isOrdenado, 1 - isOrdenado
int quickSort(int *vetor, int inicio, int fim);
int *criaLista()
{
    int *lista;
    lista = malloc(maximo * sizeof(int));

    if (lista)
        return lista;

    printf("\nAconteceu algum problema. A lista nao foi alocada.");
    exit(1);
}

// Utilizamos busca sequencial quando a lista não está ordenada
int buscaSequencial(int *lista, int valor)
{
    for (int i = 0; i < quantidade; i++)
        if (valor == lista[i])
            return i;

    return -1;
}

// Podemos utilizar busca binaria quando a lista está ordenada
int buscaBinaria(int *vetor, int valor)
{
    int inicio = 0;
    int fim = quantidade;

    int meio = trunc((inicio + fim) / 2);

    int maxPassosNecessarios = ceil(log2(quantidade));

    for (int i = 0; i < maxPassosNecessarios; i++)
    {
        if (valor == vetor[meio])
            return meio;
        else if (valor > vetor[meio])
            inicio = meio;
        else if (valor < vetor[meio])
            fim = meio;

        meio = trunc((inicio + fim) / 2);
    }

    return -1;
}
int insereDesordenadamente(int *lista, int valor)
{
    isOrdenado = 0;
    if (quantidade >= maximo)
        return 0;

    lista[quantidade++] = valor;
    return 1;
}

void mostrarLista(int *lista)
{
    // O %5d é para formatar a impressão dos números inteiros de forma que fiquem alinhados na tela com 5 espaços de largura
    for (int i = 0; i < quantidade; i++)
        printf("%5d", lista[i]);
}

int removeDesordenadamente(int *lista, int valor)
{
    int index = buscaSequencial(lista, valor);

    if (index == -1)
        return 0;

    lista[index] = lista[quantidade - 1];
    quantidade--;
    isOrdenado = 0;
    return 1;
}

int removeOrdenadamente(int *lista, int chave)
{
    int index;

    if (isOrdenado)
        index = buscaBinaria(lista, chave);
    else
        index = buscaSequencial(lista, chave);

    if (index == -1)
        return 0;

    // Desloca os elementos para a esquerda a partir do elemento removido
    while (index < quantidade - 1)
    {
        lista[index] = lista[index + 1];
        index++;
    }

    quantidade--;
    return 1;
}
int menorSequencia(int *vetor, int valor)
{
    if (valor < vetor[0])
        return 0;

    int sequencia = 1;

    while (vetor[sequencia] < valor && sequencia < quantidade)
        sequencia++;

    return sequencia;
}

int insereOrdenadamente(int *lista, int valor)
{
    if (!isOrdenado)
        quickSort(lista, 0, quantidade - 1);

    int valorMenorSequencia = menorSequencia(lista, valor);

    if (valorMenorSequencia == -1)
        return 0;

    int indexFim = quantidade;

    // Desloca os elementos para a direita a partir do elemento que sera inserido
    while (indexFim > valorMenorSequencia)
    {
        lista[indexFim] = lista[indexFim - 1];
        indexFim--;
    }

    lista[valorMenorSequencia] = valor;
    quantidade++;
    return 1;
}
int quickSort(int *vetor, int inicio, int fim)
{
    int i, j, pivo, aux;

    i = inicio;
    j = fim;
    pivo = vetor[i];

    do
    {
        // Move o indice i ate encontrar um valor maior que o pivo
        while (vetor[i] < pivo && i < fim)
            i++;

        // Move o indice j ate encontrar um valor menor que o pivo
        while (vetor[j] > pivo && j > inicio)
            j--;

        // Se os indices ainda nao se cruzaram, troca os valores
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    // Chama a funcao recursivamente para as duas metades
    if (inicio < j)
        quickSort(vetor, inicio, j);

    if (i < fim)
        quickSort(vetor, i, fim);

    isOrdenado = 1;
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
            printf("\nDigite o elemento a ser inserido desordenadamente:");
            scanf("%d", &aux);
            resp = insereDesordenadamente(vetor, aux);

            if (resp)
                printf("\nInsercao realizada");
            else
                printf("\nInsercao nao realizada");

            break;
        case 2:
            if (quantidade >= maximo)
            {
                printf("\nVetor cheio");
                break;
            }

            printf("\nDigite o elemento a ser inserido ordenadamente:");
            scanf("%d", &aux);

            resp = insereOrdenadamente(vetor, aux);

            if (resp)
                printf("\nInsercao realizada");
            else
                printf("\nInsercao nao realizada");

            break;
        case 3:
            printf("\nDigite o elemento a ser buscado:");
            scanf("%d", &aux);

            resp = buscaSequencial(vetor, aux);

            if (resp == -1)
                printf("\nElemento nao encontrado");
            else
                printf("\nElemento encontrado na posicao %d", resp);

            break;
        case 4:
            resp = quickSort(vetor, 0, quantidade - 1);

            if (resp)
                printf("\nOrdenacao realizada");
            else
                printf("\nOrdenacao nao realizada");

            break;
        case 5:
            printf("\nDigite o elemento a ser removido:");
            scanf("%d", &aux);

            resp = removeDesordenadamente(vetor, aux);

            if (resp)
                printf("\nRemocao realizada");
            else
                printf("\nRemocao nao realizada");

            break;
        case 6:
            printf("\nDigite o elemento a ser removido:");
            scanf("%d", &aux);

            resp = removeOrdenadamente(vetor, aux);

            if (resp)
                printf("\nRemocao realizada");
            else
                printf("\nRemocao nao realizada");

            break;
        case 7:
            mostrarLista(vetor);
            break;
        case 8:
            printf("\nDigite o elemento a ser buscado: ");
            scanf("%i", &aux);

            resp = buscaBinaria(vetor, aux);

            if (resp == -1)
                printf("\nValor nao encontrado");
            else
                printf("\nValor encontrado na posicao: %i", resp);

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