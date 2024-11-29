#ifndef LAB2_QUICKSORTER_HPP
#define LAB2_QUICKSORTER_HPP

#include "ISorter.hpp"
#include "data_structures/ArraySequence.h"

template<typename T>
class QuickSorter : public ISorter<T> {
private:
    void QuickSort(ArraySequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) return;

        int pivot_index = Partition(seq, left, right, cmp);
        QuickSort(seq, left, pivot_index - 1, cmp);
        QuickSort(seq, pivot_index + 1, right, cmp);
    }

    int Partition(ArraySequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        T pivot = seq->Get(right);
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (cmp(seq->Get(j), pivot) < 0) {
                i++;
                T temp = seq->Get(i);
                seq->Set(i, seq->Get(j));
                seq->Set(j, temp);
            }
        }

        T temp = seq->Get(i + 1);
        seq->Set(i + 1, seq->Get(right));
        seq->Set(right, temp);

        return i + 1;
    }

public:
    ArraySequence<T>* Sort(ArraySequence<T>* seq, int (*cmp)(const T&, const T&)) {
        QuickSort(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};

#endif //LAB2_QUICKSORTER_HPP
