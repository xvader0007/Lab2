#ifndef LAB2_IMMUTABLE_LIST_SEQUENCE_H
#define LAB2_IMMUTABLE_LIST_SEQUENCE_H

#include "list_sequence.h"

template<class T>
class ImmutableListSequence : public ListSequence<T>
{
public:
    //------------------Констркуторы------------------
    ImmutableListSequence() : ListSequence<T>() {}

    ImmutableListSequence(T* arr, int count) : ListSequence<T>(arr, count) {}

    ImmutableListSequence(const LinkedList<T>& linkedList) : ListSequence<T>(linkedList) {}

    //конструктор копирования
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}

    //конструктор перемещения
    ImmutableListSequence(ImmutableListSequence<T>&& other) noexcept : ListSequence<T>(std::move(other)) {}

    Sequence<T>* Instance() override
    {
        return this->Clone();
    }

    //clone
    Sequence<T>* Clone() const override
    {
        return new ImmutableListSequence<T>(*this);
    }

    //операции
    Sequence<T>* Append(T object) override
    {
        ImmutableListSequence<T>* newInstance = static_cast<ImmutableListSequence<T>*>(this->Clone());
        newInstance->ListSequence<T>::Append_Internal(object);
        return newInstance;
    }

    Sequence<T>* Prepend(T object) override
    {
        ImmutableListSequence<T>* newInstance = static_cast<ImmutableListSequence<T>*>(this->Clone());
        newInstance->ListSequence<T>::Prepend_Internal(object);
        return newInstance;
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        ImmutableListSequence<T>* newInstance = static_cast<ImmutableListSequence<T>*>(this->Clone());
        newInstance->ListSequence<T>::InsertAt_Internal(object, index);
        return newInstance;
    }

    const T& operator[](int index) const
    {
        return (*this->objects)[index];
    }

    //-----Деструктор-----
    ~ImmutableListSequence() override = default;
};

#endif //LAB2_IMMUTABLE_LIST_SEQUENCE_H
