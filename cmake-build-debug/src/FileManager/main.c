#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Include/FileManger.h"
#include "../Include/DoublyLinkedList.h"
#include "../Include/BinarySearchTree.h"

// Enum, to know which datatype the user wants to have his file converted.
typedef enum {
    MODE_NONE,
    MODE_BST,
    MODE_DLL
} DataMode;
DataMode activeMode = MODE_NONE;
BSTNode *fileTree = NULL;
ListNode *fileList = NULL;
char currentFile[256] = "";

// Functions declaration
void InitMenu();
void SetFile();
void LoadIntoBST();
void LoadIntoDLL();
void InsertNewEntry();
void SaveToFile();
void PrintCurrentStructure();

int main(void) {
    int choice;

    while (1) {
        InitMenu();
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1: SetFile(); break;
            case 2: LoadIntoBST(); break;
            case 3: LoadIntoDLL(); break;
            // case 4: FreeList(&fileList); ConvertBtsToList(fileTree, &fileList); activeMode = MODE_DLL; printf("Converted to DLL.\n"); break;
            // case 5: FreeTree(fileTree); fileTree = ConvertListToBts(fileList); activeMode = MODE_BST; printf("Converted to BST.\n"); break;
            case 6: InsertNewEntry(); break;
            case 7: SaveToFile(); break;
            case 8: PrintCurrentStructure(); break;
            case 9:
                FreeTree(fileTree);
                FreeList(&fileList);
                printf("Tschau!\n");
            return 0;
            default: printf("Invalid choice.\n");
        }
    }
}

void SetFile() {
    printf("Enter file name: ");
    scanf("%255s", currentFile);
    printf("Current file set to '%s'\n", currentFile);
}

void InitMenu() {
    printf("\n=== Aj's File Manager ===\n");
    printf("1. Set File\n");
    printf("2. Load File into BinarySearchTree\n");
    printf("3. Load File into Doubly Linked List\n");
    printf("4. Convert BinarySearchTree => DoublyLinkedList\n");
    printf("5. Convert DoublyLinkedList => BinarySearchTree\n");
    printf("6. Insert New Entry\n");
    printf("7. Save to File\n");
    printf("8. Print Current Structure\n");
    printf("9. Exit\n");
    printf("Choose: ");
}

void LoadIntoBST() {
    if (!FileExists(currentFile)) {
        printf("Couldn't find file.\n");
        return;
    }

    char *content = ReadFile(currentFile);
    if (!content) {
        printf("Couldn't read file.\n");
        return;
    }

    fileTree = NULL; // reset
    char *line = strtok(content, "\n");
    while (line) {
        char name[256];
        long size;
        if (sscanf(line, "%255s %ld", name, &size) == 2)
            fileTree = InsertFileBts(fileTree, name, size);
        line = strtok(NULL, "\n");
    }

    activeMode = MODE_BST;
    printf("Data successfully loaded into BinarySearchTree.\n");
    free(content);
}

void LoadIntoDLL() {
    if (!FileExists(currentFile)) {
        printf("404 File not found.\n");
        return;
    }

    char *content = ReadFile(currentFile);
    if (!content) {
        printf("Failed to read file.\n");
        return;
    }

    FreeList(&fileList); // reset
    char *line = strtok(content, "\n");
    while (line) {
        char name[256];
        long size;
        if (sscanf(line, "%255s %ld", name, &size) == 2)
            InsertFileDll(&fileList, name, size);
        line = strtok(NULL, "\n");
    }

    activeMode = MODE_DLL;
    printf("Data successfully loaded into a doubly linked list.\n");
    free(content);
}

void InsertNewEntry() {
    char fileName[256];
    long fileSize;

    printf("Dateiname: ");
    scanf("%255s", fileName);
    printf("Dateigröße (Bytes): ");
    scanf("%ld", &fileSize);

    if (activeMode == MODE_BST) {
        fileTree = InsertFileBts(fileTree, fileName, fileSize);
        printf("Eingefügt in BST.\n");
    } else if (activeMode == MODE_DLL) {
        InsertFileDll(&fileList, fileName, fileSize);
        printf("Eingefügt in DLL.\n");
    } else {
        printf("Keine Datenstruktur aktiv. Bitte zuerst laden.\n");
    }
}

void SaveToFile() {
    if (strlen(currentFile) == 0) {
        printf("Kein Dateiname gesetzt. Verwende Option 1 zuerst.\n");
        return;
    }

    ListNode *outputList = NULL;

    if (activeMode == MODE_DLL) {
        outputList = fileList;
    } else if (activeMode == MODE_BST) {
        // ConvertBSTToList(fileTree, &outputList);
    } else {
        printf("Keine Datenstruktur aktiv.\n");
        return;
    }

    FILE *f = fopen(currentFile, "w");
    if (!f) {
        printf("Konnte Datei nicht öffnen.\n");
        return;
    }

    ListNode *temp = outputList;
    while (temp) {
        fprintf(f, "%s %ld\n", temp->FileName, temp->FileSize);
        temp = temp->Next;
    }

    fclose(f);
    printf("Daten gespeichert in '%s'.\n", currentFile);

    if (activeMode == MODE_BST)
        FreeList(&outputList);  // war nur temporär
}

void PrintCurrentStructure() {
    if (activeMode == MODE_BST) {
        printf("=== BST (Sorted) ===\n");
        PrintTree(fileTree);
    } else if (activeMode == MODE_DLL) {
        printf("=== Doubly Linked List ===\n");
        PrintList(fileList);
    } else {
        printf("No data structure active.\n");
    }
}
