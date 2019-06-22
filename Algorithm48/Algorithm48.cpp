#include "pch.h"
#include <iostream>
#include <string>

int longestSubstringWithoutDuplication_1(const std::string& input)
{
	int len = input.length();

	if (len == 0)
	{
		return 0;
	}

	int maxSubLen = 0;
	int* maxSubLenArray = new int[len];
	int* preIndexArray = new int[26];
	for (int i = 0; i < 26; i++)
	{
		preIndexArray[i] = -1;
	}

	for (int i = 0; i < len; i++)
	{
		int preIndex = preIndexArray[input[i] - 'a'];
		preIndexArray[input[i] - 'a'] = i;

		if (i == 0)
		{
			maxSubLenArray[i] = 1;
		}
		else
		{
			if (preIndex < 0)
			{
				maxSubLenArray[i] = maxSubLenArray[i - 1] + 1;
			}
			else
			{
				int posDelay = i - preIndex;
				if (posDelay <= maxSubLenArray[i - 1])
				{
					maxSubLenArray[i] = posDelay;
				}
				else
				{
					maxSubLenArray[i] = maxSubLenArray[i - 1] + 1;
				}
			}
		}

		if (maxSubLenArray[i] > maxSubLen)
		{
			maxSubLen = maxSubLenArray[i];
		}
	}

	delete[] maxSubLenArray;
	delete[] preIndexArray;

	return maxSubLen;
}

int longestSubstringWithoutDuplication_2(const std::string& input)
{
	return 0;
}

// ====================测试代码====================
void testSolution1(const std::string& input, int expected)
{
	int output = longestSubstringWithoutDuplication_1(input);
	if (output == expected)
		std::cout << "Solution 1 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 1 FAILED, with input: " << input << std::endl;
}

void testSolution2(const std::string& input, int expected)
{
	/*int output = longestSubstringWithoutDuplication_2(input);
	if (output == expected)
		std::cout << "Solution 2 passed, with input: " << input << std::endl;
	else
		std::cout << "Solution 2 FAILED, with input: " << input << std::endl;*/
}

void test(const std::string& input, int expected)
{
	testSolution1(input, expected);
	testSolution2(input, expected);
}

void test1()
{
	const std::string input = "abcacfrar";
	int expected = 4;
	test(input, expected);
}

void test2()
{
	const std::string input = "acfrarabc";
	int expected = 4;
	test(input, expected);
}

void test3()
{
	const std::string input = "arabcacfr";
	int expected = 4;
	test(input, expected);
}

void test4()
{
	const std::string input = "aaaa";
	int expected = 1;
	test(input, expected);
}

void test5()
{
	const std::string input = "abcdefg";
	int expected = 7;
	test(input, expected);
}

void test6()
{
	const std::string input = "aaabbbccc";
	int expected = 2;
	test(input, expected);
}

void test7()
{
	const std::string input = "abcdcba";
	int expected = 4;
	test(input, expected);
}

void test8()
{
	const std::string input = "abcdaef";
	int expected = 6;
	test(input, expected);
}

void test9()
{
	const std::string input = "a";
	int expected = 1;
	test(input, expected);
}

void test10()
{
	const std::string input = "";
	int expected = 0;
	test(input, expected);
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();

	return 0;
}