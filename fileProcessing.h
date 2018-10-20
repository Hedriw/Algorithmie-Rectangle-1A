int ** getMapFromFile(char * fileName,int* width, int* height,int *error);
int GetLineSize(FILE* file);
int GetColumnSize(FILE* file);
void ReadMap(int *map[], int lSize, int cSize);
int GetMap(int *map[],FILE* file, int lSize, int cSize);
