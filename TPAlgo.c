#include "main.h"

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
#define MAX_T_ALGO1 1
#define MAX_T_ALGO2 0.5
#define MAX_T_ALGO3 0.4
#define MAX_T_ALGO4 0.1
#define DEFAULT_CSV_NAME "stats.csv"


int main(int argc, char *argv[])
{
	char * algorithmNumber;
	char * csvFileName;
	if(argc==1) /* When no args are provided */
	{
		displayHelp(argv[0]);
		exit(EXIT_FAILURE);
	}
	int opt;
	/* Argument parsing  */
	while ((opt = getopt(argc, argv, "hf:t:s:")) != -1)
	{
		switch (tolower(opt)) {
			case 'f': /* File processing */
			if(argc>=3)
			{
				int mustShow = 1;
				algorithmNumber = (argc == 3)? DEFAULT_ALGORITHM : argv[3]; /* Check if user provided an algorithm number */
				if(argc == 5)
				{
					if (argv[4][0] == ASCII_0) mustShow = 0;
				}
				StartCalculate(argv[2],algorithmNumber,mustShow);
			}
			break;
			case 't': /* Test */
			if(argc>=3)
			{
				if(!stringIsNumber(argv[2]))
				{
					printf("/!\\ Parameter must be a number.\n");
					exit(EXIT_FAILURE);
				}
				else
				{
					int res;
					switch (strtoimax(argv[2],NULL,10)) {
						case 1 : /* 1 : Error file testing */
						if(system("./error_test.sh")==-1)
						{
							printf("Error quitting.\n");
							exit(EXIT_FAILURE);
						};
						break;
						case 2 : /* 2 : Grid testing */
						if(system("./algo_test.sh")==-1)
						{
							printf("Error quitting.\n");
							exit(EXIT_FAILURE);
						};
						default :
						printf("Parameter must be 1 or 2\n");
						exit(EXIT_FAILURE);
						break;
					}
				}
			}
			break;
			case 's': /* Statistics */
			if(argc>=4)
			{
				if(!stringIsNumber(argv[2])||!stringIsNumber(argv[3]))
				{
					printf("/!\\ Size is not a number.\n");
					exit(EXIT_FAILURE);
				}
				else
				{
					int intSizeTo = strtoimax(argv[3],NULL,10);
					int intSizeFrom =  strtoimax(argv[2],NULL,10);
					if(intSizeFrom > intSizeTo )
					{
						printf("/!\\ Upper bound must be greater than lower bound.\n");
						exit(EXIT_FAILURE);
					}
					csvFileName = (argc==4) ? DEFAULT_CSV_NAME : argv[4]; /* Check if user specified a file name to output */
					startStatistics(intSizeFrom,intSizeTo,csvFileName);
				}
			}
			break;
			case 'h': /* Help */
			default:
			displayHelp(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}

/* * * * * * * * * * * * * * * * * * * *
	-- Common functions to Solution 1 --
* * * * * * * * * * * * * * * * * * * */

int Solution1(int **map, int width, int height, tuple *coords,tuple *sizeTuple)
{
	int tmpHeight;
	int tmpWidth;
	int maxSize = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
			int size = 0;
			for (int line2 = line; line2 < height; line2++)
			{
				for (int column2 = column; column2 < width; column2++)
				{
					int lSize = (line2 - line + 1); /* height */
					int cSize = (column2 - column + 1); /* width */
					int size = CalculSize(map,line,column,lSize,cSize); /* Check the size of the current rectangle */
					if(size>maxSize)
					{
						sizeTuple->height = lSize;
						sizeTuple->position = cSize;
						coords->position = column;
						coords->height = line;
						maxSize=size;
					}
				}
			}
		}
	}
	return maxSize;
}

int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize)
{
	if (!ContainsBlack(map,lCursor,cCursor,lSize,cSize))
	{
		return lSize * cSize;
	}

	return 0;
}

/* * * * * * * * * * * * * * * * * * * *
	-- Common functions to Solution 2 --
* * * * * * * * * * * * * * * * * * * */

int Solution2(int **map, int width, int height,tuple *coords,tuple *sizeTuple)
{
	int maxSize = 0;
	int tmpWidth = 0;
	int tmpHeight = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
			if(map[line][column]==1) continue;
			/* Getting the  maximum area from current position */
			int size = CalculMaxSizeCurrentCursorOptimized(map, width, height, line, column, sizeTuple);
			if (size > maxSize)
			{
				maxSize = size;
				coords->position = column;
				coords->height = line;
				tmpWidth = sizeTuple->position;
				tmpHeight = sizeTuple->height;
			}
		}
	}
	/* Finally update the height and width of the tuple */
	sizeTuple->position = tmpWidth;
	sizeTuple->height = tmpHeight;
	return maxSize;
}

int CalculMaxSizeCurrentCursorOptimized(int * map[],int width,int height,int lCursor,int cCursor,tuple * sizeTuple)
{
	int maxSize = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			int lSize = (line - lCursor + 1); /* height */
			int cSize = (column - cCursor + 1); /* width */
			int size =0;
			if(map[line][column] == 1) /* Recuce size of the width to iterate threw */
				width = column;
			else
			{
					size =lSize *cSize;
			}
			if(size>maxSize)
			{
				sizeTuple->height = lSize;
				sizeTuple->position = cSize;
				maxSize=size;
			}
		}
	}
	return maxSize;
}

/* * * * * * * * * * * * * * * * * * * *
	-- Common functions to Solution 3 --
* * * * * * * * * * * * * * * * * * * */

int Solution3(int *map[], int width, int height,tuple * coords,tuple *sizeTuple)
{
	int maxSize = 0;
	int *lineMap =(int *)malloc(width * sizeof(int));
	for(int i = 0;i<width;i++)
	lineMap[i]=0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
			int size = 0;
			if(map[line][column] == BLACK_CASE)
			{
				lineMap[column] = 0;
			}
			else
			{
				lineMap[column]++;
			}
			tuple tempPosition;
			tuple tempSize;
			/* Getting current max size from current column */
			size = CalculSizeSolution3(lineMap,column,height,&tempPosition,&tempSize);
			if (size > maxSize)
			{
				maxSize = size;
				coords->position = tempPosition.position;
				coords->height = line - (tempPosition.height-1);
				sizeTuple->height = tempSize.height;
				sizeTuple->position = tempSize.position;
			}
		}
	}
	free(lineMap);
	return maxSize;
}

int CalculSizeSolution3(int *lineMap,int currentColumn,int maxHeight,tuple *columnCoord,tuple* rectSize)
{
	int size = 0;
	int smallestNumberLine = maxHeight;
	int lastBlackCase = -1;
	/* Reading left to right */
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
		{
			size=tempSize;
			columnCoord->position = (currentColumn-column);
			columnCoord->height = smallestNumberLine;
			rectSize->position = (column-lastBlackCase);
			rectSize->height = smallestNumberLine;
		}
	}

	/* Reset values */
	smallestNumberLine = maxHeight;
	lastBlackCase = currentColumn+1;

	/* Now reading right to left */
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
			{
				smallestNumberLine = lineMap[column];
			}
			tempSize = smallestNumberLine*(lastBlackCase-column);
		}
		if(tempSize>size)
		{
			size=tempSize;
			columnCoord->position = column;
			columnCoord->height = smallestNumberLine;
			rectSize->position = (lastBlackCase-column);
			rectSize->height = smallestNumberLine;
		}
	}
	return size;
}

/* * * * * * * * * * * * * * * * * * * *
	-- Common functions to Solution 4 --
* * * * * * * * * * * * * * * * * * * */

int Solution4(int *map[], int width, int height,tuple * coords,tuple * rectSize)
{
	int maxSize = 0;
	int *lineMap =(int *)malloc(width * sizeof(int));
	/* Initialisation of the line */
	for(int i = 0;i<width;i++)
		lineMap[i]=0;

	stack* stack= _stack();
	for (int line = 0; line < height; line++)
	{
		int lastColumnSize = 0;
		/* Calculating lineMap */
		for (int column = 0; column < width; column++){
			if(map[line][column]==BLACK_CASE)
			{
				lineMap[column] = 0;
			}
			else
			{
				lineMap[column]++;
			}
			if(lastColumnSize < lineMap[column])
			{
				_push(stack,column,lineMap[column]);
			}
			else if(lastColumnSize > lineMap[column])
			{
				tuple tempPosition;
				tuple tempSize;
				/* Calculating the max size from current column */
				int size = CalculSizeSolution4(stack,column,lastColumnSize,lineMap[column],&tempPosition,&tempSize);
				if(size>maxSize)
				{
					maxSize = size;
					coords->position = tempPosition.position;
					coords->height = line -(tempPosition.height-1);
					rectSize->position = tempSize.position;
					rectSize->height = tempSize.height;
				}
			}
			lastColumnSize = lineMap[column];
		}
		/* Calculate size current lineMap */
		tuple tempPosition;
		tuple tempSize;
		/* Calculating the max size from current column */
		int size = CalculSizeSolution4(stack,width,0,0,&tempPosition,&tempSize);
		if(size>maxSize)
		{
			maxSize = size;
			coords->position = tempPosition.position;
			coords->height = line -(tempPosition.height-1);
			rectSize->position = tempSize.position;
			rectSize->height = tempSize.height;
		}
	}
	free(lineMap);
	return maxSize;
}


int CalculSizeSolution4(stack* stack,int currentColumn,int lastColumnSize,int currentColumnSize,tuple *columCoord,tuple* rectSize)
{
	int maxSize=0;
	tuple lastTuple = _pop(stack);
	tuple currentTuple = lastTuple;
	while(currentColumnSize<currentTuple.height)
	{
		int size = (currentColumn-currentTuple.position)*currentTuple.height;
		if(maxSize<size)
		{
			maxSize = size;
			columCoord->position = currentTuple.position;
			columCoord->height = currentTuple.height;
			rectSize->position = (currentColumn-currentTuple.position);
			rectSize->height = currentTuple.height;
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

/* * * * * * * * * * * * * * * * * * * *
	-- Struct functions --
* * * * * * * * * * * * * * * * * * * */

tuple* _tuple(int position,int height)
{
	tuple* new_tuple = malloc(sizeof(tuple));
	new_tuple->position = position;
	new_tuple->height= height;
	return new_tuple;
}

cell* _cell(int position,int height,cell* next)
{
	cell* new_cell = malloc(sizeof(cell));
	new_cell->tuple = _tuple(position,height);
	new_cell->next = next;
	return new_cell;
}

void free_cell(cell* c)
{
	if(c->tuple != NULL)
	{
		free(c->tuple);
	}
	free(c);
}

void AddHeadList(cell** currentList, int position,int height)
{
  cell* head = _cell(position,height,*currentList);
  *currentList = head;
}

void DeleteHead(cell** list)
{
  if(*list!=NULL)
    {
			cell* temp=(*list);
			*list = (*list)->next;
			free_cell(temp);
    }
}

stack* _stack()
{
  stack* stack = malloc(sizeof(stack));
  stack->linkedList= NULL;
  stack->curr_pos = -1;
  return stack;
}

int _isEmpty(stack *stack)
{
  if(stack!=NULL){
    if(stack->curr_pos==-1) return 1;
  }
  return 0;
}

tuple _pop(stack* stack)
{
  if(!_isEmpty(stack)){
		stack->curr_pos--;
    tuple temp;
		temp.position = stack->linkedList->tuple->position;
		temp.height = stack->linkedList->tuple->height;
    DeleteHead(&(stack->linkedList));
		return temp;
  }
	return *_tuple(0,0);
}

void _push(stack* stack, int position,int height)
{
  if(stack!=NULL){
      AddHeadList(&(stack->linkedList),position,height);
      stack->curr_pos++;
  }
}

/* * * * * * * * * * * * * * * * * * * *
	-- Common functions to the program --
* * * * * * * * * * * * * * * * * * * */

void displayHelp(char * binName)
{
	printf("\n");
	printf("Usage: %s -f file [AlgorithmNumber] [showGrid]\n\t - Process a grid file using an algorthim number between 1 and 4.\n",binName);
	printf("Usage: %s -h\n\t - Displays the help text\n",binName);
	printf("Usage: %s -s lowerBound upperBound [filename]\n\t - Generates a csv format file with perfs of each algorithms\n",binName);
	printf("Usage: %s -t numberTest\n\t - numberTest=1 : error_grid file testing\n\t - numberTest=2 : Algortihm testing on test_grid files",binName);
	printf("\n\n");
}

void StartCalculate(char * fileName,char * algoNumber,int mustShow)
{
	int pr = 1;
	int **map = {0};
	int width = 0;
	int height = 0;
	int error = 0;
	/* Trying to get the map */
	map = getMapFromFile(fileName,&width,&height,&error);

	/* Identyfing if an error has occured in the function*/
	switch(error)
	{
		case ERROR_CARACTER_NOT_CONFORM:
		{
			printf("/!\\ : Matrix contains none conform characters.\n");
			exit(1);
		}
		case ERROR_SIZE_NOT_CONFORM:
		{
			printf("/!\\ : Size values are not conform with the given matrix\n");
			exit(1);
		}
		case ERROR_FILE_NOT_FOUND:
		{
			printf("/!\\ : File '%s' was not found in current dir.\n",fileName);
			exit(1);
		}
		case ERROR_SIZE_VALUES_NOT_CONFORM:
		{
			printf("/!\\ : Size values contain some non digits characters.\n");
			exit(1);
		}
		case ERROR_SIZE_VALUES_ZERO:
		{
			printf("/!\\ : Size values equal to 0.\n");
			exit(1);
		}
		case SUCCES_FILE:
		{
			tuple* coords = _tuple(-1,-1);
			tuple* sizeTuple = _tuple(0,0);
			int size = 0;
			if(mustShow == 1) ReadMap(map,height,width);
			switch (algoNumber[0]) {
				case '1' :
				{
					size = Solution1(map,width,height,coords,sizeTuple);
					break;
				}
				case '2' :
				{
					size = Solution2(map,width,height,coords,sizeTuple);
					break;
				}
				case '3':
				{
					size = Solution3(map,width,height,coords,sizeTuple);
					break;
				}
				case '4':
				{
					size = Solution4(map,width,height,coords,sizeTuple);
					break;
				}
				default :
				printf("Unexpected algorithm number.\n");
				exit(1);
			}
			printf("Taille max : %i\n", size);
			printf("Found at Coordinates Column :%i Line:%i)\n",coords->position,coords->height);
			printf("Size is : (%i x %i)\n",sizeTuple->position,sizeTuple->height);
			for (int l = 0; l < height; l++) {
				free(map[l]);
			}
			free(coords);
			free(sizeTuple);
			free(map);
			break;
		}
	}
}

int ** getRandomMap(int height,int width,float percent)
{
	int ** map;
	srand(time(NULL)); /* Init for the use of rand() */
	map = (int **)malloc(height*sizeof(int*));
	for (int l = 0; l < height; l++)
	{
		map[l]=(int*)malloc(width*sizeof(int));
	}
	for(int cursor_height = 0;cursor_height<height;cursor_height++)
	{
		for(int cursor_width = 0;cursor_width<width;cursor_width++)
		{
			int r = rand()%100;
			if(r<(100-percent))
				map[cursor_height][cursor_width] = 1;
			else
				map[cursor_height][cursor_width] = 0;
		}
	}
	return map;
}

int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize)
{
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

void startStatistics(int fromSize,int toSize,char * fileName)
{
	FILE* csvFile;
	csvFile = fopen(fileName,"w");
	/* At start, Calculate all solutions until they reach its MAX time */
	int doSolution1 = 1;
	int doSolution2 = 1;
	int doSolution3 = 1;
	int doSolution4 = 1;
	double timeTaken1,timeTaken2,timeTaken3,timeTaken4;
	for(int i = fromSize;i<=toSize;i++)
	{
		tuple finalSizeTuple;
		tuple finalCoords;
		int ** randMap = getRandomMap(i,i,90);
		if(doSolution1!=0)
		{
			clock_t time1;
			time1 = clock();
			Solution1(randMap,i,i,&finalCoords,&finalSizeTuple);
			time1 = clock() - time1;
			timeTaken1 = ((double)time1)/CLOCKS_PER_SEC;
			if(timeTaken1 > MAX_T_ALGO1 )
			{
				doSolution1 = 0;
			}
		}
		else
			timeTaken1 = -1;
		if(doSolution2!=0)
		{
			clock_t time2;
			time2 = clock();
			Solution2(randMap,i,i,&finalCoords,&finalSizeTuple);
			time2 = clock() - time2;
			timeTaken2 = ((double)time2)/CLOCKS_PER_SEC;
			if(timeTaken2 > MAX_T_ALGO2 )
			{
				doSolution2 = 0;
			}
		}
		else
			timeTaken2 = -1;
		if(doSolution3!=0)
		{
			clock_t time3;
			time3 = clock();
			Solution3(randMap,i,i,&finalCoords,&finalSizeTuple);
			time3 = clock() - time3;
			timeTaken3 = ((double)time3)/CLOCKS_PER_SEC;
			if(timeTaken3 > MAX_T_ALGO3 )
			{
				doSolution3 = 0;
			}
		}
		else
			timeTaken3 = -1;
		if(doSolution4!=0)
		{
			clock_t time4;
			time4 = clock();
			Solution4(randMap,i,i,&finalCoords,&finalSizeTuple);
			time4 = clock() - time4;
			timeTaken4 = ((double)time4)/CLOCKS_PER_SEC;
			if(timeTaken4 > MAX_T_ALGO4 )
			{
				doSolution4 = 0;
			}
		}
		else
			timeTaken4 = -1;
		/*If all solutions reached their limits , quit the iteration loop*/
		if(doSolution1 == 0 && doSolution2 == 0 && doSolution3 == 0 && doSolution4 ==0)
			break;
		fprintf(csvFile,"%i;%f;%f;%f;%f;\n",i,timeTaken1,timeTaken2,timeTaken3,timeTaken4);
	}
	fclose(csvFile);
	exit(1);
}

/* * * * * * * * * * * * * * * * * * * *
	-- File proccessing --
* * * * * * * * * * * * * * * * * * * */

int GetLineSize(FILE* file)
{
	int c;
	int lineNumber = 0;
	if (file != NULL)
	{
		/* Rewinding file pointer to the start */
		rewind(file);
		/* Looking for a sequence of digits ending with space character. */
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				/* Computing the value with a base 10 algorithm */
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
		/* Rewinding file pointer to the start */

		/* Skiping the first digits of the file */
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF){}
		/* Looking for a sequence of digits ending with space character. */
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				/* Computing the value with a base 10 algorithm */
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
	for (int l = 0; l < lSize; l++)
	{
		for (int c = 0; c < cSize; c++)
		{
			printf("%i",map[l][c]);
		}
		printf("\n");
	}
}

int GetMap(int *map[],FILE* file, int lSize, int cSize)
{
	int carac;
	int caracNumber = 0;
	if (file != NULL) {
		/* Rewinding file pointer to the start */
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
					if (c < cSize) /*Cheking if the digit is out range */
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

int stringIsNumber(char * stringToTest)
{
	size_t strSize = strlen(stringToTest);
	for(int i = 0;i<strSize;i++)
	{
		if(!isdigit(stringToTest[i]))
		return 0;
	}
	return 1;
}
