#pragma once
#ifndef PQ_H
#define PQ_H

typedef struct {
    long position;      // Posici�n en el archivo
    int lineNumber;     // L�nea en la que aparece
    int score;          // Puntuaci�n de relevancia
} HeapItem;

typedef struct {
    HeapItem* items;    // Array de elementos del heap
    int capacity;       // Capacidad m�xima del heap
    int size;           // Tama�o actual del heap
} PriorityQueue;

// Funciones p�blicas
PriorityQueue* createPriorityQueue(int capacity);
void insertWithPriority(PriorityQueue* pq, HeapItem item);
HeapItem extractMax(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
void freePriorityQueue(PriorityQueue* pq);

#endif // PQ_H
