#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>

#define INDEX_OUT_OF_RANGE "Index out of range"
#define NEGATIVE_SIZE "New size must be greater than or equal to zero."

template<typename T>
class dynamic_array {
private:
    T* data;
    size_t length;

public:
    dynamic_array();
    dynamic_array(T* items, int count);
    dynamic_array(int size);
    dynamic_array(const dynamic_array<T>& other);
    ~dynamic_array();

    T get(int index) const;
    void set(int index, T value);
    int get_size() const;
    void resize(int new_size);

    T& operator[](int index);
    const T& operator[](int index) const;
};

#include "dynamic_array.tpp"

#endif // DYNAMIC_ARRAY_H
