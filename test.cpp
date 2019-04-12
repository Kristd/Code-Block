#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stddef.h>
using namespace std;

struct Person 
{
    char name[32];
    char lastn[32];
    size_t year;
};

struct S
{
	char c;
	size_t i;
	float f;
};

void init_pers(struct Person* p, const char* n, const char* ln, size_t y)
{
    strcpy(p->name, n);
    strcpy(p->lastn, ln);
    p->year = y;
}

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
	struct Person f;
	init_pers(&f, "Alan", "Wake", 1995);

	printf("First field: %s\n", (char*)&f); // prints 'Alan'
	printf("Second field: %s\n", (char*)&f + 32); // prints 'Wake'
	printf("Third field: %lu\n", *((size_t*) (((char*) &f) + 64))); // prints '6422317'
	printf("name:%p, lastn:%p, year:%p\n", f.name, f.lastn, &f.year);

	printf("the first element is at offset %zu\n", offsetof(struct Person, name));
    printf("the second element is at offset %zu\n", offsetof(struct Person, lastn));
    printf("the third element is at offset %zu\n", offsetof(struct Person, year));

	printf("the first element is at offset %zu\n", offsetof(struct S, c));
    printf("the second element is at offset %zu\n", offsetof(struct S, i));
    printf("the third element is at offset %zu\n", offsetof(struct S, f));

    string str = " a sdddff  sdd   ";
    trim(str);
    printf("str:|%s|\n", str.c_str());

	return 0;
}
