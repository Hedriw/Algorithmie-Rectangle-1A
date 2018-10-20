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
#define MAX_N_ALGO1 200
#define MAX_N_ALGO2 500
#define MAX_N_ALGO3 1100
#define DEFAULT_CSV_NAME "stats.csv"

int main(int argc, char *argv[])
{
	char * algorithmNumber;
	char * csvFileName;
	if(argc==1)
	{
		displayHelp(argv[0]);
		exit(EXIT_FAILURE);
	}
	int opt;
	while ((opt = getopt(argc, argv, "hf:ts:")) != -1) {
		switch (tolower(opt)) {
			case 'f':
			if(argc>=3)
			{
				algorithmNumber = (argc == 3)? DEFAULT_ALGORITHM : argv[3];
				StartCalculate(argv[2],algorithmNumber);
			}
			break;
			case 't':
			printf("To do tests\n");
			break;
			case 's':
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
					csvFileName = (argc==4) ? DEFAULT_CSV_NAME : argv[4];
					startStatistics(intSizeFrom,intSizeTo,csvFileName);
				}
			}
			break;
			case 'h':
			default:
			displayHelp(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}

void displayHelp(char * binName)
{
	printf("Usage: %s -f file [AlgorithmNumber]\n\t - Process a grid file using an algorthim number between 1 and 4.\n",binName);
	printf("Usage: %s -h\n",binName);
	printf("Usage: %s -s lowerBound upperBound [filename]\n\t - Generates a csv format file with perfs of each algorithms\n",binName);
	printf("Usage: %s -t\n\t - Tests each algorithm with test grids.\n",binName);
}

int ** getRandomMap(int height,int width,float percent)
{
	int ** map;
	srand(time(NULL));
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

int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize)
{
	if (!ContainsBlack(map,lCursor,cCursor,lSize,cSize))
	{
		return lSize * cSize;
	}

	return 0;
}

//SOLUTION 4

tuple _tuple(int position,int height)
{
	tuple new_tuple;
	new_tuple.position = position;
	new_tuple.height= height;
	return new_tuple;
}

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

int CalculSizeSolution4(stack* stack,int currentColumn,int lastColumnSize,int currentColumnSize,tuple *columCoord,tuple* rectSize)
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
int Solution4(int *map[], int width, int height,tuple * coords,tuple * rectSize)
{
	int maxSize = 0;
	int *lineMap =(int *)malloc(width * sizeof(int));
	//Cleaning residual memory
	for(int i = 0;i<width;i++)
	lineMap[i]=0;
	stack* stack= _stack(width);
	for (int line = 0; line < height; line++)
	{
		//Calculate lineMap
		for (int column = 0; column < width; column++)
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
		for(int column = 0;column<width;column++)
		{
			//Cas où la hauteur de la nouvelle colonne est plus grande que la précédente
			if(lastColumnSize < lineMap[column])
			{
				_push(stack,column,lineMap[column]);
			}
			else
			{
				tuple tempPosition;
				tuple tempSize;
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
		tuple tempPosition;
		tuple tempSize;
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

//SOLUTION 3
int CalculSizeSolution3(int *lineMap,int currentColumn,int maxHeight,tuple *columnCoord,tuple* rectSize)
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
		{
			size=tempSize;
			columnCoord->position = (currentColumn-column);
			columnCoord->height = smallestNumberLine;
			rectSize->position = (column-lastBlackCase);
			rectSize->height = smallestNumberLine;
		}
	}
	//Reset values
	smallestNumberLine = maxHeight;
	lastBlackCase = currentColumn+1;
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
	// printf("\n\n");
	return size;
}

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
			if(map[line][column]==BLACK_CASE)
			{
				lineMap[column] = 0;
			}
			else
			{
				lineMap[column]++;
			}
			tuple tempPosition;
			tuple tempSize;
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
//SOLUTION 2
int CalculMaxSizeCurrentCursor(int ** map, int width, int height, int lCursor, int cCursor, tuple * sizeTuple)
{
	//printf("Cursor is at (%i,%i)\n",lCursor,cCursor);
	int maxSize = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int size = CalculSize(map,lCursor,cCursor,lSize,cSize);
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

int CalculMaxSizeCurrentCursorOptimized(int ** map,int width,int height,int lCursor,int cCursor,tuple * sizeTuple)
{
	int maxSize = 0;
	int one_cumul = 0;
	for (int line = lCursor; line < height; line++)
	{
		for (int column = cCursor; column < width; column++)
		{
			int lSize = (line - lCursor + 1);
			int cSize = (column - cCursor + 1);
			int size = CalculSize(map,lCursor,cCursor,lSize,cSize);
			if(size == 0)
			width = column;
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

int Solution2(int **map, int width, int height,tuple *coords,tuple *sizeTuple)
{
	int maxSize = 0;
	int tmpWidth;
	int tmpHeight;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
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
	sizeTuple->position = tmpWidth;
	sizeTuple->height = tmpHeight;
	return maxSize;
}

int Solution1(int **map, int width, int height, tuple *coords,tuple *sizeTuple)
{
	int tmpHeight;
	int tmpWidth;
	int maxSize = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
			int size = CalculMaxSizeCurrentCursor(map, width, height, line, column,sizeTuple);
			if (size > maxSize)
			{
				maxSize = size;
				tmpWidth = sizeTuple->position;
				tmpHeight = sizeTuple->height;
				coords->position = column;
				coords->height = line;
			}
		}
	}
	sizeTuple->height =tmpHeight;
	sizeTuple->position =tmpWidth;
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

void startStatistics(int fromSize,int toSize,char * fileName)
{
	FILE* csvFile;
	csvFile = fopen(fileName,"w");
	fputs("mapSize;Algo1;Algo2;Algo3;Algo4\n",csvFile);
	double timeTaken1,timeTaken2,timeTaken3,timeTaken4;
	for(int i = fromSize;i<=toSize;i++)
	{
		tuple finalSizeTuple;
		tuple finalCoords;
		int ** randMap = getRandomMap(i,i,80);
		ReadMap(randMap,i,i);
		printf("\n\n");
		if(i<=MAX_N_ALGO1)
		{
			clock_t time1;
			time1 = clock();
			Solution1(randMap,i,i,&finalCoords,&finalSizeTuple);
			time1 = clock() - time1;
			timeTaken1 = ((double)time1)/CLOCKS_PER_SEC;
		}
		else
		timeTaken1 = -1;
		if(i<=MAX_N_ALGO2)
		{
			clock_t time2;
			time2 = clock();
			Solution2(randMap,i,i,&finalCoords,&finalSizeTuple);
			time2 = clock() - time2;
			timeTaken2 = ((double)time2)/CLOCKS_PER_SEC;
		}
		else
		timeTaken2 = -1;
		if(i<=MAX_N_ALGO3)
		{
			clock_t time3;
			time3 = clock();
			Solution3(randMap,i,i,&finalCoords,&finalSizeTuple);
			time3 = clock() - time3;
			timeTaken3 = ((double)time3)/CLOCKS_PER_SEC;
		}
		else
		timeTaken3 = -1;
		clock_t time4;
		time4 = clock();
		Solution4(randMap,i,i,&finalCoords,&finalSizeTuple);
		time4 = clock() - time4;
		timeTaken4 = ((double)time4)/CLOCKS_PER_SEC;
		if(i>=MAX_N_ALGO3)
		{
			fprintf(csvFile,"%i;;;;%g;\n",i,timeTaken4);
		}
		else if(i>=MAX_N_ALGO3)
		{
			fprintf(csvFile,"%i;;;%g;%g;\n",i,timeTaken3,timeTaken4);
		}
		else if (i>=MAX_N_ALGO1)
		{
			fprintf(csvFile,"%i;;%g;%g;%g;\n",i,timeTaken2,timeTaken3,timeTaken4);
		}
		else
		{
			fprintf(csvFile,"%i;%g;%g;%g;%g;\n",i,timeTaken1,timeTaken2,timeTaken3,timeTaken4);
		}
	}
	fclose(csvFile);
	exit(1);
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
			tuple coords = _tuple(-1,-1);
			tuple sizeTuple = _tuple(0,0);
			int size = 0;
			ReadMap(map,height,width);
			switch (algoNumber[0]) {
				case '1' :
				{
					size = Solution1(map,width,height,&coords,&sizeTuple);
					break;
				}
				case '2' :
				{
					size = Solution2(map,width,height,&coords,&sizeTuple);
					break;
				}
				case '3':
				{
					size = Solution3(map,width,height,&coords,&sizeTuple);
					break;
				}
				case '4':
				{
					size = Solution4(map,width,height,&coords,&sizeTuple);
					break;
				}
				default :
				printf("Unexpected algorithm number.\n");
				exit(1);
			}
			printf("Taille max : %i\n", size);
			printf("Found at Coordinates Column :%i Line:%i)\n",coords.position,coords.height);
			printf("Size is : (%i x %i)\n",sizeTuple.position,sizeTuple.height);
			for (int l = 0; l < height; l++) {
				free(map[l]);
				free(map);
				break;
			}
		}
	}
}
