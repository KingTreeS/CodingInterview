#include "pch.h"
#include <iostream>
#include <queue>

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

void Print(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
	{
		return; 
	}

	std::queue<BinaryTreeNode*> m_queue;
	m_queue.push(pRoot);

	int levelNodes = 1;
	int nextLevelNodes = 0;

	while (!m_queue.empty())
	{
		BinaryTreeNode* pLeft = m_queue.front()->m_pLeft;
		BinaryTreeNode* pRight = m_queue.front()->m_pRight;

		std::cout << m_queue.front()->m_nValue << " ";
		m_queue.pop();
		levelNodes--;

		if (pLeft != nullptr)
		{
			nextLevelNodes++;
			m_queue.push(pLeft);
		}
		if (pRight != nullptr)
		{
			nextLevelNodes++;
			m_queue.push(pRight);
		}

		if (levelNodes == 0)
		{
			std::cout << "\n";
			levelNodes = nextLevelNodes;
			nextLevelNodes = 0;
		}
	}
}

// ====================测试代码====================
//            8
//        6      10
//       5 7    9  11
void Test1()
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

	printf("====Test1 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("8 \n");
	printf("6 10 \n");
	printf("5 7 9 11 \n\n");

	printf("Actual Result is: \n");
	Print(pNode8);
	printf("\n");

	DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);

	printf("====Test2 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n");
	printf("4 \n");
	printf("3 \n");
	printf("2 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode2);

	printf("====Test3 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n");
	printf("4 \n");
	printf("3 \n");
	printf("2 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

void Test4()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	printf("====Test4 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

void Test5()
{
	printf("====Test5 Begins: ====\n");
	printf("Expected Result is:\n");

	printf("Actual Result is: \n");
	Print(nullptr);
	printf("\n");
}

//        100
//        /
//       50   
//         \
//         150
void Test6()
{
	BinaryTreeNode* pNode100 = CreateBinaryTreeNode(100);
	BinaryTreeNode* pNode50 = CreateBinaryTreeNode(50);
	BinaryTreeNode* pNode150 = CreateBinaryTreeNode(150);

	ConnectTreeNodes(pNode100, pNode50, nullptr);
	ConnectTreeNodes(pNode50, nullptr, pNode150);

	printf("====Test6 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("100 \n");
	printf("50 \n");
	printf("150 \n\n");

	printf("Actual Result is: \n");
	Print(pNode100);
	printf("\n");
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