
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HashTable.h"
#include "PositionList.h"
#include "StopWords.h"
#include "Pq.h"

#define MAX_DIST 100
#define MAX_CONTEXT 300
#define RESULTS_PER_PAGE 5  // Mostrar 5 resultados por página (puedes cambiar M a cualquier número)

// Función que verifica si una palabra aparece dentro de los 100 caracteres de la anterior

void cleanQuery(char* input, char* cleanedWords[], int* count) {
    char* token = strtok(input, " \t\n\r");
    *count = 0;
    while (token != NULL) {
        cleanWord(token);  // Debes implementar cleanWord si no lo tenés
        if (strlen(token) > 2 && !isStopWord(token)) {
            cleanedWords[(*count)++] = _strdup(token);
        }
        token = strtok(NULL, " \t\n\r");
    }
}
void displayResultsWithPagination(HeapItem results[], int totalResults, const char* filename) {
    int currentPage = 0;

    while (1) {  // Bucle principal para manejar la navegación
        // Limpiar la consola antes de mostrar el resultado
#ifdef _WIN32
        system("cls");  // Comando para limpiar la consola en Windows
#else
        system("clear");  // Comando para limpiar la consola en Linux/Mac
#endif

        // Mostrar el resultado actual
        printf("-------------------------------------------------\n");
        printf("Resultado %d de %d\n", currentPage + 1, totalResults);
        printf("Las palabras encontradas se encuentran en la línea %d (posición %ld).\n",
            results[currentPage].lineNumber, results[currentPage].position);
        printContext(results[currentPage].lineNumber, filename, 1, 1);  // Mostrar el contexto de la línea

        // Preguntar al usuario si desea continuar
        char input[10];
        printf("\nIngrese 'siguiente' para ver más, 'anterior' para volver, o 'salir' para terminar: ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Eliminar el salto de línea al final de la entrada
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "siguiente") == 0) {
                if (currentPage + 1 < totalResults) {
                    currentPage++;  // Avanzar a la siguiente página
                }
                else {
                    printf("\nNo hay más resultados.\n");
                }
            }
            else if (strcmp(input, "anterior") == 0) {
                if (currentPage > 0) {
                    currentPage--;  // Retroceder a la página anterior
                }
                else {
                    printf("\nNo hay resultados anteriores.\n");
                }
            }
            else if (strcmp(input, "salir") == 0) {
                break;  // Salir del bucle
            }
            else {
                printf("Entrada no válida. Intente nuevamente.\n");
            }
        }
        else {
            // Si fgets falla, limpiar el buffer de entrada
            printf("Error al leer la entrada. Intente nuevamente.\n");
            while (getchar() != '\n');  // Limpiar el buffer de entrada
        }
    }

    printf("\nFin de la navegación de resultados.\n");
}


void searchPhrase(HashTable table, const char* filename, const char* query) {
    printf("Buscando la frase: %s\n", query);

    // Limpiar la consulta y dividirla en palabras
    char* cleanedWords[100];  // Para almacenar las palabras limpiadas
    int count = 0;
    cleanQuery(query, cleanedWords, &count);

    if (count < 2) {
        printf("El query debe contener al menos dos palabras para buscar una frase completa.\n");
        return;
    }

    // Obtener las posiciones de las palabras en el índice
    PositionList* results[1000];  // Para almacenar las listas de posiciones de cada palabra
    int foundWords = 0;

    for (int i = 0; i < count; i++) {
        PositionList* list = NULL;
        if (HTGet(table, cleanedWords[i], (void**)&list)) {
            results[foundWords++] = list;
        }
        else {
            printf("La palabra '%s' no se encontró en el texto.\n", cleanedWords[i]);
            return;
        }
    }
    // Crear una cola de prioridades para almacenar los resultados
    PriorityQueue* pq = createPriorityQueue(100);

    // Buscar frases completas
    PositionNode* firstWordNode = results[0]->head;
    while (firstWordNode != NULL) {
        long startPos = firstWordNode->position;
        int isPhraseValid = 1;

        // Verificar que las palabras siguientes estén en orden y dentro de MAX_DIST
        long currentPos = startPos;
        for (int i = 1; i < count; i++) {
            PositionNode* nextWordNode = results[i]->head;
            int foundNextWord = 0;

            while (nextWordNode != NULL) {
                if (nextWordNode->position > currentPos &&
                    nextWordNode->position - currentPos <= MAX_DIST) {
                    currentPos = nextWordNode->position;
                    foundNextWord = 1;
                    break;
                }
                nextWordNode = nextWordNode->next;
            }

            if (!foundNextWord) {
                isPhraseValid = 0;
                break;
            }
        }

        // Si la frase es válida, agregarla a la cola de prioridades
        if (isPhraseValid) {
            HeapItem item;
            item.position = startPos;
            item.lineNumber = firstWordNode->lineNumber;
            item.score = count;  // Usamos el número de palabras encontradas como puntuación
            insertWithPriority(pq, item);
        }

        firstWordNode = firstWordNode->next;
    }
    // Extraer los resultados de la cola de prioridades
    HeapItem finalResults[1000];
    int finalResultCount = 0;

    while (!isEmpty(pq)) {
        finalResults[finalResultCount++] = extractMax(pq);
    }
    // Mostrar los resultados con paginación
    displayResultsWithPagination(finalResults, finalResultCount, filename);
    freePriorityQueue(pq);
}


int isLinePrinted(int lineNumber, int* printedLines, int printedLineCount) {
    for (int i = 0; i < printedLineCount; i++) {
        if (printedLines[i] == lineNumber) {
            return 1;  // Ya está impresa
        }
    }
    return 0;  // No está impresa
}

int isWithinDistance(PositionNode* current, PositionNode* previous) {
    return (current->position - previous->position) <= MAX_DIST;
}




