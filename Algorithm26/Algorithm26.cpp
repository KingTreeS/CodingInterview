#include "pch.h"
#include <iostream>

struct BinaryTreeNode
{
	double				m_dbValue;
	BinaryTreeNode*		m_pLeft;
	BinaryTreeNode*		m_pRight;
};

BinaryTreeNode* CreateBinaryTreeNode(double value)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_dbValue = value;
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

bool equalNode(BinaryTreeNode* pNode1, BinaryTreeNode* pNode2)
{
	if (pNode1 == nullptr || pNode2 == nullptr)
	{
		return false;
	}

	if ((pNode1->m_dbValue - pNode2->m_dbValue > -0.0000001) && (pNode1->m_dbValue - pNode2->m_dbValue < 0.0000001))
	{
		return true;
	}

	return false;
}

bool HasSubtreeCore(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot2 == nullptr)
	{
		return true;
	}

	if (pRoot1 == nullptr && pRoot2 != nullptr)
	{
		return false;
	}

	if (!equalNode(pRoot1, pRoot2))
	{
		return false;
	}

	bool result = (HasSubtreeCore(pRoot1->m_pLeft, pRoot2->m_pLeft) && HasSubtreeCore(pRoot1->m_pRight, pRoot2->m_pRight));
	if (result)
	{
		return true;
	}

	return HasSubtreeCore(pRoot1->m_pLeft, pRoot2) || HasSubtreeCore(pRoot1->m_pRight, pRoot2);
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1==nullptr || pRoot2==nullptr)
	{
		return false;
	}

	return HasSubtreeCore(pRoot1, pRoot2);
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2, bool expected)
{
	if (HasSubtree(pRoot1, pRoot2) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s failed.\n", testName);
}

// 树中结点含有分叉，树B是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
void Test1()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test1", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点含有分叉，树B不是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
void Test2()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA6 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNodeA7 = CreateBinaryTreeNode(7);

	ConnectTreeNodes(pNodeA1, pNodeA2, pNodeA3);
	ConnectTreeNodes(pNodeA2, pNodeA4, pNodeA5);
	ConnectTreeNodes(pNodeA5, pNodeA6, pNodeA7);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, pNodeB3);

	Test("Test2", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树B是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    2
//         /      
//        2        
//       /
//      5
void Test3()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test3", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有左子结点，树B不是树A的子结构
//                8                  8
//              /                   / 
//             8                   9   
//           /                    /
//          9                    3
//         /      
//        2        
//       /
//      5
void Test4()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, pNodeA2, nullptr);
	ConnectTreeNodes(pNodeA2, pNodeA3, nullptr);
	ConnectTreeNodes(pNodeA3, pNodeA4, nullptr);
	ConnectTreeNodes(pNodeA4, pNodeA5, nullptr);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);

	ConnectTreeNodes(pNodeB1, pNodeB2, nullptr);
	ConnectTreeNodes(pNodeB2, pNodeB3, nullptr);

	Test("Test4", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树中结点只有右子结点，树B是树A的子结构
//       8                   8
//        \                   \ 
//         8                   9   
//          \                   \
//           9                   2
//            \      
//             2        
//              \
//               5
void Test5()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, nullptr, pNodeB3);

	Test("Test5", pNodeA1, pNodeB1, true);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树A中结点只有右子结点，树B不是树A的子结构
//       8                   8
//        \                   \ 
//         8                   9   
//          \                 / \
//           9               3   2
//            \      
//             2        
//              \
//               5
void Test6()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);
	BinaryTreeNode* pNodeA5 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, nullptr, pNodeA3);
	ConnectTreeNodes(pNodeA3, nullptr, pNodeA4);
	ConnectTreeNodes(pNodeA4, nullptr, pNodeA5);

	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test6", pNodeA1, pNodeB1, false);

	DestroyTree(pNodeA1);
	DestroyTree(pNodeB1);
}

// 树A为空树
void Test7()
{
	BinaryTreeNode* pNodeB1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeB2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeB3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeB4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeB1, nullptr, pNodeB2);
	ConnectTreeNodes(pNodeB2, pNodeB3, pNodeB4);

	Test("Test7", nullptr, pNodeB1, false);

	DestroyTree(pNodeB1);
}

// 树B为空树
void Test8()
{
	BinaryTreeNode* pNodeA1 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNodeA2 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNodeA3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNodeA4 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNodeA1, nullptr, pNodeA2);
	ConnectTreeNodes(pNodeA2, pNodeA3, pNodeA4);

	Test("Test8", pNodeA1, nullptr, false);

	DestroyTree(pNodeA1);
}

// 树A和树B都为空
void Test9()
{
	Test("Test9", nullptr, nullptr, false);
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
	Test9();

	return 0;
}