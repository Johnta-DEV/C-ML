#include "stdio.h"
#include <locale.h>
#include "stdlib.h"
#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h> 

#include "ml/ml.h"
#include "random/random.h"
#include "threads/threads.h"


void ThreadTestFunc()
{
	size_t randomNumber = Random();
	sleep(randomNumber % 5);
	printf("Thread %u started...\n", randomNumber);
}

int main()
{
	// Подключение кириллицы
	//setlocale(LC_ALL, "UTF8");

	#define LAYERS_COUNT 3
	size_t layers[LAYERS_COUNT] = {5, 6, 3};

	MlModel* model = MlCreateModel(&layers, LAYERS_COUNT);


#pragma region Multithreading
	// #define THREADS_COUNT 3
	// printf("Creating %u threads...\n", THREADS_COUNT);

	// pthread_t threads[THREADS_COUNT];
	// for (size_t i = 0; i < THREADS_COUNT; i++)
	// {
    // 	pthread_create(&threads[i], NULL, &ThreadTestFunc, NULL);
	// }
	// WaitAllThreads(threads, THREADS_COUNT);
#pragma endregion

	return 0;
}