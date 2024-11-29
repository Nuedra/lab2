#ifndef QUICKSORTER_HPP
#define QUICKSORTER_HPP

#include "ISorter.hpp"
#include "data_structures/ArraySequence.h"
#include "SmrtPtr.hpp"
#include "compare.hpp"

template<typename T>
class QuickSorter : public ISorter<T> {
public:
    SmrtPtr<ArraySequence<T>> Sort(SmrtPtr<ArraySequence<T>> seq, int (*cmp)(const T&, const T&) = compare_default<T>) override {
        QuickSort(seq, 0, seq->get_length() - 1, cmp);
        return seq;
    }

private:
    void QuickSort(SmrtPtr<ArraySequence<T>> seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) return;

        int pivot_index = Partition(seq, left, right, cmp);
        QuickSort(seq, left, pivot_index - 1, cmp);
        QuickSort(seq, pivot_index + 1, right, cmp);
    }

    int Partition(SmrtPtr<ArraySequence<T>> seq, int left, int right, int (*cmp)(const T&, const T&)) {
        T pivot = seq->get(right);
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (cmp(seq->get(j), pivot) < 0) {
                i++;
                T temp = seq->get(i);
                seq->set(i, seq->get(j));
                seq->set(j, temp);
            }
        }

        T temp = seq->get(i + 1);
        seq->set(i + 1, seq->get(right));
        seq->set(right, temp);

        return i + 1;
    }


};

#endif //QUICKSORTER_HPP
