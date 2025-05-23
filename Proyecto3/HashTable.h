#ifndef DEFINE_HASHTABLE_H
#define DEFINE_HASHTABLE_H
#include "boolean.h"
/*
 Copyright (c) 2017. Universidad Nacional de Itapua.

 En general no deberias tener que modificar este archivo a menos que el
 profesor se haya equivocado!

*/
/*Implementacion de una tabla hash con arreglo dinamico*/
typedef struct _celda {
	char* clave;
	void* valor;
	struct _celda* sig;
} Celda;

typedef struct __HashTable {
	Celda** arr; // arreglo de listas
	int tam;    // cantidad de elementos actuales
	int cap;    // capacidad (tama?o del arreglo)
} _HashTable;


typedef _HashTable* HashTable;

/* Crea un HashTable, devuelve el puntero a la estructura creada*/
HashTable HTCreate();

/* Agrega el valor con la clave dada en el hash table, en el caso de repetir la clave se sobreescriben los datos
   Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTPut(HashTable p, char* clave, void* valor);

/* Obtiene el valor asociado a la clave dentro del HashTable y lo pasa por referencia a retval
   Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTGet(HashTable p, char* clave, void** retval);

/* Remueve el valor asociado a la clave pasada
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTRemove(HashTable p, char* clave);

/* Devuelve TRUE si el HashTable contiene la clave*/
BOOLEAN HTContains(HashTable p, char* clave);

/* Devuelve la cantidad de elementos (tamanho) cargados en el HashTable*/
int HTSize(HashTable p);
/* Devuelve la capacidad (tamanho) del HashTable*/
BOOLEAN HTDestroy(HashTable p);

#endif