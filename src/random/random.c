#include "stdlib.h"
#include "time.h"
#include "random.h"

size_t rnd_previousRand = 0;

size_t Random()
{
	srand((unsigned)time(NULL) + rnd_previousRand);
	size_t rnd = rand();
	rnd_previousRand = rnd;
	return rnd;
}

float RandomFloat(float min, float max)
{
	float value = Random01();
	return Lerp(min, max, value);
}

float Random01()
{
	srand((unsigned)time(NULL) + rnd_previousRand);
	size_t rnd = rand();
	rnd_previousRand = rnd;
	return (float)rnd / ((float)RAND_MAX);
}

float Lerp(float a, float b, float value)
{
	return a + (b - a) * Clamp01(value);
}

float InverseLerp(float a, float b, float value)
{
	if (a != b)
		return Clamp01((value - a) / (b - a));
	else
		return 0;
}

float Clamp(float min, float max, float value)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

float Clamp01(float value)
{
	return Clamp(0, 1, value);
}
