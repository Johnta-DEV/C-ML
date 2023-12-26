#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>
#include <assert.h>

#include "johntalib_string.h"
#include "../johntalib/johntalib.h"

bool IsPathDirectory(const char* fullPath)
{
	DWORD attrs = GetFileAttributesA(fullPath);
	// 0x00000010(16) - битовая маска указывающая что полученный атрибут - это директория в ОС
	bool isDirectory = (attrs & 0x00000010) > 0; 
	return isDirectory;
}

// TODO: НЕ РАБОТАЭ
bool IsPathFile(const char* fullPath)
{
	DWORD attrs = GetFileAttributesA(fullPath);
	// (0x00000080)(128) - битовая маска указывающая что полученный атрибут - это директория в ОС
	bool isFile = (attrs & 0x00000080) > 0; 
	return isFile;
}

char** GetFilesInDirectory(const char* fullPath, size_t* outFilesCount)
{
	assert(fullPath != NULL);
	assert(outFilesCount != NULL);

	LinkedList* filesList = CreateLinkedList();

	WIN32_FIND_DATA data;
	char* searchDir = AppendCharArray(fullPath, "*", false); 
	HANDLE hFind = FindFirstFile(searchDir, &data); 
	
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
			char* fullPathOfItem = AppendCharArray(fullPath, &(data.cFileName), false);
			bool isFile = IsPathDirectory(fullPathOfItem) == false;
			if (isFile)
			{
				AddItemToLinkedList(filesList, fullPathOfItem, sizeof(char*));
			}
			else
			{
				free(fullPathOfItem);
			}
            //printf("--File: %s type: %s, is directory: %u\n", data.cFileName, fileType, isDirectory);
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
	free(searchDir);

	char** result = calloc(filesList->count, sizeof(char*));
	for (size_t i = 0; i < filesList->count; i++)
	{
		result[i] = (char*)(GetItemFromLinkedList(filesList, i)->ptr);
	}

	*outFilesCount = filesList->count;
	FreeLinkedList(filesList);

	return result;
}


// void TestFunc()
// {
// 		char dir[] = "C:\\";
	

// 	WIN32_FIND_DATA data;
// 	char* searchDir = AppendCharArray(dir, "*", false); 
// 	HANDLE hFind = FindFirstFile(searchDir, &data); 

//     if ( hFind != INVALID_HANDLE_VALUE ) {
//         do {
// 			char* fileType = GetFileExtension(data.cFileName);
			
// 			char* temp = AppendCharArray(&dir, &(data.cFileName), false);
// 			DWORD attrs = GetFileAttributesA(temp);
// 			free(temp);
// 			bool isDirectory = (attrs & 0x00000010) > 0; // 0x00000010(16) - битовая маска указывающая что полученный атрибут - это директория в ОС

//             printf("--File: %s type: %s, is directory: %u\n", data.cFileName, fileType, isDirectory);
// 			free(fileType);
//         } while (FindNextFile(hFind, &data));
//         FindClose(hFind);
//     }
// 	free(searchDir);

// }