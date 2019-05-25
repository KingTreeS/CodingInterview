#include "pch.h"
#include <iostream>


bool equal(double num1, double num2)
{
	if (num1 - num2 > -0.0000001 && num1 - num2 < 0.0000001)
	{
		return true;
	}
	return false;
}

double PowerCore(double base, int exponent)
{
	if (exponent == 0)
	{
		return 1.0;
	}

	if (exponent == 1)
	{
		return base;
	}

	double result = PowerCore(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1)
	{
		result *= base;
	}

	return result;
}

bool g_InvalidInput = false;

double Power(double base, int exponent)
{
	if (equal(base, 0.0) && exponent < 0)
	{
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int exp = (unsigned int)(exponent < 0 ? -exponent : exponent);
	double result = PowerCore(base, exp);

	if (exponent < 0)
	{
		result = 1.0 / result;
	}

	return result;
}

// ====================测试代码====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
	double result = Power(base, exponent);
	if (equal(result, expectedResult) && g_InvalidInput == expectedFlag)
		std::cout << testName << " passed" << std::endl;
	else
		std::cout << testName << " FAILED" << std::endl;
}

int main()
{
	// 底数、指数都为正数
	Test("Test1", 2, 3, 8, false);

	// 底数为负数、指数为正数
	Test("Test2", -2, 3, -8, false);

	// 指数为负数
	Test("Test3", 2, -3, 0.125, false);

	// 指数为0
	Test("Test4", 2, 0, 1, false);

	// 底数、指数都为0
	Test("Test5", 0, 0, 1, false);

	// 底数为0、指数为正数
	Test("Test6", 0, 4, 0, false);

	// 底数为0、指数为负数
	Test("Test7", 0, -4, 0, true);

	return 0;
}