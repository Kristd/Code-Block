#include "Logger.h"
#include <time.h>

Logger::Logger(char* filePath) {
	strncpy(m_path, filePath, strlen(filePath));
	m_file = fopen(m_path, "a+");
}

Logger::~Logger() {
	if(m_file != NULL) {
		fclose(m_file);
		m_file = NULL;
	}
}

BOOL Logger::init(char* filePath) {
	if(strlen(filePath) == 0) {
		return FALSE;
	}

	try {
		m_instant = new Logger(filePath);
		return TRUE;
	}
	catch(...) {
		return FALSE;
	}
}

void Logger::release() {
	if(m_instant != NULL) {
		m_instant->~Logger();
	}

	m_instant = NULL;
}

Logger* Logger::instant() {
	if(m_instant) {
		return m_instant;
	}
	else {
		return NULL;
	}
}

int Logger::writeLog(char* msg) {
	if(msg == NULL || strlen(msg) == 0) {
		return -1;
	}

	WaitForSingleObject(m_mutex, INFINITE);
	char* buff = NULL;
	int ret = -99;

	try{
		time_t var = 0;
		struct tm* ctime = NULL;
		time(&var);
		ctime = localtime(&var);
		buff = new char[2048+1];
		memset(buff, 0, 2048+1);
		sprintf(buff, "%d%d%d\t%s\n", 1900+ctime->tm_year, 1+ctime->tm_mon, ctime->tm_mday, msg);
	
		if(m_file != NULL) {
			fwrite(buff, 1, strlen(buff), m_file);
			fflush(m_file);
		}

		ret = 0;
	}
	catch(...) {
		ret = -2;
	}

	if(buff != NULL) {
		delete[] buff;
		buff = NULL;
	}

	ReleaseMutex(m_mutex);
	return ret;
}

#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <windows.h>

class Logger
{
public:
	static BOOL init(char* filePath);
	static Logger* instant();
	int writeLog(char* msg);
	static void release();

private:
	Logger();
	Logger(char* filePatj);
	~Logger();

	char* m_path;
	FILE* m_file;
	static Logger* m_instant;
	HANDLE m_mutex;
};

#endif
