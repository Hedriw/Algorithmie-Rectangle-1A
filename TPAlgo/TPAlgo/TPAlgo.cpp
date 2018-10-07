// TPAlgo.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

void generate(int *map[], int widht, int height)
{
	for (int line = 0; line < height; line++)
	{
		for (int colum = 0; colum < widht; colum++)
		{
			int nb = 0;
			if (line == colum)
				nb = 1;
			map[line][colum] = nb;
		}
	}
}
void StartCalculate()
{

	//Récupération du dallage dans un fichier
	int **map = { 0 };
	/*int lSize = GetLineSize();
	int cSize = GetColumnSize();*/
	int lSize = 50;
	int cSize = 50;
	if (lSize > 0 && cSize > 0)
	{
		map = (int **)malloc(lSize * sizeof(int *));
		for (int l = 0; l < lSize; l++)
			map[l] = (int*)malloc(cSize * sizeof(int));
		generate(map, cSize, lSize);
		/*switch (GetMap(map, lSize, cSize))
		{
		case ERROR_CARACTER_NOT_CONFORM:
		{
			printf("File contains none conform caracter!!!");
			break;
		}
		case ERROR_SIZE_NOT_CONFORM:
		{
			printf("Size not conform!");
			break;
		}
		case ERROR_FILE_NOT_FOUND:
		{
			printf("File not found!");
			break;
		}
		case SUCCES_FILE:
		{

			ReadMap(map, lSize, cSize);
			clock_t begin = clock();
			int size = Solution1(map, cSize, lSize);
			clock_t end = clock();
			printf("Taille max : %i\n", size);
			printf("Temps parcourue : %f", (double)(end - begin));
			free(map);
			break;
		}
		}*/
		ReadMap(map, lSize, cSize);
		clock_t begin = clock();
		int size = Solution1(map, cSize, lSize);
		clock_t end = clock();
		printf("Taille max : %i\n", size);
		printf("Temps parcourue : %f", (double)(end - begin));
		getchar();
	}

}


int main()
{
	StartCalculate();
	return 0;
}

