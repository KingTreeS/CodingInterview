#pragma once
#ifndef _STACK_WITH_MIN_H__
#define _STACK_WITH_MIN_H__

#include <stack>

template<typename T>
class StackWithMin
{
public:
	StackWithMin() {};
	virtual ~StackWithMin() {};

public:
	void push(T item)
	{
		m_stack1.push(item);

		if (m_stack2.empty())
		{
			m_stack2.push(item);
		}
		else
		{
			if (item < m_stack2.top())
			{
				m_stack2.push(item);
			}
			else
			{
				m_stack2.push(m_stack2.top());
			}
		}
	}

	void pop()
	{
		m_stack1.pop();
		m_stack2.pop();
	}

	T min()
	{
		return m_stack2.top();
	}

private:
	std::stack<T> m_stack1;
	std::stack<T> m_stack2;

};
#endif // !_STACK_WITH_MIN_H__
