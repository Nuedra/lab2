#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "sequence.h"
#include "linked_list.h"

#define EMPTY_LIST_SEQUENCE "Sequence is empty"

template<typename T>
class list_sequence : public sequence<T> {
private:
    linked_list<T> list;

public:
    list_sequence();
    list_sequence(const T* items, int count);
    list_sequence(const list_sequence<T>& sequence);
    list_sequence(const linked_list<T>& list);

    T get_first() const override;
    T get_last() const override;
    T get(int index) const override;
    sequence<T>* get_subsequence(int start_index, int end_index) const override;
    int get_length() const override;
    void append(const T& item) override;
    void prepend(const T& item) override;
    void insert_at(const T& item, int index) override;
    void set(int index, const T& item) override;
    sequence<T>* concat(sequence<T>* other_list) const override;
};

#include "list_sequence.tpp"

#endif // LIST_SEQUENCE_H
