//
// Created by jakob on 20.03.2025.
//

#include "../Include/DoublyLinkedList.h"
#include <string.h>

#define STACK_MAX 1000

// create node for doubly linked list
DListNode *createDListNode(const char *artist, const char *album, int year) {
    DListNode *node = malloc(sizeof(DListNode));
    if (!node) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    node->artist = strdup(artist);
    node->album  = strdup(album);
    node->year   = year;
    node->prev   = NULL;
    node->next   = NULL;
    return node;
}

// add new node at the end
DListNode *insertDListNode(DListNode *head, const char *artist, const char *album, int year) {
    DListNode *newNode = createDListNode(artist, album, year);
    if (head == NULL) {
        return newNode;
    }

    // go to end of list
    DListNode *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = newNode;
    newNode->prev = tail;
    return head;
}

// print details of dlist
void printDList(DListNode *head) {
    DListNode *current = head;
    while (current != NULL) {
        printf("Artist: %s, Album: %s, Year: %d\n", current->artist, current->album, current->year);
        current = current->next;
    }
}

// free memory of list
void freeDList(DListNode *head) {
    DListNode *current = head;
    while (current != NULL) {
        DListNode *temp = current;
        current = current->next;
        free(temp->artist);
        free(temp->album);
        free(temp);
    }
}

// parse csv list to doubly linked lsit
DListNode *parseCSVToDoublyList(char *fileContent) {
    DListNode *head = NULL;
    char *saveptrLine = NULL;
    // one entry every line
    char *line = strtok_r(fileContent, "\n", &saveptrLine);
    int lineNumber = 0;

    while (line != NULL) {
        if (lineNumber == 0) {
            line = strtok_r(NULL, "\n", &saveptrLine);
            lineNumber++;  // WARUM GEHT ER DA IMMER AUS DER SCHLEIFE ???!!!
            continue;
        }

        // dismantle at , for Artist,Album,Year
        char *saveptrToken;
        char *artist = strtok_r(line, ",", &saveptrToken);
        char *album  = strtok_r(NULL, ",", &saveptrToken);
        char *yearStr = strtok_r(NULL, ",", &saveptrToken);

        if (artist && album && yearStr) {
            int year = (int)strtol(yearStr, NULL, 10);
            head = insertDListNode(head, artist, album, year);
        }

        line = strtok_r(NULL, "\n", &saveptrLine);
        lineNumber++;
    }

    return head;
}