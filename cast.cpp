#include <stdio.h>

class A {
    int aa;
    virtual void f1() {
        return;
    }
};

class B : public A {
    char bb[10];
    virtual void f1() {
        return;
    }
};

int main() {
    A *a = new A();
    B *b1 = static_cast<B*>(a);
    //B *b1 = dynamic_cast<B*>(a);
    printf("%p \n", b1);

    return 0;
}
