#include "pch.h"
#include <iostream>
#include <map>
#include "Sort.h"

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
	bool validInput = hashFind(numbers, lengthNumbers, &duplication);

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

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	return 0;
}