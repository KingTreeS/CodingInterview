#include "pch.h"
#include <iostream>

struct ListNode
{
	int			m_nValue;
	ListNode*	m_pNext;
};

ListNode* CreateListNode(int value)
{
	ListNode* pNode = new ListNode();
	pNode->m_nValue = value;
	pNode->m_pNext = nullptr;

	return pNode;
}

void ConnectListNodes(ListNode* pNode1, ListNode* pNode2)
{
	if (pNode1 == nullptr)
	{
		return;
	}

	pNode1->m_pNext = pNode2;
}

void DestroyList(ListNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	ListNode* pNode = pHead->m_pNext;
	DestroyList(pNode);

	delete pHead;
	pHead = nullptr;
}


void PrintList(ListNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	while (pHead != nullptr)
	{
		std::cout << pHead->m_nValue << " ";
		pHead = pHead->m_pNext;
	}

	std::cout << "\n";
}

ListNode* ReverseList(ListNode* pHead)
{
	if (pHead ==  nullptr)
	{
		return nullptr;
	}

	ListNode* ptr1 = pHead;
	ListNode* ptr2 = pHead->m_pNext;

	if (ptr2 == nullptr)
	{
		return ptr1;
	}

	ListNode* ptr3 = ptr2;
	while (ptr3 != nullptr)
	{
		ptr2 = ptr3;
		ptr3 = ptr3->m_pNext;

		if (ptr1 == pHead)
		{
			ptr1->m_pNext = nullptr;
		}
		ptr2->m_pNext = ptr1;

		ptr1 = ptr2;
	}

	return ptr2;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);

	ListNode* pReversedHead = ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}

// 输入的链表有多个结点
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
	Test(nullptr);
}

int main()
{
	Test1();
	Test2();
	Test3();

	return 0;
}