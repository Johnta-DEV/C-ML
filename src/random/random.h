#ifndef RANDOM_HEADER
#define RANDOM_HEADER

#include <stddef.h>

size_t Random();

float RandomFloat(float min, float max);

float Random01();

float Lerp(float a, float b, float value);

float InverseLerp(float a, float b, float value);

float Clamp(float min, float max, float value);

float Clamp01(float value);

#endif