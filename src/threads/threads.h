#ifndef THREADS_HEADER
#define THREADS_HEADER

// Ожидает завершения всех потоков
void WaitAllThreads(pthread_t* threads, size_t threadsCount);

#endif

