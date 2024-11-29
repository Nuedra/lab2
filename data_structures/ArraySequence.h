#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "sequence.h"
#include "dynamic_array.h"

#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTY_ARRAY_SEQ "Array is empty"

template<typename T>
class ArraySequence: public sequence<T> {
private:
    dynamic_array<T>* data;
    int length;
    int capacity;

    void ensure_capacity(int min_capacity);

public:
    ArraySequence();
    ArraySequence(const T* items, int count);
    ArraySequence(const ArraySequence<T>& ArraySequence);
    ~ArraySequence();

    T get_first() const override;
    T get_last() const override;
    T get(int index) const override;
    sequence<T>* get_subsequence(int start_index, int end_index) const override;
    int get_length() const override;
    void append(const T& item);
    void prepend(const T& item) override;
    void insert_at(const T& item, int index) override;
    void set(int index, const T& item) override;
    sequence<T>* concat(sequence<T>* list) const override;
};

#include "ArraySequence.tpp"

#endif // ARRAY_SEQUENCE_H
