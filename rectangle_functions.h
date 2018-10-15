int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize);

int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize);

int CalculMaxSizeCurrentCursorOptimized(int ** map,int width,int height,int lCursor,int cCursor);

int CalculMaxSizeCurrentCursor(int ** map, int width, int height, int lCursor, int cCursor);

int Solution2(int **map, int widht, int height);

int Solution1(int **map, int widht, int height);

int GetLineSize(FILE* file);

int GetColumnSize(FILE* file);

void ReadMap(int *map[], int lSize, int cSize);

int GetMap(int *map[],FILE* file, int lSize, int cSize);

int ** getMapFromFile(char * fileName,int* width, int* height,int *error);

void StartCalculate(char * fileName,char * algoNumber);
