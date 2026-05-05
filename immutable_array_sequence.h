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
        ImmutableArraySequence<T>* newInstance = static_cast<ImmutableArraySequence<T>*>(this->Clone());
        newInstance->ArraySequence<T>::Append_Internal(object);
        return newInstance;
    }

    Sequence<T>* Prepend(T object) override
    {
        ImmutableArraySequence<T>* newInstance = static_cast<ImmutableArraySequence<T>*>(this->Clone());
        newInstance->ArraySequence<T>::Prepend_Internal(object);
        return newInstance;
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        ImmutableArraySequence<T>* newInstance = static_cast<ImmutableArraySequence<T>*>(this->Clone());
        newInstance->ArraySequence<T>::InsertAt_Internal(object, index);
        return newInstance;
    }

    const T& operator[](int index) const override
    {
        return (*this->objects)[index];
    }

    //-----Деструктор-----
    ~ImmutableArraySequence() override = default;
};

#endif //LAB2_IMMUTABLE_ARRAY_SEQUENCE_H
