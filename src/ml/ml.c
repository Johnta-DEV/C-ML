#include "ml.h"
#include "assert.h"
#include "stdio.h"
#include "locale.h"
#include "stdlib.h"
#include <stddef.h>

// Создаёт модель ML. Принимает int массив с колвом нейронов в каждом слое
MlModel* MlCreateModel(size_t* layers, size_t layersCount)
{
	//printf("Trying to create ML model...");
	
	MlModel* resultModel = malloc(sizeof(MlModel));
	resultModel->NeuronLayers = malloc(sizeof(MlNeuron) * layersCount);
	
	MlNeuron* previousLayer = NULL;
	int previousLayerSize = 0;
	
	// Проходимся по всем слоям модели
	for (size_t i = 0; i < layersCount; i++)
	{
		size_t curLayerNeuronsCount = *(layers + i);
		MlNeuron** curLayer = malloc(sizeof(MlNeuron) * curLayerNeuronsCount);

		// Проходимся по всем неиронам в текущем слое
		for (size_t n = 0; n < curLayerNeuronsCount; n++)
		{
			MlNeuron* neuron = malloc(sizeof(MlNeuron));
			if (previousLayer != NULL)
			{
				// Проходимся по всем неиронам в предыдущем слое
				for (size_t z = 0; z < previousLayerSize; z++)
				{
					neuron->InputNeurons = previousLayer;
					neuron->InputNeuronWeights = malloc(sizeof(float) * previousLayerSize);
					neuron->InputNeuronsCount = previousLayerSize;
				}
			}
			// Сохраняем указатель на текущий неирон в текущий слой
			*(curLayer + n) = neuron;
		}
		
		*(resultModel->NeuronLayers + i) = *curLayer;
		previousLayerSize = curLayerNeuronsCount;
		previousLayer = *curLayer;
	}
	
	return resultModel;
}

// Предскзать результат с помощью ML
void MlPredict(MlModel* trainedModel)
{
	assert(trainedModel != NULL);
	
	printf("Ml model not empty... Yeeeeeah!");
}