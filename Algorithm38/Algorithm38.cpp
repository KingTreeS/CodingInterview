#include "pch.h"
#include <iostream>

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

// ====================测试代码====================
void Test(char* pStr)
{
	if (pStr == nullptr)
		printf("Test for nullptr begins:\n");
	else
		printf("Test for %s begins:\n", pStr);

	Permutation(pStr);

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