#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 100

typedef struct {
    int tempoProximoSpawn; // quando o inimigo vai aparecer
    int tipo; // 0, 1 ou 2
    int frequencia; // intervalo de tempo entre aparições
} Inimigo;

// Funções auxiliares
Inimigo* criarInimigo(int tempo, int tipo, int freq) {
    Inimigo* novo = malloc(sizeof(Inimigo));
    novo->tempoProximoSpawn = tempo;
    novo->tipo = tipo;
    novo->frequencia = freq;
    return novo;
}

// Heap
typedef struct {
    Inimigo* itens[MAX_HEAP];
    int tamanho;
} MinHeap;

MinHeap* criarHeap() {
    MinHeap* h = malloc(sizeof(MinHeap));
    h->tamanho = 0;
    return h;
}

void trocar(Inimigo** a, Inimigo** b) {
    Inimigo* temp = *a;
    *a = *b;
    *b = temp;
}

void subir(MinHeap* h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->itens[i]->tempoProximoSpawn < h->itens[pai]->tempoProximoSpawn) {
            trocar(&h->itens[i], &h->itens[pai]);
            i = pai;
        } else break;
    }
}

void descer(MinHeap* h, int i) {
    while (2*i + 1 < h->tamanho) {
        int esq = 2*i + 1, dir = 2*i + 2, menor = esq;
        if (dir < h->tamanho && h->itens[dir]->tempoProximoSpawn < h->itens[esq]->tempoProximoSpawn)
            menor = dir;
        if (h->itens[i]->tempoProximoSpawn > h->itens[menor]->tempoProximoSpawn) {
            trocar(&h->itens[i], &h->itens[menor]);
            i = menor;
        } else break;
    }
}

void inserir(MinHeap* h, Inimigo* inimigo) {
    h->itens[h->tamanho] = inimigo;
    subir(h, h->tamanho);
    h->tamanho++;
}

Inimigo* removerMin(MinHeap* h) {
    if (h->tamanho == 0) return NULL;
    Inimigo* min = h->itens[0];
    h->itens[0] = h->itens[--h->tamanho];
    descer(h, 0);
    return min;
}

// Main
int main() {
    MinHeap* heap = criarHeap();

    // Frequências diferentes para cada tipo
    inserir(heap, criarInimigo(3, 0, 3)); // tipo 0: aparece a cada 3s
    inserir(heap, criarInimigo(5, 1, 5)); // tipo 1: aparece a cada 5s
    inserir(heap, criarInimigo(7, 2, 7)); // tipo 2: aparece a cada 7s

    int tempoAtual = 0;
    int tempoFinal = 30; // simular até o tempo 30

    while (tempoAtual <= tempoFinal) 
    {
        // verifica se algum inimigo deve aparecer
        while (heap->tamanho > 0 && heap->itens[0]->tempoProximoSpawn <= tempoAtual) 
        {
            // se sim, remove do heap e mostra na tela
            Inimigo* inimigo = removerMin(heap);
            printf("Tempo %d: Inimigo tipo %d apareceu!\n", tempoAtual, inimigo->tipo);

            // Reagendar o próximo spawn desse tipo de inimigo
            inimigo->tempoProximoSpawn += inimigo->frequencia;
            inserir(heap, inimigo);
        }
        tempoAtual++;
    }

    free(heap);
    return 0;
}
