# Vector

![version][version-badge]  

"Rankų darbo" C++ vektoriaus klasė.

### Funkcijos
5 pasirinktos man labiausiai patikusios realizuoti funkcijos

##### Reserve

```c++
void reserve(size_type _n) {
    if (_n > capacity()) {
        // allocate new memory
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
```

##### Resize 	

```c++
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
```

##### Pop_back


```c++
void pop_back() {
    iterator _last_elem = _avail;
    alloc.destroy(--_last_elem);
    _avail = _last_elem;
}
```

##### Erase

```c++
void erase(iterator _first, iterator _last) {
// if erase ranges all the way to the last element
    if (_last == _avail && _elem != nullptr) {
        // allocate new memory and copy elements
        iterator _new_elem = alloc.allocate(_first - _elem);
        iterator _new_avail = std::uninitialized_copy(_elem, _first, _new_elem);

     	// destroy old memory
        uncreate();

        // update pointers
        _elem = _new_elem;
        _avail = _limit = _new_avail;
    } else {
        // allocate new memory
        iterator _new_elem = alloc.allocate(size() - (_last - _first));
        iterator _new_avail;
// if erase starts from the start of the vector
        if (_first == _elem && _elem != nullptr) {
            // fill remaining values
            _new_avail = std::uninitialized_copy(_last, _avail, _new_elem);
// if erase starts from the end of the vector
        } else if (_first == _avail && _elem != nullptr) {
            // fill remaining values
            _new_avail = std::uninitialized_copy(_elem, _avail-1, _new_elem);
// if there are no elements
        } else if(_avail == nullptr) {
			
        } else {
            // fill old values before pos
            _new_avail = std::uninitialized_copy(_elem, _first, _new_elem);
            // fill old values after pos
            _new_avail = std::uninitialized_copy(_last, _avail, _new_elem + (_first - _elem));
        }

        // destroy old elements (if were any)
        if(!empty()) uncreate();

        // update pointers
        _elem = _new_elem;
        _avail = _limit = _new_avail;
    }
}
```

##### Insert

```c++
void insert(iterator _pos, iterator _first, iterator _last) {
    // determine new size
    size_type _new_size = size() + (_last - _first);

    if (_new_size > capacity()) {
        // new memory allocation
        iterator _new_elem = alloc.allocate(_new_size);
        iterator _new_avail;
// if position iterator points to the first elem
        if (_pos == _elem && _elem != nullptr) {
            // fill new values
            _new_avail = std::uninitialized_copy(_first, _last, _new_elem);
            // fill old values
            _new_avail = std::uninitialized_copy(_pos, _avail, _new_elem + (_last - _first));
// if position iterator points to the last* element
        } else if (_pos == _avail && _elem != nullptr) {
            // fill old values
            _new_avail = std::uninitialized_copy(_elem, _pos, _new_elem);
            // fill new values
            _new_avail = std::uninitialized_copy(_first, _last, _new_elem + (_first - _last));
// if there are no elements in the vector
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

        // delete old elements (if were any)
        if(!empty()) uncreate();

        // update pointers
        _elem = _new_elem;
        _avail = _new_avail;
        _limit = _new_elem + _new_size;
    } else {
        if (!empty()) {
            // back up old elements from the vector
            iterator _old_elem = alloc.allocate(capacity());
            iterator _old_avail = std::uninitialized_copy(_elem, _avail, _old_elem);

          	// destroy old elements from the vector
            destroy();

// if position iterator points to the first element of the vector
            if (_pos == _elem && _elem != nullptr) {
                // fill new values
                _avail = std::uninitialized_copy(_first, _last, _elem);
                // fill old values
                _avail = std::uninitialized_copy(_old_elem, _old_avail, _elem + (_last - _first));
// if position iterator points to the last* element of the vector
            } else if (_pos == _avail && _elem != nullptr) {
                // fill old values
                _avail = std::uninitialized_copy(_old_elem, _old_avail, _elem);
                // fill new values
                _avail = std::uninitialized_copy(_first, _last, _elem + (_old_avail - _old_elem));
// if there are no elements in the vector
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
}
```



### Analizė

#### ``` vector<int> ```

Sukuriami vektoriai ir užpildomi reikšmėmis [0 ; dydis)

| KONTEINERIS\DYDIS | 100000   | 1000000  | 10000000 | 100000000 |
| ----------------- | -------- | -------- | -------- | --------- |
| STD::VECTOR       | 0.000992 | 0.006448 | 0.07688  | 0.772766  |
| CUSTOM VECTOR     | 0.000497 | 0.004465 | 0.062497 | 0.570895  |

#### ``` vector<Student> ```

Sukuriami vektoriai ir užpildomi prieš tai sukurtu studento objektu

```c++
Student stud = Student();
stud.setName("Jonas");
stud.setSurname("Jonaitis");
stud.setGrades({10, 9, 9, 10, 8, 7, 9, 10});
stud.setExam(10);
stud.setGalutinis(9.8);
stud.setGalutinisMedian(9);
stud.setVargsiukas(false);
```

| KONTEINERIS\DYDIS | 100000   | 1000000  | 10000000                                      | 100000000                                     |
| ----------------- | -------- | -------- | --------------------------------------------- | --------------------------------------------- |
| STD::VECTOR       | 0.049104 | 0.549566 | <span style="color:red">std::bad_alloc</span> | <span style="color:red">std::bad_alloc</span> |
| CUSTOM VECTOR     | 0.063983 | 0.370017 | <span style="color:red">std::bad_alloc</span> | <span style="color:red">std::bad_alloc</span> |

### Vektorių atminties paskirstymas

| KONTEINERIS\DYDIS | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| ----------------- | ------ | ------- | -------- | --------- | --------- |
| STD::VECTOR       | 15     | 3       | 3        | 4         |3|
| CUSTOM VECTOR     | 15     | 18      | 21       | 25        |28|


### Vector'ius 3-oje užduotyje

##### STD::VECTOR 100000 studentų įrašų

Nuskaitymas iš failo truko: 1.11302 s
Studentų filtravimas (skirstymas) truko: 0.299338 s
Įrašymas į failą truko: 2.06385 s
Darbas su "kursiokai100000.txt" užtruko: 3.4787 s

##### CUSTOM VECTOR 100000 studentų įrašų

Nuskaitymas iš failo truko: 1.35655 s
Studentų filtravimas (skirstymas) truko: 0.361583 s
Įrašymas į failą truko: 1.84214 s
Darbas su "kursiokai100000.txt" užtruko: 3.56672 s

## Changelog
### [v1.1](https://github.com/zygisau/Vector/releases/tag/v1.1) - (2019-05-25)

**Pridėta**
- Nauja vektoriaus klasė, su kuria galima buvo atlikti visas užduotis.

**Koreguota**
- Padarytos užduotys įdėtos į readme skiltį

> SVARBU
Sena klasė *NĖRA* naudojama. Palikau tik dėl to, jog ten irgi buvo įdėta darbo.
**Naudojama klasė yra ./NewVector./vector.h faile**

### [v1.0](https://github.com/zygisau/Vector/releases/tag/v1.0) - (2019-05-18)  

**Pridėta** 

- Pagrindinės vektoriaus funkcijos

[version-badge]: https://img.shields.io/badge/version-1.1-green.svg
