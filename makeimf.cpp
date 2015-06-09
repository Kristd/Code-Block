#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#endif

#include "atm_enc_dll.h"
#include "des.h"
#include "main.h"


int showUsage() {
	printf("Usage: makeimf [-f filename] | [-c [add | upd | del]] | -s imf\n");
	return 0;
}


int checkParams(char* argv[], commands comm) {
	return 0;
}






int makeImf(int argc, char* argv[]) {
	int ret = -999;
	FILE* src = NULL;
	FILE* dst = NULL;
	char* buff = NULL;
	char* pbrn = NULL;
	char* atmp = NULL;
	BOOL bfound = FALSE;

	commands commd;
	
	try {
		if(argc == 1 || argc%2 == 0) {
			printf("parameter(s) are invalid.\terr=-1\n");
			showUsage();
			return -1;
		}

		checkParams(argv, commd);
		
		if((dst = fopen(TMPFILE, "r+")) == NULL) {
			printf("create temp file failed.\terr=-2\n");
			return -2;
		}
	
		if(commd.get_file_cfg() == 0) {
			;
		}
		else {
			if((src = fopen(KMCFILE, "r+")) == NULL) {
				printf("open kmc.ini failed.\terr=-3\n");
				return -3;
			}
		}
		
		buff = new char[BUFSIZE];
		memset(buff, 0, BUFSIZE);
		fseek(src, 0, SEEK_SET);
		
		while(NULL != fgets(buff, BUFSIZE, src)) {
			if(strncmp(buff, IMF, 3) == 0) {
				pbrn = strstr(buff, "0755");
				
				if(pbrn != NULL) {
					bfound = TRUE;
					int len = strlen(buff);
					
					char p[64];
					if(strstr(buff, leftTAG) == NULL) {
						return -3;
					}
					memset(p, 0, 64);
					strcpy(p, strstr(buff, leftTAG));

					int t = strlen(buff) - strlen(p);
					char prefix[64];
					memset(prefix, 0, 64);
					strncpy(prefix, buff, t);

					atmp = new char[BUFSIZE];
					memset(atmp, 0, BUFSIZE);
					
					//sprintf(atmp, "%s<0,%s,,%s,%s>\n", prefix, "0755", "111.111.111.111", "1111");
					sprintf(atmp, "%s<0,%s,,%s,%s>\n", prefix, commd.get_imf_cfg()->get_branch(), commd.get_imf_cfg()->get_ipaddr(), commd.get_imf_cfg()->get_port());
					int len1 = strlen(atmp);

					fprintf(dst, "%s", atmp);
				}
				else {
					fprintf(dst, "%s", buff);
				}
			}
			else {
				fprintf(dst, "%s", buff);
			}
		}
		

		fflush(src);
		fclose(src);
		src = NULL;

		fflush(dst);
		fclose(dst);
		src = NULL;

		if(rename("dst.txt", "dstnew.txt") != 0) {
			printf("error\n");
		}

		if (bfound == TRUE)	{
			ret = 0;
			printf("restart.x\n");
			//system("./restart.x");
		}
		else {
			ret = -4;
		}
	}
	catch(...) {
		printf("unknown error..\n");
		ret = -999;
	}

	if(buff != NULL) {
		delete[] buff;
		buff = NULL;
	}

	if(atmp != NULL) {
		delete[] atmp;
		atmp = NULL;
	}
	
	return ret;
}



int main() {
	makeImf(1, NULL);
	return 0;
}



char* trimLeft(char* input)
{
	if(NULL == input) {
		return NULL;
	}

	char* ptr = input;
	
	while(ptr != '\0' && ISSPACE(*ptr)) {
		ptr++;
	}

	strcpy(input, ptr);
	return input;
}


char* trimRight(char* input)
{
	if(NULL == input) {
		return NULL;
	}

	char* ptr = input + strlen(input) - 1;

	while(ptr >= input && ISSPACE(*ptr)) {
		ptr--;
	}

	*++ptr = '\0';
	return input;
}


char* trimSpace(char* input)
{
	if(NULL == input) {
		return NULL;
	}

	trimLeft(input);
	trimRight(input);
	return input;
}
