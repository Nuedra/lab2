#ifndef LAB2_QUICKSORTER_HPP
#define LAB2_QUICKSORTER_HPP

#include "ISorter.hpp"
#include "data_structures/ArraySequence.h"

template<typename T>
class QuickSorter : public ISorter<T> {
private:


public:
    SmrtPtr<ArraySequence<T>> Sort(SmrtPtr<ArraySequence<T>> seq,
                                   int (*cmp)(const T&, const T&) = CompareDefault<T>) override {
        QuickSort(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};

#endif //LAB2_QUICKSORTER_HPP
