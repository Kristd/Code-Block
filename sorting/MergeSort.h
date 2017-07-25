
#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H

int Sort(int array[], int begin, int mid, int end, int dest[])
{
	int i = begin;
	int j = mid + 1;
	int pos = 0;

	while(i <= mid && j <= end)
	{
		if(array[i] < array[j])
		{
			dest[pos] = array[i];
			i++;
		}
		else
		{
			dest[pos] = array[j];
			j++;
		}

		pos++;
	}

	while(i <= mid)
	{
		dest[pos] = array[i];
		i++;
		pos++;
	}

	while(j <= end)
	{
		dest[pos] = array[j];
		j++;
		pos++;
	}

	for(int k = 0; k < pos; k++)
	{
		array[begin + k] = dest[k];
	}

	return 0;
}


int MergeSort(int array[], int begin, int end, int dest[])
{
	int mid = 0;
	
	if(begin < end)
	{
		mid = (begin + end) / 2;
		MergeSort(array, begin, mid, dest);
		MergeSort(array, mid + 1, end, dest);
		Sort(array, begin, mid, end, dest);
	}

	return 0;
}

#endif
