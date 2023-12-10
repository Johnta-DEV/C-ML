#ifndef ML_HEADER
#define ML_HEADER

#include <stddef.h>

typedef struct MlNeuron MlNeuron;
typedef struct MlModel MlModel;

// Структура представляющая из себя еденичный нейрон
struct MlNeuron
{
	MlNeuron* InputNeurons;
	float* InputNeuronWeights;
	size_t InputNeuronsCount;
};

// Структура для хранения Machine Learning модели
struct MlModel
{
	MlNeuron** NeuronLayers;
};

MlModel* MlCreateModel(size_t* layers, size_t layersCount);

void MlPredict(MlModel* model);

#endif