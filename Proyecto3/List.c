#include <stdlib.h>
#include <stdio.h>
#include "List.h"

#define CAP_INICIAL 4

Lista* crearLista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (!l) return NULL;
    l->capacidad = CAP_INICIAL;
    l->tam = 0;
    l->datos = (int*)malloc(sizeof(int) * l->capacidad);
    return l;
}

void agregarElemento(Lista* lista, int valor) {
    if (lista->tam == lista->capacidad) {
        lista->capacidad *= 2;
        lista->datos = realloc(lista->datos, lista->capacidad * sizeof(int));
    }
    lista->datos[lista->tam++] = valor;
}

void destruirLista(Lista* lista) {
    if (!lista) return;
    free(lista->datos);
    free(lista);
}

int obtenerElemento(Lista* lista, int index) {
    if (index >= 0 && index < lista->tam) return lista->datos[index];
    return -1;
}

int tamanoLista(Lista* lista) {
    return lista->tam;
}
