#include "pch.h"
#include <iostream>
#include <vector>

//递归实现
int Fibonacci_Solution1(int n)
{
	if (n == 0)
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	return Fibonacci_Solution1(n - 1) + Fibonacci_Solution1(n - 2);
}
//循环实现
int Fibonacci_Solution2(int n)
{
	int result[2] = { 0, 1 };

	if (n == 0)
	{
		return result[0];
	}

	if (n == 1)
	{
		return result[1];
	}

	while (n-- > 2)
	{
		int tmp = result[0];
		result[0] = result[1];
		result[1] += tmp;
	}

	return result[0] + result[1];
}
//矩阵相乘，递归
int Fibonacci_Solution3(int n)
{
	return 0;
}

//青蛙跳（一种就是斐波那契的转化，一种是2^(n-1)）
long long FrogJump2(int n)
{
	std::vector<long long> result;
	result.push_back(1);

	if (n == 1)
	{
		return 1;
	}

	while (n-- > 1)
	{
		long long sum = 1;
		for (auto num : result)
		{
			sum += num;
		}
		result.push_back(sum);
	}

	return result.back();
}

//矩形面积覆盖（斐波那契数列形式）

// ====================测试代码====================
void Test(int n, int expected)
{
	if (Fibonacci_Solution1(n) == expected)
		printf("Test for %d in solution1 passed.\n", n);
	else
		printf("Test for %d in solution1 failed.\n", n);

	if (Fibonacci_Solution2(n) == expected)
		printf("Test for %d in solution2 passed.\n", n);
	else
		printf("Test for %d in solution2 failed.\n", n);

	/*if (Fibonacci_Solution3(n) == expected)
		printf("Test for %d in solution3 passed.\n", n);
	else
		printf("Test for %d in solution3 failed.\n", n);*/
}

int main()
{
	Test(0, 0);
	Test(1, 1);
	Test(2, 1);
	Test(3, 2);
	Test(4, 3);
	Test(5, 5);
	Test(6, 8);
	Test(7, 13);
	Test(8, 21);
	Test(9, 34);
	Test(10, 55);

	//Test(40, 102334155);

	std::cout << "青蛙跳：" << std::endl;
	std::cout << "Test: 5 " << FrogJump2(5) << std::endl;
	std::cout << "Test: 10 " << FrogJump2(10) << std::endl;
	std::cout << "Test: 22 " << FrogJump2(22) << std::endl;
	std::cout << "Test: 17 " << FrogJump2(17) << std::endl;
	std::cout << "Test: 23 " << FrogJump2(23) << std::endl;
	std::cout << "Test: 44 " << FrogJump2(44) << std::endl;

	return 0;
}