#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int GetTranslationCountCore(string& strNum)
{
	int len = strNum.length();
	int* countArray = new int[len];

	int curCount = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (i == len - 1)
		{
			curCount = 1;
		}
		else
		{
			curCount = countArray[i + 1];
		}

		if (i < len - 1)
		{
			int num1 = strNum[i] - '0';
			int num2 = strNum[i + 1] - '0';
			int num = num1 * 10 + num2;

			if (num >= 10 && num <= 25)
			{
				if (i < len - 2)
				{
					curCount += countArray[i + 2];
				}
				else
				{
					curCount++;
				}
			}
		}

		countArray[i] = curCount;
	}

	int count = countArray[0];
	delete[] countArray;

	return count;
}

int GetTranslationCount(int number)
{
	if (number < 0)
	{
		return 0;
	}

	string strNum = to_string(number);
	return GetTranslationCountCore(strNum);
}

// ====================测试代码====================
void Test(const char* testName, int number, int expected)
{
	if (GetTranslationCount(number) == expected)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}

void Test1()
{
	int number = 0;
	int expected = 1;
	Test("Test1", number, expected);
}

void Test2()
{
	int number = 10;
	int expected = 2;
	Test("Test2", number, expected);
}

void Test3()
{
	int number = 125;
	int expected = 3;
	Test("Test3", number, expected);
}

void Test4()
{
	int number = 126;
	int expected = 2;
	Test("Test4", number, expected);
}

void Test5()
{
	int number = 426;
	int expected = 1;
	Test("Test5", number, expected);
}

void Test6()
{
	int number = 100;
	int expected = 2;
	Test("Test6", number, expected);
}

void Test7()
{
	int number = 101;
	int expected = 2;
	Test("Test7", number, expected);
}

void Test8()
{
	int number = 12258;
	int expected = 5;
	Test("Test8", number, expected);
}

void Test9()
{
	int number = -100;
	int expected = 0;
	Test("Test9", number, expected);
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
	Test8();
	Test9();

	return 0;
}