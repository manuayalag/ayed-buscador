#pragma once
#ifndef LIST_H
#define LIST_H

typedef struct {
    int* datos;
    int capacidad;
    int tam;
} Lista;

Lista* crearLista();
void agregarElemento(Lista* lista, int valor);
void destruirLista(Lista* lista);
int obtenerElemento(Lista* lista, int index); // opcional
int tamanoLista(Lista* lista); // opcional

#endif
