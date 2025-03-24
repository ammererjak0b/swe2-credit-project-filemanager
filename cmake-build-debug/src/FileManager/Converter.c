//
// Created by jakob on 24.03.2025.
//

#include <stdlib.h>
#include "../Include/Converter.h"

// Recursively traverse the BST in-order, inserting each entry into the DList.
DListNode *ConvertBinarySearchTreeToDoublyList(AlbumNode *root, DListNode *head) {
    if (!root) {
        return head;
    }

    // Convert left subtree first
    head = ConvertBinarySearchTreeToDoublyList(root->left, head);

    // Insert the main album for this node
    head = insertDListNode(
        head,
        root->artist,
        root->album,
        root->year
        );

    // Insert duplicates (if any)
    DuplicateAlbum *duplicateAlbum = root->duplicates;
    while (duplicateAlbum != NULL) {
        head = insertDListNode(
            head,
            root->artist,
            duplicateAlbum->album,
            duplicateAlbum->year
            );
        duplicateAlbum = duplicateAlbum->next;
    }

    // Convert right subtree
    head = ConvertBinarySearchTreeToDoublyList(root->right, head);
    return head;
}

// Traverse the DList from head to tail, inserting each entry into the BST.
AlbumNode *ConvertDoublyListToBinarySearchTree(DListNode *head) {
    AlbumNode *root = NULL;
    DListNode *current = head;

    while (current != NULL) {
        root = insertAlbum(root, current->artist, current->album, current->year);
        current = current->next;
    }
    return root;
}
