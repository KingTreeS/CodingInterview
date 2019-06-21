#include "pch.h"
#include <iostream>
using namespace std;

int PowOfBase(int n)
{
	if (n < 0)
	{
		return 0;
	}

	int count = 1;
	while (n)
	{
		count *= 10;
		n--;
	}
	return count;
}

void GetDigit(int& digit, int& index)
{
	if (index <= digit * 9 * PowOfBase(digit - 1))
	{
		return;
	}

	index -= digit * 9 * PowOfBase(digit - 1);
	digit++;
}

int GetNum(int digit, int index)
{
	int pos1 = index / digit;
	int pos2 = index % digit;

	int num = PowOfBase(digit - 1);
	num = num + pos1 - 1;
	if (pos2 != 0)
	{
		num++;
	}

	char numStr[50];
	sprintf_s(numStr, "%d", num);

	if (pos2 == 0)
	{
		return numStr[digit - 1] - '0';
	}
	return  numStr[pos2 - 1] - '0';
}

int digitAtIndex(int index)
{
	if (index <= 9)
	{
		return index;
	}

	int digit = 2;
	index -= 9;
	GetDigit(digit, index);

	return GetNum(digit, index);
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if (digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int main()
{
	test("Test1", 0, 0);
	test("Test2", 1, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // 数字99的最后一位，9
	test("Test6", 190, 1);  // 数字100的第一位，1
	test("Test7", 1000, 3); // 数字370的第一位，3
	test("Test8", 1001, 7); // 数字370的第二位，7
	test("Test9", 1002, 0); // 数字370的第三位，0
	return 0;
}