#include "pch.h"
#include <iostream>

struct BinaryTreeNode
{
	int					m_nValue;
	BinaryTreeNode*		m_pLeft;
	BinaryTreeNode*		m_pRight;
};

BinaryTreeNode* ConstructCore(int* preorder, int preStart, int preEnd, int* inorder, int inStart, int inEnd)
{
	if (preStart > preEnd)
	{
		return nullptr;
	}

	int rootValue = preorder[preStart];
	int rootIndex = inStart;

	while (rootIndex <= inEnd && inorder[rootIndex] != rootValue)
	{
		rootIndex++;
	}

	if (rootIndex > inEnd)
	{
		throw std::exception("Invalid input.");
	}

	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;

	root->m_pLeft = ConstructCore(preorder, preStart + 1, preStart + rootIndex - inStart, inorder, inStart, rootIndex - 1);
	root->m_pRight = ConstructCore(preorder, preStart + rootIndex - inStart + 1, preEnd, inorder, rootIndex + 1, inEnd);

	return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int len)
{
	if (preorder == nullptr || inorder == nullptr || len <= 0)
	{
		return nullptr;
	}

	return ConstructCore(preorder, 0, len - 1, inorder, 0, len - 1);
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

// ====================测试代码====================
void Test(const char* testName, int* preorder, int* inorder, int length)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The preorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", preorder[i]);
	printf("\n");

	printf("The inorder sequence is: ");
	for (int i = 0; i < length; ++i)
		printf("%d ", inorder[i]);
	printf("\n");

	try
	{
		BinaryTreeNode* root = Construct(preorder, inorder, length);
		PrintTree(root);

		DestroyTree(root);
	}
	catch (std::exception& exception)
	{
		printf("Invalid Input.\n");
	}
}
// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
	const int length = 8;
	int preorder[length] = { 1, 2, 4, 7, 3, 5, 6, 8 };
	int inorder[length] = { 4, 7, 2, 1, 5, 3, 8, 6 };

	Test("Test1", preorder, inorder, length);
}
// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 5, 4, 3, 2, 1 };

	Test("Test2", preorder, inorder, length);
}
// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
	const int length = 5;
	int preorder[length] = { 1, 2, 3, 4, 5 };
	int inorder[length] = { 1, 2, 3, 4, 5 };

	Test("Test3", preorder, inorder, length);
}
// 树中只有一个结点
void Test4()
{
	const int length = 1;
	int preorder[length] = { 1 };
	int inorder[length] = { 1 };

	Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 5, 1, 6, 3, 7 };

	Test("Test5", preorder, inorder, length);
}
// 输入空指针
void Test6()
{
	Test("Test6", nullptr, nullptr, 0);
}
// 输入的两个序列不匹配
void Test7()
{
	const int length = 7;
	int preorder[length] = { 1, 2, 4, 5, 3, 6, 7 };
	int inorder[length] = { 4, 2, 8, 1, 6, 3, 7 };

	Test("Test7: for unmatched input", preorder, inorder, length);
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

	return 0;
}