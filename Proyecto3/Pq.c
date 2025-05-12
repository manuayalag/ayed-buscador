#include <stdlib.h>
#include <stdio.h>
#include "Pq.h"

// Funciones auxiliares
int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

void swap(HeapItem* a, HeapItem* b) {
    HeapItem temp = *a;
    *a = *b;
    *b = temp;
}

// Crear una cola de prioridades
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    pq->items = malloc(sizeof(HeapItem) * capacity);
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// Reorganizar hacia arriba (heapify up)
void heapifyUp(PriorityQueue* pq, int index) {
    while (index != 0 && pq->items[parent(index)].score < pq->items[index].score) {
        swap(&pq->items[index], &pq->items[parent(index)]);
        index = parent(index);
    }
}

// Insertar un elemento con prioridad
void insertWithPriority(PriorityQueue* pq, HeapItem item) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->items = realloc(pq->items, sizeof(HeapItem) * pq->capacity);
    }
    pq->items[pq->size] = item;
    heapifyUp(pq, pq->size);
    pq->size++;
}

// Reorganizar hacia abajo (heapify down)
void heapifyDown(PriorityQueue* pq, int index) {
    int largest = index;
    int l = left(index);
    int r = right(index);

    if (l < pq->size && pq->items[l].score > pq->items[largest].score) {
        largest = l;
    }
    if (r < pq->size && pq->items[r].score > pq->items[largest].score) {
        largest = r;
    }
    if (largest != index) {
        swap(&pq->items[index], &pq->items[largest]);
        heapifyDown(pq, largest);
    }
}

// Extraer el elemento con mayor prioridad
HeapItem extractMax(PriorityQueue* pq) {
    if (pq->size == 0) {
        HeapItem empty = { 0, 0, 0 };
        return empty;
    }
    HeapItem root = pq->items[0];
    pq->items[0] = pq->items[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return root;
}

// Verificar si la cola está vacía
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Liberar la memoria de la cola de prioridades
void freePriorityQueue(PriorityQueue* pq) {
    free(pq->items);
    free(pq);
}
