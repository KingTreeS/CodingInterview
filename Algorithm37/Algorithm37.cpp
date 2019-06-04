#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

void Serialize(BinaryTreeNode* pRoot, ofstream& fileOut)
{
	if (pRoot == nullptr)
	{
		fileOut << "*" << " ";
		return;
	}

	fileOut << pRoot->m_nValue << " ";
	Serialize(pRoot->m_pLeft, fileOut);
	Serialize(pRoot->m_pRight, fileOut);
}

bool ReadNum(ifstream& fileIn, int& value)
{
	if (fileIn.eof())
	{
		return false;
	}

	string filedata;
	fileIn >> filedata;

	if (filedata == "*")
	{
		return false;
	}

	value = atoi(filedata.c_str());
	return true;
}

void Deserialize(BinaryTreeNode** pRoot, ifstream& fileIn)
{
	if (fileIn.peek() == EOF)
	{
		return;
	}

	int value;
	if (ReadNum(fileIn, value))
	{
		*pRoot = new BinaryTreeNode();
		(*pRoot)->m_nValue = value;
		(*pRoot)->m_pLeft = nullptr;
		(*pRoot)->m_pRight = nullptr;

		Deserialize(&(*pRoot)->m_pLeft, fileIn);
		Deserialize(&(*pRoot)->m_pRight, fileIn);
	}
}

// ==================== Test Code ====================
bool isSameTree(const BinaryTreeNode* pRoot1, const BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr && pRoot2 == nullptr)
		return true;

	if (pRoot1 == nullptr || pRoot2 == nullptr)
		return false;

	if (pRoot1->m_nValue != pRoot2->m_nValue)
		return false;

	return isSameTree(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
		isSameTree(pRoot1->m_pRight, pRoot2->m_pRight);
}

void Test(const char* testName, BinaryTreeNode* pRoot)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	PrintTree(pRoot);

	const char* fileName = "test.txt";
	ofstream fileOut;
	fileOut.open(fileName);

	Serialize(pRoot, fileOut);
	fileOut.close();

	// print the serialized file
	ifstream fileIn1;
	char ch;
	fileIn1.open(fileName);
	while (!fileIn1.eof())
	{
		fileIn1 >> ch;
		cout << ch;
	}
	fileIn1.close();
	cout << endl;

	ifstream fileIn2;
	fileIn2.open(fileName);
	BinaryTreeNode* pNewRoot = nullptr;
	Deserialize(&pNewRoot, fileIn2);
	fileIn2.close();

	PrintTree(pNewRoot);

	if (isSameTree(pRoot, pNewRoot))
		printf("The deserialized tree is same as the oritinal tree.\n\n");
	else
		printf("The deserialized tree is NOT same as the oritinal tree.\n\n");
DestroyTree
	(pNewRoot);
}

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

	Test("Test1", pNode8);

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

	Test("Test2", pNode5);

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

	Test("Test3", pNode5);

	DestroyTree(pNode5);
}

void Test4()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	Test("Test4", pNode5);

	DestroyTree(pNode5);
}

void Test5()
{
	Test("Test5", nullptr);
}

//        5
//         5
//          5
//         5
//        5
//       5 5
//      5   5
void Test6()
{
	BinaryTreeNode* pNode1 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode61 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode62 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode71 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode72 = CreateBinaryTreeNode(5);

	ConnectTreeNodes(pNode1, nullptr, pNode2);
	ConnectTreeNodes(pNode2, nullptr, pNode3);
	ConnectTreeNodes(pNode3, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode5, nullptr);
	ConnectTreeNodes(pNode5, pNode61, pNode62);
	ConnectTreeNodes(pNode61, pNode71, nullptr);
	ConnectTreeNodes(pNode62, nullptr, pNode72);

	Test("Test6", pNode1);

	DestroyTree(pNode1);
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