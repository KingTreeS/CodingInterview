#include "pch.h"
#include <iostream>

bool g_bInputInvalid = true;

void checkIfMoreThanHalf(int* numbers, int length, int expectedNum)
{
	if (numbers == nullptr)
	{
		g_bInputInvalid = true;
	}

	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (numbers[i] == expectedNum)
		{
			count++;
		}
	}

	g_bInputInvalid = count > length / 2 ? false : true;
}

void Swap(int* num1, int* num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

int MoreThanHalfNum_Solution1Core(int* numbers, int start, int end, int midPosition)
{
	int flag = start + rand() % (end - start + 1);
	int flagNum = numbers[flag];
	Swap(numbers + flag, numbers + start);

	int startPtr = start;
	int endPtr = end;
	int pos = start;

	while (startPtr < endPtr)
	{
		while (endPtr > pos && numbers[endPtr] >= flagNum)
		{
			endPtr--;
		}
		if (endPtr > pos)
		{
			Swap(numbers + pos, numbers + endPtr);
			pos = endPtr;
		}

		while (startPtr < pos && numbers[startPtr] <= flagNum)
		{
			startPtr++;
		}
		if (startPtr < pos)
		{
			Swap(numbers + pos, numbers + startPtr);
			pos = startPtr;
		}
	}

	if (pos == midPosition)
	{
		return numbers[pos];
	}

	if (pos < midPosition)
	{
		return MoreThanHalfNum_Solution1Core(numbers, pos + 1, end, midPosition);
	}

	if (pos > midPosition)
	{
		return MoreThanHalfNum_Solution1Core(numbers, start, pos - 1, midPosition);
	}
}

int MoreThanHalfNum_Solution1(int* numbers, int length)
{
	if (numbers == nullptr || length < 1)
	{
		g_bInputInvalid = true;
		return 0;
	}

	int expectedNum = MoreThanHalfNum_Solution1Core(numbers, 0, length - 1, length / 2);

	checkIfMoreThanHalf(numbers, length, expectedNum);
	if (g_bInputInvalid)
	{
		return 0;
	}
	return expectedNum;
}

int MoreThanHalfNum_Solution2(int* numbers, int length)
{
	if (numbers == nullptr || length < 1)
	{
		g_bInputInvalid = true;
		return 0;
	}

	int expectedNum = numbers[0];
	int expectedNumCount = 1;
	int i = 1;
	while (i < length)
	{
		if (expectedNum != numbers[i])
		{
			expectedNumCount--;
			if (expectedNumCount == 0)
			{
				expectedNum = numbers[i];
				expectedNumCount = 1;
			}
		}
		else
		{
			expectedNumCount++;
		}
		i++;
	}

	checkIfMoreThanHalf(numbers, length, expectedNum);
	if (g_bInputInvalid)
	{
		return 0;
	}
	return expectedNum;
}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, int expectedValue, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	int* copy = new int[length];
	for (int i = 0; i < length; ++i)
		copy[i] = numbers[i];

	printf("Test for solution1: ");
	int result = MoreThanHalfNum_Solution1(numbers, length);
	if (result == expectedValue && g_bInputInvalid == expectedFlag)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	printf("Test for solution2: ");
	result = MoreThanHalfNum_Solution2(copy, length);
	if (result == expectedValue && g_bInputInvalid == expectedFlag)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	delete[] copy;
}

// 存在出现次数超过数组长度一半的数字
void Test1()
{
	int numbers[] = { 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
void Test2()
{
	int numbers[] = { 1, 2, 3, 2, 4, 2, 5, 2, 3 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
void Test3()
{
	int numbers[] = { 2, 2, 2, 2, 2, 1, 3, 4, 5 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
void Test4()
{
	int numbers[] = { 1, 3, 4, 5, 2, 2, 2, 2, 2 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 输入空指针
void Test5()
{
	int numbers[] = { 1 };
	Test("Test5", numbers, 1, 1, false);
}

// 输入空指针
void Test6()
{
	Test("Test6", nullptr, 0, 0, true);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}