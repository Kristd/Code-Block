#include <>

int	fn(char *term, char *inbuf, int inlen, char *key, int key_cat, char **outbuf, int *outlen) {
	char *ptr, *buf, *info;
	char data[9], iv[17], templ[64];
	int	i, rc, len;
	int loop = 0, templ_len = 0;

    try {
		if ( NULL == inbuf || 0 == inlen ) {
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAB_gen\tfile %s, line %d\tinput data null\n",
				__FILE__, __LINE__);
#endif

			return(-1);
		}

		if ( NULL == key ) {
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAB_gen\tfile %s, line %d\tinput data null\n",
				__FILE__, __LINE__);
#endif

			return(-2);
		}

		len = inlen + strlen(key) + 64;
		buf	= new char[len];
		info = new char[len];

		if (NULL == buf) {
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAB_gen\tfile %s, line %d\tmemory allocation failure\n",
				__FILE__, __LINE__);
#endif

			return(-3);
		}

		memset(iv, 0 ,17);
		memset(buf, 0, len);
		memset(templ, 0, 64);
		
		//ptr = templ+2;
		ptr = templ;
		printf("%d\n", ptr);
		printf("%d\n", templ);
		
		strncpy(ptr, "00", 2);
		printf("ptr:[%s]", templ);
		ptr	+= 2;

		strncpy(ptr, app_name, app_name_len);
		printf("ptr:[%s]", templ);
		ptr	+= app_name_len;

		strncpy(ptr, SJL_CMD_MAB_TAK_GEN, 2);
		printf("ptr:[%s]", templ);
		ptr += 2;
		
		*ptr = '\0';
		
		printf("templ:[%s]\tloop:[%d]\n", templ, loop);

		//block flag
		strncpy(ptr, "%d", 2);
		ptr += 2;

		//key type
		if(key_cat == PIN_HSM_TAK) {
			strncpy(ptr, "0", 1);
			ptr += 1;
		}
		else if(key_cat == PIN_HSM_ZAK) {
			strncpy(ptr, "1", 1);
			ptr += 1;
		}
		else {
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAB_gen\tfile %s, line %d\tmemory allocation failure\n",
				__FILE__, __LINE__);
#endif

			return(-4);
		}

		//key length
		strncpy(ptr, "0", 1);
		ptr += 1;

		//msg type
		strncpy(ptr, "0", 1);
		ptr += 1;

		//key value
		strncpy(ptr, "F37EF0190A4E166B", 16);
		//memcpy(ptr, key, 16);
		ptr += 16;

		//iv
		strncpy(ptr, "%s", 2);
		ptr += 2;

		//block length
		strncpy(ptr, "0008", 4);
		ptr += 4;

		*ptr = '\0';

		loop = inlen / 8;
		if(0 != inlen % 8) {
			loop++;
		}
		
		
		printf("templ:[%s]\tloop:[%d]\n", templ, loop);
		

		for(int i = 0; i < loop; i++) {
			memset(buf, 0, len);
			memset(data, 0, 9);

			if(i == 0) {
				memcpy(data, inbuf, MSG_BLOCK_LENGTH);
				sprintf(buf, templ, 1, "");
				
				printf("buf:[%s]\ti:[%d]\n", buf, i);
			}
			else if(i == loop-1) {
				memcpy(data, "0", MSG_BLOCK_LENGTH);
				memcpy(data, (inbuf + loop*MSG_BLOCK_LENGTH), inlen - loop*MSG_BLOCK_LENGTH);
				sprintf(buf, templ, 3, iv);
			}
			else {
				memcpy(data, (inbuf + loop*MSG_BLOCK_LENGTH), MSG_BLOCK_LENGTH);
				sprintf(buf, templ, 2, iv);
			}

			templ_len = strlen(buf);

			ptr = buf;
			ptr += templ_len;
			memcpy(ptr, data, MSG_BLOCK_LENGTH);
			
			printf("1 MSG_BLOCK_LENGTH buf:[%s]\n", buf);

			ptr += MSG_BLOCK_LENGTH;
			*ptr = '\0';
			memset(info, 0, len);
			sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAB_gen send buf[%s]", term, buf+2);
			m_pLog->WriteLog(info);

			int msglen = templ_len+MSG_BLOCK_LENGTH-2;
			
			printf("2 MSG_BLOCK_LENGTH msglen:[%d]\n", msglen);
			
			buf[0] = (char)(msglen/256);
			buf[1] = (char)(msglen%256);
			
			printf("3 MSG_BLOCK_LENGTH buf:[%c]\n", buf[1]);
			printf("3 MSG_BLOCK_LENGTH buf:[%s]\n", buf);

#ifdef WIN32
			i = send(sock, buf, templ_len+MSG_BLOCK_LENGTH, 0);
#else
			i = write(sock, buf, templ_len+MSG_BLOCK_LENGTH);
#endif

			if ( i < 0 ) {
#ifdef _DEBUG
				printf("ERROR\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tsocket failure\n", __FILE__, __LINE__);
#endif
				rc	= -5;
				goto err;
			}

#ifdef WIN32
			i = recv(sock, buf, len, 0);
#else
			i = read(sock, buf, len);
#endif

			i	= (((unsigned char)buf[0])<<8) + ((unsigned char)buf[1]);
			if ( i < 8 ) {
#ifdef _DEBUG
				printf("ERROR\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tresponse message failure\t%d\t%02x %02x\t%s\n",
					__FILE__, __LINE__, i, (unsigned char)buf[0], (unsigned char)buf[1], buf+2);
#endif
				rc	= ERR_HSM_OP;
				goto err;
			}

			ptr	= buf+2;
			ptr[i]	= '\0';

			memset(info, 0, len);
			sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAB_gen recv buf[%s]", term, buf+2);
			m_pLog->WriteLog(info);

			if ( strncmp(ptr, app_name, app_name_len) )	{
#ifdef _DEBUG
				printf("ERROR\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tresponse message failure\t%s\n",
					__FILE__, __LINE__, buf+2);
#endif

				rc	= ERR_HSM_SSN;
				goto err;
			}

			ptr	+= app_name_len;

			if (strncmp(ptr, SJL_REP_MAB_TAK_GEN, strlen(SJL_REP_MAB_TAK_GEN)))	{
#ifdef _DEBUG
				printf("ERROR\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tinvalid response code\n",
					__FILE__, __LINE__);
#endif

				rc	= ERR_HSM_SSN;
				goto err;
			}

			if ( strncmp(ptr, "00", 2) != 0 ) {
#ifdef _DEBUG
				printf("ERROR\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tresponse error\n",
					__FILE__, __LINE__);
#endif

				rc	= ERR_HSM_SSN;
				goto err;
			}

			ptr += 2;

			memset(iv, 0, 17);
			memcpy(iv, ptr, MAB_LENGTH);
		}

		if ( outbuf ) {
			if ( outlen ) {
				if ( *outlen > strlen(ptr) ) {
					strncpy(*outbuf, iv, MAB_LENGTH);
					*outlen	= MAB_LENGTH;
				}
				else {
					*outlen	= MAB_LENGTH;
				}
			}
		}

		rc = *outlen;
err:
		for ( i = 0; i < 100; i++ ) {
			memset(buf, (unsigned char)i, sizeof(buf));
		}

		if(buf) {
			delete[] buf;
			buf = NULL;
		}

		if(info) {
			delete[] info;
			info = NULL;
		}

		return(rc);
    }
    catch(...) {
    	printf("EXCEPT\tPIN_HSM_sjl::MAB_gen\tfile %s, line %d\tunexpected exception\t%s\t%s\n",
    				__FILE__, __LINE__, inbuf, key);

		if(buf) {
			delete[] buf;
			buf = NULL;
		}

		if(info) {
			delete[] info;
			info = NULL;
		}

    	return(ERR_HSM_EXCEPT);
    }
}


int main() {
	fn();
	return 0;
}
