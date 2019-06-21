#include "pch.h"
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

int NumberOf1Between1AndN_Solution1Core(int n)
{
	int count = 0;
	while (n)
	{
		if (n % 10 == 1)
		{
			count++;
		}
		n = n / 10;
	}

	return count;
}

int NumberOf1Between1AndN_Solution1(int n)
{
	if (n < 1)
	{
		return 0;
	}

	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		count += NumberOf1Between1AndN_Solution1Core(i);
	}

	return count;
}

int PowOfBase(int n)
{
	if (n <0)
	{
		return 1;
	}

	int sum = 1;
	while (n)
	{
		sum *= 10;
		n--;
	}
	return sum;
}

int NumberOf1Between1AndN_Solution2Core(const char* numStr)
{
	if (numStr == nullptr || *numStr < '0' || *numStr >'9' || *numStr == '\0')
	{
		return 0;
	}

	int first = *numStr - '0';
	int len = strlen(numStr);

	if (len == 1 && first == 0)
	{
		return 0;
	}
	if (len==1 && first > 0)
	{
		return 1;
	}

	int countOfHigh = 0;
	int countOfOther = 0;
	int countOfSplit = 0;

	if (first > 1)
	{
		countOfHigh = PowOfBase(len - 1);
	}
	else if (first == 1)
	{
		countOfHigh = std::atoi(numStr + 1) + 1;
	}

	countOfOther = first * (len - 1) * PowOfBase(len - 2);
	countOfSplit = NumberOf1Between1AndN_Solution2Core(numStr + 1);

	return countOfHigh + countOfOther + countOfSplit;
}

int NumberOf1Between1AndN_Solution2(int n)
{
	if (n < 1)
	{
		return 0;
	}

	char numStr[50];
	sprintf_s(numStr, "%d", n);

	return NumberOf1Between1AndN_Solution2Core(numStr);
}

// ====================测试代码====================
void Test(const char* testName, int n, int expected)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	if (NumberOf1Between1AndN_Solution1(n) == expected)
		printf("Solution1 passed.\n");
	else
		printf("Solution1 failed.\n");

	if (NumberOf1Between1AndN_Solution2(n) == expected)
		printf("Solution2 passed.\n");
	else
		printf("Solution2 failed.\n");

	printf("\n");
}

void Test()
{
	Test("Test1", 1, 1);
	Test("Test2", 5, 1);
	Test("Test3", 10, 2);
	Test("Test4", 55, 16);
	Test("Test5", 99, 20);
	Test("Test6", 10000, 4001);
	Test("Test7", 21345, 18821);
	Test("Test8", 0, 0);
}

int main()
{
	Test();

	return 0;
}