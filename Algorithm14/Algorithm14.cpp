#include "pch.h"
#include <iostream>

//动态规划
int maxProductAfterCutting_solution1(int length)
{
	if (length < 2)
	{
		return 0;
	}

	int* result = new int[length];
	memset(result, 0, length);
	result[0] = 1;

	int i = 1;
	while (i < length)
	{
		int max = 0;
		for (int j = 0; j <= (i - 1) / 2; j++)
		{
			int tmp1 = result[j] * result[i - j - 1];
			int tmp2 = (j + 1)*(i - j);
			int tmp3 = (j + 1)* result[i - j - 1];
			int tmp4 = result[j] * (i - j);

			int tmp = (tmp1 > tmp2 ? tmp1 : tmp2) > (tmp3 > tmp4 ? tmp3 : tmp4) ? (tmp1 > tmp2 ? tmp1 : tmp2) : (tmp3 > tmp4 ? tmp3 : tmp4);
			if (max < tmp)
			{
				max = tmp;
			}
		}
		result[i] = max;
		i++;
	}

	return result[length - 1];
}

//贪婪算法
int maxProductAfterCutting_solution2(int length)
{
	return 0;
}

// ====================测试代码====================
void test(const char* testName, int length, int expected)
{
	int result1 = maxProductAfterCutting_solution1(length);
	if (result1 == expected)
		std::cout << "Solution1 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution1 for " << testName << " FAILED." << std::endl;

	/*int result2 = maxProductAfterCutting_solution2(length);
	if (result2 == expected)
		std::cout << "Solution2 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution2 for " << testName << " FAILED." << std::endl;*/
}

void test1()
{
	int length = 1;
	int expected = 0;
	test("test1", length, expected);
}

void test2()
{
	int length = 2;
	int expected = 1;
	test("test2", length, expected);
}

void test3()
{
	int length = 3;
	int expected = 2;
	test("test3", length, expected);
}

void test4()
{
	int length = 4;
	int expected = 4;
	test("test4", length, expected);
}

void test5()
{
	int length = 5;
	int expected = 6;
	test("test5", length, expected);
}

void test6()
{
	int length = 6;
	int expected = 9;
	test("test6", length, expected);
}

void test7()
{
	int length = 7;
	int expected = 12;
	test("test7", length, expected);
}

void test8()
{
	int length = 8;
	int expected = 18;
	test("test8", length, expected);
}

void test9()
{
	int length = 9;
	int expected = 27;
	test("test9", length, expected);
}

void test10()
{
	int length = 10;
	int expected = 36;
	test("test10", length, expected);
}

void test11()
{
	int length = 50;
	int expected = 86093442;
	test("test11", length, expected);
}

int main(int agrc, char* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();

	return 0;
}