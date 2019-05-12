//
// Created by zygisau on 27/04/2019.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
template <typename _T>
class Vector {
private:
    unsigned int _sz;
    unsigned int _capac;
    _T* _elem;

    void _change_size_and_capacity(const unsigned int &__sz, const unsigned int &__capac) {
        _sz = __sz;
        _capac = __capac;
    }
public:
    Vector() : _sz(0), _capac(0), _elem(new _T[_sz]) {};
    Vector(unsigned int size, _T val) : _sz(size), _capac(size), _elem(new _T[size]) { std::fill_n(_elem, _sz, val); }
    Vector(std::initializer_list<_T> _list) : _sz(_list.size()), _capac(_list.size()), _elem(new _T[_list.size()]) { std::copy(_list.begin(), _list.end(), _elem); }
    explicit Vector(unsigned int _sk) : _sz(_sk), _capac(_sk), _elem(new _T[_sk]) {};
    Vector(const Vector<_T>& v) : _elem{new _T[v._sz]}, _sz{v._sz}, _capac{v._capac} {
        std::cout << "Copy c-tor" << std::endl;
        std::copy(v.begin(), v.back(), (*this).begin());
    }
    Vector(Vector&& v) noexcept : _sz{v._sz}, _capac{v._capac} , _elem{v._elem} { v._elem = nullptr; v._sz=0; v._capac=0; std::cout << "Move c-tor" << std::endl; }
    ~Vector() { delete[] _elem; }
    unsigned int size() const {return _sz;}

    _T& operator[](int i) {
        if (i < 0 || i >= _sz)
            throw std::out_of_range { "Vector::operator[]" };
        return _elem[i];
    }

    Vector<_T>& operator=(const Vector<_T>& v) {
        std::cout << "Copy operator" << std::endl;
        // Savęs aptikimas
        if (&v == this) return *this;

        _T* newElem = new _T[v._sz];
//        for(int i=0; i<v._sz; i++)
//            newElem[i] = v._elem[i];
        std::copy(v.begin(), v.back(), &newElem[0]);

        delete[] _elem;
        _elem = v._elem;
        _sz = v._sz;
        _capac = v._capac;

        return *this;
    };
    Vector<_T>& operator=(Vector<_T>&& v) noexcept {
        std::cout << "Move operator" << std::endl;

        // Savęs aptikimas
        if( &v == this)
            return *this;

        delete[] _elem;
        _elem = v._elem;
        _sz = v._sz;
        _capac = v._capac;

        v._elem = nullptr;
        v._sz = 0;
        v._capac = 0;

        return *this;
    };

    _T * begin() const {
        return &_elem[0];
    };
    _T * back() const {
        return &_elem[_sz-1];
    };
    _T * end() const {
        return &_elem[_sz];
    };
    unsigned int capacity() const {
        return _capac;
    };
    void reserve(unsigned int _n) {
        // If n is greater than the current vector capacity
        if(_n > _capac) {
            _T* _temp = _elem;
//            std::copy(&_elem[0], &_elem[_sz], &_temp[0]);

//            delete[] _elem;
            _elem = new _T[_n]; // the function causes the container to reallocate its storage increasing its capacity to n
            std::copy(&_temp[0], &_temp[_sz], &_elem[0]);

            _change_size_and_capacity(_sz, _n); // size remains the same
        }
    }
    void resize(unsigned int _n) {
        // @throw  std::length_error  If @a n exceeds @c max_size().
//        if (_n > )
//            throw std::length_error("Vector::resize");
        // If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
        _T* _temp;
        if (_n < _sz) {
            _temp = new _T[_n];
            std::copy(&_elem[0], &_elem[_n], &_temp[0]);

            delete[] _elem;
            _elem = _temp;

            _change_size_and_capacity(_n, _n);
        }

        //  If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.
        if (_n > _sz) {
            // If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
            if (_n > _capac) {
                reserve(_n);
                std::fill(&_elem[_sz], &_elem[_n], 0);
                _change_size_and_capacity(_n, _n);
            } else {
                _temp = _elem;
                _elem = new _T[_n];

                std::copy(&_temp[0], &_temp[_sz], &_elem[0]);
                std::fill(&_elem[_sz], &_elem[_n], 0);

                _change_size_and_capacity(_n, _capac);
            }
        }
    }
    void push_back(_T _val) {
        // If vector is still capable to store one more value
        if (_sz+1 <= _capac) {
            _elem[_sz] = _val;
            _sz++;
        } else { // If new value exceeds capacity of the vector
            reserve(_capac + 200);
            _elem[_sz] = _val;
            _sz++;
        }
    }
    void shrink_to_fit() {
        if (_capac > _sz) {
            _T* _temp = new _T[_sz];
            std::copy(&_elem[0], &_elem[_sz], &_temp[0]);

            delete[] _elem;
            _elem = _temp;

            _change_size_and_capacity(_sz, _sz);
        }
    }
    void clear() {
        delete[] _elem;
        _elem = new _T[0];
        _change_size_and_capacity(0, 0);
    }
};


#endif //VECTOR_VECTOR_H
