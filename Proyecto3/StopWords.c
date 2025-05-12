#include "StopWords.h"
#include <string.h>
#include <ctype.h>

const char* stopwords[] = {
    "el", "la", "los", "las", "de", "en", "y", "que", "a", "por",
    "con", "para", "un", "una", "unos", "unas", "al", "del", "o",
    "se", "es", "no", "su", "lo", "como", "más", "pero", "ya",
    "le", "ha", "me", "si", "sin", "sobre", "este", "esta", "entre",
    NULL // Fin de lista
};

bool isStopWord(const char* word) {
    for (int i = 0; stopwords[i] != NULL; i++) {
        if (strcmp(stopwords[i], word) == 0) return true;
    }
    return false;
}

void cleanWord(char* word) {
    int len = strlen(word);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalnum((unsigned char)word[i])) {
            word[j++] = tolower((unsigned char)word[i]);
        }
    }
    word[j] = '\0';
}
