//
// Created by jakob on 20.03.2025.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

// Struct for duplicate entry (if artist has more then one album)
typedef struct DuplicateAlbum {
    char *album;
    int year;
    struct DuplicateAlbum *next;
} DuplicateAlbum;

// Struct for node in Binary Search Tree
typedef struct AlbumNode {
    char *artist;              // Key: Artistname (nicht das idealste, aber in diesem beispiel als key verwendet um duplicate Einträge zu haben.
    char *album;               // First found album of artist
    int year;                  // Release Year
    DuplicateAlbum *duplicates; // More albums of the artist if available
    struct AlbumNode *left;
    struct AlbumNode *right;
} AlbumNode;

// Creates a new duplicate node
DuplicateAlbum *createDuplicateAlbum(const char *album, int year);

// Creates a new tree node
AlbumNode *createAlbumNode(const char *artist, const char *album, int year);

// Inserts an album into the BST. If the artists match, the album is saved as a duplicate.
AlbumNode *insertAlbum(AlbumNode *root, const char *artist, const char *album, int year);

// Performs an in-order traversal of the tree and outputs the entries.
void inorderPrint(AlbumNode *root);

// Free the duplicate list.
void freeDuplicateList(DuplicateAlbum *dup);

// Free the entire tree.
void freeBST(AlbumNode *root);

// Parses the CSV file content (as a string) line by line and inserts the data records into the binary search tree.
AlbumNode *parseCsvToBst(char *fileContent);

//Converts BinarySearchTree to Doubly List

#endif //BINARYSEARCHTREE_H
