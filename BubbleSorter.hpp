#ifndef BUBBLESORTER_HPP
#define BUBBLESORTER_HPP

#include "ISorter.hpp"
#include "data_structures/ArraySequence.h"
#include "SmrtPtr.hpp"
#include "compare.hpp"

template<typename T>
class BubbleSorter : public ISorter<T> {
public:
    SmrtPtr<ArraySequence<T>> Sort(SmrtPtr<ArraySequence<T>> seq, int (*cmp)(const T&, const T&) = compare_default<T>) override {
        BubbleSort(seq, cmp);
        return seq;
    }

private:
    void BubbleSort(SmrtPtr<ArraySequence<T>> seq, int (*cmp)(const T&, const T&)) {
        int n = seq->get_length();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (cmp(seq->get(j), seq->get(j + 1)) > 0) {
                    T temp = seq->get(j);
                    seq->set(j, seq->get(j + 1));
                    seq->set(j + 1, temp);
                }
            }
        }
    }
};

#endif //BUBBLESORTER_HPP
