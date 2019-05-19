#include "vector.h"
#include <vector>

int main() {
//    vector<double> v1(10, 4.0);
//    vector<double> v2(11, 7.0);
//    vector<double> v3 = v2;
////    for (int i = 0; i<v1.size(); i++) {
////        std::cout << v1[i] << " ";
////    }
//    std::copy(v1.begin(), v1.back(), v2.begin());
////    for (int i = 0; i<v2.size(); i++) {
////        std::cout << v2[i] << " ";
////    }
//    vector<int> v4{10, 9};
//    v4.reserve(200000);
//    vector<int> v5 {10, 9, 8, 7, 6, 5, 4, 3, 2};
////    for (int i = 0; i<v5.size(); i++) {
////        std::cout << v5[i] << " ";
////    }
//    std::cout << std::endl;

    vector<int> v6 {10, 9, 8, 7, 6, 5, 4, 3, 2, 4};
    v6.resize(15);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;

//    v6.resize(50);
//    for (int i = 0; i<v6.size(); i++) {
//        std::cout << v6[i] << " ";
//    }
//    std::cout << std::endl;
    v6.resize(10);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;

    v6.reserve((int)2000 + v6.size() * 1.5);
//    for (int i = 0; i<v6.size(); i++) {
//        std::cout << v6[i] << " ";
//    }
//    std::cout << std::endl;
    v6.resize(20);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;
    v6.shrink_to_fit();
    v6.push_back(34);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;
    std::cout << v6.size() << std::endl;
    std::cout << v6.capacity() << std::endl;
    vector<int> v7 {10, 9, 8, 7, 6, 3, 7, 8, 34, 222};
    std::cout << v7.size() << std::endl;
    std::cout << v7.capacity() << std::endl;
    v6.pop_back();
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl << v6.back() << std::endl;
    v6.insert(&v6[5], 80);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;
    v7.insert(&v7[5], 1000);
    for (int i = 0; i<v7.size(); i++) {
        std::cout << v7[i] << " ";
    }
    std::cout << std::endl;
    std::cout << *(v7.insert(&v7[9], v6.begin()+1, v6.begin()+5)) << std::endl;
    for (int i = 0; i<v7.size(); i++) {
        std::cout << v7[i] << " ";
    }
    std::cout << std::endl;
    v7.erase(v7.begin()+5, v7.begin()+10);
    for (int i = 0; i<v7.size(); i++) {
        std::cout << v7[i] << " ";
    }
    vector<double> v8;
    v8.push_back(12.6);
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