#pragma once
#ifndef SEARCH_H
#define SEARCH_H

void cleanQuery(char* input, char* cleanedWords[], int* count);
void searchPhrase(HashTable table, const char* filename, const char* query);
#endif
