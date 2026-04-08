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
    Sequence<T>* Append(T object)
    {
        return this->Instance()->Append_Internal(object);
    }

    Sequence<T>* Prepend(T object)
    {
        return this->Instance()->Prepend_Internal(object);
    }

    Sequence<T>* InsertAt(T object, int index)
    {
        return this->Instance()->InsertAt_Internal(object, index);
    }

    //-----Деструктор-----
    ~ImmutableListSequence() override = default;
};

#endif //LAB2_IMMUTABLE_LIST_SEQUENCE_H
