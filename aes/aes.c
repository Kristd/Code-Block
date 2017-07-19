#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "openssl/aes.h"

int main(int argc, char *argv[]) {
	int i = 0;
	const char *in = "\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34";
	unsigned char out[256] = {0};
	AES_KEY *aeskey = NULL;
	
	const char *testkey = "\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34";
	const int length = 128;

	aeskey = (AES_KEY*)malloc(sizeof(AES_KEY));
	memset(aeskey, 0, sizeof(AES_KEY));
	
	memcpy(out, AES_options(), strlen(AES_options()));
	printf("key=%s\n", testkey);
	
	int ret = AES_set_encrypt_key((const unsigned char*)testkey, length, aeskey);
	if(ret != 0) {
		printf("ret=%d\n", ret);
	}
	
	AES_ecb_encrypt((const unsigned char*)in, out, aeskey, AES_ENCRYPT);
	for(i = 0; i < strlen((const char*)out); i++) {
		printf("%02X", out[i]);
	}
	
	printf("\n");
	free(aeskey);
	
	return 0;
}
