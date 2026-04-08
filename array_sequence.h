#ifndef LAB2_ARRAY_SEQUENCE_H
#define LAB2_ARRAY_SEQUENCE_H

#include "sequence.h"
#include "dynamic_array.h"

template<class T>
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T>* objects; //массив

    //внутрення логика
    Sequence<T>* Append_Internal(T object)
    {
        objects->Resize(objects->GetSize() + 1);
        objects->Set(objects->GetSize() - 1, object);

        return this;
    }
    Sequence<T>* Prepend_Internal(T object)
    {
        objects->Resize(objects->GetSize() + 1);

        for(int i = objects->GetSize() - 1; i > 0 ; i--)
        {
            objects->Set(i, objects->Get(i - 1));
        }

        objects->Set(0, object);

        return this;
    }

    Sequence<T>* InsertAt_Internal(T object, int index)
    {
        if(index < 0 || index >= objects->GetSize())
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
                                    std::to_string(index) + "не в диапозоне [0, " + std::to_string(objects->GetSize()) + "]");
        }
        else if(index == 0) return Prepend_Internal(object);
        else if(index == objects->GetSize()) return Append_Internal(object);

        objects->Resize(objects->GetSize() + 1);

        for(int i = objects->GetSize() - 1; i > index; i--)
        {
            objects->Set(i, objects->Get(i - 1));
        }

        objects->Set(index, object);

        return this;
    }

    virtual Sequence<T>* Instance() = 0;

public:
    //------------------Констркуторы------------------
    ArraySequence() : objects(new DynamicArray<T>(0)) {}

    ArraySequence(T* arr, int count) : objects(new DynamicArray<T>(arr, count)) {}

    ArraySequence(const DynamicArray<T>& dynamic_array) : objects(new DynamicArray<T>(dynamic_array)) {}

    //копирующий конструктор
    ArraySequence(const ArraySequence<T>& other) : objects(new DynamicArray<T>(*other.objects)) {}

    //конструктор перемещения
    ArraySequence(ArraySequence<T>&& other) noexcept : objects(other.objects)
    {
        other.objects = nullptr;
    }

    //-------Геттеры-------

    T GetFirst() const override
    {
        if(objects->GetSize() == 0) throw std::out_of_range("InvalidOperationException: последовательность пуста");

        return objects->Get(0);
    }

    T GetLast() const override
    {
        if(objects->GetSize() == 0) throw std::out_of_range("InvalidOperationException: последовательность пуста");

        return objects->Get(objects->GetSize() - 1);
    }

    T Get(int index) const override
    {
        return objects->Get(index);
    }

    Sequence<T>* GetSubsequence(int start, int end) const override
    {
        if(start < 0 || end >= objects->GetSize() || start > end)
        {
            throw std::out_of_range("IndexOutOfRangeException: некорректный диапазон");
        }

        int sub_size = end - start + 1;
        T* sub_Array = new T[sub_size];

        for(int i = 0; i < sub_size; i++)
        {
            sub_Array[i] = objects->Get(start + i);
        }

        Sequence<T>* result = new ArraySequence<T>(sub_Array, sub_size);
        delete[] sub_Array;

        return result;
    }

    int GetLen() const override
    {
        return objects->GetSize();
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

        //копия
        ArraySequence<T>* result = new ArraySequence<T>(*this);

        for(int i = 0; i < other->GetLen(); i++)
        {
            result->Append_Internal(other->Get(i));
        }

        return result;
    }

    //clone для immutable
    Sequence<T>* Clone() const override
    {
        return new ArraySequence<T>(*this);
    }

    //-----Деструктор-----
    ~ArraySequence() override
    {
        delete objects;
    }
};

#endif //LAB2_ARRAY_SEQUENCE_H
