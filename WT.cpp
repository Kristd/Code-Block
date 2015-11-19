int	PIN_HSM_sjl::MAC_gen_SM4(char* devId, char *data, int data_len, char *key, int key_cat, char **obuf, int *olen)
{
	char* info;
	char *ptr, ch;
	int	i, rc, len;
	char *buf;

    try
    {
		len = data_len + strlen(key) + 256;
		info = new char[len];

		if ( NULL == data || 0 == data_len )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tinput data null\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, 1024);
			sprintf(info, "[%s]ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tInput data null.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			return(ERR_HSM_DATA_NULL);
		}

		if ( NULL == key )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tinput data null\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, 1024);
			sprintf(info, "[%s]ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tInput key null.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			return(ERR_HSM_TAKZAK);
		}

		buf = new char[len];
		memset(buf, 0 , len);

		if ( NULL == buf )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tmemory allocation failure\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tMemory allocation failure.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			return(ERR_MEM_ALLOC);
		}


		ptr	= buf + 2;

		strncpy(ptr, app_name, app_name_len);
		ptr += app_name_len;

		if ( PIN_HSM_TAK == key_cat ) {
			strcpy(ptr, SJL_CMD_MAC_TAK_GEN_SM4);
			ptr	+= strlen(SJL_CMD_MAC_TAK_GEN_SM4);
		}
		else if ( PIN_HSM_ZAK == key_cat ) {
			strcpy(ptr, SJL_CMD_MAC_ZAK_GEN_SM4);
			ptr	+= strlen(SJL_CMD_MAC_ZAK_GEN_SM4);
		}
		else
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tmemory allication failure\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM::MAC_gen_SM4\tfile %s, line %d\tKeytype error",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			return(ERR_HSM_KEY);
		}

		//mode flag
		strncpy(ptr, MKMAC, strlen(MKMAC));
		ptr += 1;

		//key flag
		strncpy(ptr, "Y", 1);
		ptr += 1;

		//key type
		if(PIN_HSM_TAK == key_cat) {
			strncpy(ptr, TAK_FLAG, 3);
			ptr += 3;
		}
		else if(PIN_HSM_ZAK == key_cat) {
			strncpy(ptr, ZAK_FLAG, 3);
			ptr += 3;
		}
		else {
			return(ERR_HSM_KEY);
		}

		//key value
		strncpy(ptr, key, 32);
		ptr	+= 32;

		//MAC calc method
		strncpy(ptr, "1", 1);
		ptr += 1;

		//msg type
		strncpy(ptr, "0", 1);
		ptr += 1;

		//data len
		char slen[5];
		memset(slen, 0, 5);
		sprintf(slen, "%04d", data_len);
		strncpy(ptr, slen, 4);
		ptr += 4;

		//data
		memcpy(ptr, data, data_len);
		ptr += data_len;

		*ptr = '\0';
		memset(info, 0, len);
		sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAC_gen_SM4 send buf[%s]", devId, buf+2);
		m_pLog->WriteLog(info);

		i = ptr-buf-2;
		buf[0] = (char)(i/256);
		buf[1] = (char)(i%256);

#ifdef WIN32
		i	= send(sock, buf, ptr-buf, 0);
#else
		i	= write(sock, buf, ptr-buf);

		memset(info, 0, len);
		sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAC_gen_SM4 write ret[%d]", devId, i);
		m_pLog->WriteLog(info);
#endif
		if ( i < 0 )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tsocket failure\n",
				__FILE__, __LINE__);
#endif

			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tsocket failure.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_SSN_SOCK;
			goto err;
		}

#ifdef WIN32
		i	= recv(sock, buf, len, 0);
#else
		i	= read(sock, buf, len);

		memset(info, 0, len);
		sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAC_gen_SM4 read ret[%d]", devId, i);
		m_pLog->WriteLog(info);
#endif

		i = (((unsigned char)buf[0])<<8) + ((unsigned char)buf[1]);

		if ( i < 8 )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tresponse message failure\t%d\t%02x %02x\t%s\n",
				__FILE__, __LINE__, i, (unsigned char)buf[0], (unsigned char)buf[1], buf+4);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tresponse message failure.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_OP;
			goto err;
		}

		ptr = buf+2;
		ptr[i] = '\0';

		memset(info, 0, len);
		sprintf(info, "[%s]INFO\tPIN_HSM_sjl::MAC_gen_SM4 recv buf[%s]", devId, buf+2);
		m_pLog->WriteLog(info);

		//	if ( strncmp(ptr, app_name, 4) )
		if (strncmp(ptr, app_name, app_name_len))
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tresponse message failure\t%s\n",
				__FILE__, __LINE__, buf+2);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tresponse message error.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc = ERR_HSM_SSN;
			goto err;
		}

		//	ptr	+= 4;		// skip the message header
		//	i	-= 4;
		ptr	+= app_name_len;		// skip the message header
		i -= app_name_len;

		if ( ( PIN_HSM_TAK == key_cat ) && strncmp(ptr, SJL_REP_MAC_TAK_GEN_SM4, strlen(SJL_REP_MAC_TAK_GEN_SM4)) )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response code\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response code.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc = (ERR_HSM_SSN);
			goto err;
		}
		else if ( ( PIN_HSM_ZAK == key_cat ) && strncmp(ptr, SJL_REP_MAC_ZAK_GEN_SM4, strlen(SJL_REP_MAC_ZAK_GEN_SM4)) )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response code\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response code.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= (ERR_HSM_SSN);
			goto err;
		}

		ptr += 2;

		if ( ( PIN_HSM_ZAK == key_cat ) && ( strncmp(ptr, "02", 2) == 0 ) )
		{
			// ZAK not single length
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tZAK not single length\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tZAK not single length.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_ZAK;
			goto err;
		}
		else if ( strncmp(ptr, "10", 2) == 0 )
		{
			// TAK parity error
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tPVK parity error\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tTPK parity error.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_KEY;
			goto err;
		}
		else if ( strncmp(ptr, "12", 2) == 0 )
		{
			// no key loaded in user storage
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tno key loaded in user storage\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tno key loaded in user storage.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_KEY;
			goto err;
		}
		else if ( strncmp(ptr, "13", 2) == 0 )
		{
			// LMK error, report to adm
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tencrypted PASS\t%s\n",
				__FILE__, __LINE__, ptr);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tLMK error.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_LMK;
			goto err;
		}
		else if ( strncmp(ptr, "15", 2) == 0 )
		{
			// error in input data
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tencrypted PASS\t%s\n",
				__FILE__, __LINE__, ptr);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tInput data error.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_DATA;
			goto err;
		}
		else if ( strncmp(ptr, "21", 2) == 0 )
		{
			// invalid user storage index
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid user storage index\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid user storage index.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_TAK;
			goto err;
		}
		else if ( ( PIN_HSM_TAK == key_cat ) && ( strncmp(ptr, "27", 2) == 0 ) )
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tTAK not single length\n",
				__FILE__, __LINE__);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tTAK not single length.",
					devId, __FILE__, __LINE__);
			m_pLog->WriteLog(info);

			rc	= ERR_HSM_TAK;
			goto err;
		}
		else if (strncmp(ptr, "00", 2))
		{
#ifdef _DEBUG
			printf("ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response message\t%s\n",
				__FILE__, __LINE__, buf+2);
#endif
			memset(info, 0, len);
			sprintf(info, "[%s]ERROR\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tinvalid response message:\t%s.",
					devId, __FILE__, __LINE__, buf+2);
			m_pLog->WriteLog(info);

			rc	= (ERR_HSM_SSN);
			goto err;
		}

		ptr	+= 2;
		//i	-= 2;

#ifdef _DEBUG
		printf("PIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tMAC result\t%s\n",	__FILE__, __LINE__, ptr);
#endif

		if ( obuf )	{
			if ( olen )	{
				if ( *olen > strlen(ptr) ) {
					strncpy(*obuf, ptr, MAC_DATA_LEN);
					//*olen	= strlen(ptr);
					*olen = MAC_DATA_LEN;
				}
				else {
					//*olen	= strlen(ptr);
					*olen = MAC_DATA_LEN;
				}
			}
		}

		rc	= strlen(ptr);
err:
/*
		for ( i = 0; i < 100; i++ )
			memset(buf, (unsigned char)i, sizeof(buf));

		free(buf);
*/
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
#ifdef _DEBUG
    	printf("EXCEPT\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tunexpected exception\t%s\t%s\n",
    			__FILE__, __LINE__, data, key);
#endif
		memset(info, 0, len);
		sprintf(info, "[%s]EXCEPT\tPIN_HSM_sjl::MAC_gen_SM4\tfile %s, line %d\tunexpected exception.",
				devId, __FILE__, __LINE__);
		m_pLog->WriteLog(info);

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
