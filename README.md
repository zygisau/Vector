# Vector
Savadarbė C++ vektoriaus klasė.

### Funkcijos
5 pasirinktos man labiausiai patikusios realizuoti funkcijos

```c++
void reserve(int _n) {
        // If n is greater than the current vector capacity

        if(_n > _capac) {
            _T* _temp = _elem;

            _elem = new _T[_n]; // the function causes the container to reallocate its storage increasing its capacity to n
            
            std::copy(&_temp[0], &_temp[_sz], &_elem[0]);
            _change_size_and_capacity(_sz, _n); // size remains the same
        }
    }
```



```c++
void resize(unsigned int _n) {
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
```




```c++
void push_back(_T _val) {
        // If vector is still capable to store one more value
        if (_sz+1 <= _capac) {
            _elem[_sz] = _val;
            _sz++;
        } else { // If new value exceeds capacity of the vector
            reserve(std::round(1 + _capac * 1.5));
            _elem[_sz] = _val;
            _sz++;
        }
    }
```



```c++
_T* erase(_T* _it_first, _T* _it_last) {
    // if pointers are out of array's bounds
        if ((_it_first < this->begin() || _it_first >= this->end())
            || (_it_last < this->begin() || _it_last > this->end()))
            throw std::out_of_range { "Vector::erase, possession of invalid memory" };

        int _ind = _it_first - this->begin(); // index
        int _dist = _it_last - _it_first; // distance
        _T* _temp = new _T[_capac];

        int _new_sz = 0;
    
    // if area that needs to be deleted isn't the beggining of the vector
        if(_it_first != &_elem[0]) {
            std::copy(&_elem[0], _it_first, &_temp[0]);
            _new_sz += _ind;
        }
    
    // if area that needs to be deleted isn't the ending of the vector
        if(_it_last != &_elem[_sz]) {
            std::copy(_it_last, &_elem[_sz], &_temp[_new_sz]);
            _new_sz += _sz - _dist - _ind;
        }

        delete[] _elem; // deleting old array
        _elem = _temp;
        _change_size_and_capacity(_new_sz, _capac);

        return &_elem[_ind]; // returning pointer to the memory where first deleted value was
    }
```



```c++
_T* insert(_T* _it_pos, _T* _it_first, _T* _it_last) {
        int _ind = _it_pos - this->begin(); // finding position's index

        if (_ind >= _sz) // if iterator is pointing to the invalid memory
            throw std::out_of_range { "Vector::insert, possession of invalid memory" };

        int _dist = _it_last - _it_first; // distance (number of values to be inserted)
    
        _T* _temp = new _T[_dist];
        std::copy(_it_first, _it_last, &_temp[0]);
    
        if(_sz+_dist <= _capac) { // if there capacity is big enough to store values
            _insert_value_in_pos(_temp, _ind, _dist);
        } else { // if it need reallocation
            reserve(_sz + _dist);
            _insert_value_in_pos(_temp, _ind, _dist);
        }
    
        delete[] _temp;
        return &_elem[_ind];
    }
```

