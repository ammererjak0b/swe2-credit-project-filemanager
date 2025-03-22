//
// Created by jakob on 20.03.2025.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct
typedef struct ListNode {
    char *FileName;
    long FileSize;
    struct ListNode *Prev;
    struct ListNode *Next;
} ListNode;

// Functions
ListNode *CreateListNode(const char *fileName, long fileSize);
void InsertFileDll(ListNode **head, const char *fileName, long fileSize);
bool DeleteFileDll(ListNode **head, const char *fileName);
ListNode *SearchFile(ListNode *head, const char *fileName);
void PrintList(ListNode *head);
void PrintListReverse(ListNode *head);
void FreeList(ListNode **head);
#endif //DOUBLYLINKEDLIST_H
