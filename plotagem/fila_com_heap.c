#include <stdio.h>
#include <stdlib.h>
#include "comparacao.h"


void trocar(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void inserir_heap(FilhaCom* heap, int valor, int* comp)
{
    if(heap->tamanho == heap->capacidade)
    {
        printf("Heap cheio!\n");
        return;
    }

    int i = heap->tamanho;
    heap->item[i] = valor;
    heap->tamanho++;

    while(i != 0)
    {
        int pai = (i - 1) / 2;
        (*comp)++;
        if(heap->item[pai] < heap->item[i])
        {
            trocar(&heap->item[i], &heap->item[pai]);
            i = pai;
        }
        else
        {
            break;
        }
    }
}


void max_heapify(FilhaCom* heap, int i, int* comp)
{
    int maior = i;
    int esq = 2*i + 1;
    int dir = 2*i +2;

    if(esq < heap->tamanho && heap->item[esq] > heap->item[maior])
    {
        maior = esq;
        (*comp)++;
    }
    if(dir < heap->tamanho && heap->item[dir] > heap->item[maior])
    {
        maior = dir;
        (*comp)++;
    }
    if(maior != i)
    {
        trocar(&heap->item[i], &heap->item[maior]);
        max_heapify(heap, maior, comp);
    }
}


int extract_max_heap(FilhaCom* heap, int* comp)
{
    if(heap->tamanho <= 0)
    {
        return -1;
    }

    int max = heap->item[0];
    heap->item[0] = heap->item[heap->tamanho - 1];
    heap->tamanho--;
    max_heapify(heap, 0, comp);

    return max;
}