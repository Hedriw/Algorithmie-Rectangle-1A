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
#define DEFAULT_ALGORITHM "1"
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

int CalculMaxSizeCurrentCursor(int ** map,int width,int height,int lCursor,int cCursor)
{
	printf("Cursos beeing tried is (%i,%i)\n",lCursor,cCursor);
	int maxSize = 0;
	int test = 0;
	int one_cumul = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			for(int rect_line = lCursor; rect_line<=line;rect_line++)
			{
				for(int rect_col = cCursor; rect_col<=line;rect_col++)
				{
					printf("%i",map[rect_line][rect_col]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
	return maxSize;
}


//SOLUTION 2
int CalculMaxSizeCurrentCursorOptimized(int ** map, int widht, int height, int lCursor, int cCursor)
{
	int maxSize = 0;
	int currentSize = 0;
	int column = 0;
	for (int line = lCursor; line < height; line++)
	{
		if(map[line][column]!=0)
		{
			height = line;
			break;
		}
		for (column = cCursor; column < widht; column++)
		{
			if(map[line][column]!=0)
			{
				widht = column;
				break;
			}
			/* Calculating the current area of the rectangle wich goes from the point(cCursor,lCursor) to point(column,line) */
			currentSize = (column - cCursor + 1)*(line - lCursor + 1);
			if(currentSize>maxSize)
				maxSize = currentSize;
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

// FILEREAD

int GetLineSize(FILE* file)
{
	int c;
	int lineNumber = 0;
	rewind(file);
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

int GetColumnSize(FILE* file)
{
	int c;
	int columnNumber = 0;
	rewind(file);
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
	printf("Size width : %i\n",cSize);
	printf("Size height : %i\n",lSize);
	for (int l = 0; l < lSize; l++)
	{
		for (int c = 0; c < cSize; c++)
		{
			//char tempC = map[l][c];
			printf("%i",map[l][c]);
		}
		printf("\n");
	}
}

int GetMap(int *map[],FILE* file, int lSize, int cSize)
{
	int carac;
	int conform = 1;
	int firstreturn = 0;
	int caracNumber = 0;
	rewind(file);
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

int ** getMapFromFile(char * fileName,int* width, int* height,int *error)
{
	FILE *file;
	int ** map;
	int carac;
	int mapResult;
	file = fopen(fileName,"r");
	if(file!=NULL){
		*width = GetColumnSize(file);
		*height = GetLineSize(file);
		if(*width>0 && *height>0)
	  {
	    map = (int **)malloc(*height*sizeof(int*));
	    for (int l = 0; l < *height; l++)
			{
	     map[l]=(int*)malloc(*width*sizeof(int));
	   	}
			mapResult = GetMap(map,file,*height,*width);
			*error = mapResult;
		}
	}
	else
	{
		*error = ERROR_FILE_NOT_FOUND;
	}
	fclose(file);
	return map;
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

void StartCalculate(char * fileName,char * algoNumber)
{
  //Récupération du dallage dans un fichier
	int pr = 1;
  int **map = {0};
	int width = 0;
	int height = 0;
	int error = 0;
	map = getMapFromFile(fileName,&width,&height,&error);
    switch(error)
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
				int size = 0;
        ReadMap(map,height,width);
				switch (algoNumber[0]) {
					case '1' :
					{
						size = Solution1(map,width,height);
						break;
					}
					case '2' :
					{
						size = Solution2(map,width,height);
						break;
					}
					default :
					printf("Unexpected number for algorithm.\n");
				}
        printf("Taille max : %i\n", size);
        for (int l = 0; l < height; l++) {
          free(map[l]);
        free(map);
        break;
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
	}
}

int main(int argc, char *argv[])
{
	if(argc==3){
		StartCalculate(argv[1],argv[2]);
	}
	else if(argc==2){
		printf("No algoNumber specified. Algorithm n°%s by default.\n",DEFAULT_ALGORITHM);
		StartCalculate(argv[1],DEFAULT_ALGORITHM);
	}
	else{
		printf("Usage : ./outFile file algoNumber\n");
		printf("\tAlgoNumber = 1|2|3|4\n");
	}
  return 0;
}
