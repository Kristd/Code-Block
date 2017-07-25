
#ifndef _SHELLSORT_H_
#define _SHELLSORT_H_


void ShellSort(int myArray[], size_t size)
{
	size_t i, j, gap;

	for(gap = size/2; gap > 0; gap = gap/2)
	{
		for (i = gap; i < size; i++)
		{
			int temp = myArray[i];

			for (j = i-gap; j >= 0, temp < myArray[j]; j -= gap)
			{
				myArray[j + gap] = myArray[j];
			}

			myArray[j + gap] = temp;
		}
	}
}


#endif
