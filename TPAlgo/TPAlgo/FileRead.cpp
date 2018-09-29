#include "stdafx.h"
int GetLineSize()
{
	int c;
	FILE *file;
	int lineNumber = 0;
	errno_t err = fopen_s(&file, "C:\\Users\\Hedriw\\Desktop\\TP Algo\\TPAlgo\\test.txt", "r");
	if (err == 0)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (48 <= c && c <= 57)
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
	errno_t err = fopen_s(&file, "C:\\Users\\Hedriw\\Desktop\\TP Algo\\TPAlgo\\test.txt", "r");
	if (err == 0)
	{
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF) {}
		while (!iswblank(c = getc(file)) && !iswcntrl(c) && c != EOF)
		{
			if (48 <= c && c <= 57)
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
void GetMap(int *map[], int lSize, int cSize)
{
	int carac;
	int conform = 1;
	int firstreturn = 0;
	int caracNumber = 0;
	FILE *file;
	errno_t err = fopen_s(&file, "C:\\Users\\Hedriw\\Desktop\\TP Algo\\TPAlgo\\test.txt", "r");
	if (err == 0) {
		while (!iswcntrl(carac = getc(file))) {}
		for (int l = 0; l < lSize; l++)
		{
			int c = 0;
			do
			{
				carac = getc(file);
				if ((carac == 48 || carac == 49) && c<cSize)
				{
					map[l][c] = carac - 48;
					c++;
				}
				else if (iswcntrl(carac) || iswblank(carac) || carac == EOF)
				{
					break;
				}
				else
				{
					printf("File not conform!!!");
					l = lSize;
					break;
				}
			} while (1);
		}
		fclose(file);
	}
	else
	{
		printf("The file wasn't open");
	}
}
