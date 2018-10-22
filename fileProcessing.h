/**
 * \file fileProcessing.h
 * \author GERTNER Pierre & DUVET Youri
 * \date 20 Oct 2018
 * \brief Header containing all functions needed to process the grid files.
 */

#ifndef FILE_PROCESSING_HEADER_FILE
#define FILE_PROCESSING_HEADER_FILE

/**
 * \fn int ** getMapFromFile(char * fileName,int* width, int* height,int *error);
 * \brief Function that generates a int ** from a grid file.
 *
 * The function will first check if the file exists if not, the *error pointer will take the \b ERROR_FILE_NOT_FOUND value.
 * Then it will check the indicated height and width of the grid map.
 * If any of these are negativ values the *error pointer will take the \b ERROR_SIZE_VALUES_NOT_CONFORM value.
 * If any of these values contain non digit values, the *error pointer will take the \b ERROR_SIZE_VALUES_NOT_CONFORM value.
 * If any of these values are equal to 0, the *error pointer will take the \b ERROR_SIZE_VALUES_ZERO value;
 * Then, it will check the given grid :
 * If any of the grid values are not equal to 0 or 1, the *error pointer will take the \b ERROR_CARACTER_NOT_CONFORM value.
 * If the given grid has any line containing too much or not enough digits, the *error pointer will take the \b ERROR_SIZE_NOT_CONFORM value.
 * If the given grid has not enough or too much lines, the *error pointer will take the \b ERROR_SIZE_NOT_CONFORM value.
 * Else, the map is conform to the values expected and *error will contain \b SUCCES_FILE value.
 * \param fileName Name of the file containing the grid.
 * \param width Pointer to int that will contain the grids width.
 * \param error Pointer to the errors value. Used to manage exceptions.
 * \return The processed map
 * \prec \p width and \p height must be positive.
 *          The \p map, \p coords and \p sizeTuple must not be NULL.
 *  \warning Allways check the value of the \b *error before processing algrothims to the map.
 */
int ** getMapFromFile(char * fileName,int* width, int* height,int *error);


/**
 * \fn int GetLineSize(FILE* file);
 * \brief Function that will return the indicated amount of lines in the grid file.
 *
 * This function will check the first line of the grid file and will check if every character until a space are digits.
 * If it encounter a non digit character will return -1.
 * Else it will calculate the given value using a base10 algortihm :
 * ie. : 101 = 1*10^2 + 0*10^1 + 1*10^3
 *
 * \param file pointer to the file.
 * \return The indicated amount of lines.
 * \prec \p file must not be NULL.
 */
int GetLineSize(FILE* file);

/**
 * \fn int GetColumnSize(FILE* file);
 * \brief Function that will return the indicated amount of columns in the grid file.
 *
 * This function will first skip the first digits until s space. Then will check if every character until a space are digits.
 * If it encounter a non digit character will return -1.
 * Else it will calculate the given value using a base10 algortihm :
 * ie. : 101 = 1*10^2 + 0*10^1 + 1*10^3
 *
 * \param file pointer to the file.
 * \return The indicated amount of columns.
 * \prec \p file must not be NULL.
 */
int GetColumnSize(FILE* file);

/**
 * \fn int GetMap(int *map[],FILE* file, int lSize, int cSize);
 * \brief Function that will fill the **int grid with the grid values in the file.
 *
 * This function skips the first line containg the line and columns amount.
 * It will check for every character that it is a digit. If not will return \b ERROR_CARACTER_NOT_CONFORM.
 * If the given width or height do not correpond to the grid in the file : Not enough or too much characters on the height or width. It will return a \b ERROR_SIZE_NOT_CONFORM.
 * \param file pointer to the file.
 * \return 1 if success else an ERROR value.
 * \prec \p file must not be NULL.
 */
int GetMap(int *map[],FILE* file, int lSize, int cSize);

/**
 * \fn void ReadMap(int *map[], int lSize, int cSize);
 * \brief Functions that outputs the given map
 *
 * This function will first skip the first digits until s space. Then will check if every character until a space are digits.
 * If it encounter a non digit character will return -1.
 * Else it will calculate the given value using a base10 algortihm :
 * ie. : 101 = 1*10^2 + 0*10^1 + 1*10^3
 *
 * \param lSize Height of the map
 * \param cSize Width of the map
 * \prec \p map must not be NULL.
 */
void ReadMap(int *map[], int lSize, int cSize);
#endif
