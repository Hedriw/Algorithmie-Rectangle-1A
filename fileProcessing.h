/**
 * \file fileProcessing.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all functions and definitions for the structs used in the program.
 */

#ifndef FILE_PROCESSING_HEADER_FILE
#define FILE_PROCESSING_HEADER_FILE

int ** getMapFromFile(char * fileName,int* width, int* height,int *error);
int GetLineSize(FILE* file);
int GetColumnSize(FILE* file);
void ReadMap(int *map[], int lSize, int cSize);
int GetMap(int *map[],FILE* file, int lSize, int cSize);

#endif
