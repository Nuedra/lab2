#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include "linked_list.h"
#include <stdexcept>
#include <cstddef>

template<typename T>
linked_list_node<T>::linked_list_node(const T& value, linked_list_node<T>* next)
    : value(value), next(next) {}

template<typename T>
void linked_list<T>::clear() {
    while (head != nullptr) {
        linked_list_node<T>* current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    length = 0;
}

template<typename T>
linked_list<T>::linked_list() : head(nullptr), tail(nullptr), length(0) {}

template<typename T>
linked_list<T>::linked_list(const T* items, int count) : head(nullptr), tail(nullptr), length(0) {
    for (int i = 0; i < count; ++i) {
        append(items[i]);
    }
}

template<typename T>
linked_list<T>::linked_list(const linked_list<T>& list) : head(nullptr), tail(nullptr), length(0) {
    linked_list_node<T>* current = list.head;
    while (current != nullptr) {
        append(current->value);
        current = current->next;
    }
}

template<typename T>
linked_list<T>::~linked_list() {
    clear();
}

template<typename T>
linked_list<T>* linked_list<T>::get_sub_list(int start_index, int end_index) {
    if (start_index < 0 || end_index < 0 || start_index > end_index || end_index >= this->length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    auto* sub_list = new linked_list<T>();
    linked_list_node<T>* current = this->head;
    for (int i = 0; i < start_index; ++i) {
        current = current->next;
    }
    for (int i = start_index; i <= end_index; ++i) {
        sub_list->append(current->value);
        current = current->next;
    }
    return sub_list;
}

template<typename T>
void linked_list<T>::append(T item) {
    linked_list_node<T>* node = new linked_list_node<T>(item, nullptr);
    if (tail == nullptr) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    length++;
}

template<typename T>
size_t linked_list<T>::get_length() const {
    return length;
}

template<typename T>
T linked_list<T>::get_first() const {
    if (head == nullptr) throw std::out_of_range(EMPTY_LINKED_LIST);
    return head->value;
}

template<typename T>
T linked_list<T>::get_last() const {
    if (tail == nullptr) throw std::out_of_range(EMPTY_LINKED_LIST);
    return tail->value;
}

template<typename T>
T linked_list<T>::get(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    linked_list_node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<typename T>
void linked_list<T>::prepend(T item) {
    linked_list_node<T>* new_node = new linked_list_node<T>(item, head);
    head = new_node;
    if (length == 0) {
        tail = new_node;
    }
    length++;
}

template<typename T>
void linked_list<T>::insert_at(T item, int index) {
    if (index < 0 || index > length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    if (index == 0) {
        prepend(item);
        return;
    }
    if (index == length) {
        append(item);
        return;
    }
    linked_list_node<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    linked_list_node<T>* new_node = new linked_list_node<T>(item, current->next);
    current->next = new_node;
    length++;
}

template<typename T>
void linked_list<T>::set(int index, const T& value) {
    if (index < 0 || index >= length) {
        throw std::out_of_range(INDEX_OUT_OF_RANGE);
    }
    linked_list_node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    current->value = value;
}

#endif // LINKED_LIST_TPP
