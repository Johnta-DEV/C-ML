#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "diskSpace.h"

double GetDiskFreeSpaceMB(const char* diskPath, double* outTotalSpace)
{
	BOOL bSuccess;

	DWORD dwSectorsPerCluster;
	DWORD dwBytesPerSector;
	DWORD dwFreeClusters;
	DWORD dwTotalClusters;

	bSuccess = GetDiskFreeSpace(
		diskPath, 						// Текущий диск
		&dwSectorsPerCluster, 			// Кол-во секторов на кластер
		&dwBytesPerSector, 				// Кол-во байт на сектор
		&dwFreeClusters, 				// Кол-во свободных кластеров
		&dwTotalClusters 				// Общее кол-во кластеров
		);

	if (bSuccess == false)
		return -1;
		
	#ifdef DEBUG
	printf("Bytes per sector: %d\n", dwBytesPerSector);
	printf("Sectors per cluster: %d\n", dwSectorsPerCluster);
	printf("Free clusters: %d\n", dwFreeClusters);
	printf("Total clusters: %d\n", dwTotalClusters);
	#endif

	unsigned long long uiKBPerCluster = (dwBytesPerSector * dwSectorsPerCluster) / 1024;
	double result = ((double)uiKBPerCluster * dwFreeClusters / 1024);
	
	if (outTotalSpace != NULL)
		*outTotalSpace = ((double)uiKBPerCluster * dwTotalClusters / 1024);

	#ifdef DEBUG
	printf("You have %.2f MB of free storage\n", result);
	printf("You have %.2f MB of total storage\n", (double) uiKBPerCluster * dwTotalClusters / 1024);
	#endif

	return result;
}
