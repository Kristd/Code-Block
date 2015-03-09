#include "SocketCommunicator.h"
#include <errno.h>

SocketCommunicator::SocketCommunicator() {
	m_nSock = 0;
	m_nPort = 0;
	m_sHostname ="";
	m_nTimeout = 10;
	m_bConnect = false;
	m_bInit = false;
//	WSADATA wsaData;
//	if(WSAStartup(MAKEWORD(2,0), &wsaData) ==  0)
	m_bInit = true;
}

SocketCommunicator::~SocketCommunicator() {
	Close();
	if(m_bInit)	{
//		WSACleanup();
		m_bInit = false;
	}
}

void SocketCommunicator::Close() {
	if(!m_bConnect) {
		return ;
	}
	//closesocket(m_nSock);
	close(m_nSock);
	m_bConnect = false;
}

int SocketCommunicator::Connect(const string& sIP,int nPort,int nTimeout,int nMaxConnTime)
{
	int nRet = -99;
	//SOCKET socketfd = INVALID_SOCKET;
	int socketfd = INVALID_SOCKET;
	int len	= sIP.length();

	if(m_bInit == false)
		return 1;
	
	if ( len == 0 )
		return(2);

	if ( nPort == 0 )
		return(3);

	struct sockaddr_in host;
	bzero(&host, sizeof(host));
	//memset((void *)&host, 0, sizeof(host));
	host.sin_family = AF_INET;
	host.sin_port = htons(nPort);
	host.sin_addr.s_addr = inet_addr(sIP.c_str());

	//printf("KMC ADDR: %s:%d\r\n",sIP.c_str(),nPort);

    for(int nConnTime =0; nConnTime < max(nMaxConnTime,1); nConnTime++) {
		socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if(socketfd >= 0) {
			//int nRealTimeOut = max(m_nTimeout, nTimeout);
			//nRealTimeOut = 1000 * nRealTimeOut;
			int ret = -99;
			struct timeval timeout={10,0};
			ret = setsockopt(socketfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval));
			if(ret < 0) {
				printf("setsockopt SOL_SOCKET failed#1:%d, errno:%d\n", ret, errno);
				return ret;
			}
			ret = setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval));
			if (ret < 0) {
				printf("setsockopt SOL_SOCKET failed#2:%d, errno:%d\n", ret, errno);
				return ret;
			}
			int nsockopt = 1;
			ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, (char*)(&nsockopt), sizeof(int));
			if (ret < 0) {
				printf("setsockopt IPPROTO_TCP failed:%d, errno:%d\n", ret, errno);
				return ret;
			}
			/// set nonblocking socket
			unsigned long i	= 1;
			//if(SOCKET_ERROR  == ioctlsocket(socketfd, FIONBIO, (unsigned long *)&i)) {
			ret = fcntl(socketfd, F_SETFL, fcntl(socketfd, F_GETFL) & ~O_NONBLOCK);
			if(ret < 0) {
				printf("fcntl failed:%d, errno:%d\n", ret, errno);
				//closesocket(socketfd);
				close(socketfd);
				socketfd = INVALID_SOCKET;
				nRet = 5;
				continue;
			}
			
			int nSocketError = 0;
			ret = connect(socketfd, (struct sockaddr*)&host, sizeof(host));
			if(ret < 0) {
				//nSocketError = WSAGetLastError();
				//if((WSAEINPROGRESS != nSocketError) && (WSAEWOULDBLOCK != nSocketError))
				if(errno != EINPROGRESS && errno != EWOULDBLOCK ) {
					printf("connect failed, errno:%d\n", errno);		//mark
					//closesocket(socketfd);
					close(socketfd);
					socketfd = INVALID_SOCKET;
					nRet = 6;
					continue;
				}
				//sleep(10);
			}
			/// for nonblocking socket
			fd_set r_list;
			fd_set w_list;
			FD_ZERO(&r_list);
			FD_SET(socketfd, &r_list);
			memcpy((void*)&w_list, (void*)&r_list, sizeof(r_list));
			struct timeval tv;
			tv.tv_sec = 2;
			tv.tv_usec = 0;
			nSocketError = select(socketfd+1, (fd_set*) &r_list, (fd_set*) &w_list, NULL, &tv);
			if(nSocketError < 0) {
				//closesocket(socketfd);
				close(socketfd);
				socketfd = INVALID_SOCKET;
				nRet = 7;
				continue;
			}
			//time out
			if(0 == nSocketError) {
				//closesocket(socketfd);
				close(socketfd);
				socketfd = INVALID_SOCKET;
				nRet = 8;
				continue;
			}

			i = 0;
			//ioctlsocket(socketfd, FIONBIO, ( unsigned long * ) &i);
			//fcntl(socketfd, F_SETFL);		//mark
			////end of nonblocking socket
			break;
		}
		else {
			//create socket failed
			printf("Create socket failed%d\n", socketfd);
			return socketfd;
		}
	}

	if(socketfd < 0) {
		return nRet;
	}

    m_nSock = socketfd;
    m_nPort = nPort;
    m_sHostname = sIP;
    //m_nTimeout = nTimeout;
    m_bConnect = true;
	return(0);	
}

/*
 *  return value: 0 succ
 *              other failed 
 */
int SocketCommunicator::Communicate(const string sData, string& sRec) {
	if(!m_bConnect) {
		return 1;
	}
	
	int r = Send(sData);
	if(0 != r) {
		return 2*10+r;
	}

	//sleep(3);

	string sRecData = "";
	r = Receive(sRecData);
	
	if(0 != r) {
		return 3*10+r;
	}

	sRec = sRecData;
	return 0;
}

int SocketCommunicator::Send(const string& sData) {
	if(!m_bConnect) {
		return 1;
	}
	if(sData.length() <= 0) {
		return 2;
	}

	int nDataLen = sData.length();
	char* pBuf = new char[nDataLen+8];
	
	if(pBuf == NULL) {
		return 3;
	}
	
	memset(pBuf, 0, nDataLen+8);
	memcpy(pBuf, sData.c_str(), nDataLen);
	//int r = write(m_nSock, pBuf, nDataLen);
	int r = send(m_nSock, pBuf, nDataLen, 0);
	//if(r != nDataLen)

	if(r < 0) {
		printf("socket send data failed:%d\n", r);
		return 4;
	}

	delete pBuf;
	return 0;	
}

int SocketCommunicator::Receive(string &sRec) {
	if(!m_bConnect) {
		return 1;
	}
	string sRet = "";
	char szRecBuf[10240];
	int nRecBufLen = sizeof(szRecBuf);
	int r = 0;
	do{
		memset(szRecBuf,0,nRecBufLen);
		//r = read(m_nSock,szRecBuf,nRecBufLen);
		r = recv(m_nSock,szRecBuf,nRecBufLen,0);
		if(r > 0) {
			sRet += string(szRecBuf,r);
		}
	}while(r > 0);
	if(sRet.length() <=0) {
		return 2;
	}
	sRec = sRet;
	return 0;
}
