#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


#define PASSWD_FILE_DEC "passwdfile_dec.log"
#define PASSWD_FILE_ENC "passwdfile_enc.log"

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

	for(int i = 0; i < len;) {
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

		if(res == (unsigned char)'0x0D' || res == (unsigned char)'0x0A') {
			continue;
		}

		*ptr = res;
		ptr++;
		i++;
	}

	*ptr = '\0';
	*length = len;
	
	return 0;
}


int savToFiles(unsigned char *passwd, int len, FILE* fp) {
	if(fp == NULL) {
		return -1;
	} 

	fwrite(passwd, len, 1, fp);
	fwrite("\n", 1, 1, fp);

	fflush(fp);
	return 0;
}


int calcPasswd(unsigned char *inbuf, int inlen, unsigned char *outbuf, int *outlen) {
	unsigned char *ptr = NULL;

	if(inbuf == NULL) {
		return -1;
	}

	if(outbuf == NULL) {
		return -2;
	}

	if(inlen > *outlen) {
		return -3;
	}

	ptr = outbuf;

	for(int i = 0; i < inlen; i++) {
		*ptr = inbuf[i] + 0x01;
		ptr++;
	}

	*outlen = inlen;
	return *outlen;
}

int compareStr(unsigned char *decbuf, int declen, unsigned char *encbuf, int enclen) {
	unsigned char *pDec = NULL;
	unsigned char *pEnc = NULL;

	if(decbuf == NULL) {
		return -1;
	}

	if(encbuf == NULL) {
		return -2;
	}

	if(declen != enclen) {
		return -3;
	}

	pDec = decbuf;
	pEnc = encbuf;

	for(int i = 0; i < declen; i++) {
		if(*pDec != (*pEnc-0x01)) {
			return -4;
		}

		pDec++;
		pEnc++;
	}

	return 0;
}

int main() {
	int count = 3;
	unsigned char passwd[32];
	int len = 32;
	unsigned char encPasswd[32];
	int enclen = 32;

	unsigned char content1[32];
	unsigned char content2[32];

	FILE *fp1 = NULL;
	FILE *fp2 = NULL;

	if((fp1 = fopen(PASSWD_FILE_DEC, "ab+")) == NULL) {
		printf("Open %s failed.\n", PASSWD_FILE_DEC);
		return -1;
	}

	if((fp2 = fopen(PASSWD_FILE_ENC, "ab+")) == NULL) {
		printf("Open %s failed\n", PASSWD_FILE_ENC);
		return -2;
	}

	for(int i = 0; i < count; i++) {
		len = 32;
		memset(passwd, 0, len);

		enclen = 32;
		memset(encPasswd, 0, enclen);

		createPasswds(passwd, &len);
		savToFiles(passwd, len, fp1);

		calcPasswd(passwd, len, encPasswd, &enclen);
		savToFiles(encPasswd, enclen, fp2);
	}

	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);

	memset(content1, 0, 32);
	memset(content2, 0, 32);

	while(1) {
		if(fgets((char*)content1, 32, fp1) == NULL || fgets((char*)content2, 32, fp2) == NULL) {
			printf("Bot of the files.\n");
			break;
		}

		if(!strcmp((char*)content1, (char*)content2)) {
			printf("Comparing error.\n");;
		}
	}

	if(fp2 != NULL) {
		fflush(fp2);
		fclose(fp2);
	}

	if(fp1 != NULL) {
		fflush(fp1);
		fclose(fp1);
	}

	return 0;
}

