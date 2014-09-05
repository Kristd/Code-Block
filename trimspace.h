#ifndef _TRIMSPACE_H_
#define _TRIMSPACE_H_

char* leftTrim(char* input)
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


char* rightTrim(char* input)
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


char* Trim(char* input)
{
	if(NULL == input) {
		return NULL;
	}

	leftTrim(input);
	rightTrim(input);

	return input;
}

#endif
