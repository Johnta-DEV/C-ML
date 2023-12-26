#ifndef JOHNTALIB_STRING_HEADER
#define JOHNTALIB_STRING_HEADER

#include "../johntalib/johntalib.h"

bool IsPathDirectory(const char* fullPath);

bool IsPathFile(const char* fullPath);

char** GetFilesInDirectory(const char* fullPath, size_t* outFilesCount);

#endif
