#include "pch.h"
#include <iostream>
#include <deque>

struct BinaryTreeNode
{
	int					m_nValue;
	BinaryTreeNode*		m_pLeft;
	BinaryTreeNode*		m_pRight;
};

BinaryTreeNode* CreateBinaryTreeNode(int value)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_nValue = value;
	pNode->m_pLeft = nullptr;
	pNode->m_pRight = nullptr;

	return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pNode1, BinaryTreeNode* pNode2, BinaryTreeNode* pNode3)
{
	if (pNode1 == nullptr)
	{
		return;
	}

	pNode1->m_pLeft = pNode2;
	pNode1->m_pRight = pNode3;
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

void FindPathCore(int expectedSum, std::deque<BinaryTreeNode*>& m_deque)
{
	BinaryTreeNode* pNode = m_deque.back();

	if (pNode->m_pLeft==nullptr && pNode->m_pRight==nullptr && expectedSum == pNode->m_nValue)
	{
		for (auto node : m_deque)
		{
			std::cout << node->m_nValue << "、";
		}
		std::cout << "\n";

		m_deque.pop_back();
		return;
	}

	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr && expectedSum != pNode->m_nValue)
	{
		m_deque.pop_back();
		return;
	}

	if (pNode->m_nValue <= expectedSum)
	{
		expectedSum -= pNode->m_nValue;

		BinaryTreeNode* pLeft = pNode->m_pLeft;
		BinaryTreeNode* pRight = pNode->m_pRight;

		if (pLeft != nullptr)
		{
			m_deque.push_back(pLeft);
			FindPathCore(expectedSum, m_deque);
		}
		if (pRight != nullptr)
		{
			m_deque.push_back(pRight);
			FindPathCore(expectedSum, m_deque);
		}
	}

	m_deque.pop_back();
	return;
}

void FindPath(BinaryTreeNode* pRoot, int expectedSum)
{
	if (pRoot == nullptr)
	{
		return;
	}

	std::deque<BinaryTreeNode*> m_deque;
	m_deque.push_back(pRoot);

	FindPathCore(expectedSum, m_deque);
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	FindPath(pRoot, expectedSum);

	printf("\n");
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 有两条路径上的结点和为22
void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("Two paths should be found in Test1.\n");
	Test("Test1", pNode10, 22);

	DestroyTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 没有路径上的结点和为15
void Test2()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNode10, pNode5, pNode12);
	ConnectTreeNodes(pNode5, pNode4, pNode7);

	printf("No paths should be found in Test2.\n");
	Test("Test2", pNode10, 15);

	DestroyTree(pNode10);
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
// 有一条路径上面的结点和为15
void Test3()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);
	ConnectTreeNodes(pNode2, pNode1, nullptr);

	printf("One path should be found in Test3.\n");
	Test("Test3", pNode5, 15);

	DestroyTree(pNode5);
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
// 没有路径上面的结点和为16
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode5);

	printf("No paths should be found in Test4.\n");
	Test("Test4", pNode1, 16);

	DestroyTree(pNode1);
}

// 树中只有1个结点
void Test5()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);

	printf("One path should be found in Test5.\n");
	Test("Test5", pNode1, 1);

	DestroyTree(pNode1);
}

// 树中没有结点
void Test6()
{
	printf("No paths should be found in Test6.\n");
	Test("Test6", nullptr, 0);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}