#include "pch.h"
#include <iostream>


void PrintNum(const char* num)
{
	while (*num == '0')
	{
		num++;
	}
	while (*num != '\0')
	{
		std::cout << *num++;
	}
	std::cout << "\n";
}

void PrintToMaxCore(char* num, int n, int index)
{
	if (index == n)
	{
		PrintNum(num);
		return;
	}

	for (int i = 0; i <= 9; i++)
	{
		num[index] = i + '0';
		PrintToMaxCore(num, n, index + 1);
	}
}

//全排列
void Print1ToMaxOfNDigits_1(int n)
{
	if (n < 1)
	{
		return;
	}

	char* num = new char[n + 1];
	num[n] = '\0';

	PrintToMaxCore(num, n, 0);
}

// ====================测试代码====================
void Test(int n)
{
	printf("Test for %d begins:\n", n);

	Print1ToMaxOfNDigits_1(n);
	//Print1ToMaxOfNDigits_2(n);

	printf("\nTest for %d ends.\n", n);
}

int main(int argc, char* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(0);
	Test(-1);

	return 0;
}