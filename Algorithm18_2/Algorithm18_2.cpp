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

void DestroyList(ListNode* pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	ListNode* pTmp = pHead->m_pNext;
	delete pHead;
	pHead = nullptr;

	DestroyList(pTmp);
}

void DeleteDuplication(ListNode** pHead)
{
	if (pHead == nullptr || *pHead == nullptr)
	{
		return;
	}

	bool needDelete = false;//判断是否处在重复节点中（用于边界节点判断）
	ListNode* pDeleteNode = nullptr;//待删除节点
	ListNode* pNode = *pHead;//当前指针在链表中的位置
	ListNode* pPreNode = *pHead;//前一个节点
	while (pNode->m_pNext != nullptr)
	{
		ListNode* pTmp = pNode->m_pNext;
		//判断节点值是否重复
		if (pNode->m_nValue < pTmp->m_nValue)
		{
			//判断是否是重复节点的最后一个节点
			if (needDelete)
			{
				//判断当前节点是否为头结点
				if (pPreNode == *pHead && pPreNode == pNode)
				{
					*pHead = pTmp;
					pPreNode = pTmp;
				}
				else
				{
					pPreNode->m_pNext = pTmp;
				}
				pDeleteNode = pNode;
				pNode = pTmp;

				delete pDeleteNode;
				pDeleteNode = nullptr;
				needDelete = false;
			}
			else
			{
				pPreNode = pNode;
				pNode = pTmp;
			}
		}
		else
		{
			//判断当前节点是否为头结点
			if (pPreNode == *pHead && pPreNode==pNode)
			{
				*pHead = pTmp;
				pPreNode = pTmp;
			}
			else
			{
				pPreNode->m_pNext = pTmp;
			}
			pDeleteNode = pNode;
			pNode = pTmp;

			delete pDeleteNode;
			pDeleteNode = nullptr;
			needDelete = true;
		}
	}
	//处理尾节点
	if (needDelete)
	{
		//判断此时链表中是否只有一个节点
		if (pPreNode == *pHead)
		{
			*pHead = nullptr;
		}
		else
		{
			pPreNode->m_pNext = nullptr;
		}
		delete pNode;
		pNode = nullptr;
	}
}

// ====================测试代码====================
void Test(const char* testName, ListNode** pHead, int* expectedValues, int expectedLength)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	DeleteDuplication(pHead);

	int index = 0;
	ListNode* pNode = *pHead;
	while (pNode != nullptr && index < expectedLength)
	{
		if (pNode->m_nValue != expectedValues[index])
			break;

		pNode = pNode->m_pNext;
		index++;
	}

	if (pNode == nullptr && index == expectedLength)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// 某些结点是重复的
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(4);
	ListNode* pNode6 = CreateListNode(4);
	ListNode* pNode7 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2, 5 };
	Test("Test1", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 没有重复的结点
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);
	ListNode* pNode6 = CreateListNode(6);
	ListNode* pNode7 = CreateListNode(7);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2, 3, 4, 5, 6, 7 };
	Test("Test2", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 除了一个结点之外其他所有结点的值都相同
void Test3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(1);
	ListNode* pNode5 = CreateListNode(1);
	ListNode* pNode6 = CreateListNode(1);
	ListNode* pNode7 = CreateListNode(2);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 2 };
	Test("Test3", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 所有结点的值都相同
void Test4()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(1);
	ListNode* pNode4 = CreateListNode(1);
	ListNode* pNode5 = CreateListNode(1);
	ListNode* pNode6 = CreateListNode(1);
	ListNode* pNode7 = CreateListNode(1);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);

	ListNode* pHead = pNode1;

	Test("Test4", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 所有结点都成对出现
void Test5()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(2);
	ListNode* pNode5 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(3);
	ListNode* pNode7 = CreateListNode(4);
	ListNode* pNode8 = CreateListNode(4);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);
	ConnectListNodes(pNode7, pNode8);

	ListNode* pHead = pNode1;

	Test("Test5", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 除了两个结点之外其他结点都成对出现
void Test6()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);
	ListNode* pNode3 = CreateListNode(2);
	ListNode* pNode4 = CreateListNode(3);
	ListNode* pNode5 = CreateListNode(3);
	ListNode* pNode6 = CreateListNode(4);
	ListNode* pNode7 = CreateListNode(5);
	ListNode* pNode8 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);
	ConnectListNodes(pNode5, pNode6);
	ConnectListNodes(pNode6, pNode7);
	ConnectListNodes(pNode7, pNode8);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 2, 4 };
	Test("Test6", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 链表中只有两个不重复的结点
void Test7()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);

	ConnectListNodes(pNode1, pNode2);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1, 2 };
	Test("Test7", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 结点中只有一个结点
void Test8()
{
	ListNode* pNode1 = CreateListNode(1);

	ConnectListNodes(pNode1, nullptr);

	ListNode* pHead = pNode1;

	int expectedValues[] = { 1 };
	Test("Test8", &pHead, expectedValues, sizeof(expectedValues) / sizeof(int));

	DestroyList(pHead);
}

// 结点中只有两个重复的结点
void Test9()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(1);

	ConnectListNodes(pNode1, pNode2);

	ListNode* pHead = pNode1;

	Test("Test9", &pHead, nullptr, 0);

	DestroyList(pHead);
}

// 空链表
void Test10()
{
	ListNode* pHead = nullptr;

	Test("Test10", &pHead, nullptr, 0);
}

int main(int argc, char* argv[])
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
	Test10();

	return 0;
}