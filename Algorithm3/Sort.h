#pragma once
#ifndef _SORT_H__
#define _SORT_H__

#include <vector>
#include <iostream>

class Sort
{
public:
	Sort() {};
	virtual ~Sort() {};

public:
	//冒泡排序：时间复杂度：最好O(n)，最坏O(n^2)；空间复杂度O(1)
	void bubble_sort(int num[], int len)
	{
		for (int i = len; i > 0; i--)
		{
			for (int j = 0; j < i - 1; j++)
			{
				if (num[j] > num[j + 1])
				{
					int temp = num[j];
					num[j] = num[j + 1];
					num[j + 1] = temp;
				}
			}
		}
	}

	//选择排序：时间复杂度：最好O(n^2)，最坏O(n^2)；空间复杂度O(1)
	void select_sort(int num[], int len)
	{
		int flag;
		int min;
		for (int i = 0; i < len; i++)
		{
			flag = i;
			min = num[i];
			for (int j = i + 1; j < len; j++)
			{
				if (min > num[j])
				{
					flag = j;
					min = num[j];
				}
			}
			num[flag] = num[i];
			num[i] = min;
		}
	}

	//插入排序：时间复杂度：最好O(n)，最坏O(n^2)；空间复杂度O(1)
	void insert_sort(int num[], int len)
	{
		for (int i = 1; i < len; i++)
		{
			for (int j = i; j > 0; j--)
			{
				if (num[j] < num[j - 1])
				{
					int temp = num[j];
					num[j] = num[j - 1];
					num[j - 1] = temp;
				}
			}
		}
	}

	//希尔排序：时间复杂度：最好O(n(logn)^2)，最坏O(n(logn)^2)；空间复杂度O(1)
	void shell_sort(int num[], int len)
	{
		int increment = len;
		while (increment > 1)
		{
			increment = increment / 3 + 1;
			for (int i = 0; i < increment; i++)
			{
				for (int j = i; j < len; j += increment)
				{
					for (int k = j; k < len; k += increment)
					{
						if (k + increment < len && num[k + increment] < num[k])
						{
							int temp = num[k];
							num[k] = num[k + increment];
							num[k + increment] = temp;
						}
					}
				}
			}
		}
	}

	//归并排序：时间复杂度：最好O(nlogn)，最坏O(nlogn)；空间复杂度O(n)
	void merge_sort(int num[], int reg[], int start, int end)
	{
		if (start >= end)
		{
			return;
		}

		int mid = (end - start) / 2 + start;
		int start1 = start;
		int end1 = mid;
		int start2 = mid + 1;
		int end2 = end;

		merge_sort(num, reg, start1, end1);
		merge_sort(num, reg, start2, end2);

		int k = start;
		while (start1 <= end1 && start2 <= end2)
		{
			reg[k++] = num[start1] < num[start2] ? num[start1++] : num[start2++];
		}

		while (start1 <= end1)
		{
			reg[k++] = num[start1++];
		}

		while (start2 <= end2)
		{
			reg[k++] = num[start2++];
		}

		for (int j = start; j <= end; j++)
		{
			num[j] = reg[j];
		}
	}

	//快速排序：时间复杂度：最好O(nlogn)，最坏O(n^2)；空间复杂度O(nlogn)
	void quick_sort(int num[], int start, int end)
	{
		if (start >= end)
		{
			return;
		}

		int flag = start;
		int i = start;
		int j = end;

		while (i < j)
		{
			while (j > flag && num[j] >= num[flag])
			{
				j--;
			}
			if (j > flag)
			{
				int temp = num[j];
				num[j] = num[flag];
				num[flag] = temp;
				flag = j;
			}

			while (i < flag && num[i] <= num[flag])
			{
				i++;
			}
			if (i < flag)
			{
				int temp = num[i];
				num[i] = num[flag];
				num[flag] = temp;
				flag = i;
			}
		}

		quick_sort(num, start, flag - 1);
		quick_sort(num, flag + 1, end);
	}

	//堆排序：时间复杂度：最好O(nlogn)，最坏O(nlogn)；空间复杂度O(1)
	void heap_sort(int num[], int len)
	{
		for (int i = len / 2 - 1; i >= 0; i--)
		{
			maxHeapDown(num, i, len - 1);
		}

		for (int i = len - 1; i > 0; i--)
		{
			int temp = num[i];
			num[i] = num[0];
			num[0] = temp;

			maxHeapDown(num, 0, i - 1);
		}
	}
	void maxHeapDown(int num[], int start, int end)
	{
		int current = start;
		int left = 2 * current + 1;
		int temp = num[current];
		for (; left <= end; current = left, left = 2 * current + 1)
		{
			if (left < end && num[left] < num[left + 1])
			{
				left++;
			}
			if (temp >= num[left])
			{
				break;
			}
			else
			{
				num[current] = num[left];
				num[left] = temp;
			}
		}
	}

	void Print(int num[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			std::cout << num[i] << " ";
		}
		std::cout << std::endl;
	}

};
#endif // !_SORT_H__
