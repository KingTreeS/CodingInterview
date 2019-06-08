#include "pch.h"
#include <iostream>
#include <vector>

//排列问题
void PermutationCore(char* pStr, char* pStart)
{
	if (*pStart == '\0')
	{
		while (*pStr != '\0')
		{
			std::cout << *pStr;
			pStr++;
		}
		std::cout << " ";
		return;
	}

	for (char* ptr = pStart; *ptr != '\0'; ptr++)
	{
		char tmp = *pStart;
		*pStart = *ptr;
		*ptr = tmp;

		PermutationCore(pStr, pStart + 1);

		tmp = *pStart;
		*pStart = *ptr;
		*ptr = tmp;
	}
}

void Permutation(char* pStr)
{
	if (pStr == nullptr)
	{
		return;
	}

	PermutationCore(pStr, pStr);
}

//组合问题
void CombineCore(char* pStr, int m, std::vector<char*>& m_vectorList)
{
	if (m == 0)
	{
		for (auto character : m_vectorList)
		{
			std::cout << *character;
		}
		std::cout << "、";
		return;
	}

	if (*pStr != '\0')
	{
		CombineCore(pStr + 1, m, m_vectorList);

		m_vectorList.push_back(pStr);
		CombineCore(pStr + 1, m-1, m_vectorList);
		m_vectorList.pop_back();
	}

	return;
}

void Combine(char* pStr)
{
	if (pStr == nullptr)
	{
		return;
	}

	char* pStart = pStr;
	int length = 0;
	while (*pStr != '\0')
	{
		length++;
		pStr++;
	}

	std::vector<char*> m_vectorList;

	for (int i = 1; i <= length; i++)
	{
		CombineCore(pStart, i, m_vectorList);
	}
}

// ====================测试代码====================
void Test(char* pStr)
{
	if (pStr == nullptr)
		printf("Test for nullptr begins:\n");
	else
		printf("Test for %s begins:\n", pStr);

	std::cout << "排列情况："<<"\n";
	Permutation(pStr);

	std::cout << "\n" << "组合情况：" << "\n";
	Combine(pStr);

	printf("\n");
}

int main()
{
	Test(nullptr);

	char string1[] = "";
	Test(string1);

	char string2[] = "a";
	Test(string2);

	char string3[] = "ab";
	Test(string3);

	char string4[] = "abc";
	Test(string4);

	return 0;
}