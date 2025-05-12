#include "HashTable.h"
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 1009

#define LOAD_FACTOR_MAX 0.7
#define DELETED (char*)-1  // Usamos una direcci?n de memoria inv?lida o un valor especial

/* Crea un HashTable, devuelve el puntero a la estructura creada*/
HashTable HTCreate() {
	HashTable tabla = malloc(sizeof(_HashTable));
	tabla->cap = INITIAL_CAPACITY;
	tabla->tam = 0;
	tabla->arr = calloc(tabla->cap, sizeof(Celda*)); // inicializa a NULL
	return tabla;
}

/**
funcion privada de ayuda
Devuelve un numero entero grande (long) correspondiente a la clave pasada
por ejemplo pueden utilizar:
_stringLong("ABC") = 11*27^2 + 12*27^1 + 13*27^0 = 8356
_stringLong("09A") = 1*27^2  + 10*27^1 +  11*27^0 = 1010

o sino algo como
_stringLong("ABC") = 65*10000 + 66*100 + 67 = 656667

*/
long _stringLong(char* clave) {
	/*AYUDA SOBRE STRINGS
	Tabla de conversion de caracteres validos
	caracteres       valor ascii
	A-Z ... a-z   =  65 al 122
	0-9           =  48 al 59

	Ejemplos
	para saber el valor ascii de un caracter
	char* a = "ABC";
	int x = a[0] // x = 65

	para saber el tamanho del string
	int tam = strlen(a); // tam = 3

	AYUDA PARA CALCULOS MATEMATICOS
	int potencia = pow(27,2) // potencia = 27^2

	*/
	long resultado = 0l;
	int i, tam = strlen(clave);
	long exp = 1; // Inicializa la exponenciaci?n a 27^0 = 1

	for (i = tam - 1; i >= 0; i--) {  // Recorremos de derecha a izquierda
		if (clave[i] >= 'A' && clave[i] <= 'Z') {
			resultado += (clave[i] - 'A') * exp;
		}
		else if (clave[i] >= '0' && clave[i] <= '9') {
			resultado += (clave[i] - '0') * exp;
		}
		// Si hay letras min?sculas, convertirlas a may?sculas
		else if (clave[i] >= 'a' && clave[i] <= 'z') {
			resultado += (clave[i] - 'a') * exp;
		}
		exp *= 27;  // Sumar la siguiente potencia de 27
	}

	return resultado;
}

/*
funcion privada de ayuda
devuelve el hash para cada intento de insercion/busqueda
sea i el numero de intento y clave la clave usada.
aplicar la formula:
hash(x,i) = ((stringInt(x) mod CAP) + i^2) mod CAP
*/


int hash(const char* clave, int cap) {
	unsigned int h = 0;
	while (*clave) {
		h = (h * 31) + (unsigned char)(*clave++);
	}
	return h % cap;
}




/* Agrega el valor con la clave dada en el hash table, en el caso de repetir la clave se sobreescriben los datos
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTPut(HashTable tabla, char* clave, void* valor) {
	unsigned int idx = hash(clave, tabla->cap);
	Celda* celda = tabla->arr[idx];

	while (celda) {
		if (strcmp(celda->clave, clave) == 0) {
			celda->valor = valor; // sobreescribe
			return TRUE;
		}
		celda = celda->sig;
	}

	// no encontrado, insertar al inicio
	Celda* nuevo = malloc(sizeof(Celda));
	nuevo->clave = _strdup(clave); // copia la clave
	nuevo->valor = valor;
	nuevo->sig = tabla->arr[idx];
	tabla->arr[idx] = nuevo;
	tabla->tam++;
	return TRUE;
}


/* Obtiene el valor asociado a la clave dentro del HashTable y lo pasa por referencia a retval
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTGet(HashTable tabla, char* clave, void** retval) {
	unsigned int idx = hash(clave, tabla->cap);
	Celda* celda = tabla->arr[idx];
	while (celda) {
		if (strcmp(celda->clave, clave) == 0) {
			*retval = celda->valor;
			return TRUE;
		}
		celda = celda->sig;
	}
	return FALSE;
}


/* Remueve el valor asociado a la clave pasada
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTRemove(HashTable tabla, char* clave) {
	unsigned int idx = hash(clave, tabla->cap);
	Celda* celda = tabla->arr[idx];
	Celda* prev = NULL;

	while (celda) {
		if (strcmp(celda->clave, clave) == 0) {
			if (prev) prev->sig = celda->sig;
			else tabla->arr[idx] = celda->sig;
			free(celda->clave);
			free(celda);
			tabla->tam--;
			return TRUE;
		}
		prev = celda;
		celda = celda->sig;
	}
	return FALSE;
}


/* Devuelve TRUE si el HashTable contiene la clave*/
BOOLEAN HTContains(HashTable tabla, char* clave) {
	void* dummy;
	return HTGet(tabla, clave, &dummy);
}


/* Devuelve la cantidad de elementos (tamanho) cargados en el HashTable*/
int HTSize(HashTable tabla) {
	return tabla->tam;
}

/* Destruye la estructura*/
BOOLEAN HTDestroy(HashTable tabla) {
	for (int i = 0; i < tabla->cap; i++) {
		Celda* celda = tabla->arr[i];
		while (celda) {
			Celda* temp = celda;
			celda = celda->sig;
			free(temp->clave);
			free(temp);
		}
	}
	free(tabla->arr);
	free(tabla);
	return TRUE;
}

void printTable(HashTable p) {
	for (int i = 0; i < p->cap; i++) {
		if (p->arr[i] != NULL) {
			printf("Celda[%d]: clave = %s, valor = %p\n", i, p->arr[i]->clave, p->arr[i]->valor);
		}
	}
}