#ifndef LAB2_IMMUTABLE_LIST_SEQUENCE_H
#define LAB2_IMMUTABLE_LIST_SEQUENCE_H

#include "list_sequence.h"

template<class T>
class ImmutableListSequence : public ListSequence<T>
{
public:
    using ListSequence<T>::ListSequence;

    Sequence<T>* Instance() override {
        return this->Clone();
    }

    Sequence<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

    // Деструктор
    ~ImmutableListSequence() override = default;
};

#endif