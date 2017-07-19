#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "openssl/crypto.h"
#include "openssl/sha.h"

int main(int argc, char *argv[]) {
	int iDatLen = 1024;
	SHA256_CTX ctx;

	unsigned char pSrcDat[1024] = {0};
	unsigned char pDscDat[1024] = {0};
	int i = 0;

	for (i = 0; i < iDatLen; i++) {
		pSrcDat[i] = i;
		pDscDat[i] = 0;
	}
	pSrcDat[1024] = 0;

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, pSrcDat, iDatLen);
    SHA256_Final(pDscDat, &ctx);
	OPENSSL_cleanse(&ctx, sizeof(ctx));
	
	for (i = 0; i < strlen((const char*)pDscDat); i++) {
		printf("%02X", pDscDat[i]);
	}
	
	printf("\n");
	return 0;
}
