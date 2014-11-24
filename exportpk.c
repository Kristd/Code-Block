
#include <stdlib.h>
#include <stdio.h>
#include "union_rsapair_key"
#include "union_common_keydef.h"

/*
功能：从RSA密钥对表中，读取一个密钥。
输入参数：
pkeyIndex，指向一个RSA密钥对的指针。
输出参数：
pkey，读出的RSA密钥对。注：这个指针指向的密钥缓冲，必须预先分配。
返回值：
<0，函数执行失败，值为失败的错误码
>=0，函数执行成功。
*/
//int UnionReadRsaPairKeyAnyway(PUnionKeyIndex pkeyIndex,PUnionRsaPairKey pkey);

int main(int argc, char* argv[]) {
	int ret = -9999;
	char app_name[16+1];
	char term_name[32+1];
	TUnionRsaPairType type;

	memset();
	memset();
	memset();

	PUnionKeyIndex pkIndx = NULL;

	memset(pkIndx->app_name, 0, sizeof(pkIndx->app_name));
	memset(pkIndx->term_name, 0, sizeof(pkIndx->term_name));

	PUnionRsaPairKey pRSAkey = NULL;
	memset(pRSAkey, 0, sizeof(TUnionRsaPairKey));

	printf("Input PK attribute:");
	sprintf();
	sprintf();
	sprintf();

	UnionReadRsaPairKeyAnyway(pkIndx, pRSAkey);
	printf("Public Key String: %s\n", pRSAkey->pkValue);

	return 0;
}


