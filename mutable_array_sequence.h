#ifndef LAB2_MUTABLE_ARRAY_SEQUENCE_H
#define LAB2_MUTABLE_ARRAY_SEQUENCE_H

#include "array_sequence.h"

template<class T>
class MutableArraySequence : public ArraySequence<T>
{
public:
    //------------------Констркуторы------------------
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(T* arr, int count) : ArraySequence<T>(arr, count) {}

    MutableArraySequence(const DynamicArray<T>& dynamicArray) : ArraySequence<T>(dynamicArray) {}

    //копирующий конструктор
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}

    //конструктор перемещения
    MutableArraySequence(MutableArraySequence<T>&& other) noexcept : ArraySequence<T>(std::move(other)) {}

    //переопределение Instance()
    //возвращаем this
    Sequence<T>* Instance() override
    {
        return this;
    }

    //Clone
    Sequence<T>* Clone() const override
    {
        return new MutableArraySequence<T>(*this);
    }

    //переопределение
    Sequence<T>* Append(T object) override
    {
        auto* instance = static_cast<MutableArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::Append_Internal(object);
        return instance;
    }

    Sequence<T>* Prepend(T object) override
    {
        auto* instance = static_cast<MutableArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::Prepend_Internal(object);
        return instance;
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        auto* instance = static_cast<MutableArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::InsertAt_Internal(object, index);
        return instance;
    }

    T& operator[](int index) override
    {
        return (*this->objects)[index];
    }

    const T& operator[](int index) const override
    {
        return (*this->objects)[index];
    }

    //-----Деструктор-----
    ~MutableArraySequence() override = default;
};

#endif //LAB2_MUTABLE_ARRAY_SEQUENCE_H
