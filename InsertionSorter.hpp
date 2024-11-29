#ifndef INSERTIONSORTER_HPP
#define INSERTIONSORTER_HPP

#include "ISorter.hpp"
#include "data_structures/ArraySequence.h"
#include "SmrtPtr.hpp"
#include "compare.hpp"

template<typename T>
class InsertionSorter : public ISorter<T> {
public:
    SmrtPtr<ArraySequence<T>> Sort(SmrtPtr<ArraySequence<T>> seq, int (*cmp)(const T&, const T&) = compare_default<T>) override {
        InsertionSort(seq, cmp);
        return seq;
    }

private:
    void InsertionSort(SmrtPtr<ArraySequence<T>> seq, int (*cmp)(const T&, const T&)) {
        int n = seq->get_length();
        for (int i = 1; i < n; ++i) {
            T key = seq->get(i);
            int j = i - 1;

            while (j >= 0 && cmp(seq->get(j), key) > 0) {
                seq->set(j + 1, seq->get(j));
                --j;
            }
            seq->set(j + 1, key);
        }
    }
};

#endif // INSERTIONSORTER_HPP
