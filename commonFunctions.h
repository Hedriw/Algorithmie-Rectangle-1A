/**
 * \file commonFunctions.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all usfull common functions for the program.
 */

#ifndef COMMON_HEADER_FILE
#define COMMON_HEADER_FILE

/**
 * \fn int ** getRandomMap(int height,int width,float percent);
 * \brief Function that returns a random height*width map with percent% of walls
 *
 * \param height Height of the map.
 * \param width Width of the map.
 * \return the int map.
 * \warning The \p height,\p width and \p percent must be positive numbers.
 */
int ** getRandomMap(int height,int width,float percent);

/**
 * \fn int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize);
 * \brief Function that checks if an area of a map contains any walls.
 *
 * This function checks if an area contains any walls.
 * The area is definied by one point(\p cCursor, \p lCursor) wich is the upper left corner and its width and height from this point.
 *
 * \param map containing the area.
 * \param lCursor Y coordinate of the point of the area.
 * \param cCursor X coordinate of the point of the area.
 * \param lSize Height of the area to check.
 * \param cSize Width of the area to check.
 * \return 1 if area contains a wall. 0 if not.
 * \warning The \p lCursor,\p cCursor,\p lSize and \p cSize  must be positive numbers.
 *          The \p map must not be NULL.
 */
int ContainsBlack(int *map[],int lCursor,int cCursor,int lSize,int cSize);

/**
 * \fn int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize);
 * \brief Function that calculates the size of the area of a map.
 *
 * The function calculates the size of an area of a map. The area is definied by one point(\p cCursor, \p lCursor) wich is the upper left corner and its width and height from this point.
 * It first checks if it contains black using <b>ContainsBlack</b> then return the size of the area if there's no walls.
 *
 * \param map containing the area.
 * \param lCursor Y coordinate of the point of the area.
 * \param cCursor X coordinate of the point of the area.
 * \param lSize Height of the area to check.
 * \param cSize Width of the area to check.
 * \return The size of the area if the area does not contain walls. Else, will return 0.
 * \warning The \p lCursor,\p cCursor,\p lSize and \p cSize  must be positive numbers.
 *          The \p map must not be NULL.
 */
int CalculSize(int **map,int lCursor,int cCursor,int lSize,int cSize);

/**
 * \fn int stringIsNumber(char * stringToTest);
 * \brief Function that checks if a string is a number.
 *
 * \param stringToTest String to be tested.
 * \return 1 if the string is a number. Else 0.
 * \warning The \p stringToTest must not be NULL.
 */
int stringIsNumber(char * stringToTest);

/**
 * \fn void startStatistics(int fromSize,int toSize, char* fileName);
 * \brief Function that generates a csv of the performences of the different algorthims.
 *
 * \param fromSize Smallest size to test.
 * \param toSize Biggest size to test.
 * \warning The \p fromSize must be lower or equal to \p toSize.
 *          The \p fileName must not be NULL.
 */
void startStatistics(int fromSize,int toSize, char* fileName);

/**
 * \fn void StartCalculate(char * fileName,char * algoNumber);
 * \brief Function that will treat a map from a file using the specified algorithm.
 *
 * \param fileName Smallest size to test.
 * \param algoNumber Number of the algorithm to be used.
 * \param mustShow Boolean value to indicate if the map should be printed.
 * \warning The \p algoNumber must be part of the available algorithms.
 *          The \p fileName must not be NULL.
 */
void StartCalculate(char * fileName,char * algoNumber, int mustShow);

/**
 * \fn void displayHelp(char * binName);
 * \brief Function that displays the help text to use the binary.
 *
 * \param binName Name of the compiled binary used.
 * \warning he \p binName must not be NULL.
 */
void displayHelp(char * binName);

#endif
