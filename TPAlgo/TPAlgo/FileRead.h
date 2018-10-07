#pragma once
#define ASCII_0 48
#define ASCII_1 49
#define ASCII_9 57
#define FILENAME 0
#define ERROR_SIZE_NOT_CONFORM -1
#define ERROR_CARACTER_NOT_CONFORM -3
#define ERROR_FILE_NOT_FOUND 0
#define SUCCES_FILE 1
#define FILENAME "C:\\Users\\Hedriw\\Desktop\\TP Algo\\TPAlgo\\test.txt"
int GetLineSize();
int GetColumnSize();
void ReadMap(int *map[], int lSize, int cSize);
int GetMap(int *map[], int lSize, int cSize);