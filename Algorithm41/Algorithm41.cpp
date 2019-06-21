#include "pch.h"
#include <iostream>
#include "DynamicArray.h"

// ====================测试代码====================
void Test(const char* testName, DynamicArray<double>& numbers, double expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (abs(numbers.GetMedian() - expected) < 0.0000001)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

int main()
{
	DynamicArray<double> numbers;

	printf("Test1 begins: ");
	try
	{
		numbers.GetMedian();
		printf("FAILED.\n");
	}
	catch (const std::exception&)
	{
		printf("Passed.\n");
	}

	numbers.Insert(5);
	Test("Test2", numbers, 5);

	numbers.Insert(2);
	Test("Test3", numbers, 3.5);

	numbers.Insert(3);
	Test("Test4", numbers, 3);

	numbers.Insert(4);
	Test("Test6", numbers, 3.5);

	numbers.Insert(1);
	Test("Test5", numbers, 3);

	numbers.Insert(6);
	Test("Test7", numbers, 3.5);

	numbers.Insert(7);
	Test("Test8", numbers, 4);

	numbers.Insert(0);
	Test("Test9", numbers, 3.5);

	numbers.Insert(8);
	Test("Test10", numbers, 4);

	return 0;
}