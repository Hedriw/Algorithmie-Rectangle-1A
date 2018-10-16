#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wctype.h>

#define WHITE_CASE 0
#define BLACK_CASE 1
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

typedef struct tuple tuple;
typedef struct stack stack;


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
			if (map[line][column] == BLACK_CASE)
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
//SOLUTION 4
struct tuple{
	int position;
	int height;
};
tuple _tuple(int position,int height)
{
	tuple new_tuple;
	new_tuple.position = position;
	new_tuple.height= height;
	return new_tuple;
}

struct stack {
    int size;
    int curr_pos;
    tuple *array;
};
stack* _stack(int p_size){
  stack* stack = malloc(sizeof(stack));
  stack->array = malloc(p_size*sizeof(tuple));
  stack->size = p_size;
  stack->curr_pos = -1;
  return stack;
}
void resize(stack *stack,int new_size){
  tuple *tmp = malloc(new_size*sizeof(tuple));
  for(int i = 0;i<=stack->curr_pos;i++){
    tmp[i] = stack->array[i];
  }
  free(stack->array);
  stack->array = tmp;
  stack->size = new_size;
}
int _isEmpty(stack *stack){
  if(stack!=NULL){
    if(stack->curr_pos==-1) return 1;
  }
  return 0;
}
tuple _pop(stack* stack){
  if(!_isEmpty(stack)){
		stack->curr_pos--;
		return stack->array[stack->curr_pos+1];
  }
	return _tuple(0,0);
}
int _push(stack* stack, int position,int height){
  if(stack!=NULL){
    if(stack->curr_pos+1>=stack->size){
      int new_size = stack->size * 2;
      resize(stack,new_size);
    }
      stack->array[stack->curr_pos+1]=_tuple(position,height);
      stack->curr_pos++;
  }
}

int TupleSize(tuple t,int currentPosition)
{
	return  (currentPosition-t.position)*t.height;
}
void print_stack(stack* stack){
  if(stack!=NULL){
    printf("[ ");
    for(int i = 0;i<=stack->curr_pos;i++){
      printf("Pos:%i Height:%i ",stack->array[i].position,stack->array[i].height);
    }
    printf("]\n");
  }
}
int CalculSizeSolution4(stack* stack,int currentColumn,int lastColumnSize,int currentColumnSize)
{
	int maxSize=0;
	tuple lastTuple = _pop(stack);
	tuple currentTuple = lastTuple;
	while(currentColumnSize<currentTuple.height)
	{
		int size = TupleSize(currentTuple,currentColumn);
		if(maxSize<size)
		{
			maxSize = size;
		}
		lastTuple = currentTuple;
		currentTuple = _pop(stack);
	}
	_push(stack,currentTuple.position,currentTuple.height);
	if(lastColumnSize>0 && currentColumnSize>0)
	{
		_push(stack,lastTuple.position,currentColumnSize);
	}

	return maxSize;
}
int Solution4(int *map[], int widht, int height)
{
	int maxSize = 0;
	int *lineMap =(int *)malloc(widht * sizeof(int));
	//Cleaning residual memory
	for(int i = 0;i<widht;i++)
		lineMap[i]=0;
	stack* stack= _stack(widht);
	for (int line = 0; line < height; line++)
	{
		//Calculate lineMap
		for (int column = 0; column < widht; column++)
		{
			if(map[line][column]==BLACK_CASE)
			{
				lineMap[column] = 0;
			}
			else
			{
				lineMap[column]++;
			}
		}
		//Calculate size current lineMap
		int lastColumnSize = 0;
		for(int column = 0;column<widht;column++)
		{
			//Cas où la hauteur de la nouvelle colonne est plus grande que la précédente
			printf("LastH:%i, CurrentH:%i\n",lastColumnSize,lineMap[column]);
			if(lastColumnSize < lineMap[column])
			{
				_push(stack,column,lineMap[column]);
			}
			else
			{
				printf("Pop time\n");
				print_stack(stack);
				int size = CalculSizeSolution4(stack,column,lastColumnSize,lineMap[column]);
				print_stack(stack);
				printf("Size:%i\n",size);
				if(size>maxSize)
					maxSize = size;
			}
			lastColumnSize = lineMap[column];
		}
		printf("\n\n");
		int size = CalculSizeSolution4(stack,widht,0,0);
		if(size>maxSize)
			maxSize = size;
	}
	free(lineMap);
	return maxSize;
}
//SOLUTION 3
int CalculSizeSolution3(int *lineMap,int currentColumn,int maxHeight)
{
	int size = 0;
	int smallestNumberLine = maxHeight;
	int lastBlackCase = -1;
	//Reading left to right
	for(int column = 0;column<=currentColumn;column++)
	{
		int tempSize = 0;
		if(lineMap[column]==0)
		{
			lastBlackCase = column;
		}
		else
		{
			if(lineMap[column]<smallestNumberLine)
				smallestNumberLine = lineMap[column];
			tempSize = smallestNumberLine*(column-lastBlackCase);
		}
		if(tempSize>size)
			size=tempSize;
	}
	//Reset values
	smallestNumberLine = maxHeight;
	lastBlackCase = -1;
	//Reading right to left
	for(int column = currentColumn;column>=0;column--)
	{
		int tempSize = 0;
		if(lineMap[column]==0)
		{
			lastBlackCase = column;
		}
		else
		{
			if(lineMap[column]<smallestNumberLine)
				smallestNumberLine = lineMap[column];
			tempSize = smallestNumberLine*(currentColumn-column-lastBlackCase);
		}
		if(tempSize>size)
			size=tempSize;
	}
	return size;
}

int Solution3(int *map[], int widht, int height)
{
	int maxSize = 0;
	int *lineMap =(int *)malloc(widht * sizeof(int));
	for(int i = 0;i<widht;i++)
		lineMap[i]=0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < widht; column++)
		{
			int size = 0;
			if(map[line][column]==BLACK_CASE)
			{
				lineMap[column] = 0;
			}
			else
			{
				lineMap[column]++;
			}
			size=CalculSizeSolution3(lineMap,column,height);
			if (size > maxSize)
				maxSize = size;
		}
	}
	free(lineMap);
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
					case '3':
					{
						size = Solution3(map,width,height);
						break;
					}
					case '4':
					{
						size = Solution4(map,width,height);
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
