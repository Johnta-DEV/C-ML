#include "pthread.h"

#include "thread.h"

void WaitAllThreads(pthread_t* threads, size_t threadsCount)
{
	for (size_t i = 0; i < threadsCount; i++)
	{
		pthread_join(threads[i], NULL);
	}
}