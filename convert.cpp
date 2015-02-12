string ConvertBytesToHex(const string& data)
{
	string sRet="";
	for(int i=0;i<data.length();i++)
	{
		unsigned char uc = (unsigned char)data[i];
		char buf[3];
		memset(buf,0,3);
		buf[0] = (uc>>4) & 0x0f;
		buf[1] = uc & 0x0f;
		if(buf[0] >= 0x0A)
			buf[0] = buf[0]+'A' -0x0a;
		else
			buf[0] = buf[0] + '0';
		
		if(buf[1] >= 0x0A)
			buf[1] = buf[1]+'A'-0x0a;
		else
			buf[1] = buf[1] + '0';
		sRet += string(buf,2);
	}
	return sRet;
}


void Asc2Hex(char* szAsc,int iAsc,char* szHex, int iHex )
{
	for(int i=0; i<iAsc/2; i++)
	{
		char szleft;
		if( (szAsc[2*i] >= '0') & (szAsc[2*i] <= '9') )
			szleft = 0x0 + (szAsc[2*i] - '0' );
		else if( (szAsc[2*i] >= 'A') & (szAsc[2*i] <= 'F') )
			szleft = 0xA + (szAsc[2*i] - 'A' );
		else if( (szAsc[2*i] >= 'a') & (szAsc[2*i] <= 'f') )
			szleft = 0xa + (szAsc[2*i] - 'a' );
		else 
			break;

		char szright;
		if( (szAsc[2*i+1] >= '0') & (szAsc[2*i+1] <= '9') )
			szright = 0x0 + (szAsc[2*i+1] - '0' );
		else if( ( szAsc[2*i+1] >= 'A') &  (szAsc[2*i+1] <= 'F') )
			szright = 0xA + (szAsc[2*i+1] - 'A' );
		else if( (szAsc[2*i+1] >= 'a') & (szAsc[2*i+1] <= 'f') )
			szright = 0xa + (szAsc[2*i+1] - 'a' );
		else 
			break;

		szHex[i] = (szleft<<4) + szright;
	}
}


string Asc2Hex(const string &in)
{
	char *szAsc = new char[in.length()];
	int iAsc = in.length();
	char *szHex = new char[in.length()/2];
	int iHex = in.length() /2 ;

	memcpy(szAsc,in.c_str(),iAsc);

	Asc2Hex(szAsc,iAsc, szHex, iHex);
	string sret = string(szHex,iHex);

	delete szAsc;
	delete szHex;

	return sret;	
}
