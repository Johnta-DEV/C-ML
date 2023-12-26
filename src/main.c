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

typedef enum Vegitables
{
	UnknownVegitable = 0,
	Bean = 1,
	BittegGourd = 2,
	BottleGourd = 3,
	Brinjal = 4,
	Broccoli = 5,
	Cabbage = 6,
	Capsicum = 7,
	Carrot = 8,
	Cauliflower = 9,
	Cucumber = 10,
	Papaya = 11,
	Potato = 12,
	Pumkin = 13,
	Radish = 14,
	Tomato = 15
} Vegitables;

int main(int argc, char *argv[])
{
	// Подключение кириллицы
	//setlocale(LC_ALL, "UTF8");
	#define DATASET_TRAIN_LOCATION "A:\\GitHub\\C\\samples\\Dataset\\ppm\\train\\"
	#define PATH_TO_SAVE_ML_MODEL "A:\\GitHub\\C\\mlmodels\\"

	#define LAYERS_COUNT 3
	size_t layers[LAYERS_COUNT] = {5, 6, 3};
	
	// Создаём модель	
	MlModel* pMlModel = MlCreateModel(layers, LAYERS_COUNT, true, 0.5);

	// Загружаем датасет
	MlDataset* pTrainDataset = LoadPPMDataset(DATASET_TRAIN_LOCATION);

	// Тренеруем модель
	TrainMlModel(pMlModel, pTrainDataset, 0.08);
	
	// Сохраняем модель
	SaveMlModel(pMlModel, PATH_TO_SAVE_ML_MODEL);


























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


	// size_t count;
	// Stopwatch sw;
	// StartStopwatch(&sw);
	// printf("Starting stopwatch...\n");

	// char** result = GetFilesInDirectory(DATASET_TRAIN_LOCATION, &count);
	
	// double elapsedTime = StopStopwatch(&sw);
	// printf("Stopwatch stopped! Elapsed: %f ms\n", elapsedTime);


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