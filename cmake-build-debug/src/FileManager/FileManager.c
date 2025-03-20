#include "../Include/FileManger.h"

bool FileExists(const char *FilePath) {
    if (FilePath == NULL) {
        return false;
    }

    FILE *File = fopen(FilePath, "r");
    if (File) {
        fclose(File);
        return true;
    }
    return false;
}

char *ReadFile(const char *FilePath) {
    if (!FileExists(FilePath)) {
        return NULL;
    }

    FILE *File = fopen(FilePath, "r");
    if (!File) {
        return NULL;
    }

    fseek(File, 0, SEEK_END);
    long FileSize = ftell(File);
    rewind(File);

    if (FileSize <= 0) {
        fclose(File);
        return NULL;
    }

    char *Buffer = (char *)malloc(FileSize + 1);
    if (!Buffer) {
        fclose(File);
        return NULL;
    }

    fread(Buffer, 1, FileSize, File);
    Buffer[FileSize] = '\0';

    fclose(File);
    return Buffer;
}

bool WriteFile(const char *FilePath, const char *Data) {
    if (FilePath == NULL || Data == NULL) {
        return false;
    }

    FILE *File = fopen(FilePath, "w");
    if (!File) {
        return false;
    }

    if (fprintf(File, "%s", Data) < 0) {
        fclose(File);
        return false;
    }

    fclose(File);
    return true;
}

bool AppendToFile(const char *FilePath, const char *Data) {
    if (FilePath == NULL || Data == NULL) {
        return false;
    }

    FILE *File = fopen(FilePath, "a");
    if (!File) {
        return false;
    }

    if (fprintf(File, "%s", Data) < 0) {
        fclose(File);
        return false;
    }

    fclose(File);
    return true;
}

bool DeleteFile(const char *FilePath) {
    if (!FileExists(FilePath)) {
        return false;
    }

    return (remove(FilePath) == 0);
}

long GetFileSize(const char *FilePath) {
    if (!FileExists(FilePath)) {
        return -1;
    }

    FILE *File = fopen(FilePath, "r");
    if (!File) {
        return -1;
    }

    fseek(File, 0, SEEK_END);
    long FileSize = ftell(File);
    fclose(File);

    return FileSize;
}

bool CopyFile(const char *SourcePath, const char *DestinationPath) {
    if (!FileExists(SourcePath) || DestinationPath == NULL) {
        return false;
    }

    FILE *Source = fopen(SourcePath, "r");
    if (!Source) {
        return false;
    }

    FILE *Destination = fopen(DestinationPath, "w");
    if (!Destination) {
        fclose(Source);
        return false;
    }

    char Buffer[1024];
    size_t BytesRead;
    while ((BytesRead = fread(Buffer, 1, sizeof(Buffer), Source)) > 0) {
        fwrite(Buffer, 1, BytesRead, Destination);
    }

    fclose(Source);
    fclose(Destination);
    return true;
}

bool MoveFile(const char *SourcePath, const char *DestinationPath) {
    if (!FileExists(SourcePath) || DestinationPath == NULL) {
        return false;
    }

    if (rename(SourcePath, DestinationPath) == 0) {
        return true;
    }

    if (CopyFile(SourcePath, DestinationPath)) {
        return DeleteFile(SourcePath);
    }

    return false;
}

bool RenameFile(const char *OldName, const char *NewName) {
    if (!FileExists(OldName) || NewName == NULL) {
        return false;
    }

    return (rename(OldName, NewName) == 0);
}

