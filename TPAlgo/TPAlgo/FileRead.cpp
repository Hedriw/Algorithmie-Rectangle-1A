#include "stdafx.h"
int GetLineSize()
{
	int c;
	FILE *file;
	int lineNumber = 0;
	errno_t err = fopen_s(&file, FILENAME, "r");
	if (err == 0)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				lineNumber = lineNumber * 10 + (c - 48);
			}
			else
			{
				lineNumber = -1;
				break;
			}
		}

	}
	return lineNumber;
}
int GetColumnSize()
{
	int c;
	FILE *file;
	int columnNumber = 0;
	errno_t err = fopen_s(&file, FILENAME, "r");
	if (err == 0)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF) {}
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (ASCII_0 <= c && c <= ASCII_9)
			{
				columnNumber = columnNumber * 10 + (c - 48);
			}
			else
			{
				columnNumber = -1;
				break;
			}
		}
	}
	return columnNumber;
}
void ReadMap(int *map[], int lSize, int cSize)
{
	for (int l = 0; l < lSize; l++)
	{
		for (int c = 0; c < cSize; c++)
		{
			char tempC = map[l][c];
			printf("%i", map[l][c]);
		}
		printf("\n");
	}
}
int GetMap(int *map[], int lSize, int cSize)
{
	int carac;
	int conform = 1;
	int firstreturn = 0;
	int caracNumber = 0;
	FILE *file;
	errno_t err = fopen_s(&file, FILENAME, "r");
	if (err == 0) {
		while (!iswcntrl(carac = getc(file))) {}
		for (int l = 0; l < lSize; l++)
		{
			int c = 0;
			do
			{
				carac = getc(file);
				if ((carac == ASCII_0 || carac == ASCII_1))
				{
					if (c < cSize)
					{
						map[l][c] = carac - ASCII_0;
						c++;
					}
					else
					{
						return ERROR_SIZE_NOT_CONFORM;
					}
					
				}
				else if (iswcntrl(carac) || iswblank(carac) || carac == EOF)
				{
					if (c < cSize)
						return ERROR_SIZE_NOT_CONFORM;
					break;
				}
				else
				{
					return ERROR_CARACTER_NOT_CONFORM;
				}
			} while (1);
		}
		fclose(file);
		return 1;
	}
	else
	{
		return ERROR_FILE_NOT_FOUND;
	}
}
