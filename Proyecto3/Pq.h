#pragma once
#ifndef PQ_H
#define PQ_H

typedef struct {
    long position;      // Posición en el archivo
    int lineNumber;     // Línea en la que aparece
    int score;          // Puntuación de relevancia
} HeapItem;

typedef struct {
    HeapItem* items;    // Array de elementos del heap
    int capacity;       // Capacidad máxima del heap
    int size;           // Tamaño actual del heap
} PriorityQueue;

// Funciones públicas
PriorityQueue* createPriorityQueue(int capacity);
void insertWithPriority(PriorityQueue* pq, HeapItem item);
HeapItem extractMax(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
void freePriorityQueue(PriorityQueue* pq);

#endif // PQ_H
