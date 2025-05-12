#include <stdlib.h>
#include <stdio.h>
#include "PositionList.h"

PositionList* createPositionList() {
    PositionList* list = malloc(sizeof(PositionList));
    list->head = list->tail = NULL;
    return list;
}

void addPosition(PositionList* list, long pos, int lineNumber) {
    // Crear un nuevo nodo de posici�n
    PositionNode* newNode = (PositionNode*)malloc(sizeof(PositionNode));
    newNode->position = pos;
    newNode->lineNumber = lineNumber;
    newNode->next = NULL;

    // Si la lista est� vac�a, simplemente agregamos el primer nodo
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        // Si ya existe un nodo con la misma posici�n y l�nea, no lo agregamos
        PositionNode* current = list->head;
        while (current != NULL) {
            if (current->position == pos && current->lineNumber == lineNumber) {
                free(newNode);  // Evitamos duplicados
                return;
            }
            current = current->next;
        }
        // Si no hay duplicados, lo agregamos al final
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void printPositionList(PositionList* list, const char* filename) {
    if (list == NULL || list->head == NULL) {
        printf("No hay posiciones registradas.\n");
        return;
    }

    PositionNode* current = list->head;
    while (current != NULL) {
        printf("Posicion: %ld, Linea: %d\n", current->position, current->lineNumber);
        printLineWithWord(filename, current->lineNumber);  // Mostrar la l�nea
        current = current->next;
    }
}
void printLineWithWord(const char* filename, int lineNumber) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("No se pudo abrir el archivo");
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    while (fgets(buffer, sizeof(buffer), f)) {
        if (currentLine == lineNumber) {
            printf("Linea %d: %s", currentLine, buffer);
            break;
        }
        currentLine++;
    }

    fclose(f);
}

// Funci�n que imprime el contexto alrededor de una palabra (dada su posici�n en el archivo)
void printContext(int lineNumber, const char* filename, int linesBefore, int linesAfter) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char buffer[1024];
    int currentLine = 1;

    // Determinar las l�neas de inicio y fin del contexto
    int startLine = (lineNumber - linesBefore > 0) ? lineNumber - linesBefore : 1;
    int endLine = lineNumber + linesAfter;

    // Leer el archivo l�nea por l�nea y mostrar el contexto
    printf("\n--- Contexto alrededor de la linea %d ---\n", lineNumber);
    while (fgets(buffer, sizeof(buffer), file)) {
        if (currentLine >= startLine && currentLine <= endLine) {
            printf("Linea %d: %s", currentLine, buffer);
        }
        if (currentLine > endLine) {
            break;
        }
        currentLine++;
    }

    fclose(file);
}



void freePositionList(PositionList* list) {
    PositionNode* current = list->head;
    while (current) {
        PositionNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
