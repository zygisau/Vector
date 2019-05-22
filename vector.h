//
// Created by zygisau on 27/04/2019.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>
template <typename _T>
class vector {
private:
    unsigned int _sz;
    unsigned int _capac;
    _T* _elem;

    void _change_size_and_capacity(const unsigned int &__sz, const unsigned int &__capac) {
        _sz = __sz;
        _capac = __capac;
    }
    void _insert_value_in_pos(const _T _val[], int _ind, int _arr_sz=1) {
        if(_sz != 0) {
            int _temp_arr_sz = _sz - _ind;
            _T _temp[_temp_arr_sz]; //FIXME: dynamic!
            _sz += _arr_sz;

            std::copy(&_elem[_ind], &_elem[_sz], &_temp[0]);

            if (_arr_sz == 1)
                _elem[_ind] = _val[0];
            else
                std::copy(&_val[0], &_val[_arr_sz], &_elem[_ind]);

            if (_temp_arr_sz == 1)
                _elem[_ind + _temp_arr_sz] = _temp[0];
            else
                std::copy(&_temp[0], &_temp[_temp_arr_sz], &_elem[_ind + _arr_sz]);
        } else {
            std::cout << "NO" << std::endl;
            std::copy(&_val[0], &_val[_arr_sz], &_elem[0]);
        }
    }
public:
    vector() : _sz(0), _capac(0), _elem(new _T[_sz]) {};
    vector(unsigned int size, _T val) : _sz(size), _capac(size), _elem(new _T[size]) { std::fill_n(_elem, _sz, val); }
    vector(std::initializer_list<_T> _list) : _sz(_list.size()), _capac(_list.size()), _elem(new _T[_list.size()]) { std::copy(_list.begin(), _list.end(), _elem); }
    explicit vector(unsigned int _sk) : _sz(_sk), _capac(_sk), _elem(new _T[_sk]) {};
    vector(const vector<_T>& v) : _elem{new _T[v._sz]}, _sz{v._sz}, _capac{v._capac} {
//        std::cout << "Copy c-tor" << std::endl;
        std::copy(v.begin(), v.end(), (*this).begin());
    }
    vector(vector&& v) noexcept : _sz{v._sz}, _capac{v._capac} , _elem{v._elem} { v._elem = nullptr; v._sz=0; v._capac=0; std::cout << "Move c-tor" << std::endl; }
    ~vector() { delete[] _elem; }
    unsigned int size() const {return _sz;}

    _T& operator[](int i) {
        if (i < 0 || i >= _sz)
            throw std::out_of_range { "vector::operator[]" };
        return _elem[i];
    }

    vector<_T>& operator=(const vector<_T>& v) {
//        std::cout << "Copy operator" << std::endl;
        // Savęs aptikimas
        if (&v == this) return *this;

        _T* newElem = new _T[v._sz];
//        for(int i=0; i<v._sz; i++)
//            newElem[i] = v._elem[i];
        std::copy(v.begin(), v.end(), &newElem[0]);

        delete[] _elem;
        _elem = v._elem;
        _sz = v._sz;
        _capac = v._capac;

        return *this;
    };
    vector<_T>& operator=(vector<_T>&& v) noexcept {
//        std::cout << "Move operator" << std::endl;

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
    _T back() const {
        return _elem[_sz-1];
    };
    _T * end() const {
        return &_elem[_sz];
    };
    unsigned int capacity() const {
        return _capac;
    };
    void reserve(int _n) {
        // If n is greater than the current vector capacity

        if(_n > _capac) {
            _T* _temp = _elem;

            _elem = new _T[_n]; // the function causes the container to reallocate its storage increasing its capacity to n
            std::copy(&_temp[0], &_temp[_sz], &_elem[0]);

            _change_size_and_capacity(_sz, _n); // size remains the same
        }
    }
    void resize(unsigned int _n) {
        // @throw  std::length_error  If @a n exceeds @c max_size().
//        if (_n > )
//            throw std::length_error("vector::resize");
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
            this->reserve(std::round(1 + _capac * 1.5));
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
    void pop_back() {
        delete &_elem[_sz-1];

        _change_size_and_capacity(_sz-1, _capac);
    }

    _T* insert(const _T* _it_pos, const _T& _val) {
        int _ind;
        if (_sz == 0) {
            reserve(1);
        }
        _ind = _it_pos - this->begin();

        if (_ind >= _sz && _sz != 0)
            throw std::out_of_range { "Vector::insert, possession of invalid memory" };

        if(_sz+1 <= _capac) { // If capacity is big enough for value insertion
            _T _temp[1] = {_val};
//            _sz++;
            _insert_value_in_pos(_temp, _ind);
        } else { // if size with new value surpasses vector's capacity
            reserve(_sz+1);
            _T _temp[1] = {_val};
//            _sz++;
            _insert_value_in_pos(_temp, _ind);
        }
        return &_elem[_ind];
    }
    _T* insert(_T* _it_pos, _T* _it_first, _T* _it_last) {
        int _ind;
        if (_sz == 0) {
            reserve(1);
            _ind = 0;
        } else {
            _ind = _it_pos - this->begin();
        }

        if (_ind >= _sz && _sz != 0)
            throw std::out_of_range { "Vector::insert, possession of invalid memory" };

        int _dist = _it_last - _it_first;
        _T* _temp = new _T[_dist];
        std::copy(_it_first, _it_last, &_temp[0]);
        if(_sz+_dist <= _capac) {
            _insert_value_in_pos(_temp, _ind, _dist);
        } else {
            reserve(_sz + _dist);
//            _sz += _dist;
            _insert_value_in_pos(_temp, _ind, _dist);
        }
        delete[] _temp;
        return &_elem[_ind];
    }

    _T* erase(_T* _it_first, _T* _it_last) {
        if ((_it_first < this->begin() || _it_first >= this->end())
            || (_it_last < this->begin() || _it_last > this->end()))
            throw std::out_of_range { "Vector::erase, possession of invalid memory" };

        int _ind = _it_first - this->begin();
        int _dist = _it_last - _it_first;
        _T* _temp = new _T[_capac];

        int _new_sz = 0;
        if(_it_first != &_elem[0]) {
            std::copy(&_elem[0], _it_first, &_temp[0]);
            _new_sz += _ind;
        }
        if(_it_last != &_elem[_sz]) {
            std::copy(_it_last, &_elem[_sz], &_temp[_new_sz]);
            _new_sz += _sz - _dist - _ind;
        }

        delete[] _elem;
        _elem = _temp;
        _change_size_and_capacity(_new_sz, _capac);

        return &_elem[_ind];
    }
};

#endif //VECTOR_VECTOR_H
