//
// Created by jakob on 24.03.2025.
//

#ifndef CONVERTER_H
#define CONVERTER_H

#include "../Include/BinarySearchTree.h"
#include "../Include/DoublyLinkedList.h"

// Converts all entries from a BST (including duplicates) into a doubly linked list.
// The function returns the head of the newly built DList.
DListNode *ConvertBinarySearchTreeToDoublyList(AlbumNode *root, DListNode *head);

// Converts all entries from a doubly linked list into a BST (duplicates stored in BST duplicates).
// The function returns the root of the newly built BST.
AlbumNode *ConvertDoublyListToBinarySearchTree(DListNode *head);

#endif //CONVERTER_H
