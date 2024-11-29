#ifndef ISORTER_H
#define ISORTER_H

#include "data_structures/ArraySequence.h"
#include "SmrtPtr.hpp"

template<typename T>
class ISorter {
public:
    virtual ~ISorter() = default;

    virtual SmrtPtr<ArraySequence<T>> Sort(SmrtPtr<ArraySequence<T>> seq,
      int (*cmp)(const T&, const T&) = CompareDefault<T>) = 0;
};

#endif // ISORTER_H
