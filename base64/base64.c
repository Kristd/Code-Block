#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "openssl/evp.h"
#include "openssl/buffer.h"
#include "openssl/ossl_typ.h"

int base64_encode(char *str, int str_len, char *encode, int encode_len) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;
	
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
	
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, str, str_len); //encode
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    
	if(bptr->length>encode_len) {
        printf("encode_len too small\n");
        return -1; 
    }   
    
	encode_len = bptr->length;
    memcpy(encode, bptr->data, bptr->length);

    BIO_free_all(b64);
    return encode_len;
}

int base64_decode(char *str, int str_len, char *decode, int decode_len) {
    int len = 0;
    BIO *b64, *bmem;
	
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(str, str_len);
    
	bmem = BIO_push(b64, bmem);
    len = BIO_read(bmem, decode, decode_len);
    decode[len] = 0;
	
    BIO_free_all(bmem);
    return 0;
}

int main(int argc, char *argv[]) {
	int ret = -1;
	char in[] = {"\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34\x31\x32\x33\x34"};
	char out[256] = {0};
	
	ret = base64_encode(in, 16, out, 256);
	if(ret > 0) {
		printf("encode:%s\n", out);
	}
	
	memset(in, 0, strlen(in));
	ret = base64_decode(out, strlen(out), in, 16);
	if(ret == 0) {
		printf("decode:%s\n", in);
	}
	
	return 0;
}






