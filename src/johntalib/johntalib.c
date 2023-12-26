#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "johntalib.h"

char* AppendCharArray(char* targetStr, const char* sourceStr, bool freeTargetString)
{
    size_t charsCountInTarget = strlen(targetStr);
    size_t charsCountInSourceStr = strlen(sourceStr);

    char* newStr = calloc(charsCountInTarget + charsCountInSourceStr + 1, sizeof(char));
    memcpy(newStr, targetStr, charsCountInTarget);
    memcpy(newStr + (charsCountInTarget * sizeof(char)), sourceStr, charsCountInSourceStr);

    if (freeTargetString)
        free(targetStr);
    return newStr;
}

char* GetFileExtension(const char* fileName)
{
    assert(fileName != NULL);
    size_t strLen = strlen(fileName);
    assert(strLen > 0);
    assert(strLen <= MAX_FILE_PATH);

    char* result = calloc(MAX_FILE_PATH, sizeof(char));
    size_t resultPointer = 0;
    bool isComaFound = false;

    // Копируем расширение файла с конца до точки
    for (size_t i = strLen - 1; i > 0; i--)
    {
        char ch = fileName[i];
        if (ch == '.')
        {
            isComaFound = true;
            break;
        }
        result[resultPointer] = ch;
        resultPointer++;
    }

    // Инвертируем получившуюся строку
    size_t resultLen = strlen(result);
    size_t swapIterations = (resultLen / 2) + 1;
    resultPointer = resultLen - 1;
    for (size_t i = 0; i < swapIterations; i++)
    {
        char tempCh = result[i];
        result[i] = result[resultPointer];
        result[resultPointer] = tempCh;
        resultPointer--;
    }
    
    
    if (isComaFound == false)
    {
        free(result);
        return NULL;
    }
    
    return result;
}


LinkedList* CreateLinkedList()
{
    LinkedList* list = malloc(sizeof(LinkedList));

    list->firstItem = NULL;
    list->lastItem = NULL;
    list->count = 0;

    return list;
}

LinkedList* AddItemToLinkedList(LinkedList* list, void* entityPtr, size_t entitySize)
{
    assert(list != NULL);

    ListItem* item = malloc(sizeof(ListItem));
    item->ptr = entityPtr;
    item->size = entitySize;
    item->nextItem = NULL;

    if (list->firstItem == NULL)
        list->firstItem = item;

    //if (list->lastItem == NULL)
    if (list->lastItem != NULL)
    {
        list->lastItem->nextItem = item;
        //list->lastItem = item;
    }

    list->lastItem = item;
    list->count++;

    return list;
}

ListItem* GetItemFromLinkedList(LinkedList* list, size_t index)
{
    assert(list != NULL);
    assert(index >= 0);
    assert(index < list->count);

    ListItem* result = NULL;
    
    ListItem* nextItem = list->firstItem;
    
    size_t i = 0;
    do
    {
        if (i == index)
        {
            result = nextItem;
            break;
        }

        nextItem = nextItem->nextItem;
        i++;
    }while(i <= index);

    return result;
}

void FreeLinkedList(LinkedList* list)
{
    assert(list != NULL);

    ListItem* nextItem = list->firstItem;
    ListItem* temp = NULL;

    while(nextItem != NULL)
    {
        temp = nextItem;
        nextItem = nextItem->nextItem;
        free(temp);
    }

    free(list);
}


void StartStopwatch(Stopwatch* p_sw)
{
    assert(p_sw != NULL);

    p_sw->StartTime = clock();
    p_sw->EndTime = p_sw->StartTime;
    p_sw->IsRunning = true;
}

double StopStopwatch(Stopwatch* p_sw)
{
    assert(p_sw != NULL);

    p_sw->EndTime = clock();
    p_sw->IsRunning = false;
    p_sw->ElapsedTime = p_sw->EndTime - p_sw->StartTime;

    return p_sw->ElapsedTime;
}