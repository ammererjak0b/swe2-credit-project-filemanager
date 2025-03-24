#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/BinarySearchTree.h"

DuplicateAlbum *createDuplicateAlbum(const char *album, int year) {
    DuplicateAlbum *dup = malloc(sizeof(DuplicateAlbum));
    if (!dup) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    dup->album = strdup(album);
    dup->year = year;
    dup->next = NULL;
    return dup;
}

AlbumNode *createAlbumNode(const char *artist, const char *album, int year) {
    AlbumNode *node = malloc(sizeof(AlbumNode));
    if (!node) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    node->artist = strdup(artist);
    node->album = strdup(album);
    node->year = year;
    node->duplicates = NULL;
    node->left = node->right = NULL;
    return node;
}

AlbumNode *insertAlbum(AlbumNode *root, const char *artist, const char *album, int year) {
    if (root == NULL) {
        return createAlbumNode(artist, album, year);
    }

    int cmp = strcmp(artist, root->artist);
    if (cmp < 0) {
        root->left = insertAlbum(root->left, artist, album, year);
    } else if (cmp > 0) {
        root->right = insertAlbum(root->right, artist, album, year);
    } else {
        // Wenn gleicher Künstler dann als Duplikat adden
        DuplicateAlbum *dup = createDuplicateAlbum(album, year);
        dup->next = root->duplicates;
        root->duplicates = dup;
    }
    return root;
}

void inorderPrint(AlbumNode *root) {
    if (root == NULL) return;

    inorderPrint(root->left);
    printf("Artist: %s, Album: %s, Year: %d\n", root->artist, root->album, root->year);
    DuplicateAlbum *dup = root->duplicates;
    while (dup != NULL) {
        printf("  Duplicate -> Album: %s, Year: %d\n", dup->album, dup->year);
        dup = dup->next;
    }
    inorderPrint(root->right);
}

void freeDuplicateList(DuplicateAlbum *dup) {
    while (dup) {
        DuplicateAlbum *temp = dup;
        dup = dup->next;
        free(temp->album);
        free(temp);
    }
}

void freeBST(AlbumNode *root) {
    if (root == NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root->artist);
    free(root->album);
    freeDuplicateList(root->duplicates);
    free(root);
}

AlbumNode *parseCsvToBst(char *fileContent) {
    AlbumNode *root = NULL;
    char *saveptrLine;
    char *line = strtok_r(fileContent, "\n", &saveptrLine);  //https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
    int lineNumber = 0;

    while (line != NULL) {
        // Ignore Header line
        if (lineNumber == 0) {
            line = strtok_r(NULL, "\n", &saveptrLine);
            lineNumber++;
            continue;
        }

        // Use strtok_r to split the line using commas
        char *saveptrToken;
        char *artist = strtok_r(line, ",", &saveptrToken);
        char *album  = strtok_r(NULL, ",", &saveptrToken);
        char *yearStr = strtok_r(NULL, ",", &saveptrToken);

        if (artist && album && yearStr) {
            int year = (int)strtol(yearStr, NULL, 10);
            root = insertAlbum(root, artist, album, year);
        }

        line = strtok_r(NULL, "\n", &saveptrLine);
        lineNumber++;
    }

    return root;
}
