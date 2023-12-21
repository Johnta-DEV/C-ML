#define DEBUG

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h> 
#include <windows.h>

#include "ml/ml.h"
#include "ml/ml-dataset.h"
#include "random/random.h"
#include "thread/thread.h"
#include "johntalib/johntalib.h"
#include "string/johntalib_string.h"

#include "disk/diskSpace.h"


int main()
{
	// Подключение кириллицы
	//setlocale(LC_ALL, "UTF8");

	#define LAYERS_COUNT 3
	size_t layers[LAYERS_COUNT] = {5, 6, 3};
	
	
	MlCreateModel(layers, LAYERS_COUNT, true, 0.5);

	// MlModel* model = MlCreateModel(layers, LAYERS_COUNT, true, 0.5);

	// printf("Rand Float: %f\n", RandomFloat(0, 1));

	// char temp[] = "Hello";

	// // int sizeOfChar = sizeof(char);
	// // int strLength = strlen(temp);
	// // printf("I: %u\n", sizeOfChar);
	// // printf("S: %u\n", strLength);
	// //int strSize = strlen(temp) * sizeof(char);
	// char* dest = calloc(strlen(temp), sizeof(char));
	
	// memcpy(dest, temp, strlen(temp) * sizeof(char));

	// char source[] = " World!";

	// char* result = AppendCharArray(dest, &source, false);

	// printf("Result: %s\n", result);

	// printf("----END-----\n");


	//MlLoadPPMImage("Test.ppm", 0);
	LoadPPMDataset("");

	//double total;
	//double free = GetDiskFreeSpaceMB(".", &total);
	// int* varA = malloc(sizeof(int));
	//int* varB = malloc(sizeof(int));
	// int varA = 13;
	// int varB = 22;
	
	// LinkedList* list = CreateLinkedList(&varA, sizeof(int));

	// AddItemToLinkedList(list, &varB, sizeof(int));

	// ListItem* item = GetItemFromLinkedList(list, 1);

	// int value = *((int*)item->ptr);
	// printf("Value 2: %u", *((int*)item->ptr));


	size_t count;
	char** result = GetFilesInDirectory("C:\\", &count);
// #pragma region Multithreading
// 	// #define THREADS_COUNT 3
// 	// printf("Creating %u threads...\n", THREADS_COUNT);
// 	// pthread_t threads[THREADS_COUNT];
// 	// for (size_t i = 0; i < THREADS_COUNT; i++)
// 	// {
//     // 	pthread_create(&threads[i], NULL, &ThreadTestFunc, NULL);
// 	// }
// 	// WaitAllThreads(threads, THREADS_COUNT);
// #pragma endregion

	return 0;
}