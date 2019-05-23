#include "pch.h"
#include <iostream>

struct BinaryTreeNode
{
	int m_value;
	BinaryTreeNode* m_pHead;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

BinaryTreeNode* FindLeft(BinaryTreeNode* pHead)
{
	if (pHead == nullptr)
	{
		return nullptr;
	}

	if (pHead->m_pLeft != nullptr)
	{
		FindLeft(pHead->m_pLeft);
	}
	else
	{
		return pHead;
	}
}

BinaryTreeNode* GetNext(BinaryTreeNode* pNode)
{
	if (pNode == nullptr)
	{
		return nullptr;
	}

	if (pNode->m_pRight != nullptr)
	{
		FindLeft(pNode->m_pRight);
	}
	else
	{
		if (pNode->m_pHead == nullptr)
		{
			return nullptr;
		}

		if (pNode == pNode->m_pHead->m_pLeft)
		{
			return pNode->m_pHead;
		}
		else
		{
			while (pNode->m_pHead->m_pRight == pNode)
			{
				pNode = pNode->m_pHead;
				if (pNode->m_pHead == nullptr)
				{
					break;
				}
			}

			if (pNode->m_pHead == nullptr)
			{
				return nullptr;
			}

			return pNode->m_pHead;
		}
	}
}

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_value = value;
	pNode->m_pHead = nullptr;
	pNode->m_pLeft = nullptr;
	pNode->m_pRight = nullptr;

	return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pHead, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
	if (pHead == nullptr)
	{
		return;
	}

	pHead->m_pLeft = pLeft;
	pHead->m_pRight = pRight;

	if (pLeft != nullptr)
	{
		pLeft->m_pHead = pHead;
	}

	if (pRight != nullptr)
	{
		pRight->m_pHead = pHead;
	}
}

void DestroyTree(BinaryTreeNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	BinaryTreeNode* pLeft = pHead->m_pLeft;
	BinaryTreeNode* pRight = pHead->m_pRight;

	delete pHead;
	pHead = nullptr;

	DestroyTree(pLeft);
	DestroyTree(pRight);
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pNode, BinaryTreeNode* expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	BinaryTreeNode* pNext = GetNext(pNode);
	if (pNext == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
void Test1_7()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);

	Test("Test1", pNode8, pNode9);
	Test("Test2", pNode6, pNode7);
	Test("Test3", pNode10, pNode11);
	Test("Test4", pNode5, pNode6);
	Test("Test5", pNode7, pNode8);
	Test("Test6", pNode9, pNode10);
	Test("Test7", pNode11, nullptr);

	DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);

	Test("Test8", pNode5, nullptr);
	Test("Test9", pNode4, pNode5);
	Test("Test10", pNode3, pNode4);
	Test("Test11", pNode2, pNode3);

	DestroyTree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15()
{
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode5);

	Test("Test12", pNode5, nullptr);
	Test("Test13", pNode4, pNode5);
	Test("Test14", pNode3, pNode4);
	Test("Test15", pNode2, pNode3);

	DestroyTree(pNode2);
}

void Test16()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	Test("Test16", pNode5, nullptr);

	DestroyTree(pNode5);
}

int main()
{
	Test1_7();
	Test8_11();
	Test12_15();
	Test16();

	return 0;
}