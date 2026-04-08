#ifndef LAB2_IMMUTABLE_ARRAY_SEQUENCE_H
#define LAB2_IMMUTABLE_ARRAY_SEQUENCE_H

#include "array_sequence.h"

template<class T>
class ImmutableArraySequence : public ArraySequence<T>
{
public:
    //------------------Констркуторы------------------
    ImmutableArraySequence() : ArraySequence<T>() {}

    ImmutableArraySequence(T* arr, int count) : ArraySequence<T>(arr, count) {}

    ImmutableArraySequence(const DynamicArray<T>& dynamicArray) : ArraySequence<T>(dynamicArray) {}

    //копирующий конструктор
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}

    //конструктор перемещения
    ImmutableArraySequence(ImmutableArraySequence<T>&& other) noexcept : ArraySequence<T>(std::move(other)) {}

    //clone
    Sequence<T>* Instance() override
    {
        return this->Clone();
    }

    //clone для immutable
    Sequence<T>* Clone() const override
    {
        return new ImmutableArraySequence<T>(*this);
    }

    //операции
    Sequence<T>* Append(T object) override
    {
        return this->Instance()->Append_Internal(object);
    }

    Sequence<T>* Prepend(T object) override
    {
        return this->Instance()->Prepend_Internal(object);
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        return this->Instance()->InsertAt_Internal(object, index);
    }

    //-----Деструктор-----
    ~ImmutableArraySequence() override = default;
};

#endif //LAB2_IMMUTABLE_ARRAY_SEQUENCE_H
