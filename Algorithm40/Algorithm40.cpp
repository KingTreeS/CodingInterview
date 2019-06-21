#include "pch.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void Swap(int* num1, int* num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;

	return;
}

void GetLeastNumbers_Solution1Core(int* data, int start, int end, int k)
{
	int randFlag = start + rand() % (end - start + 1);
	Swap(&data[randFlag], &data[start]);

	int flag = start;
	int flagNum = data[start];
	int ptr1 = start;
	int ptr2 = end;

	while (ptr1<ptr2)
	{
		while (ptr2 > flag && data[ptr2] >= flagNum)
		{
			ptr2--;
		}

		if (ptr2 > flag)
		{
			Swap(&data[flag], &data[ptr2]);
			flag = ptr2;
		}

		while (ptr1 < flag && data[ptr1] <= flagNum)
		{
			ptr1++;
		}

		if (ptr1 < flag)
		{
			Swap(&data[flag], &data[ptr1]);
			flag = ptr1;
		}
	}

	if (flag == k)
	{
		return;
	}
	if (flag < k)
	{
		return GetLeastNumbers_Solution1Core(data, flag+1, end, k);
	}
	if (flag > k)
	{
		return GetLeastNumbers_Solution1Core(data, start, flag-1, k);
	}
}

void GetLeastNumbers_Solution1(int* data, int n, int* output, int k)
{
	if (data==nullptr || n <1 || k>n || k<1)
	{
		return;
	}

	GetLeastNumbers_Solution1Core(data, 0, n-1,k-1);
	for (int i = 0; i < k; i++)
	{
		output[i] = data[i];
	}
}

typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution2(vector<int>& vectorData, intSet& leastNumbers, int k)
{
	if (k<1 || k>vectorData.size())
	{
		return;
	}

	leastNumbers.clear();

	vector<int>::const_iterator item = vectorData.cbegin();
	while (item != vectorData.cend())
	{
		if (leastNumbers.size() < k)
		{
			leastNumbers.insert(*item);
		}
		else
		{
			setIterator itemGreater = leastNumbers.begin();
			if (*item < *itemGreater)
			{
				leastNumbers.erase(itemGreater);
				leastNumbers.insert(*item);
			}
		}
		item++;
	}
}

// ====================测试代码====================
void Test(const char* testName, int* data, int n, int* expectedResult, int k)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	vector<int> vectorData;
	for (int i = 0; i < n; ++i)
		vectorData.push_back(data[i]);

	if (expectedResult == nullptr)
		printf("The input is invalid, we don't expect any result.\n");
	else
	{
		printf("Expected result: \n");
		for (int i = 0; i < k; ++i)
			printf("%d\t", expectedResult[i]);
		printf("\n");
	}

	printf("Result for solution1:\n");
	int* output = new int[k];
	GetLeastNumbers_Solution1(data, n, output, k);
	if (expectedResult != nullptr)
	{
		for (int i = 0; i < k; ++i)
			printf("%d\t", output[i]);
		printf("\n");
	}

	delete[] output;

	printf("Result for solution2:\n");
	intSet leastNumbers;
	GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
	printf("The actual output numbers are:\n");
	for (setIterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
		printf("%d\t", *iter);
	printf("\n\n");
}

// k小于数组的长度
void Test1()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4 };
	Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 2, 8 };
	int expected[] = { 1, 2 };
	Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
	int* expected = nullptr;
	Test("Test7", nullptr, 0, expected, 0);
}

int main(int argc, char* argv[])
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