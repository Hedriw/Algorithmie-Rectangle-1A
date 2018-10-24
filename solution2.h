/**
 * \file solution2.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all usfull functions for the solution2.
 */

#ifndef SOLUTION2_HEADER_FILE
#define SOLUTION2_HEADER_FILE


/**
 * \fn int Solution2(int **map, int widht, int height, tuple *coords,tuple *size_tuple);
 * \brief Naive function that will calculate the biggest area containing no wall in the specified map.
 *
 * Algorithm that will calculate the maximum area in a grid. It is an upgraded version of the Solution1() with a cost of O(n⁶).
 * The algorithm will produce every area possible checking if it contains any walls :
 * From a cursor represented by a point(X,Y), it will create all the area having the point as its upper left point and iterate threw the height and width.
 * But if from a certain point(X,Y), it encounters a wall at point(wallX,wallY), the next "width" iterations from this point will stop at point(wallX,wallY).
 * See : CalculMaxSizeCurrentCursorOptimized()
 * \param map Grid to be treated.
 * \param width Width of the Grid.
 * \param height Height of the Grid.
 * \param coords Pointer to a struct that will contain the coordinates of the upper left point(X,Y) of the biggest area found.
 * \param sizeTuple Pointer to a struct that will contain the height and width of the biggest area found.
 * \return The size of the biggest area.
 * \prec \p width and \p height must be positive.
 *          The \p map, \p coords and \p sizeTuple must not be NULL.
 */
int Solution2(int **map, int widht, int height,tuple *coords,tuple *sizeTuple);


/**
 * \fn int CalculMaxSizeCurrentCursorOptimized(int ** map,int width,int height,int lCursor,int cCursor,tuple * sizeTuple);
 * \brief Function used by the upgraded algorithm to return the maximum size from the current cursor.
 *
 * The function returns the largest area from a point(X,Y) : It will iterate threw the given height and width.
 * But when encoutering a "wall" at a point(xWall,yWall), the next "width" iterations will not go further than the width at point(xWall,yWall)
 *
 * \param map Grid to be treated.
 * \param width Width of the Grid.
 * \param height Height of the Grid.
 * \param lCursor First coord of the cursor.
 * \param cCursor Second coord of the cursor.
 * \param sizeTuple Pointer to a struct that will contain the height and width of the biggest area found.
 * \return The size of the biggest area.
 * \prec \p width,\p height,\p lCursor and \p cCursor must be positive.
 *          The \p map and \p sizeTuple must not be NULL.
 */
int CalculMaxSizeCurrentCursorOptimized(int * map[],int width,int height,int lCursor,int cCursor,tuple * sizeTuple);
#endif
