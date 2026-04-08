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
    MutableArraySequence<T>* Append(T object)
    {
        return static_cast<MutableArraySequence<T>*>(this->Instance()->Append_Internal(object));
    }

    MutableArraySequence<T>* Prepend(T object)
    {
        return static_cast<MutableArraySequence<T>*>(this->Instance()->Prepend_Internal(object));
    }

    MutableArraySequence<T>* InsertAt(T object, int index)
    {
        return static_cast<MutableArraySequence<T>*>(this->Instance()->InsertAt_Internal(object, index));
    }

    //-----Деструктор-----
    ~MutableArraySequence() override = default;
};

#endif //LAB2_MUTABLE_ARRAY_SEQUENCE_H
