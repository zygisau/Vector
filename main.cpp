#include<iostream>
#include "./NewVector/vector.h"
//#include <vector>
#include<algorithm>
int main() {
    unsigned int sz = 10;
    vector<int> v2, v3;
    for (int i = 1; i <= sz; ++i) {
        v2.push_back(i);
        v3.push_back(i+20);
    }
//    v2.insert(v2.end()-1, v3.begin(), v3.begin()+5);
    vector<int> v4;
    v4.insert(v4.begin(), v3.begin(), v3.end());
    for (int i = 0; i<v4.size(); i++) {
        std::cout << v4[i] << " ";
    }
    std::cout << std::endl;
//    v4.erase(v4.begin()+1, v4.end());
    std::sort(v4.begin(), v4.end());
    std::cout << v4.size() << std::endl;
    v4.pop_back();
    std::cout << v4.size() << std::endl;
    for (int i = 0; i<v4.size(); i++) {
        std::cout << v4[i] << " ";
    }
    std::cout << std::endl;
//    vector<double> v1(10, 4.0);
//    vector<double> v2(11, 7.0);
//    vector<double> v3 = v2;
//    for (int i = 0; i<v1.size(); i++) {
//        std::cout << v1[i] << " ";
//    }
//    vector<int> v6 {10, 9, 8, 7, 6, 5, 4, 3, 2, 4};
//    std::cout << v6.size() << std::endl;
//    for (int i = 0; i<v6.size(); i++) {
//        std::cout << v6[i] << " ";
//    }
//    std::cout << std::endl;

    return 0;
}


/*
 * TODO: assign
 * TODO: get_allocator
 * TODO: at
 * TODO: front
 * TODO: cbegin
 * TODO: cend
 * TODO: rbegin crbegin
 * TODO: rend crend
 * TODO: empty
 * TODO: size
 * TODO: max_size
 *                  TODO: insert
 *                  TODO: erase
 * TODO: pop_back
 * TODO: swap
 * TODO: operator==
        operator!=
        operator<
        operator<=
        operator>
        operator>=
 * TODO: std::swap
*/