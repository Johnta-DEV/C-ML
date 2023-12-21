#ifndef ML_DATASET_HEADER
#define ML_DATASET_HEADER

#include "stdlib.h"
#include "../johntalib/johntalib.h"

typedef struct MlDataset MlDataset;
typedef struct MlDatasetItem MlDatasetItem;

// Элемент датасета ML модели
struct MlDatasetItem
{
	// Категория которой соответствует данный элемент датасета
	size_t CategoryType;
	// Длинна данных. Должна совпадать с кол-вом входных неиронов ML модели
	size_t DataLength;
	// Массив данных для обучения/предсказания ML модели
	float* Data;
};

// Датасет ML модели. Может использоваться например для обучения
struct MlDataset
{
	// Кол-во неиронов которое должно быть в ML модели
	int InputNeuronsCount;
	// Кол-во элементов в датасете
	int ItemsCount;
	// Элементы датасета
	MlDatasetItem* Items;
};


MlDatasetItem* MlLoadPPMImage(const char* relativePathToFile, size_t mlCategoryType);

LinkedList* MlLoadPPMImagesFromDirectory(const char* directory, MlDataset* dataset, size_t mlCategoryType);

MlDataset* LoadPPMDataset(const char* relativeFolderPath);

#endif