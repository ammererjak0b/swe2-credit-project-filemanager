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

bool appendAlbumToCSV(const char *filename, const char *artist, const char *album, int year);
void addAlbumToCSV(const char *filename);
void loadBSTAndPrint(const char *filename);
void loadDListAndPrint(const char *filename);
void convertBSTtoDListAndPrint(const char *filename);
void convertDListToBSTAndPrint(const char *filename);
void printAllAlbumsDirectly(const char *filename);
void initMenu(void);
void test();

int main(void) {
    //test();





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
    printf("\n===== Album Manager =====\n");
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
    char artist[100], album[100];
    int year;
    int ch;

    printf("Enter artist: ");
    fgets(artist, sizeof(artist), stdin);
    artist[strcspn(artist, "\n")] = '\0';  // remove newline

    printf("Enter album: ");
    fgets(album, sizeof(album), stdin);
    album[strcspn(album, "\n")] = '\0';

    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        fprintf(stderr, "Invalid year input.\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        return;
    }
    while ((ch = getchar()) != '\n' && ch != EOF); // clear buffer

    if (appendAlbum(filename, artist, album, year)) {
        printf("Album added successfully!\n");
    } else {
        printf("Error adding album.\n");
    }
}

void loadBSTAndPrint(const char *filename) {
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

void loadDListAndPrint(const char *filename) {
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

void convertBSTtoDListAndPrint(const char *filename) {
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

void convertDListToBSTAndPrint(const char *filename) {
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

void printAllAlbumsDirectly(const char *filename) {
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
        if (lineNumber > 0) { // skip header
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
