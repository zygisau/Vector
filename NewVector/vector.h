//
// Created by zygisau on 20/05/2019.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H


#include<exception>
#include<iostream>
#include<iterator>
#include<memory>
#include <cmath>

using std::cout; using std::endl; using std::size_t; using std::allocator;

template <class _T>
class vector {
public:
    // typedefs
    typedef _T* iterator;
    typedef const _T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef const std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;
    typedef _T value_type;

    // constructors
    vector() { create(); }
    explicit vector(size_type _n, const _T& _val = _T{}) { create(_n, _val); }
    vector(std::initializer_list<_T> _list) { create(_list); }
    vector(const vector<_T>& _v) { create(_v.begin(), _v.end()); } // copy c-tor
    vector(vector<_T>&& _v) noexcept :
        _avail{_v._avail}, _limit{_v._limit} , _elem{_v._elem} { _v._elem = _v._avail = _v._limit = nullptr; } // move c-tor
    ~vector() { uncreate(); }

    // size
    size_type size() const { return _avail - _elem; }
    size_type capacity() const { return _limit - _elem; }
    bool empty() { return _elem == nullptr; }

    // operators
    _T operator[](size_type _n) {
        if ( _n > size() || _n < 0) throw std::out_of_range("operator[]: out of bounds");
        return _elem[_n];
    }
    const _T operator[](size_type _n) const {
        if ( _n > size() || _n < 0) throw std::out_of_range("operator[]: out of bounds");
        return _elem[_n];
    }
    vector<_T>& operator=(const vector<_T>& _v) {
        // Savęs aptikimas
        if (this == &_v) return *this;

        uncreate();
        create(_v.begin(), _v.end());
    }
    vector<_T>& operator=(vector<_T>&& _v) noexcept { // move operator
        // Savęs aptikimas
        if (this == &_v) return *this;

        delete[] _elem;
        _elem = _v._elem;
        _avail = _v._avail;
        _limit = _v._limit;

        _v._elem = _v._avail = _v._limit = nullptr;

        return *this;
    }
    bool operator==(const vector<_T>& _v2) {
        if(this->size() != _v2.size()) // compare sizes
            return false;

        for (int i=0; i<this->size(); i++) {// compare values
            if((*this)[i] != _v2[i]) return false;
        }

        return true;
    }
    bool operator!=(const vector<_T>& _v2) {
        return !((*this) == _v2);
    }
    bool operator<(const vector<_T>& _v2) {
        return std::lexicographical_compare(this->begin(), this->end(), _v2.begin(), _v2.end());
    }
    bool operator>(const vector<_T>& _v2) {
        return _v2 < (*this);
    }
    bool operator<=(const vector<_T>& _v2) {
        return !(_v2 < (*this));
    }
    bool operator>=(const vector<_T>& _v2) {
        return !((*this) < _v2);
    }

    // iterators/values returning functions
    iterator begin() { return _elem; }
    const_iterator begin() const { return _elem; }
    iterator end() { return _avail; }
    const_iterator end() const { return _avail; }
    value_type front() { return _elem; }
    const value_type front() const { return _elem; }
    value_type& back() { return *(end()-1); }
    const value_type back() const {
        iterator _it = _avail;
        return *(--_it); }
    reverse_iterator rbegin() {
        return reverse_iterator(_avail);
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(_avail);
    }
    iterator rend() {
        return reverse_iterator(_elem);
    }
    const_iterator rend() const {
        return const_reverse_iterator(_elem);
    }

    void push_back(const _T& _val) {
        if (_avail == _limit)
            grow();
        unchecked_append(_val);
    }

    // reserve
    void reserve(size_type _n) {
        if (_n > capacity()) {
            iterator _new_elem = alloc.allocate(_n);
            iterator _new_avail = std::uninitialized_copy(_elem, _avail, _new_elem);

            // delete data
            uncreate();

            // update pointers
            _elem = _new_elem;
            _avail = _new_avail;
            _limit = _elem + _n;
        }
    }
    // resize
    void resize(size_type _n, value_type _val = _T()) {
        if (_n < size()) {
            iterator _new_elem = alloc.allocate(_n);
            iterator _new_avail = std::uninitialized_copy(_elem, _elem+_n, _new_elem);

            // delete data
            uncreate();

            // update pointers
            _elem = _new_elem;
            _avail = _new_avail;
            _limit = _elem + _n;
        }
        if(_n > size()) {
            iterator _new_elem = alloc.allocate(_n);
            iterator _new_avail = std::uninitialized_copy(_elem, _elem+size(), _new_elem);
            std::uninitialized_fill(_elem+size(), _elem+_n, _val);

            iterator _new_limit;
            if (capacity() < _new_avail - _new_elem)
            {
                _new_limit = _new_avail;
            }
            else
            {
                _new_limit = _new_elem + capacity();
            }

            // delete data
            uncreate();

            // update pointers
            _elem = _new_elem;
            _avail = _new_avail;
            _limit = _new_limit;
        }
    }
    // shrink_to_fit
    void shrink_to_fit() {
            if (capacity() != size())
                std::__shrink_to_fit_aux<vector>::_S_do_it(*this);
    }
    // clear
    void clear() {
        uncreate();
    }
    // pop_back
    void pop_back() {
        iterator _last_elem = _avail;
        alloc.destroy(--_last_elem);
        _avail = _last_elem;
    }
    // insert
    iterator insert(iterator _pos, iterator _first, iterator _last) {
        size_type _new_size = size() + (_last - _first);
        const int _index = _pos - _elem;

        if (_new_size > capacity()) {
            // new memory allocation
            iterator _new_elem = alloc.allocate(_new_size);
            iterator _new_avail;

            if (_pos == _elem && _elem != nullptr) {
                // fill new values
                _new_avail = std::uninitialized_copy(_first, _last, _new_elem);
                // fill old values
                _new_avail = std::uninitialized_copy(_pos, _avail, _new_elem + (_last - _first));
            } else if (_pos == _avail && _elem != nullptr) {
                // fill old values
                _new_avail = std::uninitialized_copy(_elem, _pos, _new_elem);
                // fill new values
                _new_avail = std::uninitialized_copy(_first, _last, _new_elem + (_first - _last));
            } else if(_avail == nullptr) {
                _new_avail = std::uninitialized_copy(_first, _last, _new_elem);
            } else {
                // fill old values before pos
                _new_avail = std::uninitialized_copy(_elem, _pos, _new_elem);
                // fill new values
                _new_avail = std::uninitialized_copy(_first, _last, _new_elem + (_pos - _elem));
                // fill old values after pos
                _new_avail = std::uninitialized_copy(_pos, _pos + (_last - _pos), _new_elem + (_pos - _elem) + (_last - _first));
            }

            if(!empty()) uncreate();

            _elem = _new_elem;
            _avail = _new_avail;
            _limit = _new_elem + _new_size;
        } else {
            if (!empty()) {
                iterator _old_elem = alloc.allocate(capacity());
                iterator _old_avail = std::uninitialized_copy(_elem, _avail, _old_elem);

                destroy();

                if (_pos == _elem && _elem != nullptr) {
                    // fill new values
                    _avail = std::uninitialized_copy(_first, _last, _elem);
                    // fill old values
                    _avail = std::uninitialized_copy(_old_elem, _old_avail, _elem + (_last - _first));
                } else if (_pos == _avail && _elem != nullptr) {
                    // fill old values
                    _avail = std::uninitialized_copy(_old_elem, _old_avail, _elem);
                    // fill new values
                    _avail = std::uninitialized_copy(_first, _last, _elem + (_old_avail - _old_elem));
                } else if(_avail == nullptr) {
                    _avail = std::uninitialized_copy(_first, _last, _elem);
                } else {
                    // fill old values before pos
                    _avail = std::uninitialized_copy(_old_elem, _old_elem + (_pos - _elem), _elem);
                    // fill new values
                    _avail = std::uninitialized_copy(_first, _last, _pos);
                    // fill old values after pos
                    _avail = std::uninitialized_copy(_old_elem + (_pos - _elem), _old_avail, _pos + (_last - _first));
                }
            } else {
                _avail = std::uninitialized_copy(_first, _last, _elem);
            }
        }
        return _avail[_index];
    }
    // erase
    iterator erase(iterator _first, iterator _last) {
        const int _index = _first - _avail;
        if (_last == _avail && _elem != nullptr) {
            iterator _new_elem = alloc.allocate(_first - _elem);
            iterator _new_avail = std::uninitialized_copy(_elem, _first, _new_elem);

            uncreate();

            _elem = _new_elem;
            _avail = _limit = _new_avail;
        } else {
            iterator _new_elem = alloc.allocate(size() - (_last - _first));
            iterator _new_avail;

            if (_first == _elem && _elem != nullptr) {
                // fill remaining values
                _new_avail = std::uninitialized_copy(_last, _avail, _new_elem);
            } else if (_first == _avail && _elem != nullptr) {
                // fill remaining values
                _new_avail = std::uninitialized_copy(_elem, _avail-1, _new_elem);
            } else if(_avail == nullptr) {

            } else {
                // fill old values before pos
                _new_avail = std::uninitialized_copy(_elem, _first, _new_elem);
                // fill old values after pos
                _new_avail = std::uninitialized_copy(_last, _avail, _new_elem + (_first - _elem));
            }

            if(!empty()) uncreate();

            _elem = _new_elem;
            _avail = _limit = _new_avail;
        }
        return _elem[_index];
    }
private:
    iterator _elem;
    iterator _limit;
    iterator _avail;

    std::allocator<_T> alloc;

    // creators
    void create() {
        _elem = _limit = _avail = nullptr;
    }
    void create(size_type _n, const _T& _val) {
        _elem = alloc.allocate(_n);
        _limit = _avail = _elem + _n;
        std::uninitialized_fill(_elem, _limit, _val);
    }
    void create(const_iterator _first, const_iterator _last) {
        _elem = alloc.allocate(_last - _first);
        _limit = _avail = std::uninitialized_copy(_first, _last, _elem);
    }
    void create(vector<_T> &&_v) {
        _elem = alloc.allocate(_v.size());
        _limit = _limit = std::uninitialized_copy(_v.begin(), _v.end(), _elem); // C++ 17 has std::uninitialized_move
    }
    void create(std::initializer_list<_T> _list) {
        _elem = alloc.allocate(_list.size());
        _limit = _avail = std::uninitialized_copy(_list.begin(), _list.end(), _elem);
    }

    // uncreator
    void uncreate() {
        // if there are values in the array
        if(_elem) {
            iterator _it = _avail;
            // reverse delete all elements
            while(_it != _elem)
                alloc.destroy(--_it);
            // deallocate available but not taken memory
            alloc.deallocate(_elem, _limit - _elem);
        }
        // reset pointers
        _elem = _limit = _avail = nullptr;
    }
    void destroy() {
        if(_elem) {
            iterator _it = _avail;
            // reverse delete all elements
            while(_it != _elem)
                alloc.destroy(--_it);
        }
        // reset pointers to needed position
        _avail = _elem;
    }

    //
    void grow() {
        // double sise
        size_type _new_size = std::max(2 * (_limit - _elem), ptrdiff_t(1));

        // new data and capacity
        iterator _new_elem = alloc.allocate(_new_size);
        iterator _new_avail = std::uninitialized_copy(_elem, _avail, _new_elem);

        // delete data
        uncreate();

        // update pointers
        _elem = _new_elem;
        _avail = _new_avail;
        _limit = _elem + _new_size;
    }
    void unchecked_append(const _T& _val) {
        alloc.construct(_avail++, _val);
    }
};


#endif //VECTOR_VECTOR_H
