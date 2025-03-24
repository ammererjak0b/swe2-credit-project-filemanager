#ifndef FILEMANGER_H
#define FILEMANGER_H
#include <stdbool.h>

char* readFile(const char *filename);
bool writeFile(const char *filename, const char *content);
bool appendAlbum(const char *filename, const char *artist, const char *album, int year);
#endif //FILEMANGER_H
