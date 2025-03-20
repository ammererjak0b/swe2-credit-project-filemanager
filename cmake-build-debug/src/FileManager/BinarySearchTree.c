#include "../include/BinarySearchTree.h"
#include <string.h>

/*
 *  Basically implemented CRUD for BinarySearchTree
 */


// Create a new node with filename and file size
BSTNode *CreateNode(const char *fileName, long fileSize) {
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    if (!newNode) return NULL; // Memory allocation check

    newNode->FileName = strdup(fileName); // Duplicate string to avoid pointer issues
    newNode->FileSize = fileSize;
    newNode->Left = newNode->Right = NULL;

    return newNode;
}

// Insert a file into BST (sorted by filename)
BSTNode *InsertFile(BSTNode *root, const char *fileName, long fileSize) {
    if (!root) return CreateNode(fileName, fileSize); // Insert at empty position

    if (strcmp(fileName, root->FileName) < 0)
        root->Left = InsertFile(root->Left, fileName, fileSize); // Insert left
    else if (strcmp(fileName, root->FileName) > 0)
        root->Right = InsertFile(root->Right, fileName, fileSize); // Insert right

    return root;
}

// Search for a file by name in BST
BSTNode *SearchFile(BSTNode *root, const char *fileName) {
    if (!root || strcmp(fileName, root->FileName) == 0) return root; // Found or empty tree

    return (strcmp(fileName, root->FileName) < 0) ?
        SearchFile(root->Left, fileName) :
        SearchFile(root->Right, fileName);
}

// Find the smallest node in the BST
BSTNode *FindMinimum(BSTNode *root) {
    while (root && root->Left) root = root->Left;
    return root;
}

// Delete a file node from BST and maintain BST structure
BSTNode *DeleteFileNode(BSTNode *root, const char *fileName) {
    if (!root) return NULL;

    if (strcmp(fileName, root->FileName) < 0)
        root->Left = DeleteFileNode(root->Left, fileName); // Search left
    else if (strcmp(fileName, root->FileName) > 0)
        root->Right = DeleteFileNode(root->Right, fileName); // Search right
    else {
        // Case 1 & 2: Node has one or no child
        if (!root->Left) {
            BSTNode *tempNode = root->Right;
            free(root->FileName);
            free(root);
            return tempNode;
        } else if (!root->Right) {
            BSTNode *Temp = root->Left;
            free(root->FileName);
            free(root);
            return Temp;
        }

        // Case 3: Node has two children -> Replace with min node in right subtree
        BSTNode *Temp = FindMinimum(root->Right);
        free(root->FileName);
        root->FileName = strdup(Temp->FileName);
        root->FileSize = Temp->FileSize;
        root->Right = DeleteFileNode(root->Right, Temp->FileName);
    }

    return root;
}

// Print all file entries in sorted order (inorder traversal)
void PrintTree(BSTNode *root) {
    if (root) {
        PrintTree(root->Left);
        printf("%s (%ld bytes)\n", root->FileName, root->FileSize);
        PrintTree(root->Right);
    }
}

// Free all nodes in the BST (recursive)
void FreeTree(BSTNode *root) {
    if (root) {
        FreeTree(root->Left);
        FreeTree(root->Right);
        free(root->FileName);
        free(root);
    }
}
