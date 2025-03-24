//
// Created by jakob on 20.03.2025.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct doubly linked list node
typedef struct DListNode {
    char *artist;
    char *album;
    int year;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

// Creates a new node of the doubly linked list
DListNode *createDListNode(const char *artist, const char *album, int year);

// Inserts a new node at the end of the list and returns the (possibly new) header
DListNode *insertDListNode(DListNode *head, const char *artist, const char *album, int year);

// Outputs the contents of the list (from header to end)
void printDList(DListNode *head);

// Free the memory of the entire list
void freeDList(DListNode *head);

// Parses the CSV file content (as a string) line by line and inserts the data records into the double-linked list.
DListNode *parseCSVToDList(char *fileContent);
#endif //DOUBLYLINKEDLIST_H
