#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[30];
    int prioridade; // quanto maior, mais urgente
} Evento;

typedef struct {
    Evento eventos[MAX];
    int tamanho;
} MaxHeap;

void trocar(Evento *a, Evento *b) {
    Evento temp = *a;
    *a = *b;
    *b = temp;
}

void subir(MaxHeap *heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (heap->eventos[i].prioridade > heap->eventos[pai].prioridade) {
            trocar(&heap->eventos[i], &heap->eventos[pai]);
            i = pai;
        } else break;
    }
}

void descer(MaxHeap *heap, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < heap->tamanho && heap->eventos[esquerda].prioridade > heap->eventos[maior].prioridade)
        maior = esquerda;
    if (direita < heap->tamanho && heap->eventos[direita].prioridade > heap->eventos[maior].prioridade)
        maior = direita;
    
    if (maior != i) {
        trocar(&heap->eventos[i], &heap->eventos[maior]);
        descer(heap, maior);
    }
}

void inserir(MaxHeap *heap, char *nome, int prioridade) {
    if (heap->tamanho == MAX) {
        printf("Heap cheio!\n");
        return;
    }
    Evento novo;
    strcpy(novo.nome, nome);
    novo.prioridade = prioridade;
    heap->eventos[heap->tamanho] = novo;
    subir(heap, heap->tamanho);
    heap->tamanho++;
}

Evento remover(MaxHeap *heap) {
    if (heap->tamanho == 0) {
        printf("Heap vazio!\n");
        Evento vazio = {"", -1};
        return vazio;
    }
    Evento raiz = heap->eventos[0];
    heap->eventos[0] = heap->eventos[heap->tamanho - 1];
    heap->tamanho--;
    descer(heap, 0);
    return raiz;
}

int main() {
    MaxHeap heap;
    heap.tamanho = 0;

    inserir(&heap, "Explosao", 90);
    inserir(&heap, "Ataque inimigo", 70);
    inserir(&heap, "Curar personagem", 50);
    inserir(&heap, "Coletar item", 20);

    printf("Simulando eventos:\n");
    while (heap.tamanho > 0) {
        Evento e = remover(&heap);
        printf("Executando evento: %s (prioridade %d)\n", e.nome, e.prioridade);
    }

    return 0;
}
