#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comparacao.h"

int main()
{
    const int NUM_TESTES = 1000;
    const int CAPACIDADE = 10000;

    FilhaCom heap = {
        .item= malloc(CAPACIDADE * sizeof(int)),
        .capacidade = CAPACIDADE,
        .tamanho = 0
    };

    FilhaSem fila = {
        .elemento = malloc(CAPACIDADE * sizeof(int)),
        .capacidade = CAPACIDADE,
        .tamanho = 0,
    };

    FILE* saida = fopen("comparacoes.csv", "w");
    fprintf(saida, "Valor, Comparacoes_Heap, Comparacoes_Lista\n");

    int valor, comp_heap, comp_fila;
    for(int i = 0; i < NUM_TESTES; i++)
    {
        valor = rand() % 1000;
        comp_heap = 0;
        comp_fila = 0;

        inserir_heap(&heap, valor, &comp_heap);
        inserir_fila(&fila, valor, &comp_fila);

        fprintf(saida, "%d, %d, %d\n", valor, comp_heap, comp_fila);
    }

    printf("Arquivo comparacoes.csv gerado com succeso\n");

    fclose(saida);
    free(heap.item);
    free(fila.elemento);

    return 0;
}
