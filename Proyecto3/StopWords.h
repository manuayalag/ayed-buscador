#pragma once
#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <stdbool.h>

bool isStopWord(const char* word);
void cleanWord(char* word); // Elimina puntuación y pasa a minúsculas

#endif
