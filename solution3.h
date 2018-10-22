/**
 * \file solution3.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all usfull functions for the solution number 3.
 */

#ifndef SOLUTION3_HEADER_FILE
#define SOLUTION3_HEADER_FILE

int CalculSizeSolution3(int *lineMap,int currentColumn,int maxHeight,tuple *columnCoord,tuple* rectSize);
/**
 * \fn int Solution3(int *map[], int widht, int height, tuple *coords,tuple *size_tuple);
 * \brief Intermediary array function that will calculate the biggest area containing no wall in the specified map.
 *
 * \param map Grid to be treated.
 * \param width Width of the map.
 * \param height Height of the map.
 * \param coords Pointer to a struct that will contain the coordinates of the upper left point(X,Y) of the biggest area found.
 * \param sizeTuple Pointer to a struct that will contain the height and width of the biggest area found.
 * \return The size of the biggest area.
 * \prec \p width and \p height must be positive.
 *          The \p map, \p coords and \p sizeTuple must not be NULL.
 */
int Solution3(int *map[], int widht, int height,tuple * coords,tuple *sizeTuple);

#endif
