#include "assert.h"
#include "stdio.h"
#include "locale.h"
#include "stdlib.h"
#include <stddef.h>
#include "stdbool.h"
#include <math.h>

#include "ml.h"
#include "../random/random.h"


MlModel* MlCreateModel(size_t* layers, size_t layersCount, bool assignRandomWeights, float bias)
{
	printf("Creating ML model with %llu layers...\n", layersCount);
	
	const size_t SIZE_OF_NEURON = sizeof(MlNeuron);

	MlModel* resultModel = malloc(sizeof(MlModel));
	resultModel->NeuronLayers = calloc(layersCount, SIZE_OF_NEURON);
	resultModel->LayersCount = layersCount;

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
			neuron->CurrentNeuronIndex = n;
			neuron->Bias = bias;
			neuron->Value = 0;

			// Проходимся по всем неиронам в предыдущем слое
			if (previousLayer != NULL)
			{
				for (size_t z = 0; z < previousLayerSize; z++)
				{
					neuron->InputNeurons = previousLayer;
					neuron->InputNeuronsCount = previousLayerSize;
					neuron->InputNeuronWeights = calloc(previousLayerSize, sizeof(float));
					if (assignRandomWeights)
					{
						for (size_t i = 0; i < neuron->InputNeuronsCount; i++)
						{
							neuron->InputNeuronWeights[i] = Random01();
						}
					}
				}
			}
			// Если предыдущего слоя нет - просто инициализируем нейрон пустыми значениями
			else
			{
				neuron->InputNeurons = NULL;	
				neuron->InputNeuronWeights = NULL;
				neuron->InputNeuronsCount = 0;
			}
		}
		
		resultModel->NeuronLayers[i] = curLayer;

		previousLayerSize = curLayerNeuronsCount;
		previousLayer = curLayer;
	}
	
	printf("ML model with %llu layers created!\n", layersCount);
	return resultModel;
}

float ActivationFunc(MlNeuron* neurons, size_t neuronsCount, float bias)
{
	float result = 0;

	for (size_t i = 0; i < neuronsCount; i++)
	{
		MlNeuron currentNeuron = neurons[i];
		result += currentNeuron.Value;
	}
	result += bias;

	return Sigmoid(result);
}

float Sigmoid(float input)
{
	return 1 / (1 + exp(-input));
}

// Предскзать результат с помощью ML
void MlPredict(MlModel* trainedModel, float* dataInput, int dataInputCount)
{
	assert(trainedModel != NULL);
	assert(trainedModel->NeuronsPerLayer[0] == dataInputCount);
	
	//trainedModel->

	printf("Ml model not empty... Yeeeeeah!");
}

void TrainMlModel(MlModel* model, MlDataset* dataset, float learningRate)
{

}

float CalculateNewNeuronWeight(float currentWeight, float learningRate, float expectedValue, 
	float predictedValue, float neuronValue)
{
	return currentWeight + learningRate * (expectedValue - predictedValue) * neuronValue;
}