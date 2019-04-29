/* Vector klasė
 TODO: unsigned int size
 TODO: pointer to dynamic array
 TODO: constructor (), (Vector), (size, val),
 TODO: ~destructor
 TODO: operator []
 TODO: operator =
 TODO: r5? */
#include "Vector.h"

int main() {
    Vector v1{10, 4.0};
    Vector v2{v1};
    Vector v3 = v2;
    double a = v1[0];
    std::cout << &a << " " << &v1[0] << std::endl;
    std::cout << v1[0] << std::endl;
    return 0;
}