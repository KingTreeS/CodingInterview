#include "pch.h"
#include <iostream>
#include <stack>

bool IsPopOrderCore(const int* pPush, const int* pPop, int pushFlag, int popFlag, int length, std::stack<int>& stack)
{
	if (pushFlag == length)
	{
		for (int i = popFlag; i < length; i++)
		{
			if (stack.top() != pPop[i])
			{
				return false;
			}
			stack.pop();
		}
		return true;
	}

	if (!stack.empty())
	{
		if (stack.top() == pPop[popFlag])
		{
			stack.pop();
			return IsPopOrderCore(pPush, pPop, pushFlag, popFlag + 1, length, stack);
		}
	}

	while (pPush[pushFlag] != pPop[popFlag] && pushFlag < length)
	{
		stack.push(pPush[pushFlag]);
		pushFlag++;
	}

	if (pushFlag == length)
	{
		return false;
	}

	return IsPopOrderCore(pPush, pPop, pushFlag+1, popFlag + 1, length, stack);
}

bool IsPopOrder(const int* pPush, const int* pPop, int length)
{
	if (pPush == nullptr || pPop == nullptr || length < 1)
	{
		return false;
	}

	std::stack<int> m_stack;

	return IsPopOrderCore(pPush, pPop, 0, 0, length, m_stack);
}

// ====================测试代码====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (IsPopOrder(pPush, pPop, nLength) == expected)
		printf("Passed.\n");
	else
		printf("failed.\n");
}

void Test1()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 4, 5, 3, 2, 1 };

	Test("Test1", push, pop, nLength, true);
}

void Test2()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 3, 5, 4, 2, 1 };

	Test("Test2", push, pop, nLength, true);
}

void Test3()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 4, 3, 5, 1, 2 };

	Test("Test3", push, pop, nLength, false);
}

void Test4()
{
	const int nLength = 5;
	int push[nLength] = { 1, 2, 3, 4, 5 };
	int pop[nLength] = { 3, 5, 4, 1, 2 };

	Test("Test4", push, pop, nLength, false);
}

// push和pop序列只有一个数字
void Test5()
{
	const int nLength = 1;
	int push[nLength] = { 1 };
	int pop[nLength] = { 2 };

	Test("Test5", push, pop, nLength, false);
}

void Test6()
{
	const int nLength = 1;
	int push[nLength] = { 1 };
	int pop[nLength] = { 1 };

	Test("Test6", push, pop, nLength, true);
}

void Test7()
{
	Test("Test7", nullptr, nullptr, 0, false);
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