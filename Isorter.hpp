#ifndef LAB2_ISORTER_HPP
#define LAB2_ISORTER_HPP

#include "data_structures/ArraySequence.h"

template<typename T>
class ISorter {
public:
    virtual ~ISorter() = default;

    // Чистый виртуальный метод сортировки
    virtual ArraySequence<T>* Sort(ArraySequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
};

#endif //LAB2_ISORTER_HPP
