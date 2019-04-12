#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <map>
using namespace std;



int calcMinNumberByAnchorId(std::list<std::pair<int, int> > numberList) {
	if (numberList.size() == 0) {
		return -1;
	}

	
	map<int, int> singleNumberMap;
	std::pair<map<int, int>::iterator, bool> ret;

	for (std::list<std::pair< int,  int> >::iterator it = numberList.begin(); it != numberList.end(); it++) {
		 int uid = it->first;
		 int num = it->second;

		ret = singleNumberMap.insert(std::pair<int, int>(num, uid));
		if (!ret.second) {
			//删除重复数字
			singleNumberMap.erase(num);
		}
	}

	map< int,  int>::iterator lastIt;
	int smallest = 10001;

	//最小值
	for (map<int, int>::iterator it = singleNumberMap.begin(); it != singleNumberMap.end(); ++it) {
		int number = it->first;

		if (it == singleNumberMap.begin()) {
			smallest = number;
			lastIt = it;
			continue;
		}

		if (number < smallest) {
			smallest = number;
			lastIt = it;
		}
	}

	 int lastNumber = lastIt->first;
	return lastNumber;
}


int main(int argc, char** argv) {
	std::list<std::pair< int,  int> > numberList;
	srand(time(0));

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 50; i++) {
			int n = rand()%20;
			numberList.push_back(make_pair(i, n));
		}

		for (std::list<std::pair< int,  int> >::iterator it = numberList.begin(); it != numberList.end(); ++it) {
			printf("%u ", it->second);
		}

		int ret = calcMinNumberByAnchorId(numberList);

		printf("\nret:%u\n\n", ret);
		numberList.clear();
	}

	return 0;
}


