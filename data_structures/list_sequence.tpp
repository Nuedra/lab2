#ifndef LIST_SEQUENCE_TPP
#define LIST_SEQUENCE_TPP

#include "list_sequence.h"

template<typename T>
list_sequence<T>::list_sequence() : list() {}

template<typename T>
list_sequence<T>::list_sequence(const T* items, int count) : list(items, count) {}

template<typename T>
list_sequence<T>::list_sequence(const list_sequence<T>& sequence) : list(sequence.list) {}

template<typename T>
list_sequence<T>::list_sequence(const linked_list<T>& list) : list(list) {}

template<typename T>
T list_sequence<T>::get_first() const {
    if (list.get_length() == 0) throw std::out_of_range(EMPTY_LIST_SEQUENCE);
    return list.get_first();
}

template<typename T>
T list_sequence<T>::get_last() const {
    if (list.get_length() == 0) throw std::out_of_range(EMPTY_LIST_SEQUENCE);
    return list.get_last();
}

template<typename T>
T list_sequence<T>::get(int index) const {
    if (index < 0 || index >= list.get_length()) throw std::out_of_range(INDEX_OUT_OF_RANGE);
    return list.get(index);
}

template<typename T>
sequence<T>* list_sequence<T>::get_subsequence(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= list.get_length() || start_index > end_index)
        throw std::out_of_range(INDEX_OUT_OF_RANGE);

    list_sequence<T>* sub_list = new list_sequence<T>();
    for (int i = start_index; i <= end_index; ++i) {
        sub_list->append(list.get(i));
    }
    return sub_list;
}

template<typename T>
int list_sequence<T>::get_length() const {
    return list.get_length();
}

template<typename T>
void list_sequence<T>::append(const T& item) {
    list.append(item);
}

template<typename T>
void list_sequence<T>::prepend(const T& item) {
    list.prepend(item);
}

template<typename T>
void list_sequence<T>::insert_at(const T& item, int index) {
    list.insert_at(item, index);
}

template<typename T>
void list_sequence<T>::set(int index, const T& item) {
    if (index < 0 || index >= list.get_length()) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    list.set(index, item);
}

template<typename T>
sequence<T>* list_sequence<T>::concat(sequence<T>* other_list) const {
    list_sequence<T>* result = new list_sequence<T>();
    for (int i = 0; i < this->get_length(); i++) {
        result->append(this->get(i));
    }
    for (int i = 0; i < other_list->get_length(); i++) {
        result->append(other_list->get(i));
    }
    return result;
}

#endif // LIST_SEQUENCE_TPP
