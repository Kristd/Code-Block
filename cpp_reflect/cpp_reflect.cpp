#include <stdio.h>
#include <stdlib.h>

class Base {
public:
	Base() {
		printf("CalssBase\n");
	}
};


class A : public Base {
public:	
	A() {
		printf("CalssA\n");
	}
};


class create_A {
public:
	static Base* newInst() {
		return new A();
	}
};


#define CREATE(p, name) \
p = create_##name::newInst(); \
printf("%s\n", #name);

int main(int argc, char** argv) {
	Base* p;
	CREATE(p, A);
	delete p;
	return 0;
}