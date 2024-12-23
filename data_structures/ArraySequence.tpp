#ifndef ARRAY_SEQUENCE_TPP
#define ARRAY_SEQUENCE_TPP

#include "ArraySequence.h"
#include <stdexcept>

template<typename T>
ArraySequence<T>::ArraySequence() : data(new dynamic_array<T>(10)), length(0), capacity(10) {}

template<typename T>
ArraySequence<T>::ArraySequence(const T* items, int count)
        : data(new dynamic_array<T>(count)), length(count), capacity(count) {
    for (int i = 0; i < count; ++i) {
        data->set(i, items[i]);
    }
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other)
        : data(new dynamic_array<T>(*other.data)), length(other.length), capacity(other.capacity) {}

template<typename T>
ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence<T>& other) {
    if (this != &other) {
        delete data;
        data = new dynamic_array<T>(*other.data);
        length = other.length;
        capacity = other.capacity;
    }
    return *this;
}

template<typename T>
ArraySequence<T>::~ArraySequence() {
    delete data;
    data = nullptr;
}

template<typename T>
const T& ArraySequence<T>::get_first() const {
    if (length == 0) {
        throw std::out_of_range(EMPTY_ARRAY_SEQ);
    }
    return data->get(0);
}

template<typename T>
const T& ArraySequence<T>::get_last() const {
    if (length == 0) {
        throw std::out_of_range(EMPTY_ARRAY_SEQ);
    }
    return data->get(length - 1);
}

template<typename T>
const T& ArraySequence<T>::get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data->get(index);
}

template<typename T>
T& ArraySequence<T>::get(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    return data->get(index);
}

template<typename T>
sequence<T>* ArraySequence<T>::get_subsequence(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= length || start_index > end_index) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    int sub_length = end_index - start_index + 1;
    T* items = new T[sub_length];
    for (int i = 0; i < sub_length; ++i) {
        items[i] = data->get(start_index + i);
    }
    sequence<T>* subsequence = new ArraySequence<T>(items, sub_length);
    delete[] items;
    return subsequence;
}

template<typename T>
int ArraySequence<T>::get_length() const {
    return length;
}

template<typename T>
void ArraySequence<T>::ensure_capacity(int min_capacity) {
    if (min_capacity > capacity) {
        int new_capacity = capacity * 2;
        if (new_capacity < min_capacity) {
            new_capacity = min_capacity;
        }
        data->resize(new_capacity);
        capacity = new_capacity;
    }
}

template<typename T>
void ArraySequence<T>::append(const T& item) {
    ensure_capacity(length + 1);
    data->set(length, item);
    length++;
}

template<typename T>
void ArraySequence<T>::prepend(const T& item) {
    ensure_capacity(length + 1);
    for (int i = length; i > 0; --i) {
        data->set(i, data->get(i - 1));
    }
    data->set(0, item);
    length++;
}

template<typename T>
void ArraySequence<T>::insert_at(const T& item, int index) {
    if (index < 0 || index > length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    ensure_capacity(length + 1);
    for (int i = length; i > index; --i) {
        data->set(i, data->get(i - 1));
    }
    data->set(index, item);
    length++;
}

template<typename T>
void ArraySequence<T>::set(int index, const T& item) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    data->set(index, item);
}

template<typename T>
void ArraySequence<T>::swap(int index1, int index2) {
    if (index1 < 0 || index1 >= length || index2 < 0 || index2 >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    T temp = data->get(index1);
    data->set(index1, data->get(index2));
    data->set(index2, temp);
}

template<typename T>
sequence<T>* ArraySequence<T>::concat(sequence<T>* list) const {
    int new_length = length + list->get_length();
    T* new_array = new T[new_length];
    for (int i = 0; i < length; ++i) {
        new_array[i] = data->get(i);
    }
    for (int i = 0; i < list->get_length(); ++i) {
        new_array[length + i] = list->get(i);
    }
    sequence<T>* new_sequence = new ArraySequence<T>(new_array, new_length);
    delete[] new_array;
    return new_sequence;
}

template<typename T>
void ArraySequence<T>::reserve(int new_capacity) {
    if (new_capacity > capacity) {
        data->resize(new_capacity);
        capacity = new_capacity;
    }
}

#endif // ARRAY_SEQUENCE_TPP
