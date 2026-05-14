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
    Sequence<T>* Append(T object) override
    {
        auto* instance = static_cast<MutableListSequence<T>*>(this->Instance());
        instance->ListSequence<T>::Append_Internal(object);
        return instance;
    }

    Sequence<T>* Prepend(T object) override
    {
        auto* instance = static_cast<MutableListSequence<T>*>(this->Instance());
        instance->ListSequence<T>::Prepend_Internal(object);
        return instance;
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        auto* instance = static_cast<MutableListSequence<T>*>(this->Instance());
        instance->ListSequence<T>::InsertAt_Internal(object, index);
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
    ~MutableListSequence() override = default;
};

#endif //LAB2_MUTABLE_LIST_SEQUENCE_H
