/*
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0 
*/

#ifndef _SEARCHINSERTPOSITION_H_
#define _SEARCHINSERTPOSITION_H_

int searchInsert(int A[], int n, int target) {
	if(A == NULL) {
		return -1;
	}

	if(A[0] < A[n-1]) {
		return bs_big();
	}
	else {
		return bs_small();
	}
}

int bs_big(int array[], int head, int len, int tar) {
	if(len/2 == 0) {
		if (array[len/2] > tar) {
			return head+len/2;
		}
		else {
			return head+len/2+1;
		}
	}

	if(array[len/2] == tar) {
		return head + len/2;
	}
	else if(array[len/2] < tar) {
		return bs_big(array[len/2+1], len/2+1, len/2, tar);
	}
	else {
		return bs_big(array[0], 0, len/2, tar);
	}
}

int bs_small() {}

#endif
