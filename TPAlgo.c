#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wctype.h>
#define ASCII_0 48
#define ASCII_1 49
#define ASCII_9 57
#define ERROR_SIZE_NOT_CONFORM -1
#define ERROR_CARACTER_NOT_CONFORM -3
#define ERROR_FILE_NOT_FOUND 0
#define SUCCES_FILE 1
#define FILE_NAME "test.txt"
//COMMON SOLUTION
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

//SOLUTION 1
int CalculMaxSizeCurrentCursor(int ** map,int widht,int height,int lCursor,int cCursor)
{
	int maxSize = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < widht; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int ** underMap = {0};
			underMap = (int **)malloc(lSize * sizeof(int *));
			for (int l = 0; l<lSize; l++)
				underMap[l] = (int*)malloc(cSize * sizeof(int));
			Copy(map, lCursor, cCursor, lSize, cSize, underMap);
			int size = CalculSize(underMap, cSize, lSize);
			if (size > maxSize)
				maxSize = size;
			for (int l = 0; l < lSize; l++)
				free(underMap[l]);
			free(underMap);
		}
	}
	return maxSize;
}
int Solution1(int **map, int widht, int height)
{
	int maxSize = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < widht; column++)
		{
			int size = CalculMaxSizeCurrentCursor(map, widht, height, line, column);
			if (size > maxSize)
				maxSize = size;
		}
	}
	return maxSize;
}

//SOLUTION 2
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


// FILEREAD

int GetLineSize()
{
	int c;
	FILE *file;
	int lineNumber = 0;
	file = fopen(FILE_NAME, "r");
	if (file != NULL)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				lineNumber = lineNumber * 10 + (c - 48);
			}
			else
			{
				lineNumber = -1;
				break;
			}
		}
	}
	return lineNumber;
}

int GetColumnSize()
{
	int c;
	FILE *file;
	int columnNumber = 0;
	file = fopen(FILE_NAME, "r");
	if (file != NULL)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF) {}
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				columnNumber = columnNumber * 10 + (c - 48);
			}
			else
			{
				columnNumber = -1;
				break;
			}
		}
	}
	return columnNumber;
}

void ReadMap(int *map[], int lSize, int cSize)
{
	for (int l = 0; l < lSize; l++)
	{
		for (int c = 0; c < cSize; c++)
		{
			char tempC = map[l][c];
			printf("%i", map[l][c]);
		}
		printf("\n");
	}
}

int GetMap(int *map[], int lSize, int cSize)
{
	int carac;
	int conform = 1;
	int firstreturn = 0;
	int caracNumber = 0;
	FILE *file;
	file = fopen(FILE_NAME, "r");
	if (file != NULL) {
		while (!iswcntrl(carac = getc(file))) {}
		for (int l = 0; l < lSize; l++)
		{
			int c = 0;
			do
			{
				carac = getc(file);
				if ((carac == ASCII_0 || carac == ASCII_1))
				{
					if (c < cSize)
					{
						map[l][c] = carac - ASCII_0;
						c++;
					}
					else
					{
						return ERROR_SIZE_NOT_CONFORM;
					}

				}
				else if (iswcntrl(carac) || iswblank(carac) || carac == EOF)
				{
					if (c < cSize && carac !=EOF)
					{
						return ERROR_SIZE_NOT_CONFORM;
					}
					break;
				}
				else
				{
					return ERROR_CARACTER_NOT_CONFORM;
				}
			} while (1);
		}
		fclose(file);
		return 1;
	}
	else
	{
		return ERROR_FILE_NOT_FOUND;
	}
}

// MAIN
void generate(int *map[],int widht,int height)
{
  for(int line = 0;line <height;line++)
  {
      for (int colum = 0; colum < widht; colum++)
      {
        int nb =0;
        if(line==colum)
          nb = 1;
        map[line][colum]=nb;
      }
  }
}
void StartCalculate()
{
  //Récupération du dallage dans un fichier
	int pr = 1;
  int **map={0};
  int lSize = GetLineSize();
  int cSize = GetColumnSize();

  // int lSize = 50;
  // int cSize = 50;
  if(lSize>0 && cSize>0)
  {
    map = (int **)malloc(lSize*sizeof(int*));
    for (int l = 0; l < lSize; l++) {
      map[l]=(int*)malloc(cSize*sizeof(int));
    }
    switch(GetMap(map,lSize,cSize))
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
        for (int l = 0; l < lSize; l++) {
          free(map[l]);
        free(map);
        break;
      }
    }
  }
    // ReadMap(map, lSize, cSize);
    // clock_t begin = clock();
    // int size = Solution2(map, cSize, lSize);
    // clock_t end = clock();
    // printf("Taille max : %i\n", size);
    // printf("Temps parcourue : %f\n", (double)(end - begin));
    // for (int l = 0; l < lSize; l++)
    // {
    //   free(map[l]);
    // }
		// free(map);
  }
	else
	{
		printf("Line : %i Column: %i\n",lSize,cSize);
	}
}

int main(int argc, char const *argv[])
{
  StartCalculate();
  return 0;
}
