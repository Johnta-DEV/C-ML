#ifndef JOHNTA_LIB_HEADER
#define JOHNTA_LIB_HEADER

#include <stdbool.h>

#define null NULL
#define bool unsigned char
#define MAX_FILE_PATH 260

typedef struct ListItem ListItem;
typedef struct LinkedList LinkedList; 
typedef struct Stopwatch Stopwatch;


struct ListItem
{
	void* ptr;
	size_t size;
	ListItem* nextItem;
};
struct LinkedList
{
	ListItem* firstItem;
	ListItem* lastItem;
	size_t count;
};

struct Stopwatch
{
	bool IsRunning;
	double StartTime;
	double EndTime;
	double ElapsedTime;
};

char* AppendCharArray(char* targetStr, const char* sourceStr, bool freeTargetString);
// Возвращает новый указатель на строку в которой хранится расширение файла. Если у файла нет расширения - вернёт NULL
char* GetFileExtension(const char* fileName);

LinkedList* CreateLinkedList();
LinkedList* AddItemToLinkedList(LinkedList* list, void* entityPtr, size_t entitySize);
ListItem* GetItemFromLinkedList(LinkedList* list, size_t index);
void FreeLinkedList(LinkedList* list);

void StartStopwatch(Stopwatch* p_sw);
double StopStopwatch(Stopwatch* p_sw);

#endif