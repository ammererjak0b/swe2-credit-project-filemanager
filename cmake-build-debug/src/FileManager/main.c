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

void addAlbumToCSV(const char *filename);
void prepareBinarySearchTree(const char *filename);
void prepareDoublyList(const char *filename);
void prepareConversationBstToDList(const char *filename);
void prepareConversationDListToBst(const char *filename);
void printAlbums(const char *filename);
void initMenu(void);
void test();

int main(void) {
    //test();

    char filePath[256] = "";
    int choice;

    printf("Please choose a file (enter file path): ");
    scanf("%255s", filePath);

    // Guard against Null in filePath
    if (filePath == "") {
        return EXIT_FAILURE;
    }

    // Menu Loop
    while (1) {
        initMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addAlbumToCSV(filePath);
                break;
            case 2:
                prepareBinarySearchTree(filePath);
                break;
            case 3:
                prepareDoublyList(filePath);
                break;
            case 4:
                prepareConversationBstToDList(filePath);
                break;
            case 5:
                prepareConversationDListToBst(filePath);
                break;
            case 6:
                printAlbums(filePath);
                break;
            case 7:
                printf("Exiting...\n");
            exit(0);
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}

void test() {
    char *fileContent = readFile("C:\\Users\\jakob\\CLionProjects\\swe2-credit-project-filemanager\\albums.csv");
    // Guard Against Null
    if (fileContent == NULL) {
        ferror("Error: Could not read file...");
        return;
    }

    //BST
    root = parseCsvToBst(fileContent);
    printf("Inorder Traversierung des BST:\n");
    inorderPrint(root);
    free(fileContent);

    //DList
    *fileContent = readFile("C:\\Users\\jakob\\CLionProjects\\swe2-credit-project-filemanager\\albums.csv");
    head = parseCSVToDoublyList(fileContent);
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
    printf("\n----- Jakob's Album Manager -----\n");
    printf("1. Add album to CSV\n");
    printf("2. Load CSV into BST and print (inorder)\n");
    printf("3. Load CSV into Doubly Linked List and print\n");
    printf("4. Convert BST to Doubly Linked List and print\n");
    printf("5. Convert Doubly Linked List to BST and print (inorder)\n");
    printf("6. Print all albums directly\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

void addAlbumToCSV(const char *filename) {
    char artist[100] = "", album[100] = "";
    int year = 0;

    getchar();
    printf("Enter artist: \n"); // WHY DOES THIS NOT WORK AMK
    scanf("%[^\n]", artist);

    getchar();
    printf("Enter album: \n");
    scanf("%[^\n]", album);

    getchar();
    printf("Enter year: \n");
    scanf("%d", &year);

    if (appendAlbum(filename, artist, album, year)) {
        printf("Album added successfully!\n");
    } else {
        printf("Error adding album.\n");
    }
}

void printAlbums(const char *filename) {
    char *content = readFile(filename);
    if (!content) {
        printf("Error reading CSV file.\n");
        return;
    }
    char *saveptrLine = NULL;
    char *line = strtok_r(content, "\n", &saveptrLine);
    int lineNumber = 0;
    printf("\nAll Albums:\n");
    while (line != NULL) {
        if (lineNumber > 0) {
            char *saveptrToken;
            char *artist = strtok_r(line, ",", &saveptrToken);
            char *album  = strtok_r(NULL, ",", &saveptrToken);
            char *yearStr = strtok_r(NULL, ",", &saveptrToken);
            if (artist && album && yearStr) {
                printf("Artist: %s, Album: %s, Year: %s\n", artist, album, yearStr);
            }
        }
        line = strtok_r(NULL, "\n", &saveptrLine);
        lineNumber++;
    }
    free(content);
}

void prepareBinarySearchTree(const char *filename) {
    char *content = readFile(filename);
    if (!content) {
        printf("Error reading CSV file.\n");
        return;
    }
    AlbumNode *bst = parseCsvToBst(content);
    printf("\nBST Inorder Traversal:\n");
    inorderPrint(bst);
    freeBST(bst);
    free(content);
}

void prepareDoublyList(const char *filename) {
    char *content = readFile(filename);
    if (!content) {
        printf("Error reading CSV file.\n");
        return;
    }
    DListNode *dlist = parseCSVToDoublyList(content);
    printf("\nDoubly Linked List:\n");
    printDList(dlist);
    freeDList(dlist);
    free(content);
}

void prepareConversationBstToDList(const char *filename) {
    char *content = readFile(filename);
    if (!content) {
        printf("Error reading CSV file.\n");
        return;
    }
    AlbumNode *bst = parseCsvToBst(content);
    free(content);
    DListNode *dlist = ConvertBinarySearchTreeToDoublyList(bst, NULL);
    printf("\nBST to Doubly Linked List Conversion:\n");
    printDList(dlist);
    freeBST(bst);
    freeDList(dlist);
}

void prepareConversationDListToBst(const char *filename) {
    char *content = readFile(filename);
    if (!content) {
        printf("Error reading CSV file.\n");
        return;
    }
    DListNode *dlist = parseCSVToDoublyList(content);
    free(content);
    AlbumNode *bst = ConvertDoublyListToBinarySearchTree(dlist);
    printf("\nDoubly Linked List to BST Conversion (Inorder):\n");
    inorderPrint(bst);
    freeDList(dlist);
    freeBST(bst);
}

