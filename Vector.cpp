//
// Created by zygisau on 27/04/2019.
//

#include "Vector.h"

Vector& Vector::operator=(const Vector& v) {
    // Savęs aptikimas
    if (&v == this) return *this;

    double* newElem = new double(v.sz);
    for(int i=0; i<v.sz; i++) // Kopijavimas TODO: std:copy
        newElem[i] = v.elem[i];

    delete[] elem;
    elem = v.elem;
    sz = v.sz;

    return *this;
}
