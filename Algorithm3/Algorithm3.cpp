#include "pch.h"
#include <iostream>
#include <map>
#include "Sort.h"

//3.1
//思路一：先对数组进行排序，然后从前往后扫描，查找第一个重复的数字
//时间复杂度：O(nlogn)
enum SortInfo
{
	BUBBLE = 0,
	SELECT,
	INSERT,
	SHELL,
	MERGE,
	QUICK,
	HEAP
};

bool sortFind(SortInfo info, int num[], int len, int* duplication)
{
	if (num == nullptr || len <= 0)
	{
		return false;
	}

	for (int i = 0; i < len; i++)
	{
		if (num[i] <0 || num[i]>len - 1)
		{
			return false;
		}
	}

	Sort sort;
	switch (info)
	{
	case BUBBLE:
		sort.bubble_sort(num, len);
		break;
	case SELECT:
		sort.select_sort(num, len);
		break;
	case INSERT:
		sort.insert_sort(num, len);
		break;
	case SHELL:
		sort.shell_sort(num, len);
		break;
	case MERGE:
		int reg[7];
		sort.merge_sort(num, reg, 0, len - 1);
		break;
	case QUICK:
		sort.quick_sort(num, 0, len - 1);
		break;
	case HEAP:
		sort.heap_sort(num, len);
		break;
	default:
		break;
	}

	for (int i = 0; i < len - 1; i++)
	{
		if (num[i] == num[i + 1])
		{
			*duplication = num[i];
			return true;
		}
	}

	return false;
}

//思路二：通过哈希表的方式，时间复杂度O(n)，空间复杂度O(n)
bool hashFind(int num[], int len, int* duplication)
{
	if (num == nullptr || len <= 0)
	{
		return false;
	}

	for (int i = 0; i < len; i++)
	{
		if (num[i] > len - 1 || num[i] < 0)
		{
			return false;
		}
	}

	std::map<int, int> regMap;
	for (int i = 0; i < len; i++)
	{
		int flag = num[i];
		if (regMap.count(flag))
		{
			if (regMap[flag] != 0)
			{
				*duplication = flag;
				return true;
			}
		}
		else
		{
			regMap[flag] = 0;
			regMap[flag]++;
		}
	}

	return false;
}

//思路三：利用题目特性，时间复杂度O(n)，空间复杂度O(1)
bool swapFind(int num[], int len, int* duplication)
{
	if (num == nullptr || len <= 0)
	{
		return false;
	}

	for (int i = 0; i < len; i++)
	{
		if (num[i] < 0 || num[i] > len - 1)
		{
			return false;
		}
	}

	for (int i = 0; i < len; i++)
	{
		int flag = num[i];
		while (flag != i)
		{
			if (num[i] == num[flag])
			{
				*duplication = num[i];
				return true;
			}

			int temp = num[i];
			num[i] = num[flag];
			num[flag] = temp;

			flag = num[i];
		}
	}

	return false;
}


//3.2
//采用二分查找的思路，用时间换空间
int count(const int num[], int len, int start, int end)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (num[i] >= start && num[i] <= end)
		{
			count++;
		}
	}
	return count;
}

int getDuplication(const int num[], int len)
{
	if (num == nullptr || len <= 0)
	{
		return -1;
	}

	int start = 1;
	int end = len - 1;

	while (end >= start)
	{
		int mid = (end - start) / 2 + start;

		int countNum = count(num, len, start, mid);
		if (end == start)
		{
			if (countNum > 1)
			{
				return start;
			}
			else
			{
				break;
			}
		}

		if (countNum > (mid - start + 1))
		{
			end = mid;
		}
		else
		{
			start = mid + 1;
		}
	}

	return -1;

}


//3.1
// ====================测试代码====================
bool contains(int array[], int length, int number)
{
	for (int i = 0; i < length; ++i)
	{
		if (array[i] == number)
		{
			return true;
		}
	}
	return false;
}

void test(const char* testName, int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument)
{
	printf("%s begins: ", testName);

	int duplication;

	//bool validInput = sortFind(HEAP, numbers, lengthNumbers, &duplication);
	//bool validInput = hashFind(numbers, lengthNumbers, &duplication);
	bool validInput = swapFind(numbers, lengthNumbers, &duplication);

	if (validArgument == validInput)
	{
		if (validArgument)
		{
			if (contains(expected, expectedExpected, duplication))
			{
				printf("Passed.\n");
			}
			else
			{
				printf("FAILED.\n");
			}
		}
		else
		{
			printf("Passed.\n");
		}
	}
	else
	{
		printf("FAILED.\n");
	}
}
// 重复的数字是数组中最小的数字
void test1()
{
	int numbers[] = { 2, 1, 3, 1, 4 };
	int duplications[] = { 1 };
	test("Test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}
// 重复的数字是数组中最大的数字
void test2()
{
	int numbers[] = { 2, 4, 3, 1, 4 };
	int duplications[] = { 4 };
	test("Test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}
// 数组中存在多个重复的数字
void test3()
{
	int numbers[] = { 2, 4, 2, 1, 4 };
	int duplications[] = { 2, 4 };
	test("Test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}
// 没有重复的数字
void test4()
{
	int numbers[] = { 2, 1, 3, 0, 4 };
	int duplications[] = { -1 }; // not in use in the test function
	test("Test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}
// 没有重复的数字
void test5()
{
	int numbers[] = { 2, 1, 3, 5, 4 };
	int duplications[] = { -1 }; // not in use in the test function
	test("Test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}
// 无效的输入
void test6()
{
	int* numbers = nullptr;
	int duplications[] = { -1 }; // not in use in the test function
	test("Test6", numbers, 0, duplications, sizeof(duplications) / sizeof(int), false);
}


//3.2
// ====================测试代码====================
void noedit_test(const char* testName, int* numbers, int length, int* duplications, int dupLength)
{
	int result = getDuplication(numbers, length);
	for (int i = 0; i < dupLength; ++i)
	{
		if (result == duplications[i])
		{
			std::cout << testName << " PASSED." << std::endl;
			return;
		}
	}
	std::cout << testName << " FAILED." << std::endl;
}
// 多个重复的数字
void noedit_test1()
{
	int numbers[] = { 2, 3, 5, 4, 3, 2, 6, 7 };
	int duplications[] = { 2, 3 };
	noedit_test("test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 一个重复的数字
void noedit_test2()
{
	int numbers[] = { 3, 2, 1, 4, 4, 5, 6, 7 };
	int duplications[] = { 4 };
	noedit_test("test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 重复的数字是数组中最小的数字
void noedit_test3()
{
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 1, 8 };
	int duplications[] = { 1 };
	noedit_test("test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 重复的数字是数组中最大的数字
void noedit_test4()
{
	int numbers[] = { 1, 7, 3, 4, 5, 6, 8, 2, 8 };
	int duplications[] = { 8 };
	noedit_test("test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 数组中只有两个数字
void noedit_test5()
{
	int numbers[] = { 1, 1 };
	int duplications[] = { 1 };
	noedit_test("test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 重复的数字位于数组当中
void noedit_test6()
{
	int numbers[] = { 3, 2, 1, 3, 4, 5, 6, 7 };
	int duplications[] = { 3 };
	noedit_test("test6", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 多个重复的数字
void noedit_test7()
{
	int numbers[] = { 1, 2, 2, 6, 4, 5, 6 };
	int duplications[] = { 2, 6 };
	noedit_test("test7", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 一个数字重复三次
void noedit_test8()
{
	int numbers[] = { 1, 2, 2, 6, 4, 5, 2 };
	int duplications[] = { 2 };
	noedit_test("test8", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 没有重复的数字
void noedit_test9()
{
	int numbers[] = { 1, 2, 6, 4, 5, 3 };
	int duplications[] = { -1 };
	noedit_test("test9", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int));
}
// 无效的输入
void noedit_test10()
{
	int* numbers = nullptr;
	int duplications[] = { -1 };
	noedit_test("test10", numbers, 0, duplications, sizeof(duplications) / sizeof(int));
}

int main()
{
	//test for 3.1
	std::cout << "Test for 3.1:" << std::endl;
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	//test for 3.2
	std::cout << "Test for 3.2:" << std::endl;
	noedit_test1();
	noedit_test2();
	noedit_test3();
	noedit_test4();
	noedit_test5();
	noedit_test6();
	noedit_test7();
	noedit_test8();
	noedit_test9();
	noedit_test10();

	return 0;
}