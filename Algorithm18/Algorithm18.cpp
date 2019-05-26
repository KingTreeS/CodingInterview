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
	if (pNode1 == nullptr || pNode2 == nullptr)
	{
		return;
	}

	pNode1->m_pNext = pNode2;
}

void DestroyList(ListNode* pListHead)
{
	if (pListHead == nullptr)
	{
		return;
	}

	ListNode* pNext = pListHead->m_pNext;
	delete pListHead;
	pListHead = nullptr;

	DestroyList(pNext);
}

void PrintList(ListNode* pListHead)
{
	if (pListHead == nullptr)
	{
		std::cout << "\n";
		return;
	}

	std::cout << pListHead->m_nValue << " ";
	PrintList(pListHead->m_pNext);
}

void PrintListNode(ListNode* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	std::cout << pNode->m_nValue << "\n";
}

void DeleteNode(ListNode** pListHead, ListNode* pNode)
{
	if (pListHead == nullptr || pNode == nullptr || *pListHead == nullptr)
	{
		return;
	}

	if (pNode->m_pNext == nullptr)
	{
		if (*pListHead == pNode)
		{
			delete pNode;
			pNode = nullptr;

			*pListHead = nullptr;
			return;
		}

		ListNode* pTmp = *pListHead;
		while (pTmp->m_pNext != pNode)
		{
			pTmp = pTmp->m_pNext;
		}
		pTmp->m_pNext = pNode->m_pNext;
		delete pNode;
		pNode = nullptr;
		pTmp = nullptr;

		return;
	}

	ListNode* pTmp = pNode->m_pNext;
	pNode->m_nValue = pTmp->m_nValue;
	pNode->m_pNext = pTmp->m_pNext;
	delete pTmp;
	pTmp = nullptr;

	return;
}

// ====================测试代码====================
void Test(ListNode* pListHead, ListNode* pNode)
{
	printf("The original list is: \n");
	PrintList(pListHead);

	printf("The node to be deleted is: \n");
	PrintListNode(pNode);

	DeleteNode(&pListHead, pNode);

	printf("The result list is: \n");
	PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
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

	Test(pNode1, pNode3);

	DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
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

	Test(pNode1, pNode5);

	DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
void Test3()
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

	Test(pNode1, pNode1);

	DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);

	Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
	Test(nullptr, nullptr);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();

	return 0;
}