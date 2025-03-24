#include "../Include/FileManger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro while opening file... ");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        perror("Error while allocating memory... ");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, length, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

bool writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error while opening file...");
        return false;
    }

    if (fputs(content, file) == EOF) {
        perror("Erro while writing into file...");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

bool appendAlbum(const char *filename, const char *artist, const char *album, int year) {
    // Check if the file exists.
    FILE *file = fopen(filename, "r");
    bool newFile = (file == NULL);
    if (file) {
        fclose(file);
    }

    file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file for appending");
        return false;
    }

    if (newFile) {
        // Write CSV header if file is new.
        fprintf(file, "Artist,Album,Year\n");
    }

    // Append new album entry.
    fprintf(file, "%s,%s,%d\n", artist, album, year);
    fclose(file);
    return true;
}

