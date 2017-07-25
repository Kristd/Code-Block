
#ifndef _REVERVE_H_
#define _REVERVE_H_

int reverse(int x) {
	__int64 ret = 0;

	while(x) {
		ret = ret*10 + x%10;

		if(ret > 2147483647 || ret < -2147483647) {
			return ret > 0? 2147483647 : -2147483647;
		}

		x = x/10;
	}

	return ret;
}



#endif /* REVERVE_H_ */
