#ifndef SEQUENCE_H
#define SEQUENCE_H

template<typename T>
class sequence {
public:
    virtual const T& get_first() const = 0;
    virtual const T& get_last() const = 0;
    virtual const T& get(int index) const = 0;
    virtual T& get(int index) = 0;

    virtual sequence<T>* get_subsequence(int start_index, int end_index) const = 0;
    virtual int get_length() const = 0;
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insert_at(const T& item, int index) = 0;
    virtual void set(int index, const T& item) = 0;
    virtual sequence<T>* concat(sequence<T>* list) const = 0;
    virtual void swap(int index1, int index2) = 0;
    virtual void reserve(int new_capacity) = 0; // Добавлен метод reserve
    virtual ~sequence() {}
};

#endif // SEQUENCE_H
