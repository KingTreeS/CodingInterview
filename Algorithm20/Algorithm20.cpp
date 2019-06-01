#include "pch.h"
#include <iostream>

bool isOperator(const char* str)
{
	if (*str == '+' || *str == '-')
	{
		return true;
	}

	return false;
}

bool isNum(const char* str)
{
	int num = *str - '0';
	if (num >= 0 && num <= 9)
	{
		return true;
	}

	return false;
}

bool isDecimalPoint(const char* str)
{
	if (*str == '.')
	{
		return true;
	}

	return false;
}

bool isCharacter(const char* str)
{
	if (*str == 'e' || *str == 'E')
	{
		return true;
	}

	return false;
}

bool isNumericCore(const char* str, bool decimalPointExisted)
{
	if (*str == '\0')
	{
		return true;
	}

	if (isOperator(str))
	{
		if (isOperator(str+1) || isCharacter(str+1))
		{
			return false;
		}

		return isNumericCore(str + 2, decimalPointExisted);
	}

	if (isNum(str))
	{
		if (isOperator(str+1))
		{
			return false;
		}
		return isNumericCore(str + 1, decimalPointExisted);
	}

	if (isDecimalPoint(str))
	{
		if (decimalPointExisted)
		{
			return false;
		}

		decimalPointExisted = true;
		if (isOperator(str + 1) || isCharacter(str + 1))
		{
			return false;
		}
		return isNumericCore(str + 1, decimalPointExisted);
	}

	if (isCharacter(str))
	{
		if (!decimalPointExisted)
		{
			decimalPointExisted = true;
		}

		if (isDecimalPoint(str + 1) || isCharacter(str+1) || *(str + 1) == '\0')
		{
			return false;
		}
		return isNumericCore(str + 1, decimalPointExisted);
	}
}

bool isNumeric(const char* str)
{
	if (str == nullptr || *str == '\0')
	{
		return false;
	}

	if (isCharacter(str))
	{
		return false;
	}

	if (isOperator(str))
	{
		if (isDecimalPoint(str+1) && *(str+2)=='\0')
		{
			return false;
		}
	}

	if (isDecimalPoint(str) && *(str + 1) == '\0')
	{
		return false;
	}

	return isNumericCore(str, false);
}

// ====================测试代码====================
void Test(const char* testName, const char* str, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (isNumeric(str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int main()
{
	Test("Test1", "100", true);
	Test("Test2", "123.45e+6", true);
	Test("Test3", "+500", true);
	Test("Test4", "5e2", true);
	Test("Test5", "3.1416", true);
	Test("Test6", "600.", true);
	Test("Test7", "-.123", true);
	Test("Test8", "-1E-16", true);
	Test("Test9", "1.79769313486232E+308", true);

	printf("\n\n");

	Test("Test10", "12e", false);
	Test("Test11", "1a3.14", false);
	Test("Test12", "1+23", false);
	Test("Test13", "1.2.3", false);
	Test("Test14", "+-5", false);
	Test("Test15", "12e+5.4", false);
	Test("Test16", ".", false);
	Test("Test17", ".e1", false);
	Test("Test18", "e1", false);
	Test("Test19", "+.", false);
	Test("Test20", "", false);
	Test("Test21", nullptr, false);

	return 0;
}