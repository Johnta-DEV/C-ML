#ifndef JOHNTALIB_STRING_HEADER
#define JOHNTALIB_STRING_HEADER

#include "../johntalib/johntalib.h"

bool IsPathDirectory(const char* fullPath);

bool IsPathFile(const char* fullPath);
char* GetLastItemFromPath(const char* fullPathToItem);
size_t LastIndexOfSubstring(const char* string, const char* substring);

char** GetFilesInDirectory(const char* fullPath, size_t* outFilesCount);
char** GetSubdirectoriesInDirectory(const char* fullPath, size_t* outDirectoriesCount);
char** GetItemsInDirectory(const char* fullPath, size_t* outItemsCount, bool addFiles, bool addSubdirectories);

#endif
