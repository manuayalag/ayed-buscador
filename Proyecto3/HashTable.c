#include <stdlib.h>
#include "HashTable.h"


/* Crea un HashTable, devuelve el puntero a la estructura creada*/
HashTable HTCreate() {
	/*AGREGUE SU CODIGO AQUI*/
	HashTable ht = (HashTable)malloc(sizeof(_HashTable));
	if (ht == NULL) {
		return NULL;
	}
	ht->arr = (Celda**)malloc(sizeof(Celda*) * 10); // Inicializa el arreglo de celdas
	if (ht->arr == NULL) {
		free(ht);
		return NULL;
	}
	ht->tam = 0; // Inicializa el tamaño
	ht->cap = 10; // Inicializa la capacidad

	return ht;
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
	int i, x;
	int tam = strlen(clave);
	int exp = 0;

	for (i = 0; i < tam; i++) {
		if (clave[i] >= 'A' && clave[i] <= 'Z') {
			resultado += (clave[i] - 65) * pow(27, exp);
		}
		else if (clave[i] >= '0' && clave[i] <= '9') {
			resultado += (clave[i] - 48) * pow(27, exp);
		}
		exp++;
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

int _hash(char* clave, int i, int cap) {
	return ((_stringLong(clave) % cap + i*i) % cap);
}




/* Agrega el valor con la clave dada en el hash table, en el caso de repetir la clave se sobreescriben los datos
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTPut(HashTable p, char* clave, void* valor) {
	/*AGREGUE SU CODIGO AQUI*/
	if (p == NULL || clave == NULL || valor == NULL) {
		return FALSE;
	}
	for (int i = 0; i < p->cap; i++) {
		int index = _hash(clave, i, p->cap);
		
		if (p->arr[index] == NULL) {
			//Crear nueva celda si no existe
			p->arr[index] = (Celda*)malloc(sizeof(Celda));
			if (p->arr[index] == NULL) {
				return FALSE;
			}
			p->arr[index]->clave = strdup(clave);
			p->arr[index]->valor = valor;
			p->tam++;
			return TRUE;
		}
		//Si la clave ya existe, actualizar el valor
		else if (strcmp(p->arr[index]->clave, clave) == 0 && p->arr[index]->valor != NULL) {
			free(p->arr[index]->valor);
			p->arr[index]->valor = valor;
			return TRUE;
		}
	}
	//Tabla llena o colisiones sin resolver
	return FALSE;
}

/* Obtiene el valor asociado a la clave dentro del HashTable y lo pasa por referencia a retval
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTGet(HashTable p, char* clave, void** retval) {
	/*AGREGUE SU CODIGO AQUI*/
	if (p == NULL || clave == NULL || retval == NULL) {
		return FALSE;
	}
	for (int i = 0; i < p->cap; i++) {
		int index = _hash(clave, i, p->cap);

		if (p->arr[index] == NULL) {
			return FALSE;					// No se encontró la clave
		}
		//Si las claves coninciden
		if (strcmp(p->arr[index]->clave, clave) == 0) {
			*retval = p->arr[index]->valor; // Asignar el valor encontrado
			return TRUE;					// Se encontró la clave
		}
	}
	//No se encontró la clave
	return FALSE;
}

/* Remueve el valor asociado a la clave pasada
Devuelve TRUE si tuvo exito, sino FALSE*/
BOOLEAN HTRemove(HashTable p, char* clave) {
	/*AGREGUE SU CODIGO AQUI*/
	return FALSE;
}

/* Devuelve TRUE si el HashTable contiene la clave*/
BOOLEAN HTContains(HashTable p, char* clave) {
	/*AGREGUE SU CODIGO AQUI*/
	return FALSE;
}

/* Devuelve la cantidad de elementos (tamanho) cargados en el HashTable*/
BOOLEAN HTSize(HashTable p) {
	/*AGREGUE SU CODIGO AQUI*/
	return FALSE;
}

/* Destruye la estructura*/
BOOLEAN HTDestroy(HashTable p) {
	/*AGREGUE SU CODIGO AQUI*/
	return FALSE;
}