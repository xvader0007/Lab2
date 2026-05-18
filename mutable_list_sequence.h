#ifndef LAB2_MUTABLE_LIST_SEQUENCE_H
#define LAB2_MUTABLE_LIST_SEQUENCE_H

#include "list_sequence.h"

template<class T>
class MutableListSequence : public ListSequence<T>
{
public:
    using ListSequence<T>::ListSequence;

    Sequence<T>* Instance() override {
        return this;
    }

    Sequence<T>* Clone() const override {
        return new MutableListSequence<T>(*this);
    }

    // Деструктор
    ~MutableListSequence() override = default;
};

#endif