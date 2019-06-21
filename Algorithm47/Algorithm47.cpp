#include "pch.h"
#include <iostream>

int getMaxValue_solution1(const int* values, int rows, int cols)
{
	if (values == nullptr || rows < 1 || cols < 1)
	{
		return 0;
	}

	int i = rows - 1;
	int j = cols - 1;
	int maxValue = values[i * cols + j];

	while (i + j != 0)
	{
		if (i == 0)
		{
			maxValue += values[i*cols + j - 1];
			j--;
		}
		else if (j == 0)
		{
			maxValue += values[(i - 1)*cols + j];
			i--;
		}
		else if (values[i*cols + j - 1] < values[(i - 1)*cols + j])
		{
			maxValue += values[(i - 1)*cols + j];
			i--;
		}
		else
		{
			maxValue += values[i*cols + j - 1];
			j--;
		}
	}

	return maxValue;
}

// ====================测试代码====================
void test(const char* testName, const int* values, int rows, int cols, int expected)
{
	if (getMaxValue_solution1(values, rows, cols) == expected)
		std::cout << testName << ": solution1 passed." << std::endl;
	else
		std::cout << testName << ": solution1 FAILED." << std::endl;

	/*if (getMaxValue_solution2(values, rows, cols) == expected)
		std::cout << testName << ": solution2 passed." << std::endl;
	else
		std::cout << testName << ": solution2 FAILED." << std::endl;*/
}

void test1()
{
	// 三行三列
	int values[][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	int expected = 29;
	test("test1", (const int*)values, 3, 3, expected);
}

void test2()
{
	//四行四列
	int values[][4] = {
		{ 1, 10, 3, 8 },
		{ 12, 2, 9, 6 },
		{ 5, 7, 4, 11 },
		{ 3, 7, 16, 5 }
	};
	int expected = 53;
	test("test2", (const int*)values, 4, 4, expected);
}

void test3()
{
	// 一行四列
	int values[][4] = {
		{ 1, 10, 3, 8 }
	};
	int expected = 22;
	test("test3", (const int*)values, 1, 4, expected);
}

void test4()
{
	int values[4][1] = {
		{ 1 },
		{ 12 },
		{ 5 },
		{ 3 }
	};
	int expected = 21;
	test("test4", (const int*)values, 4, 1, expected);
}

void test5()
{
	// 一行一列
	int values[][1] = {
		{ 3 }
	};
	int expected = 3;
	test("test5", (const int*)values, 1, 1, expected);
}

void test6()
{
	// 空指针
	int expected = 0;
	test("test6", nullptr, 0, 0, expected);
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}