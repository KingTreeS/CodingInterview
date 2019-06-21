#include "pch.h"
#include <iostream>
#include <string.h>
#include <algorithm>

const int g_MaxNumLength = 10;
#define MAXNUMLEN g_MaxNumLength * 2 + 1

char* g_strCombine1 = new char[MAXNUMLEN];
char* g_strCombine2 = new char[MAXNUMLEN];

int compare(const void* strNum1, const void* strNum2)
{
	strcpy_s(g_strCombine1, MAXNUMLEN, *(const char**)strNum1);
	strcat_s(g_strCombine1, MAXNUMLEN, *(const char**)strNum2);

	strcpy_s(g_strCombine2, MAXNUMLEN, *(const char**)strNum2);
	strcat_s(g_strCombine2, MAXNUMLEN, *(const char**)strNum1);

	return strcmp(g_strCombine1, g_strCombine2);
}

void PrintMinNumber(int* numbers, int length)
{
	if (numbers == nullptr || length < 1)
	{
		return;
	}

	char** strNumbers = (char**)(new int[length]);
	for (int i = 0; i < length; i++)
	{
		strNumbers[i] = new char[g_MaxNumLength + 1];
		sprintf_s(strNumbers[i], g_MaxNumLength + 1, "%d", numbers[i]);
	}

	qsort(strNumbers, length, sizeof(char*), compare);

	for (int i = 0; i < length; i++)
	{
		std::cout << strNumbers[i];
	}
	std::cout << "\n";

	for (int i = 0; i < length; i++)
	{
		delete[] strNumbers[i];
	}
	delete[] strNumbers;
}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	if (expectedResult != nullptr)
		printf("Expected result is: \t%s\n", expectedResult);

	printf("Actual result is: \t");
	PrintMinNumber(numbers, length);

	printf("\n");
}

void Test1()
{
	int numbers[] = { 3, 5, 1, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), "12345");
}

void Test2()
{
	int numbers[] = { 3, 32, 321 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), "321323");
}

void Test3()
{
	int numbers[] = { 3, 323, 32123 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), "321233233");
}

void Test4()
{
	int numbers[] = { 1, 11, 111 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), "111111");
}

// 数组中只有一个数字
void Test5()
{
	int numbers[] = { 321 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), "321");
}

void Test6()
{
	Test("Test6", nullptr, 0, "Don't print anything.");
}

void Test7()
{
	int numbers[] = { 1,12,37,4,56,372,3 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), "112337237456");
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