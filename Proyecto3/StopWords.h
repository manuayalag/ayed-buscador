#pragma once
#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include "boolean.h"

BOOLEAN isStopWord(const char* word);
void cleanWord(char* word); // Elimina puntuaci�n y pasa a min�sculas

#endif
