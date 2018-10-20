/**
 * \file solution4.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all usfull functions for the solution number 4.
 */

#ifndef SOLUTION4_HEADER_FILE
#define SOLUTION4_HEADER_FILE

int CalculSizeSolution4(stack* stack,int currentColumn,int lastColumnSize,int currentColumnSize,tuple *columCoord,tuple* rectSize);
int Solution4(int *map[], int widht, int height,tuple * coords,tuple * rectSize);

#endif
