#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    time_t now = time(0);
    long a = 3000000000UL-now;
    long b = 3000000000-now;

    cout << a << endl;
    cout << b << endl;

    std::vector<string> vec;
    std::string str("heloo");
    vec.push_back(str);

    printf("%u\n", vec.size());

    return 0;
}
