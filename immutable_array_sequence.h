#ifndef LAB2_IMMUTABLE_ARRAY_SEQUENCE_H
#define LAB2_IMMUTABLE_ARRAY_SEQUENCE_H

#include "array_sequence.h"

template<class T>
class ImmutableArraySequence : public ArraySequence<T>
{
public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* Instance() override {
        return this->Clone();
    }

    Sequence<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    // Деструктор
    ~ImmutableArraySequence() override = default;
};

#endif