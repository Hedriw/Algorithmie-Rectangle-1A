// TPAlgo.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"


void StartCalculate()
{
	int **map = { 0 };
	int lSize = GetLineSize();
	int cSize = GetColumnSize();
	if (lSize > 0 && cSize > 0)
	{
		map = (int **)malloc(lSize * sizeof(int *));
		for (int l = 0; l<lSize; l++)
			map[l] = (int*)malloc(cSize * sizeof(int));
		GetMap(map, lSize, cSize);
		ReadMap(map, lSize, cSize);
		getchar();
	}
	free(map);
}


int main()
{
	StartCalculate();
	return 0;
}

