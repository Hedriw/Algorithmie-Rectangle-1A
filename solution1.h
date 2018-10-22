/**
 * \file solution1.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all usfull functions for the solution1.
 */

#ifndef SOLUTION1_HEADER_FILE
#define SOLUTION1_HEADER_FILE


/**
 * \fn int Solution1(int **map, int widht, int height, tuple *coords,tuple *size_tuple);
 * \brief Naive function that will calculate the biggest area containing no wall in the specified map.
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
int Solution1(int **map, int width, int height, tuple *coords,tuple *sizeTuple);

/**
 * \fn int CalculMaxSizeCurrentCursor(int ** map, int width, int height, int lCursor, int cCursor, tuple * sizeTuple);
 * \brief Function that return the biggest area from a point(X,Y) of a map.
 *
 * \param map Grid to be treated.
 * \param width Width of the map.
 * \param height Height of the map.
 * \param lCursor Y coordinate of the point of the area.
 * \param cCursor X coordinate of the point of the area.
 * \param sizeTuple Pointer to a struct that will contain the height and width of the biggest area found.
 * \return Biggest size found
 * \prec The \p map, \p sizeTuple must not be NULL.
 */
int CalculMaxSizeCurrentCursor(int ** map, int width, int height, int lCursor, int cCursor, tuple * sizeTuple);

#endif
