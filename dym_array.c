#include <stdio.h>
#include <stdlib.h>

int main() {
	int* p = 0;
	p = (int*)malloc(5*sizeof(int));
	unsigned int i = 0;

	for (i = 0; i < 5; i++) {
		p[i] = i;
	}

	free(p);
	return 0;
}