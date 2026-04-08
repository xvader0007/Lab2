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
        return static_cast<MutableListSequence<T>*>(this->Instance()->Append_Internal(object));
    }

    MutableListSequence<T>* Prepend(T object)
    {
        return static_cast<MutableListSequence<T>*>(this->Instance()->Prepend_Internal(object));
    }

    MutableListSequence<T>* InsertAt(T object, int index)
    {
        return static_cast<MutableListSequence<T>*>(this->Instance()->InsertAt_Internal(object, index));
    }

    //-----Деструктор-----
    ~MutableListSequence() override = default;
};

#endif //LAB2_MUTABLE_LIST_SEQUENCE_H
