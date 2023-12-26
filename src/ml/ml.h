#ifndef ML_HEADER
#define ML_HEADER

#include <stddef.h>
#include <stdbool.h>
#include "ml-dataset.h"

typedef struct MlNeuron MlNeuron;
typedef struct MlModel MlModel;

// Структура представляющая из себя еденичный нейрон
struct MlNeuron
{
	MlNeuron* InputNeurons;
	float* InputNeuronWeights;
	size_t InputNeuronsCount;
	size_t CurrentNeuronIndex;
	float Bias;
	float Value;
};

// Структура для хранения Machine Learning модели
struct MlModel
{
	MlNeuron** NeuronLayers;
	size_t* NeuronsPerLayer;
	size_t LayersCount;
};

// Создать ML модель
MlModel* MlCreateModel(size_t* layers, size_t layersCount, bool assignRandomWeights, float bias);

// Функция активации неирона (MlNeuron)
float ActivationFunc(MlNeuron* neurons, size_t neuronsCount, float bias);

// Функция-сигмоид (используется например в активации неирона)
float Sigmoid(float input);

void MlPredict(MlModel* model, float* dataInput, int dataInputCount);

// Обучить ML модель.
void TrainMlModel(MlModel* model, MlDataset* dataset, float learningRate);

// Загрузить ML модель с диска
MlModel* LoadMlModel(const char* fullPath);
// Сохранить модель
bool SaveMlModel(MlModel* model, const char* fullPath);

#endif