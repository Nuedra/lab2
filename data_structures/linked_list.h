#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <stdexcept>

#define INDEX_OUT_OF_RANGE "Index out of range"
#define EMPTY_LINKED_LIST "LinkedList is empty"

template<typename T>
class linked_list_node {
public:
    T value;
    linked_list_node<T>* next;

    linked_list_node(const T& value, linked_list_node<T>* next = nullptr);
};

template<typename T>
class linked_list {
private:
    linked_list_node<T>* head;
    linked_list_node<T>* tail;
    size_t length;

    void clear();

public:
    linked_list();
    linked_list(const T* items, int count);
    linked_list(const linked_list<T>& list);
    ~linked_list();

    linked_list<T>* get_sub_list(int start_index, int end_index);
    void append(T item);
    void prepend(T item);
    void insert_at(T item, int index);
    size_t get_length() const;
    T get_first() const;
    T get_last() const;
    T get(int index) const;
    void set(int index, const T& value);
};

#include "linked_list.tpp"

#endif // LINKED_LIST_H
