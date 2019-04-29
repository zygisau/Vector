//
// Created by zygisau on 27/04/2019.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <algorithm>

class Vector {
private:
    unsigned int sz;
    double* elem;
public:
    Vector() : sz(0), elem(new double[sz]) {};
    Vector(int size, double val) : sz(size), elem(new double(size)) { std::fill_n(elem, sz, val); }
    Vector(const Vector& v) : elem{new double[v.sz]}, sz{v.sz} {
        for(int i=0; i!=sz; ++i) elem[i] = v.elem[i];
    } // TODO: std:copy(v.begin(), v.back(), this.begin()) begin, back, end
    ~Vector() { delete[] elem; }
    int size() const {return sz;}

    double& operator[](int i) {
        if (i < 0 || i >= size())
            throw std::out_of_range { "Vector::operator[]" };
        return elem[i];
    }
    Vector& operator=(const Vector& v);
//    int& operator<<(const double& v);
};


#endif //VECTOR_VECTOR_H
