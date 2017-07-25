
##ifndef _BINSEARCH_H_
#define  _BINSEARCH_H_

int BinSearch(int* MyArray, int length, int value)
{
	int begin = 0;
	int end = length - 1;

	return Search(MyArray, begin, end, length) + 1;
}

int Search(int* MyArray, int begin, int end, int value)
{
	int mid = (begin + end) >> 1;

	if(value < MyArray[mid])
	{
		return Search(MyArray, begin, mid, value);
	}
	else if (value > MyArray[mid])
	{
		return Search(MyArray, mid+1, end, value);
	}
	else
	{
		return -1;
	}
}

#endif
