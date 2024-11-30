#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "data_structures/ArraySequence.h"  // Подключение ArraySequence вместо vector

template<typename T>
int compare_default(const T& a, const T& b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

template <typename T, typename KeyType>
class ComparatorWrapper {
public:
    static KeyType T::*key;  // Указатель на поле для сравнения

    // Устанавливаем поле, по которому будет выполняться сравнение
    static void SetKey(KeyType T::*key_field) {
        key = key_field;
    }

    // Статическая функция сравнения, совместимая с интерфейсом сортировщика
    static int Compare(const T& a, const T& b) {
        if (a.*key < b.*key) {
            return -1;
        }
        else if (a.*key > b.*key) {
            return 1;
        }
        return 0;
    }
};

// Определение статического члена класса
template <typename T, typename KeyType>
KeyType T::*ComparatorWrapper<T, KeyType>::key = nullptr;

template <typename T>
class ChainedComparator {
public:
    static ArraySequence<int(*)(const T&, const T&)> comparators;  // Используем ArraySequence вместо vector

    static void AddComparator(int(*cmp)(const T&, const T&)) {
        comparators.append(cmp);  // Добавление через append
    }

    static int Compare(const T& a, const T& b) {
        for (int i = 0; i < comparators.get_length(); ++i) {
            int result = comparators.get(i)(a, b);
            if (result != 0) {
                return result;
            }
        }
        return 0; // Если все компараторы вернули равенство, считаем объекты равными
    }

    static void ClearComparators() {
        comparators = ArraySequence<int(*)(const T&, const T&)>();
    }
};

// Определение статического члена
template <typename T>
ArraySequence<int(*)(const T&, const T&)> ChainedComparator<T>::comparators = {};

#endif // COMPARE_HPP
