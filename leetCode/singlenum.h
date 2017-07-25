
#ifndef _SINGLENUM_H_
#define _SINGLENUM_H_


int singleNumber(int A[], int n) {
	int ret = A[0];

	for (int i = 1; i < n; i++) {
		ret = ret^A[i];
	}

	return ret;
}



#endif /* _SINGLENUM_H_ */
