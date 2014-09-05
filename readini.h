#ifndef _READINI_H_
#define _READINI_H_

#include <stdio.h>
#include <stdlib.h>

#define BUFF_LEN		2048
#define APP_LEN 		32
#define ISSPACE(x) 		(x == ' ' || x == '\n' || x == '\t' || x == '\f' || x == '\v')

#ifndef BOOL
#define BOOL 			int
#define TRUE 			1
#define FALSE			0
#endif


int GetPrivateProfileStringL(char* appName, char* keyName, char* defVal, char* keyVal, int len, char* profile)
{
	char app[APP_LEN];
	char key[APP_LEN];
	char* buf = NULL;
	char* valptr = NULL;

	FILE* fp = NULL;
	BOOL appf = FALSE;
	BOOL keyf = FALSE;

	int retcd = -1;

	try {
		if(appName == NULL || keyName == NULL) {
			printf("Input parms(s) is null.\n");
			return(-1);
		}

		if((fp = fopen(profile, "r")) == NULL) {
			printf("Open file [%s] error.\n", profile);
			return(-1);
		}

		memset(app, 0, APP_LEN);
		memset(key, 0, APP_LEN);

		buf = new char[BUFF_LEN];

		fseek(fp, 0, SEEK_SET);
		memset(app, 0, sizeof(app));
		sprintf(app,"[%s]", appName);

		while(!feof(fp) && fgets(buf, BUFF_LEN, fp) != NULL) {
			buf[strlen(buf) - 1] = '\0';
			leftTrim(buf);

			if(strlen(buf) <= 0) {
				continue;
			}

			if(appf == FALSE) {

				if(buf[0] != '[') {
					continue;
				}
				else if(strncmp(buf, app, strlen(app)) == 0) {
					appf = TRUE;
					continue;
				}
				else {
					continue;
				}
			}

			if(appf == TRUE) {
				if(buf[0] == '#') {
					continue;
				}
				else if (buf[0] == '[') {
					break;
				}
				else {
					if((valptr = (char*)strchr(buf, '=')) == NULL) {
						continue;
					}

					memset(key, 0, sizeof(key));
					sscanf(buf, "%[^=|^ |^\t]", key);

					if(strcmp(key, keyName) == 0) {
						//sscanf(++valptr, "%[^\n]", keyVal);
						strncpy(keyVal, ++valptr, len-1);
						keyf = TRUE;
						
						break;
					}
					else {
						continue;
					}
				}
			}
		}

		if(keyf == FALSE) {
			strncpy(keyVal, defVal, len-1);
		}

		keyVal[len-1] = '\0';
		retcd = strlen(keyVal) + 1;
	}
	catch(...) {
		retcd = -1;
	}

	if(fp != NULL)
	{
		fclose(fp);
	}

	delete[] buf;
	fp = NULL;
	buf = NULL;
	valptr = NULL;

	return retcd;
}

#endif
