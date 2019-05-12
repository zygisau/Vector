#include "Vector.h"
#include <vector>

int main() {
//    Vector<double> v1(10, 4.0);
//    Vector<double> v2(11, 7.0);
//    Vector<double> v3 = v2;
////    for (int i = 0; i<v1.size(); i++) {
////        std::cout << v1[i] << " ";
////    }
//    std::copy(v1.begin(), v1.back(), v2.begin());
////    for (int i = 0; i<v2.size(); i++) {
////        std::cout << v2[i] << " ";
////    }
//    Vector<int> v4{10, 9};
//    v4.reserve(200000);
//    Vector<int> v5 {10, 9, 8, 7, 6, 5, 4, 3, 2};
////    for (int i = 0; i<v5.size(); i++) {
////        std::cout << v5[i] << " ";
////    }
//    std::cout << std::endl;

    Vector<int> v6 {10, 9, 8, 7, 6, 5, 4, 3, 2, 4};
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

    v6.reserve(2000);
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
    v6. push_back(34);
    for (int i = 0; i<v6.size(); i++) {
        std::cout << v6[i] << " ";
    }
    std::cout << std::endl;
    std::cout << v6.capacity() << std::endl;
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
 * TODO: insert
 * TODO: erase
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