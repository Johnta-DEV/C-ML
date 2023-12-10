#include "ml.h"
#include "assert.h"
#include "stdio.h"
#include "locale.h"
#include "stdlib.h"
#include <stddef.h>

// Создаёт модель ML. Принимает int массив с колвом нейронов в каждом слое
MlModel* MlCreateModel(size_t* layers, size_t layersCount)
{
	printf("Creating ML model with %u layers...\n", layersCount);
	
	const size_t SIZE_OF_NEURON = sizeof(MlNeuron);

	MlModel* resultModel = malloc(sizeof(MlModel));
	resultModel->NeuronLayers = calloc(layersCount, SIZE_OF_NEURON);
	resultModel->NeuronLayersCount = layersCount;

	MlNeuron* previousLayer = NULL;
	int previousLayerSize = 0;
	
	// Проходимся по всем слоям модели
	for (size_t i = 0; i < layersCount; i++)
	{
		size_t curLayerNeuronsCount = layers[i];
		MlNeuron* curLayer = calloc(curLayerNeuronsCount, SIZE_OF_NEURON);

		// Проходимся по всем неиронам в текущем слое
		for (size_t n = 0; n < curLayerNeuronsCount; n++)
		{
			MlNeuron* neuron = &curLayer[n];
			
			// Проходимся по всем неиронам в предыдущем слое
			if (previousLayer != NULL)
			{
				for (size_t z = 0; z < previousLayerSize; z++)
				{
					neuron->InputNeurons = previousLayer;
					neuron->InputNeuronWeights = calloc(previousLayerSize, sizeof(float));
					neuron->InputNeuronsCount = previousLayerSize;
					neuron->CurrentNeuronIndex = n;
				}
			}
			// Если предыдущего слоя нет - просто инициализируем нейрон пустыми значениями
			else
			{
				neuron->InputNeurons = NULL;	
				neuron->InputNeuronWeights = NULL;
				neuron->InputNeuronsCount = 0;
				neuron->CurrentNeuronIndex = n;
			}
		}
		
		resultModel->NeuronLayers[i] = curLayer;

		previousLayerSize = curLayerNeuronsCount;
		previousLayer = curLayer;
	}
	
	printf("ML model with %u layers created!\n", layersCount);
	return resultModel;
}

// Предскзать результат с помощью ML
void MlPredict(MlModel* trainedModel)
{
	assert(trainedModel != NULL);
	
	printf("Ml model not empty... Yeeeeeah!");
}