#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/FileManger.h"
#include "../Include/DoublyLinkedList.h"
#include "../Include/BinarySearchTree.h"
#include "../Include/Converter.h"

/*
 * Name : swe2_credit_project_filemanager
 * Author : Jakob Ammerer GOAT
 * Version : 1.0
 * Description : Anrechnungsaufgabe SWE2
 */

// Enum, to know which datatype the user wants to have his file converted.
typedef enum {
    MODE_NONE,
    MODE_BST,
    MODE_DLL
} DataMode;

AlbumNode *root = NULL;
DListNode *head = NULL;

void test();
void initMenu();

int main(void) {
    test();




}

void test() {
    char *fileContent = readFile("C:\\Users\\jakob\\CLionProjects\\swe2-credit-project-filemanager\\albums.csv");
    // Guard Against Null
    if (fileContent == NULL) {
        ferror("Error: Could not read file...\n");
        return;
    }

    //BST
    root = parseCsvToBst(fileContent);
    printf("Inorder Traversierung des BST:\n");
    inorderPrint(root);
    free(fileContent);

    //DList
    *fileContent = readFile("C:\\Users\\jakob\\CLionProjects\\swe2-credit-project-filemanager\\albums.csv");
    head = parseCSVToDList(fileContent);
    printf("Print doubly linked list:\n");
    printDList(head);

    //Conversion
    AlbumNode *newBSTRoot = ConvertDoublyListToBinarySearchTree(head);
    DListNode *newDlistHead = ConvertBinarySearchTreeToDoublyList(root, NULL);

    //America
    freeBST(root);
    freeDList(head);
    free(fileContent);
}

void initMenu() {
    printf("\n===== Album Manager =====\n");
    printf("1. Add album to CSV\n");
    printf("2. Load CSV into BinarySearchTree and print (inorder)\n");
    printf("3. Load CSV into Doubly Linked List and print\n");
    printf("4. Convert BST to DList and print\n");
    printf("5. Convert DList to BST and print (inorder)\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}
