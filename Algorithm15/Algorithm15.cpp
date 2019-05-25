#include "pch.h"
#include <iostream>

//常规解法
int NumberOf1_Solution1(int number)
{
	int count = 0;
	unsigned int flag = 1;

	//利用位数超出自动置为0，跳出循环
	while (flag)
	{
		if (flag&number)
		{
			count++;
		}
		flag = flag << 1;
	}

	return count;
}

//巧妙解法
int NumberOf1_Solution2(int number)
{
	int count = 0;

	while (number)
	{
		count++;
		number = (number - 1)&number;
	}

	return count;
}

// ====================测试代码====================
void Test(int number, unsigned int expected)
{
	int actual = NumberOf1_Solution1(number);
	if (actual == expected)
		printf("Solution1: Test for %p passed.\n", number);
	else
		printf("Solution1: Test for %p failed.\n", number);

	actual = NumberOf1_Solution2(number);
	if (actual == expected)
		printf("Solution2: Test for %p passed.\n", number);
	else
		printf("Solution2: Test for %p failed.\n", number);

	printf("\n");
}

int main()
{
	// 输入0，期待的输出是0
	Test(0, 0);

	// 输入1，期待的输出是1
	Test(1, 1);

	// 输入10，期待的输出是2
	Test(10, 2);

	// 输入0x7FFFFFFF，期待的输出是31
	Test(0x7FFFFFFF, 31);

	// 输入0xFFFFFFFF（负数），期待的输出是32
	Test(0xFFFFFFFF, 32);

	// 输入0x80000000（负数），期待的输出是1
	Test(0x80000000, 1);

	return 0;
}