#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <fileapi.h>
#include <winnt.h>

#include "ml-dataset.h"
#include "../johntalib/johntalib.h"
#include "../string/johntalib_string.h"

#define PPM_FILE_HEADER_OFFSET 12

typedef struct
{
    char* DirectoryName;
    int DirectoryIntRepresentation;
} DirectoryNameWithIntRepresentation;


// Загружает .PPM файл в сущность MlDatasetItem. Сохраняются все 3 цветовых канала (RGB).
MlDatasetItem* MlLoadPPMImage(const char* relativePathToFile, size_t mlCategoryType)
{
    //
    // Получаем полный путь к рабочей директории и сохраняем её в переменную workingDir 
    //
    char workingDir[MAX_FILE_PATH];
    getcwd(workingDir, sizeof(workingDir));

    //
    // Добавляем к строке относительный путь к файлу
    //
    char* fullFilePath = AppendCharArray(workingDir, "\\", false);
    fullFilePath = AppendCharArray(fullFilePath, relativePathToFile, false);
    
    printf("Opening file: %s\n", fullFilePath);

    //
    // Открываем файл, получаем его длинну и устанавливаем курсор на начало файла
    //
    FILE* file = fopen(fullFilePath, "rb");
    fseek(file, 0, SEEK_END);
    unsigned long fileLen = ftell(file);
    rewind(file); 


    bool isFileOpened = fileLen != -1L;
    if (isFileOpened == false)
    {
        printf("Can`t open file %s\n", fullFilePath);
        assert(isFileOpened);
    }

    //
    // Создаём буфер. Выделям ему память, копируем содержимое файла в буфер и закрываем файл
    //
    char* buffer = (char *)malloc(fileLen * sizeof(char));
    fread(buffer, fileLen, 1, file);
    fclose(file);

    //
    // Получем длинну полезных данных в файле, выделяем память под массив. Проходимся по всем элементам буфера
    // и преобразуем байты (0-255) в float значени 0-1.
    //
    size_t floatArrayLength = fileLen - PPM_FILE_HEADER_OFFSET;
    float* floatArray = calloc(floatArrayLength, sizeof(float));
    size_t floatArrayPointer = 0;

    for (size_t i = PPM_FILE_HEADER_OFFSET; i < fileLen; i++)
    {
        unsigned char ch = buffer[i];
        float value = ((float)ch / 255.0);
        floatArray[floatArrayPointer] = value;
        floatArrayPointer++;
    }
    
    MlDatasetItem* result = malloc(sizeof(MlDatasetItem));
    result->CategoryType = mlCategoryType;
    result->DataLength = floatArrayLength;
    result->Data = floatArray;
    
    return result;
}

LinkedList* MlLoadPPMImagesFromDirectory(const char* directory, MlDataset* dataset, size_t mlCategoryType)
{
    LinkedList* list = CreateLinkedList();



    return list;
}

MlDataset* LoadPPMDataset(const char* relativeFolderPath)
{
    //
    // Получаем полный путь к рабочей директории и сохраняем её в переменную workingDir 
    //
    char workingDir[MAX_FILE_PATH] = { 0 };
    //getcwd(workingDir, sizeof(workingDir));

    //
    // Добавляем к строке относительный путь к файлу
    //
    memcpy(workingDir, relativeFolderPath, strlen(relativeFolderPath));
    char* fullDirectoryPath = &workingDir;
    size_t pathLength = strlen(fullDirectoryPath);

    if (fullDirectoryPath[pathLength - 1] != '\\')
        fullDirectoryPath = AppendCharArray(fullDirectoryPath, "\\", false);

    //fullDirectoryPath = AppendCharArray(fullDirectoryPath, relativeFolderPath, false);

    //
    // Получаем список всех суб директорий
    //
    size_t subFoldersCount = 0;
    char** pSubdirectories = GetSubdirectoriesInDirectory(fullDirectoryPath, &subFoldersCount);

    long currentCategory = 0;
    for (size_t i = 0; i < subFoldersCount; i++)
    {
        // Отделять из пути всё что после последнего слеша и это пихать в atoi
        char* currentFolderFullPath = pSubdirectories[i];
        
        char* currentFolderName = GetLastItemFromPath(currentFolderFullPath);

        currentCategory = atoi(currentFolderName);

        // Если имя папки - число, значит это категория
        if (currentCategory > 0)
        {

        }
    }
    
    //
    // Чистим чистим
    //
    for (size_t i = 0; i < subFoldersCount; i++)
        free(pSubdirectories[i]);
    



    //
    // Конвертируем строку в int через atoi()
    //
    //size_t v = atoi("34");

    // - Открываем директорию
    // - Получаем список всех файлов/папок
    // - Для каждой папки берём её имя и конвертируем в число (оно будет категорией)
    // - Для всех .ppm файлов в директории (и для всех директорий) проходимся по всем файлам и загружаем их
    //   в какой нить буфер
    // - из буфера буфера загружаем их в итоговую структуру



    struct dirent *de;  
    char * directoryPath = NULL;
    // opendir() возвращает указатель на тип DIR  
    DIR *directory = opendir(fullDirectoryPath); 
  
    if (directory == NULL) 
    { 
        printf("Could not open directory: %s\n", directoryPath );
        return 0; 
    } 
  
    LinkedList* directoriesList = CreateLinkedList();

    //
    // Собираем все папки в которых имя - число в список
    //

    while ((de = readdir(directory)) != NULL) 
    {
        //if (de->d_type == DT_REG)
        //{
            char* currentDirectoryName = de->d_name;
            int convertedFolderNameToInt = atoi(currentDirectoryName);
            
            if (convertedFolderNameToInt > 0)
            {
                DirectoryNameWithIntRepresentation* d = malloc(sizeof(DirectoryNameWithIntRepresentation));
                char* dirNameCopy = malloc(MAX_FILE_PATH);
                
                d->DirectoryName = strcpy(dirNameCopy, de->d_name);
                d->DirectoryIntRepresentation = convertedFolderNameToInt;
                AddItemToLinkedList(directoriesList, d, sizeof(DirectoryNameWithIntRepresentation));
            }
            
            //#if DEBUG
            //printf("Directory name: %s, int: %u, type: %s\n", de->d_name, convertedFolderNameToInt, de->d_);
            //#endif
        //}
    }   

    free(directoryPath);
    closedir(directory);     


    //unsigned long long diskFreeSpaceInMB = (*lpTotalNumberOfFreeBytes).QuadPart;// * 1024 * 1024;
    //printf("Free MBytes: %d", lpTotalNumberOfFreeBytes);
    // Далее необходимо заходить в каждую директорию и открывать все файлы с расширением .ppm
    for (size_t i = 0; i < directoriesList->count; i++)
    {
        ListItem* item = GetItemFromLinkedList(directoriesList, i);
        
    }
     
         
  
    return 0; 
}