#pragma once
#ifndef _DYNAMIC_ARRAY_H__
#define _DYNAMIC_ARRAY_H__

#include <vector>
#include <algorithm>

template <typename T>
class DynamicArray
{
public:
	DynamicArray() {};
	virtual ~DynamicArray() {};

public:
	T GetMedian()
	{
		if (m_minHeap.size() + m_maxHeap.size() == 0)
		{
			throw std::exception();
		}

		if (((m_minHeap.size() + m_maxHeap.size()) & 1) == 0)
		{
			return (m_maxHeap[0] + m_minHeap[0]) / 2;
		}
		else
		{
			return m_minHeap[0];
		}
	}

	void Insert(T val)
	{
		if (((m_minHeap.size() + m_maxHeap.size()) & 1) == 0)
		{
			m_maxHeap.push_back(val);
			std::push_heap(m_maxHeap.begin(), m_maxHeap.end(), std::less<T>());

			int max = m_maxHeap[0];
			std::pop_heap(m_maxHeap.begin(), m_maxHeap.end(), std::less<T>());
			m_maxHeap.pop_back();

			m_minHeap.push_back(max);
			std::push_heap(m_minHeap.begin(), m_minHeap.end(), std::greater<T>());
		}
		else
		{
			m_minHeap.push_back(val);
			std::push_heap(m_minHeap.begin(), m_minHeap.end(), std::greater<T>());

			int min = m_minHeap[0];
			std::pop_heap(m_minHeap.begin(), m_minHeap.end(), std::greater<T>());
			m_minHeap.pop_back();

			m_maxHeap.push_back(min);
			std::push_heap(m_maxHeap.begin(), m_maxHeap.end(), std::less<T>());
		}
	}

private:
	std::vector<T> m_minHeap;
	std::vector<T> m_maxHeap;

};
#endif // !_DYNAMIC_ARRAY_H__
