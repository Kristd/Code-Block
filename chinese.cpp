#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

bool formatAnchorNickName(std::string &in, std::string &out) {
    unsigned int count = 0;

    for (unsigned int i = 0; i < in.length(); i++) {
        if ((in[i] & 0x80) == 0) {
            out.push_back(in[i]);
        }
        else {
            out.push_back(in[i]);
            out.push_back(in[i+1]);
            out.push_back(in[i+2]);
            i = i+2;
        }

        count++;
        if (count == 5 && i != in.length()-1) {
            out = out + "...";
            break;
        }
    }

    return true;
}

int main() {
    string in = "tai太阳yang";
    string out("");

    formatAnchorNickName(in, out);
    cout << "out: " << out << endl;

    return 0;
}
