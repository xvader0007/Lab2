#ifndef LAB2_LIST_SEQUENCE_H
#define LAB2_LIST_SEQUENCE_H

#include "linked_list.h"
#include "list_enumerator.h"

template<class T> class Sequence;

template<class T>
class ListSequence : public Sequence<T>
{
protected:
    LinkedList<T>* objects;

    Sequence<T>* Append_Internal(T object)
    {
        objects->Append(object);

        return this;
    }

    Sequence<T>* Prepend_Internal(T object)
    {
        objects->Prepend(object);

        return this;
    }

    Sequence<T>* InsertAt_Internal(T object, int index)
    {
        objects->InsertAt(object, index);

        return this;
    }

public:
    //------------------Констркуторы------------------
    ListSequence() : objects(new LinkedList<T>()) {}

    ListSequence(T* arr, int count) : objects(new LinkedList<T>(arr, count)) {}

    ListSequence(const LinkedList<T>& linkedList) : objects(new LinkedList<T>(linkedList)) {}

    //копирующий контсруктор
    ListSequence(const ListSequence<T>& other) : objects(new LinkedList<T>(*other.objects)) {}

    //конструктор перемещения
    ListSequence(ListSequence<T>&& other) noexcept : objects(other.objects)
    {
        other.objects = nullptr;
    }

    //-------Геттеры-------
    IEnumerator<T>* GetEnumerator() override
    {
        return new ListEnumerator<T>(this->objects);
    }

    T GetFirst() const override
    {
        return objects->GetFirst();
    }

    T GetLast() const override
    {
        return objects->GetLast();
    }

    T Get(int index) const override
    {
        return objects->Get(index);
    }

    Sequence<T>* GetSubsequence(int start, int end) const override
    {
        LinkedList<T>* sub_list = objects->GetSublist(start, end);

        Sequence<T>* result = new ListSequence<T>(*sub_list);

        delete sub_list;

        return result;
    }

    int GetLen() const override
    {
        return objects->GetLen();
    }

    T& operator[](int index) const override
    {
        return (*objects)[index];
    }

    //операции
    Sequence<T>* Append(T object) override
    {
        return Append_Internal(object);
    }

    Sequence<T>* Prepend(T object) override
    {
        return Prepend_Internal(object);
    }

    Sequence<T>* InsertAt(T object, int index) override
    {
        return InsertAt_Internal(object, index);
    }

    Sequence<T>* Concat(Sequence<T>* other) const override
    {
        if(other == nullptr)
        {
            throw std::invalid_argument("Concat: нельзя объединить с nullptr");
        }

        ListSequence<T>* result = new ListSequence<T>(*this);

        for(int i = 0; i < other->GetLen(); i++)
        {
            result->Append_Internal(other->Get(i));
        }

        return result;
    }

    T& operator[](int index) override
    {
        return (*objects)[index];
    }

    //clone
    Sequence<T>* Clone() const override
    {
        return new ListSequence<T>(*this);
    }

    //-----Деструктор-----
    ~ListSequence() override
    {
        delete objects;
    }
};

#endif //LAB2_LIST_SEQUENCE_H
