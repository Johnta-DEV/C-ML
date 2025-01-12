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


// TODO: проверить
char* GetLastItemFromPath(const char* fullPathToItem)
{
	assert(fullPathToItem != NULL);
	
	char* result = NULL;

	// Идём с конца и ищем слэш
	size_t lastSlashIndex = LastIndexOfSubstring(fullPathToItem, "\\")
	
	if (lastSlashIndex > 0)
	{
		size_t fullPathLength = strlen(fullPathToItem);
		size_t resultLength = fullPathLength - lastSlashIndex;
		assert(resultLength > 0);

		result = malloc(sizeof(char) * resultLength);
		memcpy(result, fullPathToItem + (sizeof(char) * lastSlashIndex), resultLength);
	}

	return result;
}

size_t LastIndexOfSubstring(const char* string, const char* substring)
{
	assert(string != NULL);
	assert(sbustring != NULL);

	size_t stringLength = strlen(string);
	size_t substringLength = strlen(substring);
	
	assert(stringLength > substringLength);

	size_t result = -1;

	for (size_t i = stringLength - substringLength; i >= 0; i--)
	{
		bool totalMatch = true;
		for (size_t c = 0; c < substringLength; c++)
		{
			if (string[i] != substring[c])
			{
				totalMatch = false;
				break;
			}
		}
		
		if (totalMatch)
		{
			result = i;
			break;
		}
	}

	return result;
}



char** GetFilesInDirectory(const char* fullPath, size_t* outFilesCount)
{
	return GetItemsInDirectory(fullPath, outFilesCount, true, false);
}

char** GetSubdirectoriesInDirectory(const char* fullPath, size_t* outDirectoriesCount)
{
	return GetItemsInDirectory(fullPath, outDirectoriesCount, false, true);
}


// TODO: протестить
char** GetItemsInDirectory(const char* fullPath, size_t* outItemsCount, bool addFiles, bool addSubdirectories)
{
	assert(fullPath != NULL);
	assert(outItemsCount != NULL);

	LinkedList* filesList = CreateLinkedList();

	WIN32_FIND_DATA data;
	char* searchDir = AppendCharArray(fullPath, "*", false); 
	HANDLE hFind = FindFirstFile(searchDir, &data); 
	
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
			if (data.cFileName[strlen(data.cFileName) - 1] == '.')
				continue;

			char* fullPathOfItem = AppendCharArray(fullPath, &(data.cFileName), false);
			bool isFile = IsPathDirectory(fullPathOfItem) == false;
			
			if ((addFiles && isFile) || (addSubdirectories && isFile == false))
			{
				AddItemToLinkedList(filesList, fullPathOfItem, sizeof(char*));
				continue;
			}

			free(fullPathOfItem);

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

	*outItemsCount = filesList->count;
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