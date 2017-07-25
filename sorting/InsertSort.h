
#ifndef _INSERTSORT_H_
#define _INSERTSORT_H_

void InsertSort(int myArray[], size_t size)
{
	int i = 0;
	int j = 0;

	for(i = 1; i < size; i++)
	{
		int temp = myArray[i];

		for(j = i-1; j >= 0, temp <= myArray[j]; j--)
		{
			myArray[j+1] = myArray[j];
		}

		myArray[j+1] = temp;
	}
}

#endif
