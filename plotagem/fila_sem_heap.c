#include <stdio.h>
#include <stdlib.h>
#include "comparacao.h"


void inserir_fila(FilhaSem* fila, int valor, int* comp)
{
    if(fila->tamanho == fila->capacidade)
    {
        printf("Fila cheia!\n");
        return;
    }
    
    int i = fila->tamanho - 1;
    while(i >= 0 && fila->elemento[i] < valor)
    {
        (*comp)++;
        fila->elemento[i + 1] = fila->elemento[i];
        i--;
    }

    fila->elemento[i + 1] = valor;
    fila->tamanho++;
}


int extract_max_fila(FilhaSem* fila, int* comp)
{
    if(fila->tamanho <= 0)
    {
        return -1;
    }

    int max = fila->elemento[0];

    for( int i = 0; i < fila->tamanho; i++)
    {
        (*comp)++;
        fila->elemento[i] = fila->elemento[i+1];
    }

    fila->tamanho--;
    return max;
}