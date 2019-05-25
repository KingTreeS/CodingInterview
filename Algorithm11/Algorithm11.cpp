#include "pch.h"
#include <iostream>

int MinInArray(int* numbers, int startIndex,int endIndex)
{
	int result = numbers[startIndex];
	while (startIndex <= endIndex)
	{
		if (result > numbers[startIndex])
		{
			result = numbers[startIndex];
		}
		startIndex++;
	}

	return result;
}

int Min(int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
	{
		throw new std::exception("Invalid parameters");
	}

	int startIndex = 0;
	int endIndex = length - 1;
	int midIndex = startIndex;

	while (numbers[startIndex] >= numbers[endIndex])
	{
		if (startIndex + 1 == endIndex)
		{
			midIndex = endIndex;
			break;
		}

		midIndex = (startIndex + endIndex) / 2;

		if (numbers[startIndex] == numbers[midIndex] && numbers[midIndex] == numbers[endIndex])
		{
			return MinInArray(numbers, startIndex, endIndex);
		}

		if (numbers[startIndex] < numbers[midIndex])
		{
			startIndex = midIndex;
		}
		else if (numbers[midIndex] < numbers[endIndex])
		{
			endIndex = midIndex;
		}
	}

	return numbers[midIndex];
}

// ====================测试代码====================
void Test(int* numbers, int length, int expected)
{
	int result = 0;
	try
	{
		result = Min(numbers, length);

		for (int i = 0; i < length; ++i)
			printf("%d ", numbers[i]);

		if (result == expected)
			printf("\tpassed\n");
		else
			printf("\tfailed\n");
	}
	catch (...)
	{
		if (numbers == nullptr)
			printf("Test passed.\n");
		else
			printf("Test failed.\n");
	}
}

int main()
{
	// 典型输入，单调升序的数组的一个旋转
	int array1[] = { 3, 4, 5, 1, 2 };
	Test(array1, sizeof(array1) / sizeof(int), 1);

	// 有重复数字，并且重复的数字刚好的最小的数字
	int array2[] = { 3, 4, 5, 1, 1, 2 };
	Test(array2, sizeof(array2) / sizeof(int), 1);

	// 有重复数字，但重复的数字不是第一个数字和最后一个数字
	int array3[] = { 3, 4, 5, 1, 2, 2 };
	Test(array3, sizeof(array3) / sizeof(int), 1);

	// 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
	int array4[] = { 1, 0, 1, 1, 1 };
	Test(array4, sizeof(array4) / sizeof(int), 0);

	// 单调升序数组，旋转0个元素，也就是单调升序数组本身
	int array5[] = { 1, 2, 3, 4, 5 };
	Test(array5, sizeof(array5) / sizeof(int), 1);

	// 数组中只有一个数字
	int array6[] = { 2 };
	Test(array6, sizeof(array6) / sizeof(int), 2);

	// 输入nullptr
	Test(nullptr, 0, 0);

	return 0;
}