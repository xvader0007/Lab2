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

    void Append_Internal(T object) {
        objects->Append(object);
    }
    void Prepend_Internal(T object) {
        objects->Prepend(object);
    }
    void InsertAt_Internal(T object, int index) {
        objects->InsertAt(object, index);
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
    IEnumerator<T>* GetEnumerator() const override
    {
        return new ListEnumerator<T>(objects);
    }

    T GetFirst() const override
    {
        return objects->GetFirst();
    }

    T GetLast() const override
    {
        return objects->GetLast();
    }

    T Get(int index) const override {
        if (index < 0 || index >= objects->GetLen()) {
            throw std::out_of_range("Index out of range");
        }
        IEnumerator<T>* enumerator = this->GetEnumerator();
        for (int i = 0; i <= index; ++i) {
            if (!enumerator->MoveNext()) {
                delete enumerator;
                throw std::out_of_range("Index out of range");
            }
        }
        T result = enumerator->GetCurrent();
        delete enumerator;
        return result;
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

    const T& operator[](int index) const override
    {
        return (*objects)[index];
    }

    //операции
    Sequence<T>* Append(T object) override {
        auto* instance = static_cast<ListSequence<T>*>(this->Instance());
        instance->Append_Internal(object);
        return instance;
    }

    Sequence<T>* Prepend(T object) override {
        auto* instance = static_cast<ListSequence<T>*>(this->Instance());
        instance->Prepend_Internal(object);
        return instance;
    }

    Sequence<T>* InsertAt(T object, int index) override {
        auto* instance = static_cast<ListSequence<T>*>(this->Instance());
        instance->InsertAt_Internal(object, index);
        return instance;
    }

    Sequence<T>* Concat(Sequence<T>* other) const override {
        if (other == nullptr) {
            throw std::invalid_argument("Concat: nullptr");
        }
        ListSequence<T>* result = new ListSequence<T>(*this);
        for (int i = 0; i < other->GetLen(); i++) {
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

    Sequence<T>* Instance() override
    {
        return this;
    }

    //-----Деструктор-----
    ~ListSequence() override
    {
        delete objects;
    }
};

#endif //LAB2_LIST_SEQUENCE_H
