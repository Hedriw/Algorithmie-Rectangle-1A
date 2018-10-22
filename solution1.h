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
 * Algorithm that will calculate the maximum area in a grid. It is a naive algoithm with a cost of O(n⁶).
 * The algorithm will produce every area possible checking if it contains any walls :
 * From a cursor represented by a point(X,Y), it will create all the area having the point as its upper left point and iterate threw the height and width.
 *
 * \param map Grid to be treated.
 * \param width Width of the Grid.
 * \param height Height of the Grid.
 * \param coords Pointer to a struct that will contain the coordinates of the upper left point(X,Y) of the biggest area found.
 * \param sizeTuple Pointer to a struct that will contain the height and width of the biggest area found.
 * \return The size of the biggest area.
 * \warning \p width and \p height must be positive.
 *          The \p map, \p coords and \p sizeTuple must not be NULL.
 */
int Solution1(int **map, int width, int height, tuple *coords,tuple *sizeTuple);
#endif
