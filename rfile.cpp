//////////////////////////////////////////////////////////////////////////////////
//	RecordFile.cpp																//
//			Body file of CRecordFile											//
//					by Bill Sharely      Dec.1,1999								//														
//																				//
//	File structure of RecordFile:												//
//		Version			16	Bytes		Must be "RecordFile 1.0"				//
//		Title			32	Bytes		Reserved								//
//		FileInfo		256 Bytes		Reserved								//
//		Record size		4	Bytes		Length of record						//
//		Record count	4	Bytes		Count of records in this file			//
//		File length		4	Bytes		Length of this file						//
//		Checking sum	4	Bytes		Sum of all records' bytes in this file	//
//////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <WINBASE.H>
#include "RecordFile.h"
#include "io.h"
#include "utils.h"


/*
struct FILEHEAD
{
unsigned char			cVersion;
char	        		OrgName[8];
unsigned char			cAppID;
unsigned int            RndKeyLen;         
unsigned char           RndKey[20];
unsigned int			iRecordSize;
unsigned int			iRecordCount;
unsigned int			iFileLength;
int						iCheckSum;
};
*/

CRecordFile::CRecordFile(char* pstrFileName, int iRecordSize)
{
	if(strlen(pstrFileName) <= 255)
	{
		strcpy(m_strFileName,pstrFileName);
	}
	else
	{
		m_strFileName[0] = 0;
	}

	m_hMutex = CreateMutex(NULL,FALSE,NULL);
	m_iRecordSize = iRecordSize;
	m_pHead = NULL;
	m_pTail = NULL;
	m_iRecordCount = 0;
	m_bCopyed = false;
}

CRecordFile::~CRecordFile()
{
	RemoveAll();
	CloseHandle(m_hMutex);
}

RFSTATUS CRecordFile::ReadFile()
{
	RemoveAll();

	DWORD status=WaitForSingleObject(m_hMutex, 100000);
	if (status == WAIT_OBJECT_0)
	{
		bool bRealFileOk = true;
		unsigned int i,j;
		char cTemp;
		FILEHEAD Head;
		memset(&Head,0,sizeof(FILEHEAD));
		int iCheckSum = 0;

		FILE* pRealFile = fopen(m_strFileName,"rb");
		if(pRealFile != NULL)
		{
			int iRealSize = fread(&Head,sizeof(FILEHEAD),1,pRealFile);
			memcpy(&m_fileHead,&Head,sizeof(FILEHEAD));
			if(iRealSize != 1)
			{
				fclose(pRealFile);
				bRealFileOk = false;
			}
			else
			{
				if(m_iRecordSize != Head.iRecordSize)
				{
					fclose(pRealFile);
					ReleaseMutex(m_hMutex);
					return RF_FILE_NOT_MATCH;
				}
				int iLen = filelength(_fileno(pRealFile));
				if(iLen != (long)Head.iFileLength)
				{
					fclose(pRealFile);
					bRealFileOk = false;
				}
				else
				{
					char* pRecord = new char[m_iRecordSize];
					memset(pRecord,0,m_iRecordSize);
					for(j=0;j<Head.iRecordCount;j++)
					{
						fread(pRecord,m_iRecordSize,1,pRealFile);
						for(i=0;i<Head.iRecordSize;i++)			//Calculate Check Sum
						{
							cTemp = *(((char*)(pRecord)+i));
							iCheckSum = iCheckSum+(int)cTemp;
						}
						Add(pRecord);
					}

					delete pRecord;
					fclose(pRealFile);

					if(iCheckSum != Head.iCheckSum)
					{
						bRealFileOk = false;
					}
				}
			}
		}
		else
		{
			bRealFileOk = false;
		}
	
		if(bRealFileOk == false)
		{
			if(m_bCopyed == false)
			{
				m_bCopyed = true;
				char strMirrorFileName[256];
				strcpy(strMirrorFileName,m_strFileName);
				strcat(strMirrorFileName,"~");
				if(CopyFile(strMirrorFileName,m_strFileName) != 0)
				{
					ReadFile();
				}
				else
				{
					ReleaseMutex(m_hMutex);
					return RF_DBFILE_ERROR;
				}
			}
			else
			{
				ReleaseMutex(m_hMutex);
				return RF_DBFILE_ERROR;
			}
		}
		ReleaseMutex(m_hMutex);
	}
	//how about timeout

	return RF_SUCCESS;
}

RFSTATUS CRecordFile::WriteFile() const
{
	DWORD status=WaitForSingleObject(m_hMutex, 100000);
	if (status == WAIT_OBJECT_0)
	{
		int iShift = sizeof(FILEHEAD);
		RECORDNODE* pTemp = m_pHead;

		char strMirrorFileName[256];
		strcpy(strMirrorFileName,m_strFileName);
		strcat(strMirrorFileName,"~");

		FILE* pRealFile = fopen(m_strFileName,"wb");
		FILE* pMirrorFile = fopen(strMirrorFileName,"wb");

		if((pRealFile == NULL) || (pMirrorFile == NULL))
		{
			return RF_OPEN_FILE_FAILED;
		}

		fseek(pRealFile,iShift,0);
		fseek(pMirrorFile,iShift,0);

		unsigned int i;
		int iCheckSum = 0;
		char cTemp;
		while(pTemp != NULL)
		{
			for(i=0;i<m_iRecordSize;i++)			//Calculate Check Sum
			{
				cTemp = *(((char*)(pTemp->pRecord))+i);
				iCheckSum = iCheckSum+(int)cTemp;
			}

			unsigned int iRealSize = fwrite(pTemp->pRecord,m_iRecordSize,1,pRealFile);
			unsigned int iMirrorSize = fwrite(pTemp->pRecord,m_iRecordSize,1,pMirrorFile);
			if((iRealSize != 1) || (iMirrorSize != 1))
			{
				fclose(pRealFile);
				fclose(pMirrorFile);

				return RF_WRITE_FILE_FAILED;
			}

			pTemp = pTemp->pNextNode;
		}

		FILEHEAD Head;
		memset(&Head,0,sizeof(FILEHEAD));
		Head.cVersion = 0x01;
		Head.cAppID = 0x01;
		strcpy(Head.OrgName,"CMB");
		Head.RndKeyLen = m_fileHead.RndKeyLen;
		memcpy(Head.RndKey,m_fileHead.RndKey,m_fileHead.RndKeyLen);
		Head.iRecordSize = m_iRecordSize;
		Head.iRecordCount = m_iRecordCount;
		Head.iFileLength = sizeof(FILEHEAD)+m_iRecordCount*m_iRecordSize;
		Head.iCheckSum = iCheckSum;

		fseek(pRealFile,0,0);
		fseek(pMirrorFile,0,0);
		fwrite(&Head,sizeof(FILEHEAD),1,pRealFile);
		fwrite(&Head,sizeof(FILEHEAD),1,pMirrorFile);
	
		fclose(pRealFile);
		fclose(pMirrorFile);

		ReleaseMutex(m_hMutex);
	}

	return RF_SUCCESS;
}

int CRecordFile::GetSize() const
{
	return m_iRecordCount;
}

RFSTATUS CRecordFile::RemoveAll()
{
	RECORDNODE* pTemp = m_pHead;
	RECORDNODE* pDeleteNode;
	while(pTemp != NULL)
	{
		pDeleteNode = pTemp;
		pTemp = pTemp->pNextNode;
		delete pDeleteNode->pRecord;
		delete pDeleteNode;
	}

	m_pHead = NULL;
	m_pTail = NULL;
	m_iRecordCount = 0;
	
	return RF_SUCCESS;
}

RFSTATUS CRecordFile::GetAt(int iIndex,void* pRecord) const
{
	if(iIndex > ((int)m_iRecordCount-1) || iIndex < 0)		//m_iRecordCount=0 is rejected either
	{
		return RF_BEYOND_RANGE;
	}

	RECORDNODE* pTemp = m_pHead;
	int i;
	for(i=0;i<iIndex;i++)
	{
		pTemp = pTemp->pNextNode;
	}
	memcpy(pRecord,pTemp->pRecord,m_iRecordSize);

	return RF_SUCCESS;
}

RFSTATUS CRecordFile::SetAt(int iIndex, void* pRecord)
{
	if(iIndex > ((int)m_iRecordCount-1) || iIndex < 0)		//m_iRecordCount=0 is rejected either
	{
		return RF_BEYOND_RANGE;
	}

	RECORDNODE* pTemp = m_pHead;
	int i;
	for(i=0;i<iIndex;i++)
	{
		pTemp = pTemp->pNextNode;
	}
	memcpy(pTemp->pRecord,pRecord,m_iRecordSize);

	return RF_SUCCESS;
}

RFSTATUS CRecordFile::Add(void* pRecord)
{
	RECORDNODE* pNode = new RECORDNODE;
	pNode->pRecord = new char[m_iRecordSize];
	memset(pNode->pRecord,0,m_iRecordSize);
	memcpy(pNode->pRecord,pRecord,m_iRecordSize);
	pNode->pNextNode = NULL;

	if(m_pHead == NULL)			//First element
	{
		m_pHead = pNode;
	}
	else
	{
		m_pTail->pNextNode = pNode;
	}
	m_pTail = pNode;
	m_iRecordCount++;

	return RF_SUCCESS;
}

RFSTATUS CRecordFile::InsertAt(int iIndex,void* pRecord)
{
	if(iIndex > ((int)m_iRecordCount-1) || iIndex < 0)		//m_iRecordCount=0 is rejected either
	{
		return RF_BEYOND_RANGE;
	}

	RECORDNODE* pNode = new RECORDNODE;
	pNode->pRecord = new char[m_iRecordSize];
	memset(pNode->pRecord,0,m_iRecordSize);
	memcpy(pNode->pRecord,pRecord,m_iRecordSize);

	if(iIndex == 0)
	{
		pNode->pNextNode = m_pHead;
		m_pHead = pNode;
	}
	else
	{
		RECORDNODE* pTemp = m_pHead;
		int i;
		for(i=0;i<iIndex-1;i++)
		{
			pTemp = pTemp->pNextNode;
		}
		pNode->pNextNode = pTemp->pNextNode;
		pTemp->pNextNode = pNode;
	}

	m_iRecordCount++;

	return RF_SUCCESS;
}

RFSTATUS CRecordFile::RemoveAt(int iIndex)
{
	if(iIndex > ((int)m_iRecordCount-1) || iIndex < 0)		//m_iRecordCount=0 is rejected either
	{
		return RF_BEYOND_RANGE;
	}

	RECORDNODE* pTemp = m_pHead;
	if(iIndex == 0)	
	{
		m_pHead = m_pHead->pNextNode;
		delete pTemp->pRecord;
		delete pTemp;

		if(m_pHead == NULL)			//Tail
			m_pTail = NULL;
	}
	else
	{
		int i;
		for(i=0;i<iIndex-1;i++)
		{
			pTemp = pTemp->pNextNode;
		}
		RECORDNODE* pDeleteNode = pTemp->pNextNode;
		pTemp->pNextNode = pDeleteNode->pNextNode;
		delete pDeleteNode->pRecord;
		delete pDeleteNode;

		if(pTemp->pNextNode == NULL)		//Tail
		{
			m_pTail = pTemp;
		}
	}

	m_iRecordCount--;

	return RF_SUCCESS;
}

int CRecordFile::CopyFile(char* strSource,char* strDest)
{
	FILE* pSource = fopen(strSource,"rb");
	FILE* pDest = fopen(strDest,"wb");

	if(pSource == NULL || pDest == NULL)
	{
		if(pSource != NULL)
			fclose(pSource);

		if(pDest != NULL)
			fclose(pDest);

		return 0;
	}

	char *pBuf = new char[10240];
	memset(pBuf,0,10240);
	//int hSource = _fileno(pSource);
	//int hDest = _fileno(pDest);
	int iReadCount;
	int iCopySize = 0;

	do
	{
		iReadCount = fread(pBuf,1, 10240, pSource);
		//iReadCount = read(hSource,pBuf,10240);
		iCopySize += iReadCount;
		if(iReadCount > 0)
		{
			fwrite(pBuf, 1, iReadCount, pDest );
			//write(hDest,pBuf,iReadCount);
		}
	}
	while(iReadCount > 0);

	fclose(pSource);
	fclose(pDest);
	delete pBuf;

	return iCopySize;
}

int CRecordFile::CreateEmptyFile(const char* pFileName, int nRecordSize)
{
	FILEHEAD head;
	memset(&head,0,sizeof(head));
	head.cVersion = 0x01;
	strcpy(head.OrgName,"CMB");
	head.cAppID = 0x01;
	RandomStr((char*)(head.RndKey),20);
	head.RndKeyLen = 20;
	head.iRecordCount =0;
	head.iRecordSize = nRecordSize;
	head.iFileLength = sizeof(FILEHEAD);
	head.iCheckSum = 0;

	FILE* hFile = fopen(pFileName, "wb");
	if(hFile == NULL) {
		return 1;
	}

	fwrite(&head,sizeof(FILEHEAD),1,hFile);
	fclose(hFile);
	return 0;
}

RFSTATUS CRecordFile::GetFileHeadInfo(FILEHEAD* pFileHead )
{
	if(pFileHead!=NULL)
	{
		memcpy(pFileHead,&m_fileHead,sizeof(FILEHEAD));
	}
	return RF_SUCCESS;
}

====================


#if !defined(RECORDFILE_H)
#define RECORDFILE_H

#define NULL	0
typedef void *HANDLE;

enum RFSTATUS
{
	RF_SUCCESS,					//Success
	RF_BEYOND_RANGE,			//Index out of legal range
	RF_OPEN_FILE_FAILED,		//Open data file failed
	RF_WRITE_FILE_FAILED,		//Write data file failed
	RF_DBFILE_ERROR,			//Database file was destroyed
	RF_FILE_NOT_MATCH,			//Specified file and it's records are not match
	RF_FAILED					//Failed due to other reason
};

struct FILEHEAD
{
	unsigned char			cVersion;
	char	        		OrgName[8];
	unsigned char			cAppID;
	unsigned int            RndKeyLen;         
	unsigned char           RndKey[20];
	unsigned int			iRecordSize;
	unsigned int			iRecordCount;
	unsigned int			iFileLength;
	int						iCheckSum;
};

struct RECORDNODE
{
	void*			pRecord;
	RECORDNODE*		pNextNode;
};

class CRecordFile
{
public:
	static int CreateEmptyFile(const char* pFileName,int nRecordSize);
	CRecordFile(char* pstrFileName,int iRecordSize);
	~CRecordFile();

	RFSTATUS ReadFile();
	RFSTATUS WriteFile() const;
	int GetSize() const;
	RFSTATUS RemoveAll();
	RFSTATUS GetAt(int iIndex,void* pRecord) const;
	RFSTATUS SetAt(int iIndex, void* pRecord);
	RFSTATUS Add(void* pRecord);
	RFSTATUS InsertAt(int iIndex,void* pRecord);
	RFSTATUS RemoveAt(int iIndex);
	RFSTATUS GetFileHeadInfo(FILEHEAD* pFileHead );

protected:
	int CopyFile(char* strSource,char* strDest);
private:
	HANDLE m_hMutex;
	char m_strFileName[256];
	unsigned int m_iRecordSize;
	unsigned int m_iRecordCount;
	bool m_bCopyed;
	RECORDNODE*	m_pHead;
	RECORDNODE* m_pTail;
	FILEHEAD m_fileHead;
};

#endif // !defined(RECORDFILE_H)
