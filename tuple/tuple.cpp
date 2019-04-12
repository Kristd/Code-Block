#include <tuple>

std::tuple<int, int, int> divide(int dividend, int divisor) {
    return  std::make_tuple(dividend / divisor, dividend % divisor, dividend + divisor);
}

#include <iostream>

int main() {
    using namespace std;

    int quotient, remainder, sum;

    tie(quotient, remainder, sum) = divide(14, 3);

    cout << quotient << ',' << remainder << ','<< sum << endl;

    auto result = divide(14, 3);

    cout << std::get<0>(result) << ',' << std::get<1>(result) << ','<< std::get<2>(result) << endl;
}

// #include <tuple>

// std::tuple<int, int> divide(int dividend, int divisor) {
//     return  {dividend / divisor, dividend % divisor};
// }

// #include <iostream>

// int main() {
//     using namespace std;

//     auto [quotient, remainder] = divide(14, 3);

//     cout << quotient << ',' << remainder << endl;
// }