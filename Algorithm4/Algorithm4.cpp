#include "pch.h"
#include <iostream>

bool find(int* matrix, int rows, int columns, int number)
{
	if (matrix == nullptr || rows <= 0 || columns <= 0)
	{
		return false;
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns - 1; j++)
		{
			if (matrix[columns*i + j] > matrix[columns*i + j + 1])
			{
				return false;
			}
		}
	}

	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows - 1; j++)
		{
			if (matrix[rows*j + i] > matrix[rows*(j + 1) + i])
			{
				return false;
			}
		}
	}

	int i = 1;
	int j = columns;

	while (i <= rows && j > 0)
	{
		if (number == matrix[(i - 1)*columns + (j - 1)])
		{
			return true;
		}
		if (number < matrix[(i - 1)*columns + (j - 1)])
		{
			j--;
		}
		else
		{
			i++;
		}
	}

	return false;
}

// ====================测试代码====================
void Test(const char* testName, int* matrix, int rows, int columns, int number, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	bool result = find(matrix, rows, columns, number);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数在数组中
void Test1()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test1", (int*)matrix, 4, 4, 7, true);
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数不在数组中
void Test2()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test2", (int*)matrix, 4, 4, 5, false);
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最小的数字
void Test3()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test3", (int*)matrix, 4, 4, 1, true);
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数是数组中最大的数字
void Test4()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test4", (int*)matrix, 4, 4, 15, true);
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最小的数字还小
void Test5()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test5", (int*)matrix, 4, 4, 0, false);
}
//  1   2   8   9
//  2   4   9   12
//  4   7   10  13
//  6   8   11  15
// 要查找的数比数组中最大的数字还大
void Test6()
{
	int matrix[][4] = { {1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15} };
	Test("Test6", (int*)matrix, 4, 4, 16, false);
}
// 鲁棒性测试，输入空指针
void Test7()
{
	Test("Test7", nullptr, 0, 0, 16, false);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}