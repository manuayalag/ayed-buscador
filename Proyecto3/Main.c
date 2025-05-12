#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "HashTable.h"
#include "PositionList.h"
#include "StopWords.h"
#include "search.h"


// Indexa el archivo palabra por palabra, guardando posiciones
void indexFile(HashTable table, const char* filename) {
    FILE* f = fopen(filename, "r"); //abre archivo lectura
    if (!f) {
        perror("No se pudo abrir el archivo");
        return;
    }

    char buffer[1024];
    long position = 0;
    int lineNumber = 1; // Número de línea

    while (fgets(buffer, sizeof(buffer), f)) {
        char* token = strtok(buffer, " \t\n\r");
        while (token != NULL) {
            cleanWord(token);  // Limpiar la palabra
            if (strlen(token) > 3 && !isStopWord(token)) {
                PositionList* list = NULL;
                if (!HTGet(table, token, (void**)&list)) {
                    list = createPositionList();
                    HTPut(table, _strdup(token), list);
                }
                addPosition(list, position, lineNumber);
            }
            position += strlen(token) + 1;  // +1 por espacio
            token = strtok(NULL, " \t\n\r");
        }
        lineNumber++;  // Incrementar el número de línea
    }

    fclose(f);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Se requiere el nombre del archivo del libro como argumento.\n");
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    // Crear la tabla hash
    HashTable table = HTCreate();

    // Aquí deberías cargar el libro y construir el índice de palabras
    printf("Cargando el libro y creando el indice...\n");
    indexFile(table, filename);

    // Interfaz de búsqueda
    char query[256];
    while (1) {
        printf("\nIngrese una consulta (o 'salir' para terminar): ");
        fgets(query, sizeof(query), stdin);

        query[strcspn(query, "\n")] = '\0';  // Eliminar salto de línea

        if (strcmp(query, "salir") == 0) {
            break;
        }

        searchPhrase(table, filename, query);
    }

    // Liberar recursos
    HTDestroy(table);
    printf("\nFin del programa.\n");
    return EXIT_SUCCESS;
}
