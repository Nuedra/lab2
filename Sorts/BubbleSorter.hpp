#ifndef BUBBLESORTER_HPP
#define BUBBLESORTER_HPP

#include "../Isorter.hpp"
#include "../data_structures/ArraySequence.h"
#include "../compare.hpp"

template<typename T>
class BubbleSorter : public ISorter<T> {
public:
    void Sort(ArraySequence<T>& seq, int (*cmp)(const T&, const T&) = compare_default<T>) override {
        BubbleSort(seq, cmp);
    }

private:
    void BubbleSort(ArraySequence<T>& seq, int (*cmp)(const T&, const T&)) {
        int n = seq.get_length();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (cmp(seq.get(j), seq.get(j + 1)) > 0) {
                    seq.swap(j, j + 1);
                }
            }
        }
    }
};

#endif //BUBBLESORTER_HPP
