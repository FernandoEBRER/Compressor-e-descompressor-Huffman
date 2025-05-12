#ifndef COMPARACAO_H
#define COMPARACAO_H

typedef struct heap
{
    int* item;
    int capacidade;
    int tamanho;
}FilhaCom;

typedef struct fila 
{
    int* elemento;
    int capacidade;
    int tamanho;
}FilhaSem;

void inserir_heap(FilhaCom* heap, int valor, int* comp);
int extract_max_heap(FilhaCom* heap, int* comp);
void inserir_fila(FilhaSem* fila, int valor, int* comp);
int extract_max_fila(FilhaSem* fila, int* comp);

#endif