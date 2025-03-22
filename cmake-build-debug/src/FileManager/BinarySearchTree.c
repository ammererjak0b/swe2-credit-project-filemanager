#include "../include/BinarySearchTree.h"
#include <string.h>

/*
 *  Basically implemented CRUD for BinarySearchTree
 */

// Create a new node with filename and file size
BSTNode *CreateBtsNode(const char *fileName, long fileSize) {
    BSTNode *node = malloc(sizeof(BSTNode));
    if (!node) return NULL;

    node->FileName = strdup(fileName);
    node->Left = node->Right = NULL;

    FileEntry *entry = malloc(sizeof(FileEntry));
    entry->FileSize = fileSize;
    entry->Next = NULL;

    node->Duplicates = entry;
    return node;
}

// Insert a file into BST (sorted by filename)
BSTNode *InsertFileBts(BSTNode *root, const char *fileName, long fileSize) {
    if (!root) return CreateBtsNode(fileName, fileSize);

    int cmp = strcmp(fileName, root->FileName);
    if (cmp < 0)
        root->Left = InsertFileBts(root->Left, fileName, fileSize);
    else if (cmp > 0)
        root->Right = InsertFileBts(root->Right, fileName, fileSize);
    else {
        FileEntry *entry = malloc(sizeof(FileEntry));
        entry->FileSize = fileSize;
        entry->Next = root->Duplicates;
        root->Duplicates = entry;
    }

    return root;
}
// Search for a file by name in BST
BSTNode *SearchFileBts(BSTNode *root, const char *fileName) {
    if (!root || strcmp(fileName, root->FileName) == 0) {
        return root;
    }

    if (strcmp(fileName, root->FileName) < 0) {
        return SearchFileBts(root->Left, fileName);
    } else {
        return SearchFileBts(root->Right, fileName);
    }
}

// Find the smallest node in the BST
BSTNode *FindMinimum(BSTNode *root) {
    while (root && root->Left)
        root = root->Left;
    return root;
}

// Delete a file node from BST and maintain BST structure
BSTNode *DeleteFileBtsNode(BSTNode *root, const char *fileName) {
    if (!root) return NULL;

    int cmp = strcmp(fileName, root->FileName);
    if (cmp < 0) {
        root->Left = DeleteFileBtsNode(root->Left, fileName);
    }
    else if (cmp > 0) {
        root->Right = DeleteFileBtsNode(root->Right, fileName);
    }
    else {
        if (root->Duplicates && root->Duplicates->Next) {
            FileEntry *temp = root->Duplicates;
            root->Duplicates = temp->Next;
            free(temp);
            return root;
        }

        if (!root->Left) {
            BSTNode *right = root->Right;
            free(root->FileName);
            free(root->Duplicates);
            free(root);
            return right;
        } else if (!root->Right) {
            BSTNode *left = root->Left;
            free(root->FileName);
            free(root->Duplicates);
            free(root);
            return left;
        }

        BSTNode *min = FindMinimum(root->Right);
        free(root->FileName);
        root->FileName = strdup(min->FileName);
        root->Duplicates = min->Duplicates;
        root->Right = DeleteFileBtsNode(root->Right, min->FileName);
    }

    return root;
}

// Print all file entries in sorted order (inorder traversal)
void PrintTree(BSTNode *root) {
    if (!root) return;

    PrintTree(root->Left);
    printf("%s: ", root->FileName);
    FileEntry *entry = root->Duplicates;
    while (entry) {
        printf("%ld ", entry->FileSize);
        entry = entry->Next;
    }
    printf("bytes\n");
    PrintTree(root->Right);
}

// Free all nodes in the BST (recursive)
void FreeTree(BSTNode *root) {
    if (!root) return;

    FreeTree(root->Left);
    FreeTree(root->Right);

    free(root->FileName);
    FileEntry *entry = root->Duplicates;
    while (entry) {
        FileEntry *next = entry->Next;
        free(entry);
        entry = next;
    }

    free(root);
}