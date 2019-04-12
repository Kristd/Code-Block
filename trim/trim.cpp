#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stddef.h>
using namespace std;

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {return !std::isspace(ch);} ) );
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {return !std::isspace(ch);} ).base(), s.end() );
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

int main() {
    string str = " a sdddff  sdd   ";
    trim(str);
    printf("str:|%s|\n", str.c_str());

	return 0;
}
