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

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)
	{
		return pHead2;
	}

	if (pHead2 == nullptr)
	{
		return pHead1;
	}

	ListNode* pHead3 = nullptr;
	ListNode* pEnd3 = nullptr;

	while (pHead1 != nullptr && pHead2 != nullptr)
	{
		if (pHead3 == nullptr)
		{
			if (pHead1->m_nValue < pHead2->m_nValue)
			{
				pHead3 = pHead1;
				pHead1 = pHead1->m_pNext;
			}
			else
			{
				pHead3 = pHead2;
				pHead2 = pHead2->m_pNext;
			}
			pEnd3 = pHead3;
		}
		else
		{
			if (pHead1->m_nValue < pHead2->m_nValue)
			{
				pEnd3->m_pNext = pHead1;
				pHead1 = pHead1->m_pNext;
			}
			else
			{
				pEnd3->m_pNext = pHead2;
				pHead2 = pHead2->m_pNext;
			}
			pEnd3 = pEnd3->m_pNext;
		}
		pEnd3->m_pNext = nullptr;
	}

	while (pHead1 != nullptr)
	{
		pEnd3->m_pNext = pHead1;
		pHead1 = pHead1->m_pNext;

		pEnd3 = pEnd3->m_pNext;
		pEnd3->m_pNext = nullptr;
	}

	while (pHead2 != nullptr)
	{
		pEnd3->m_pNext = pHead2;
		pHead2 = pHead2->m_pNext;

		pEnd3 = pEnd3->m_pNext;
		pEnd3->m_pNext = nullptr;
	}

	return pHead3;
}

//采用递归方法实现
ListNode* Merge2(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)
	{
		return pHead2;
	}

	if (pHead2 == nullptr)
	{
		return pHead1;
	}

	ListNode* pHead3 = nullptr;

	if (pHead1->m_nValue < pHead2->m_nValue)
	{
		pHead3 = pHead1;
		pHead3->m_pNext = Merge2(pHead1->m_pNext, pHead2);
	}
	else
	{
		pHead3 = pHead2;
		pHead3->m_pNext = Merge2(pHead1, pHead2->m_pNext);
	}

	return pHead3;
}

// ====================测试代码====================
ListNode* Test(const char* testName, ListNode* pHead1, ListNode* pHead2)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The first list is:\n");
	PrintList(pHead1);

	printf("The second list is:\n");
	PrintList(pHead2);

	printf("The merged list is:\n");
	ListNode* pMergedHead = Merge(pHead1, pHead2);
	PrintList(pMergedHead);

	/*
	printf("The merged list is:\n");
	ListNode* pMergedHead = Merge2(pHead1, pHead2);
	PrintList(pMergedHead);
	*/

	printf("\n\n");

	return pMergedHead;
}

// list1: 1->3->5
// list2: 2->4->6
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode6 = CreateListNode(6);

	ConnectListNodes(pNode2, pNode4);
	ConnectListNodes(pNode4, pNode6);

	ListNode* pMergedHead = Test("Test1", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// 两个链表中有重复的数字
// list1: 1->3->5
// list2: 1->3->5
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(5);

	ConnectListNodes(pNode2, pNode4);
	ConnectListNodes(pNode4, pNode6);

	ListNode* pMergedHead = Test("Test2", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// 两个链表都只有一个数字
// list1: 1
// list2: 2
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);

	ListNode* pMergedHead = Test("Test3", pNode1, pNode2);

	DestroyList(pMergedHead);
}

// 一个链表为空链表
// list1: 1->3->5
// list2: 空链表
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode3);
	ConnectListNodes(pNode3, pNode5);

	ListNode* pMergedHead = Test("Test4", pNode1, nullptr);

	DestroyList(pMergedHead);
}

// 两个链表都为空链表
// list1: 空链表
// list2: 空链表
void Test5()
{
	ListNode* pMergedHead = Test("Test5", nullptr, nullptr);
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