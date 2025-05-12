#include "boolean.h"

// Definimos 'Node' como puntero a '_Node' directamente
typedef struct __Node {
    void* val;
    struct __Node* next;  // 'next' debe ser puntero a 'struct __Node'
} _Node;

typedef _Node* Node;  // 'Node' es puntero a '_Node'

typedef struct _LLQueue {
    Node front;  // Puntero al primer nodo de la cola
    Node end;    // Puntero al último nodo de la cola
} LLQueue;

typedef LLQueue* Queue;  // 'Queue' es puntero a 'LLQueue'

// Declaración de funciones
Queue create();  // Función para crear la cola

BOOLEAN isEmpty(Queue q);  // Función para verificar si la cola está vacía

BOOLEAN enqueue(Queue q, void* x);  // Función para agregar un elemento a la cola

void* dequeue(Queue q, void* retval);  // Función para eliminar un elemento de la cola
