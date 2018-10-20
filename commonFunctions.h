int ** getRandomMap(int height,int width,float percent);
int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize);
int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize);
void generate(int *map[],int widht,int height);
int stringIsNumber(char * stringToTest);
void startStatistics(int fromSize,int toSize, char* fileName);
void StartCalculate(char * fileName,char * algoNumber);
void displayHelp();
