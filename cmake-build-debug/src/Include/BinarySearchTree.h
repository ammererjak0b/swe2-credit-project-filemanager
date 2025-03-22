//
// Created by jakob on 20.03.2025.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct FileEntry {
    long FileSize;
    struct FileEntry *Next;
} FileEntry;

// Struct
typedef struct BSTNode {
    char *FileName;
    FileEntry *Duplicates;
    struct BSTNode *Left;
    struct BSTNode *Right;
} BSTNode;

// Functions
BSTNode *CreateBtsNode(const char *fileName, long fileSize);
BSTNode *InsertFileBts(BSTNode *root, const char *fileName, long fileSize);
BSTNode *SearchFileBts(BSTNode *root, const char *fileName);
BSTNode *DeleteFileBtsNode(BSTNode *root, const char *fileName);
void PrintTree(BSTNode *root);
void FreeTree(BSTNode *root);
#endif //BINARYSEARCHTREE_H
