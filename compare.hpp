#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "data_structures/ArraySequence.h"
#include "SmrtPtr.hpp"

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
    static KeyType T::*key;

    static void SetKey(KeyType T::*key_field) {
        key = key_field;
    }

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

template <typename T, typename KeyType>
KeyType T::*ComparatorWrapper<T, KeyType>::key = nullptr;

template <typename T>
class ChainedComparator {
public:
    static SmrtPtr<ArraySequence<int(*)(const T&, const T&)>> comparators;

    static void AddComparator(int(*cmp)(const T&, const T&)) {
        comparators->append(cmp);
    }

    static int Compare(const T& a, const T& b) {
        for (int i = 0; i < comparators->get_length(); ++i) {
            int result = comparators->get(i)(a, b);
            if (result != 0) {
                return result;
            }
        }

        return 0;
    }

    static void ClearComparators() {
        comparators = SmrtPtr<ArraySequence<int(*)(const T&, const T&)>>(new ArraySequence<int(*)(const T&, const T&)>());
    }
};

template <typename T>
SmrtPtr<ArraySequence<int(*)(const T&, const T&)>> ChainedComparator<T>::comparators = SmrtPtr<ArraySequence<int(*)(const T&, const T&)>>(new ArraySequence<int(*)(const T&, const T&)>());

#endif // COMPARE_HPP
