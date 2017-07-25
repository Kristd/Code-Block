
#ifndef _QUICK_SORT_H
#define _QUICK_SORT_H

int Sort(int array[], int begin, int end)
{
	int key = 0;
	int pos = 0;
	int i = 0;
	int j = 0;
	int temp = 0;

	key = array[begin];
	i = begin + 1;
	j = end;
	pos = begin;

	while(i < j)
	{	
		while(i < j && key < array[j])
		{
			j--;
		}

		array[pos] = array[j];
		pos = j;

		while(i < j && key > array[i])
		{
			i++;
		}

		array[pos] = array[i];
		pos = i;
	}

	array[pos] = key;
	return pos;
}

int QuickSort(int array[], int begin, int end)
{
	if(begin < end)
	{	
		int mid = fun1(array, begin, end);
		Sort(array, begin, mid - 1);
		Sort(array, mid + 1, end);	
	}

	return 0;
}

#endif
