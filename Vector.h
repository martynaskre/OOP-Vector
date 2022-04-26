//
// Created by Martynas Skrebė on 2022-04-24.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H


#include <algorithm>

template<typename T>
class Vector {
    typedef T value_type;
    typedef std::allocator<T> allocator_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    T *array;
    size_type space;
    size_type length;

public:
    explicit Vector(size_type n = 100);
    Vector(const Vector &vector);
    Vector(std::initializer_list<T> elements);
    Vector<T> &operator=(const Vector<T> &a);
    ~Vector();

    reference at(size_type position);
    const_reference at(size_type position) const;
    T &operator[](int i);
    const T &operator[](int i) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    iterator data();
    const_iterator data() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;

    bool empty();
    size_type size();
    size_type max_size();
    void reserve(size_type new_capacity);
    size_type capacity();
    void shrink_to_fit();

    void clear();
    iterator insert(iterator position, T element);
    iterator emplace(iterator position, T element);
    iterator erase(iterator first);
    iterator erase(iterator first, iterator last);
    void push_back(T element);
    void emplace_back(T element);
    void pop_back();
    void resize(size_type count);
    void swap(Vector<T> &other);
};

template<typename T>
Vector<T>::Vector(size_t n)
        : space(n), array(new T[n]), length(0) {
}

template<class T>
inline Vector<T>::Vector(const Vector &vector)
        : space(vector.space), length(vector.length), array(new T[vector.length]) {
    std::copy(vector.begin(), vector.end(), array);
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> elements)
        : space(elements.size()), length(elements.size()), array(new T(elements.size())) {
    std::copy(elements.begin(), elements.end(), array);
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &a) {
    if (this == &a) {
        return *this;
    }

    // Current Vector has enough space, so there is no need for new allocation
    if (a.space <= space) {
        for (int index = 0; index < a.length; ++index) {
            array[index] = a.array[index];
            length = a.length;
            return *this;
        }
    }

    T *p = new T[a.length];

    for (int index = 0; index < a.length; ++index)
        p[index] = a.array[index];

    delete[] array;
    length = a.length;
    space = a.space;
    array = p;

    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] array;
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_t position) {
    if (position > length - 1) {
        throw std::out_of_range("Out of range");
    }

    return array[position];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(Vector::size_type position) const {
    if (position > length - 1) {
        throw std::out_of_range("Out of range");
    }

    return array[position];
}

template<typename T>
T &Vector<T>::operator[](int i) {
    return array[i];
}

template<typename T>
const T &Vector<T>::operator[](int i) const {
    return array[i];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
    return array[0];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return array[0];
}

template<typename T>
typename Vector<T>::reference Vector<T>::back() {
    return array[length - 1];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return array[length - 1];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::data() {
    return array;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::data() const {
    return array;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return array;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
    return array;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return array + length;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
    return array + length;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
    return reverse_iterator(array + length);
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const noexcept {
    return reverse_iterator(array + length);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
    return reverse_iterator(array);
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const noexcept {
    return reverse_iterator(array);
}

template<typename T>
bool Vector<T>::empty() {
    return length == 0;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() {
    return length;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() {
    return std::distance(begin(), end());
}

template<typename T>
void Vector<T>::reserve(Vector<T>::size_type new_capacity) {
    if (new_capacity <= space) {
        return;
    }

    T* new_array = new T[new_capacity];

    std::copy(begin(), end(), new_array);

    array = new_array;
    space = new_capacity;
}

template<typename T>
size_t Vector<T>::capacity() {
    return space;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
    T* new_array = new T(length);

    std::copy(begin(), end(), new_array);

    array = new_array;
    space = length;
}

template<typename T>
void Vector<T>::clear() {
    delete[] array;
    array = new T[0];
    length = 0;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::insert(Vector::iterator position, T element) {
    if (position < begin() || position > end()) {
        throw std::out_of_range("Out of range");
    }

    if (length + 1 > space) {
        space *= 2;
    }

    T* new_array = new T[space];

    iterator last = std::copy(begin(), position, new_array);
    *last = element;
    std::copy(position, end(), last + 1);

    array = new_array;
    length++;

    return position;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::emplace(Vector::iterator position, T element) {
    return Vector::iterator();
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::erase(Vector::iterator first) {
    if (first > end() || first < begin()) {
        throw std::out_of_range("Out of range");
    }

    for (iterator i = first; i < end(); i++) {
        *i = *(i + 1);
    }

    length--;

    return first;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::erase(Vector::iterator first, Vector::iterator last) {
    if (last < first || first < begin() || last > end()) {
        throw std::out_of_range("Out of range");
    }

    for (iterator i = first; i < end(); i++) {
        *i = *(i + std::distance(first, last));
    }

    length -= std::distance(first, last);

    return last;
}

template<typename T>
void Vector<T>::push_back(T element) {
    if (length == space) {
        T *old = array;
        array = new T[space = space * 2];
        std::copy(old, old + length, array);
        delete[] old;
    }

    array[length++] = element;
}

template<typename T>
void Vector<T>::emplace_back(T element) {

}

template<typename T>
void Vector<T>::pop_back() {
    if (empty()) {
        return;
    }

    length--;
}

template<typename T>
void Vector<T>::resize(size_type count) {
    if (count < 0 || count >> size()) {
        throw std::invalid_argument("Invalid count");
    }

    T* new_array = new T[count];

    std::copy(begin(), begin() + count, new_array);

    array = new_array;
    length = count;
    space = count;
}

template<typename T>
void Vector<T>::swap(Vector<T> &other) {
    iterator temp = array;
    array = other.array;
    other.data = temp;

    temp = length;
    length = other.length;
    other.avail = temp;

    temp = space;
    space = other.space;
    other.space = temp;
}


#endif //VECTOR_VECTOR_H
