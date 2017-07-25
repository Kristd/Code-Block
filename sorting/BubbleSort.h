
#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_


void BubbleSort(int myArray[], int size)
{
	int i, j, temp;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-i-1; j++)
		{
			if (myArray[j] > myArray[j+1])
			{
				temp = myArray[j];
				myArray[j] = myArray[j+1];
				myArray[j+1] = temp;
			}
		}
	}
}


#endif
