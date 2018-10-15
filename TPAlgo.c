#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wctype.h>

#define ASCII_0 48
#define ASCII_1 49
#define ASCII_9 57
#define ERROR_SIZE_NOT_CONFORM -1
#define ERROR_CARACTER_NOT_CONFORM -3
#define ERROR_FILE_NOT_FOUND -2
#define ERROR_SIZE_VALUES_NOT_CONFORM -5
#define ERROR_SIZE_VALUES_ZERO -4
#define SUCCES_FILE 1
#define DEFAULT_ALGORITHM "1"
//COMMON SOLUTION

int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize)
{
	/*printf("testing black\n");
	printf("LCURSOR : %i\n",lCursor);
	printf("CCURSOR : %i\n",cCursor);
	printf("LSIZE : %i\n",lSize);
	printf("cSIZE : %i\n",cSize);*/
	for (int line = lCursor; line < lSize + lCursor; line++)
	{
		for (int column = cCursor; column < cSize + cCursor; column++)
		{
			if (map[line][column] == 1)
				return 1;
		}
	}
	return 0;
}

int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize)
{
	if (!ContainsBlack(map,lCursor,cCursor,lSize,cSize))
	{
		return lSize * cSize;
	}

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

int CalculMaxSizeCurrentCursorOptimized(int ** map,int width,int height,int lCursor,int cCursor)
{
	int maxSize = 0;
	int test = 0;
	int one_cumul = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int size = CalculSize(map,lCursor,cCursor,lSize,cSize);
			if(size == 0)
				width = column-1;
			if(size>maxSize)
				maxSize=size;
		}
	}
	return maxSize;
}

//SOLUTION 2
int CalculMaxSizeCurrentCursor(int ** map, int width, int height, int lCursor, int cCursor)
{
	//printf("Cursor is at (%i,%i)\n",lCursor,cCursor);
	int maxSize = 0;
	int test = 0;
	int one_cumul = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int size = CalculSize(map,lCursor,cCursor,lSize,cSize);
			if(size>maxSize)
				maxSize=size;
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
	if (file != NULL)
	{
		/*Rewinding file pointer to the start*/
		rewind(file);
		/*Looking for a sequence of digits ending with space character.*/
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				/*Computing the value with a base 10 algorithm*/
				lineNumber = lineNumber * 10 + (c - ASCII_0);
			}
			else
			{
				return -1;
			}
		}
	}
	return lineNumber;
}

int GetColumnSize(FILE* file)
{
	int c;
	int columnNumber = 0;
	if (file != NULL)
	rewind(file);
	{
		/*Rewinding file pointer to the start*/

		/*Skiping the first digits of the file*/
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF){}
		/*Looking for a sequence of digits ending with space character.*/
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				/*Computing the value with a base 10 algorithm*/
				columnNumber = columnNumber * 10 + (c - ASCII_0);
			}
			else
			{
				return -1;
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

	if (file != NULL) {
		/*Rewinding file pointer to the start*/
		rewind(file);
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
		printf("Height is : %i\n",*height);
		printf("Width is : %i\n",*width);
		if(*width>0 && *height>0)
	  {
	    map = (int **)malloc(*height*sizeof(int*));
	    for (int l = 0; l < *height; l++)
			{
	     map[l]=(int*)malloc(*width*sizeof(int));
	   	}
			mapResult = GetMap(map,file,*height,*width);
			*error = mapResult;
			fclose(file);
		}
		else if (*width == 0 || *height == 0)
		{
			*error = ERROR_SIZE_VALUES_ZERO;
		}
		else
		{
			*error = ERROR_SIZE_VALUES_NOT_CONFORM;
		}
	}
	else
	{
		*error = ERROR_FILE_NOT_FOUND;
	}
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
        printf("/!\\ : Matrix contains none conform characters.\n");
        break;
      }
      case ERROR_SIZE_NOT_CONFORM:
      {
        printf("/!\\ : Size values are not conform with the given matrix\n");
        break;
      }
      case ERROR_FILE_NOT_FOUND:
      {
        printf("/!\\ : File '%s' was not found in current dir.\n",fileName);
        break;
      }
			case ERROR_SIZE_VALUES_NOT_CONFORM:
      {
        printf("/!\\ : Size values contain some non digits characters.\n");
        break;
      }
			case ERROR_SIZE_VALUES_ZERO:
      {
        printf("/!\\ : Size values equal to 0.\n");
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
					printf("Unexpected algorithm number.\n");
				}
        printf("Taille max : %i\n", size);
        for (int l = 0; l < height; l++) {
          free(map[l]);
        free(map);
        break;
    	}
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
