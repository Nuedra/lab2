#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "sequence.h"
#include "dynamic_array.h"

#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTY_ARRAY_SEQ "Array is empty"

template<typename T>
class ArraySequence : public sequence<T> {
private:
    dynamic_array<T>* data;
    int length;
    int capacity;

    void ensure_capacity(int min_capacity);

public:
    ArraySequence();
    ArraySequence(const T* items, int count);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence<T>& operator=(const ArraySequence<T>& other);
    ~ArraySequence();

    // Переопределение виртуальных методов
    const T& get_first() const override;
    const T& get_last() const override;
    const T& get(int index) const override;
    T& get(int index) override;

    sequence<T>* get_subsequence(int start_index, int end_index) const override;
    int get_length() const override;
    void append(const T& item) override;
    void prepend(const T& item) override;
    void insert_at(const T& item, int index) override;
    void set(int index, const T& item) override;
    sequence<T>* concat(sequence<T>* list) const override;
    void swap(int index1, int index2) override;
    void reserve(int new_capacity) override;
};

#include "ArraySequence.tpp"

#endif // ARRAY_SEQUENCE_H
