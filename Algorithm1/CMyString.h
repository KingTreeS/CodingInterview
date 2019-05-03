#pragma once
#ifndef _CMYSTRING_H__
#define _CMYSTRING_H__

#include <string>
#include <iostream>
using namespace std;

class CMyString
{
public:
	CMyString(char* data = nullptr)
	{
		if (data == nullptr)
		{
			m_pData = new char[1];
			m_pData[0] = '\0';
		}
		else
		{
			m_pData = new char[strlen(data) + 1];
			strcpy_s(m_pData, strlen(data) + 1, data);
		}
	}

	CMyString(const CMyString& str) 
	{
		delete[] m_pData;
		m_pData = new char[strlen(str.m_pData) + 1];
		strcpy_s(m_pData, strlen(str.m_pData) + 1, str.m_pData);
	}

	virtual ~CMyString() 
	{
		delete[] m_pData;
		m_pData = nullptr;
	}

	CMyString& operator=(const CMyString& str)
	{
		//判断是否是同一实例，避免错误释放
		if (this == &str)
		{
			return *this;
		}
		//释放内存
		delete[] m_pData;
		m_pData = nullptr;
		//分配内存空间，复制数据
		m_pData = new char[strlen(str.m_pData) + 1];
		strcpy_s(m_pData, strlen(str.m_pData) + 1, str.m_pData);
		
		return *this;

		////通过局部变量，实现内存自动释放
		//if (this != &str)
		//{
		//	CMyString temp(str);
		//	char* data = temp.m_pData;
		//	temp.m_pData = m_pData;
		//	m_pData = data;
		//}
		//return *this;
	}

	void show() const
	{
		cout << m_pData << endl;
	}

private:
	char* m_pData;
};
#endif // !_CMYSTRING_H__