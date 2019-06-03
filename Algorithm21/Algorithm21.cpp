#include "pch.h"
#include <iostream>

//判断交换条件（是否为偶数）
bool isEven(int* ptr)
{
	if (ptr == nullptr)
	{
		return false;
	}

	if ((*ptr)&(0x1))
	{
		return false;
	}

	return true;
}

void ReorderOddEven_2(int* copy, int length)
{
	if (copy == nullptr || length < 1)
	{
		return;
	}

	int* ptrStart = copy;
	int* ptrEnd = copy + length - 1;

	while (ptrStart != ptrEnd)
	{
		while (ptrStart < ptrEnd && !isEven(ptrStart))
		{
			ptrStart++;
		}

		while (ptrEnd > ptrStart && isEven(ptrEnd))
		{
			ptrEnd--;
		}

		if (ptrStart != ptrEnd)
		{
			int tmp = *ptrStart;
			*ptrStart = *ptrEnd;
			*ptrEnd = tmp;
		}
	}
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
	if (length < 0)
		return;

	for (int i = 0; i < length; ++i)
		printf("%d\t", numbers[i]);

	printf("\n");
}

void Test(const char* testName, int numbers[], int length)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	int* copy = new int[length];
	for (int i = 0; i < length; ++i)
	{
		copy[i] = numbers[i];
	}

	/*printf("Test for solution 1:\n");
	PrintArray(numbers, length);
	ReorderOddEven_1(numbers, length);
	PrintArray(numbers, length);*/

	printf("Test for solution 2:\n");
	PrintArray(copy, length);
	ReorderOddEven_2(copy, length);
	PrintArray(copy, length);

	delete[] copy;
}

void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int));
}

void Test2()
{
	int numbers[] = { 2, 4, 6, 1, 3, 5, 7 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int));
}

void Test3()
{
	int numbers[] = { 1, 3, 5, 7, 2, 4, 6 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int));
}

void Test4()
{
	int numbers[] = { 1 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int));
}

void Test5()
{
	int numbers[] = { 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int));
}

void Test6()
{
	Test("Test6", nullptr, 0);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}