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

void PrintTree(BinaryTreeNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	std::cout << "The root value is: " << pHead->m_nValue << std::endl;
	if (pHead->m_pLeft != nullptr)
	{
		std::cout << "value of root's left child is: " << pHead->m_pLeft->m_nValue << std::endl;
	}
	else
	{
		std::cout << "left child is nullptr" << std::endl;
	}
	if (pHead->m_pRight != nullptr)
	{
		std::cout << "value of root's right child is: " << pHead->m_pRight->m_nValue << std::endl;
	}
	else
	{
		std::cout << "right child is nullptr" << std::endl;
	}

	PrintTree(pHead->m_pLeft);
	PrintTree(pHead->m_pRight);
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

//递归实现
void PrintFromTopToBottomCore(std::queue<BinaryTreeNode*>& m_queue)
{
	if (m_queue.empty())
	{
		return;
	}

	std::cout << m_queue.front()->m_nValue << ",";

	BinaryTreeNode* pLeft = m_queue.front()->m_pLeft;
	BinaryTreeNode* pRight = m_queue.front()->m_pRight;

	if (pLeft != nullptr)
	{
		m_queue.push(pLeft);
	}
	if (pRight != nullptr)
	{
		m_queue.push(pRight);
	}

	m_queue.pop();
	PrintFromTopToBottomCore(m_queue);
}

void PrintFromTopToBottom(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
	{
		return;
	}

	std::queue<BinaryTreeNode*> m_queue;
	m_queue.push(pRoot);

	//PrintFromTopToBottomCore(m_queue); 递归实现
	while (!m_queue.empty())
	{
		std::cout << m_queue.front()->m_nValue << ",";

		BinaryTreeNode* pLeft = m_queue.front()->m_pLeft;
		BinaryTreeNode* pRight = m_queue.front()->m_pRight;

		if (pLeft != nullptr)
		{
			m_queue.push(pLeft);
		}
		if (pRight != nullptr)
		{
			m_queue.push(pRight);
		}
		m_queue.pop();
	}
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	PrintTree(pRoot);

	printf("The nodes from top to bottom, from left to right are: \n");
	PrintFromTopToBottom(pRoot);

	printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode14 = CreateBinaryTreeNode(14);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode12 = CreateBinaryTreeNode(12);
	BinaryTreeNode* pNode16 = CreateBinaryTreeNode(16);

	ConnectTreeNodes(pNode10, pNode6, pNode14);
	ConnectTreeNodes(pNode6, pNode4, pNode8);
	ConnectTreeNodes(pNode14, pNode12, pNode16);

	Test("Test1", pNode10);

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
void Test2()
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

	Test("Test2", pNode5);

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
void Test3()
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

	Test("Test3", pNode1);

	DestroyTree(pNode1);
}

// 树中只有1个结点
void Test4()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(1);
	Test("Test4", pNode1);

	DestroyTree(pNode1);
}

// 树中没有结点
void Test5()
{
	Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}