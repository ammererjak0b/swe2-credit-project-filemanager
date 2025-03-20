//
// Created by jakob on 20.03.2025.
//

#include "../Include/DoublyLinkedList.h"
#include <string.h>

// create new node
ListNode *CreateNode(const char *fileName, long fileSize) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (!newNode) return NULL;

    newNode->FileName = strdup(fileName);
    newNode->FileSize = fileSize;
    newNode->Prev = NULL;
    newNode->Next = NULL;

    return newNode;
}

// insert at the beginning
void InsertFile(ListNode **head, const char *fileName, long fileSize) {
    ListNode *newNode = CreateNode(fileName, fileSize);
    if (!newNode) return;

    if (*head) {
        newNode->Next = *head;
        (*head)->Prev = newNode;
    }

    *head = newNode;
}

// remove file by name
bool DeleteFile(ListNode **head, const char *fileName) {
    if (!*head) return false;

    ListNode *temp = *head;

    // Find node to delete
    while (temp && strcmp(temp->FileName, fileName) != 0)
        temp = temp->Next;

    if (!temp) return false;

    // Update head if needed
    if (temp == *head) *head = temp->Next;

    // Fix links
    if (temp->Prev) temp->Prev->Next = temp->Next;
    if (temp->Next) temp->Next->Prev = temp->Prev;

    free(temp->FileName);
    free(temp);
    return true;
}

// search file by name
ListNode *SearchFile(ListNode *head, const char *fileName) {
    while (head && strcmp(head->FileName, fileName) != 0)
        head = head->Next;
    return head;
}

// Print list from head to tail
void PrintList(ListNode *head) {
    while (head) {
        printf("%s (%ld bytes)\n", head->FileName, head->FileSize);
        head = head->Next;
    }
}

// reverse print list tail to head
void PrintListReverse(ListNode *head) {
    if (!head) return;

    // Move to tail
    while (head->Next) head = head->Next;

    // Print in reverse order
    while (head) {
        printf("%s (%ld bytes)\n", head->FileName, head->FileSize);
        head = head->Prev;
    }
}

// Free list
void FreeList(ListNode **head) {
    ListNode *temp;
    while (*head) {
        temp = *head;
        *head = (*head)->Next;
        free(temp->FileName);
        free(temp);
    }
}