/* -------------------------------
 * FILE MANAGEMENT SYSTEM
 * Provides functions for handling file operations safely.
 * -------------------------------
 */

#ifndef FILEMANGER_H
#define FILEMANGER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Functions
bool FileExists(const char *FilePath);
char *ReadFile(const char *FilePath);
bool WriteFile(const char *FilePath, const char *Data);
bool AppendToFile(const char *FilePath, const char *Data);
bool DeleteFile(const char *FilePath);
long GetFileSize(const char *FilePath);
bool CopyFile(const char *SourcePath, const char *DestinationPath);
bool MoveFile(const char *SourcePath, const char *DestinationPath);
bool RenameFile(const char *OldName, const char *NewName);
#endif //FILEMANGER_H
