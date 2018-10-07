#include "stdafx.h"
int Solution2(int **map, int widht, int height)
{
	int maxSize = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < widht; column++)
		{
			int size = CalculMaxSizeCurrentCursorOptimized(map, widht, height, line, column);
			if (size > maxSize)
				maxSize = size;
		}
	}
	return maxSize;
}
int CalculMaxSizeCurrentCursorOptimized(int ** map, int widht, int height, int lCursor, int cCursor)
{
	int maxSize = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < widht; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int ** underMap = { 0 };
			underMap = (int **)malloc(lSize * sizeof(int *));
			for (int l = 0; l<lSize; l++)
				underMap[l] = (int*)malloc(cSize * sizeof(int));
			Copy(map, lCursor, cCursor, lSize, cSize, underMap);
			int size = CalculSize(underMap, cSize, lSize);
			if (size == 0)
				widht = column-1;
			else if (size > maxSize)
					maxSize = size;
			for (int l = 0; l < lSize; l++)
				free(underMap[l]);
			free(underMap);
		}
	}
	return maxSize;
}