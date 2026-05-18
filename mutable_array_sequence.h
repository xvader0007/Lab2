#ifndef LAB2_MUTABLE_ARRAY_SEQUENCE_H
#define LAB2_MUTABLE_ARRAY_SEQUENCE_H

#include "array_sequence.h"

template<class T>
class MutableArraySequence : public ArraySequence<T>
{
public:
    using ArraySequence<T>::ArraySequence;

    Sequence<T>* Instance() override {
        return this;
    }

    Sequence<T>* Clone() const override {
        return new MutableArraySequence<T>(*this);
    }

    // Деструктор
    ~MutableArraySequence() override = default;
};

#endif