#include "stdlib.h"
#include "time.h"

size_t rnd_previousRand = 0;

size_t Random()
{
	srand((unsigned)time(NULL) + rnd_previousRand);
	size_t rnd = rand();
	rnd_previousRand = rnd;
	return rnd;
}