#include <pthread.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <sys/time.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct _parms {
	void* m_handler;
	int m_id;
	int m_thd_id;
}parms;


typedef int (*Init)(const char* dllCfgPath);
typedef int (*Release)();
typedef short (*LoadWorkKey)(const char* devId, const char* bankNo, const char* branchNo, 
	const char* mkChkValue, const char* smmkChkValue, char* wkeyPkg, int* wkpLen, char* wkeySM4Pkg, int* wkSM4pLen);
typedef int (*MakeMAC_SM4)(const char* devId, const char* bankNo, const char* branchNo,
	   const char *data,int data_len, char *mac);
typedef int (*MACVerify_SM4)(const char *devId, const char* bankNo, const char* branchNo,
	   const char *data, int data_len, const char *mac);
typedef int (*DecData_SM4)(const char* devId, const char* bankNo, const char* branchNo,
	   unsigned char* pInData, int nInLen, unsigned char* pOutData, int* nOutLen);
typedef int (*PINTranslate_SM4)(const char *devId, const char* bankNo, const char* branchNo,
	   char *pin, int pin_format, char *pan, char *opin_by_zpk, int *olen);
typedef int (*MACTranslate_SM4)(const char* devId, const char* bankNo, const char* branchNo,
	   const char *data, int data_len ,char *mac);
	

void* loadLib(void** handler) {
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start, NULL);
	printf("[loadLib]INFO\tstart:%d %d\n", start.tv_sec, start.tv_usec);
	
	*handler = dlopen("./libPosTransApp.so", RTLD_LAZY);
	if(*handler == NULL) {
		printf("[loadLib]ERROR\tLoad libPosTransApp failed.\n");
	}
	else {
		printf("[loadLib]INFO\tLoad libPosTransApp success.\n");
	}
	
	gettimeofday(&end, NULL);
	printf("[loadLib]INFO\tend:%d %d\n", end.tv_sec, end.tv_usec);
	
	return NULL;
}


void* makeMAC_SM4(void* args) {
	struct timeval start;
	struct timeval end;
	int ret = -1;
	int tradeNum = 500;
	int i = 0;
	char* keybuf48 = NULL;
	
	parms* m_args = (parms*)args;
	
	void* handler = m_args->m_handler;
	int id = m_args->m_id;
	int thd_id = m_args->m_thd_id;
	
	//gettimeofday(&start, NULL);
	//printf("[makeMAC_SM4]INFO\t[id=%d|thread_id=%d]LoadWorkKey start:%d %d\n", id, thd_id, start.tv_sec, start.tv_usec);
	
	pthread_mutex_lock(&mutex);
	printf("[makeMAC_SM4]INFO\t[id=%d|thread_id=%d]pthread_mutex_lock\n", id, id);
	
	MakeMAC_SM4 makeMAC_SM4 = (MakeMAC_SM4)dlsym(handler, "MakeMAC_SM4");
	if(makeMAC_SM4 == NULL) {
		printf("[makeMAC_SM4]ERROR\tmakeMAC_SM4 is NULL\n[%s]", dlerror());
	}
	else {
		printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]makeMAC_SM4 init success\n", id, i);
	}

	pthread_mutex_unlock(&mutex);
	printf("[makeMAC_SM4]INFO\t[id=%d|thread_id=%d]pthread_mutex_unlock\n", id, id);
	
	unsigned char WA3[] = {
	"0200485a453132303035303030303030303020150812161529 \
	4779450000010103a6e800a12149010300f932254231110025 \
	45311200254232110025453213002546461533303833333031 \
	30373432483030340025464616b9ccbbb020504f5300254646 \
	14485a453132303035002546460146464646002546461fd5d0 \
	c9ccd2f8d0d00025464620d5d0c9ccd2f8d0d0002546461730 \
	333038303030300025464602363232352038382a2a202a2a2a \
	2a2033373338002546460a323031352f30382f31322031363a \
	31353a32390025464609343737393435002546460831353038 \
	3132303939363832002546461d202020202020002546461831 \
	35303831320025464607362e3636d4aa002546461b00254646 \
	2900254646100025464629002546461b00"
	};
	
	while(1) {
		gettimeofday(&start, NULL);
		printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]makeMAC_SM4 start:%d %d\n", id, i, start.tv_sec, start.tv_usec);
		
		keybuf48 = new char[256];
		memset(keybuf48, 0, 256);
		int size48 = 256;
	
		//ret = loadworkkey("HZE12005", "0571", "000000", "C9CCEA4163874701", NULL, keybuf48, &size48, NULL, NULL);
	
		ret = makeMAC_SM4("HZE12005", "0571", "000000", (char*)WA3, 292, keybuf48);
		if(ret != 0) {
			printf("[makeMAC_SM4]ERROR\t makeMAC_SM4 failed, ret: %d\n", ret);
		}
		else {
			printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]makeMAC_SM4 success\n", id, i);
		}
			
		if(keybuf48 != NULL) {
			delete[] keybuf48;
			keybuf48 = NULL;
		}
		
		//pthread_mutex_unlock(&mutex);
		//printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]pthread_mutex_unlock\n", id, i);
		
		i++;
		
		gettimeofday(&end, NULL);
		printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]makeMAC_SM4 end:%d %d\n", id, i, end.tv_sec, end.tv_usec);
		
		usleep(1000 * 250);
	}
	
	//gettimeofday(&end, NULL);
	//printf("[makeMAC_SM4]INFO\t[id=%d|trade_id=%d]LoadWorkKey end:%d %d\n", id, thd_id, end.tv_sec, end.tv_usec);
	
	pthread_exit(0);
	return NULL;
}


void* maxthread(void*) {	//max = 2156
	pthread_exit(0);
	return NULL;
}


int main() {
	const int threadNum = 100;
	int ret = -1;
	int i = 0;
	void* handler = NULL;
	pthread_t pid[threadNum];
	parms* args = NULL;
	
	/* Load libPosTransApp */
	loadLib(&handler);
	if(handler == NULL) {
		printf("[main]ERROR\tHandler is NULL.\n");
		return -1;
	}
	else {
		printf("[main]INFO\tHandler value:%d\n", handler);
	}
	
	/*Init func && Release func*/
	Init init = (Init)dlsym(handler, "Init");
	if(init == NULL) {
		printf("init is NULL\n[%s]", dlerror());
	}	   
	
	Release release = (Release)dlsym(handler, "Release");
	if(release == NULL) {
		printf("release is NULL\n[%s]", dlerror());
	}
	
	/* Init env */
	ret = init("./natm/");
	if(ret != 0) {
		printf("[main]ERROR\tinit failed.\n", ret);
	}
	else {
		printf("[main]]INFO\tinit success.\n");
	}
	
	
	/* Run makeMAC_SM4ing */
	for(i = 0; i < threadNum; i++) {
		//ret = pthread_create(&pid[i], NULL, maxthread, NULL);
		
		args = new parms();
		args->m_handler = handler;
		args->m_id = i;
		args->m_thd_id = i;
		
		ret = pthread_create(&pid[i], NULL, makeMAC_SM4, (void*)args);
		
		if(ret != 0) {
			printf("[main]ERROR\t[%d]create thread[%d] failed.ret:%d\n", i, pid[i], ret);
		}
		else {
			printf("[main]INFO\t[%d]thread:%d create\n", i, pid[i]);
		}
		
		if(args) {
			delete args;
			args = NULL;
		}
		
		//sleep(4.5);
	}
	
	/* 
		Release env 
		wait all the thread exit
	*/
	for(int i = 0; i < threadNum; i++) {
		pthread_join(pid[i], NULL);
	}
	printf("[main]Main Proc exit.\n");
	
	//pthread_mutex_destroy(&mutex);
	release();
	dlclose(handler);
	
	return 0;
}




