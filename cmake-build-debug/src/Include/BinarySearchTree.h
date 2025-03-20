//
// Created by jakob on 20.03.2025.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdio.h>
#include <stdlib.h>

// Struct
typedef struct BSTNode {
    char *FileName;
    long FileSize;
    struct BSTNode *Left;
    struct BSTNode *Right;
} BSTNode;

// Functions
BSTNode *CreateNode(const char *fileName, long fileSize);
BSTNode *InsertFile(BSTNode *root, const char *fileName, long fileSize);
BSTNode *SearchFile(BSTNode *root, const char *fileName);
BSTNode *DeleteFileNode(BSTNode *root, const char *fileName);
void PrintTree(BSTNode *root);
void FreeTree(BSTNode *root);

#endif //BINARYSEARCHTREE_H
