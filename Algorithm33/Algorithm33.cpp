#include "pch.h"
#include <iostream>

bool VerifySquenceOfBSTCore(int* subSequence, int start, int end)
{
	if (start >= end)
	{
		return true;
	}

	int rootValue = subSequence[end];

	int mid = end - 1;
	while (mid >= start)
	{
		if (subSequence[mid] < rootValue)
		{
			break;
		}

		mid--;
	}

	for (int i = start; i <= mid; i++)
	{
		if (subSequence[i] > rootValue)
		{
			return false;
		}
	}

	return VerifySquenceOfBSTCore(subSequence, start, mid) && VerifySquenceOfBSTCore(subSequence, mid + 1, end - 1);
}

bool VerifySquenceOfBST(int* sequence, int length)
{
	if (sequence == nullptr || length < 1)
	{
		return false;
	}

	return VerifySquenceOfBSTCore(sequence, 0, length - 1);
}

// ====================测试代码====================
void Test(const char* testName, int sequence[], int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (VerifySquenceOfBST(sequence, length) == expected)
		printf("passed.\n");
	else
		printf("failed.\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
	int data[] = { 4, 8, 6, 12, 16, 14, 10 };
	Test("Test1", data, sizeof(data) / sizeof(int), true);
}

//           5
//          / \
//         4   7
//            /
//           6
void Test2()
{
	int data[] = { 4, 6, 7, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), true);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
void Test3()
{
	int data[] = { 1, 2, 3, 4, 5 };
	Test("Test3", data, sizeof(data) / sizeof(int), true);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
void Test4()
{
	int data[] = { 5, 4, 3, 2, 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), true);
}

// 树中只有1个结点
void Test5()
{
	int data[] = { 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), true);
}

void Test6()
{
	int data[] = { 7, 4, 6, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), false);
}

void Test7()
{
	int data[] = { 4, 6, 12, 8, 16, 14, 10 };
	Test("Test7", data, sizeof(data) / sizeof(int), false);
}

void Test8()
{
	Test("Test8", nullptr, 0, false);
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
	Test8();

	return 0;
}