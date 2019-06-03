#include "pch.h"
#include <iostream>

void PrintNum(int** numbers, int row, int column)
{
	std::cout << numbers[row][column] << ",";
}

void PrintMatrixClockwiselyCore(int** numbers, int columns, int rows, int start)
{
	int endX = columns - start;
	int endY = rows - start;

	for (int i = start; i < endX; i++)
	{
		PrintNum(numbers, start, i);
	}

	if (start < endY - 1)
	{
		for (int i = start + 1; i < endY; i++)
		{
			PrintNum(numbers, i, endX - 1);
		}
	}

	if (start < endX - 1 && start < endY - 1)
	{
		for (int i = endX - 2; i >= start; i--)
		{
			PrintNum(numbers, endY - 1, i);
		}
	}

	if (start < endX - 1 && start < endY - 2)
	{
		for (int i = endY - 2; i > start; i--)
		{
			PrintNum(numbers, i, start);
		}
	}
}

void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
	if (numbers == nullptr || columns < 1 || rows < 1)
	{
		return;
	}

	int start = 0;
	while (columns > start * 2 && rows > start * 2)
	{
		PrintMatrixClockwiselyCore(numbers, columns, rows, start);
		start++;
	}
}

// ====================测试代码====================
void Test(int columns, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", columns, rows);

	if (columns < 1 || rows < 1)
		return;

	int** numbers = new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		numbers[i] = new int[columns];
		for (int j = 0; j < columns; ++j)
		{
			numbers[i][j] = i * columns + j + 1;
		}
	}

	PrintMatrixClockwisely(numbers, columns, rows);
	printf("\n");

	for (int i = 0; i < rows; ++i)
		delete[](int*)numbers[i];

	delete[] numbers;
}

int main()
{
	/*
	1
	*/
	Test(1, 1);

	/*
	1    2
	3    4
	*/
	Test(2, 2);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	*/
	Test(4, 4);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	21   22   23   24   25
	*/
	Test(5, 5);

	/*
	1
	2
	3
	4
	5
	*/
	Test(1, 5);

	/*
	1    2
	3    4
	5    6
	7    8
	9    10
	*/
	Test(2, 5);

	/*
	1    2    3
	4    5    6
	7    8    9
	10   11   12
	13   14   15
	*/
	Test(3, 5);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	17   18   19   20
	*/
	Test(4, 5);

	/*
	1    2    3    4    5
	*/
	Test(5, 1);

	/*
	1    2    3    4    5
	6    7    8    9    10
	*/
	Test(5, 2);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14    15
	*/
	Test(5, 3);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	*/
	Test(5, 4);

	return 0;
}