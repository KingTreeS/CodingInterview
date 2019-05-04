#include "pch.h"
#include <iostream>
#include <stack>

////链表的添加删除操作
//struct ListNode
//{
//	int m_pValue;
//	ListNode* m_pNext;
//};
//
//void addNode(ListNode** pHead, int value)
//{
//	ListNode* pNew = new ListNode();
//	pNew->m_pValue = value;
//	pNew->m_pNext = nullptr;
//
//	if (*pHead == nullptr)
//	{
//		*pHead = pNew;
//	}
//	else
//	{
//		ListNode* pNode = *pHead;
//		while (pNode->m_pNext != nullptr)
//		{
//			pNode = pNode->m_pNext;
//		}
//		pNode->m_pNext = pNew;
//	}
//}
//
//void removeNode(ListNode** pHead, int value)
//{
//	if (pHead == nullptr || *pHead == nullptr)
//	{
//		return;
//	}
//
//	ListNode* pDeleteNode = nullptr;
//
//	if ((*pHead)->m_pValue == value)
//	{
//		pDeleteNode = *pHead;
//		*pHead = (*pHead)->m_pNext;
//	}
//	else
//	{
//		ListNode* pNode = *pHead;
//		while (pNode->m_pNext != nullptr && pNode->m_pNext->m_pValue != value)
//		{
//			pNode = pNode->m_pNext;
//		}
//		if (pNode->m_pNext != nullptr && pNode->m_pNext->m_pValue == value)
//		{
//			pDeleteNode = pNode->m_pNext;
//			pNode->m_pNext = pNode->m_pNext->m_pNext;
//		}
//	}
//
//	if (pDeleteNode != nullptr)
//	{
//		delete pDeleteNode;
//		pDeleteNode = nullptr;
//	}
//}

//思路：单向链表不能修改链表结构，只能从头到尾查找，输出是后进先出操作，使用栈实现（递归的本质）
struct ListNode
{
	int m_nKey;
	ListNode* m_pNext;
};

ListNode* CreateListNode(int value)
{
	ListNode* pNew = new ListNode();
	pNew->m_nKey = value;
	pNew->m_pNext = nullptr;

	return pNew;
}

void ConnectListNodes(ListNode* first, ListNode* second)
{
	if (first == nullptr || second == nullptr)
	{
		return;
	}
	first->m_pNext = second;
}

void DestroyList(ListNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	ListNode* pDeleteNode = nullptr;
	if (pHead->m_pNext==nullptr)
	{
		pDeleteNode = pHead;
	}
	else
	{
		while (pHead->m_pNext != nullptr)
		{
			pDeleteNode = pHead;
			pHead = pHead->m_pNext;

			delete pDeleteNode;
			pDeleteNode = nullptr;
		}
	}

	delete pDeleteNode;
	pDeleteNode = nullptr;
}

void PrintListReversingly_Iteratively(ListNode* pHead)
{
	if (pHead==nullptr)
	{
		return;
	}

	std::stack<ListNode*> stackNode;
	while (pHead != nullptr)
	{
		stackNode.push(pHead);
		pHead = pHead->m_pNext;
	}

	while (!stackNode.empty())
	{
		std::cout << stackNode.top()->m_nKey << " ";
		stackNode.pop();
	}
}

void PrintListReversingly_Recursively(ListNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}
	PrintListReversingly_Recursively(pHead->m_pNext);
	std::cout << pHead->m_nKey << " ";
}


// ====================测试代码====================
void Test(ListNode* pHead)
{
	//PrintList(pHead);
	PrintListReversingly_Iteratively(pHead);
	printf("\n");
	PrintListReversingly_Recursively(pHead);
}

// 1->2->3->4->5
void Test1()
{
	printf("\nTest1 begins.\n");

	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	Test(pNode1);

	DestroyList(pNode1);
}

// 只有一个结点的链表: 1
void Test2()
{
	printf("\nTest2 begins.\n");

	ListNode* pNode1 = CreateListNode(1);

	Test(pNode1);

	DestroyList(pNode1);
}

// 空链表
void Test3()
{
	printf("\nTest3 begins.\n");

	Test(nullptr);
}

int main()
{
	Test1();
	Test2();
	Test3();

	return 0;
}