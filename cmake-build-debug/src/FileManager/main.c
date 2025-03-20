#include <stdio.h>
#include <stdlib.h>
#include "../Include/FileManger.h"
#include "../Include/DoublyLinkedList.h"
#include "../Include/BinarySearchTree.h"

BSTNode *fileTree = NULL;
ListNode *fileList = NULL;

void ShowMenu();

int main(void) {
    printf("Hello, World!\n");
    return 0;
}

void ShowMenu() {
    printf("\nFile Management System\n");
    printf("1. Insert File\n");
    printf("2. Delete File\n");
    printf("3. Search File\n");
    printf("4. Print Files (Sorted by Name - BST)\n");
    printf("5. Print Files (Insertion Order - Linked List)\n");
    printf("6. Print Files in Reverse Order\n");
    printf("7. Exit\n");
    printf("Choose an option: ");
}