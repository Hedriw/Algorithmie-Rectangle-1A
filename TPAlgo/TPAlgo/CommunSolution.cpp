#include "stdafx.h"
int ContainsBlack(int *map[], int widht, int height)
{
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < widht; column++)
		{
			if (map[line][column] == 1)
				return 1;
		}
	}
	return 0;
}
int CalculSize(int **map, int widht, int height)
{
	if (!ContainsBlack(map, widht, height))
		return widht * height;
	return 0;
}
void Copy(int *map[], int lCursor, int cCursor, int lSize, int cSize, int *underMap[])
{
	for (int line = 0; line <lSize; line++)
	{
		for (int column = 0; column <cSize; column++)
		{
			underMap[line][column] = map[line + lCursor][column + cCursor];
		}
	}
}