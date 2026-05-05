#ifndef LAB2_MUTABLE_LIST_SEQUENCE_H
#define LAB2_MUTABLE_LIST_SEQUENCE_H

#include "list_sequence.h"

template<class T>
class MutableListSequence : public ListSequence<T>
{
public:
    //------------------Констркуторы------------------
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* arr, int count) : ListSequence<T>(arr, count) {}
    MutableListSequence(const LinkedList<T>& linkedList) : ListSequence<T>(linkedList) {}
    //конструктор копирования
    MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}
    //конструктор перемещения
    MutableListSequence(MutableListSequence<T>&& other) noexcept : ListSequence<T>(std::move(other)) {}

    Sequence<T>* Instance() override
    {
        return this;
    }

    //clone
    Sequence<T>* Clone() const override
    {
        return new MutableListSequence<T>(*this);
    }

    //операции
    MutableListSequence<T>* Append(T object)
    {
        ListSequence<T>::Append_Internal(object);
        return this;
    }

    MutableListSequence<T>* Prepend(T object)
    {
        ListSequence<T>::Prepend_Internal(object);
        return this;
    }

    MutableListSequence<T>* InsertAt(T object, int index)
    {
        ListSequence<T>::InsertAt_Internal(object, index);
        return this;
    }

    T& operator[](int index)
    {
        return (*this->objects)[index];
    }

    const T& operator[](int index) const
    {
        return (*this->objects)[index];
    }

    //-----Деструктор-----
    ~MutableListSequence() override = default;
};

#endif //LAB2_MUTABLE_LIST_SEQUENCE_H
