#pragma once
#ifndef _CQUEUE_H__
#define _CQUEUE_H__

#include <stack>

template<typename T>
class CQueue
{
public:
	CQueue() {};
	virtual ~CQueue() {};

public:
	void appendTail(const T& node)
	{
		if (m_stack1.empty())
		{
			m_stack1.push(node);
			return;
		}

		while (!m_stack1.empty())
		{
			m_stack2.push(m_stack1.top());
			m_stack1.pop();
		}
		m_stack2.push(node);

		while (!m_stack2.empty())
		{
			m_stack1.push(m_stack2.top());
			m_stack2.pop();
		}

		return;
	}

	T deleteHead()
	{
		if (m_stack1.empty())
		{
			return NULL;
		}

		T node = m_stack1.top();
		m_stack1.pop();

		return node;
	}

private:
	std::stack<T> m_stack1;
	std::stack<T> m_stack2;

};
#endif // !_CQUEUE_H__
