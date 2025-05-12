#pragma once
#ifndef POSITION_LIST_H
#define POSITION_LIST_H

typedef struct _PositionNode {
    long position;                     // Posición de la palabra en el texto
    int lineNumber;                    // Número de línea donde aparece la palabra
    struct _PositionNode* next;
} PositionNode;

typedef struct {
    PositionNode* head;
    PositionNode* tail;
} PositionList;

PositionList* createPositionList();
void addPosition(PositionList* list, long pos, int lineNumber);
void freePositionList(PositionList* list);
void printPositionList(PositionList* list, const char* filename);
void printLineWithWord(const char* filename, int lineNumber);
#endif
