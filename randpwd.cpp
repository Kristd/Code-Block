#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int getPasswdLength() {
	int len = 0;
	srand(time(NULL) + rand());

	len = rand() % 20 + 1;
	return len;
}


int getPasswdChars(unsigned char *lchar, unsigned char *rchar) {
	int lnum, rnum;

	srand(time(NULL) + rand());
	lnum = rand() % 16;

	if(lnum <= 9) {
		*lchar = lnum + '0';
	}
	else {
		*lchar = lnum - 10 + 'A';
	}

	srand(time(NULL) + rand());
	rnum = rand() % 16;

	if(rnum <= 9) {
		*rchar = rnum + '0';
	}
	else {
		*rchar = rnum - 10 + 'A';
	}

	return 0;
}


int createPasswds(unsigned char *passwd, int *length) {
	int len = 0;
	unsigned char lchar = '0'; 
	unsigned char rchar = '0';
	unsigned char res = '0';
	unsigned char *ptr = passwd;

	len = getPasswdLength();
	if(len > *length) {
		return -1;
	}

	for(int i = 0; i < len; i++) {
		getPasswdChars(&lchar, &rchar);
		//printf("lchar:[%c]\trchar:[%c]\n", lchar, rchar);

		if(lchar <= '9' && lchar >= '0') {
			lchar = lchar - '0';
		}
		else {
			lchar = lchar - 'A' + 0x0A;
		}

		if(rchar <= '9' && rchar >= '0') {
			rchar = rchar - '0';
		}
		else {
			rchar = rchar - 'A' + 0x0A;
		}

		res = (lchar << 4) + rchar;
		*ptr = res;
		ptr++;
	}

	*ptr = '\0';
	*length = len;
	
	return 0;
}


int savToFiles(unsigned char *passwd, int len) {
	FILE *fp = NULL;

	if((fp = fopen(PASSWD_ASC_FILE, "ab+")) == NULL) {
		return -1;
	}

	if(0 > fwrite(passwd, len, 1, fp)) {
		return -2;
	}

	fwrite("\n", 1, 1, fp);

	fflush(fp);
	fclose(fp);
	fp = NULL;

	return 0;
}


int test() {
	unsigned char passwd[32];
	int len = 32;

	createPasswds(passwd, &len);

	savToFiles(passwd, len);
	return 0;
}

