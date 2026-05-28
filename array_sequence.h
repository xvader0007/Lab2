#ifndef LAB2_ARRAY_SEQUENCE_H
#define LAB2_ARRAY_SEQUENCE_H

#include "dynamic_array.h"
#include "array_enumerator.h"

template<class T> class Sequence;

template<class T>
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T>* objects; //массив

    //внутрення логика
    void Append_Internal(T object)
    {
        int oldSize = objects->GetSize();
        objects->Resize(oldSize + 1);
        objects->Set(oldSize, object);
    }

    void Prepend_Internal(T object)
    {
        int oldSize = objects->GetSize();
        objects->Resize(oldSize + 1);

        for (int i = oldSize; i > 0; i--) {
            objects->Set(i, objects->Get(i - 1));
        }
        objects->Set(0, object);
    }

    void InsertAt_Internal(T object, int index) {
        if (index < 0 || index > objects->GetSize()) {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
                                    std::to_string(index) + " не в диапазоне [0, " +
                                    std::to_string(objects->GetSize()) + "]");
        }
        int oldSize = objects->GetSize();
        objects->Resize(oldSize + 1);

        for (int i = oldSize; i > index; i--) {
            objects->Set(i, objects->Get(i - 1));
        }
        objects->Set(index, object);
    }

public:
    virtual Sequence<T>* Instance() override {return this; }
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

    IEnumerator<T>* GetEnumerator() const override
    {
        return new ArrayEnumerator<T>(this->objects);
    }

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

    T Get(int index) const override {
        if (index < 0 || index >= objects->GetSize())
        {
            throw std::out_of_range("Index out of range");
        }

        IEnumerator<T>* enumerator = this->GetEnumerator();
        int current_ind = 0;

        while(current_ind <= index)
        {
            if(!enumerator->MoveNext())
            {
                delete enumerator;
                throw std::out_of_range("Index out of range");
            }
            current_ind++;
        }
        T result = enumerator->GetCurrent();
        delete enumerator;
        return result;
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

    const T& operator[](int index) const override
    {
        return (*objects)[index];
    }

    //операции

    Sequence<T>* Append(T object) override {
        auto* instance = static_cast<ArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::Append_Internal(object);
        return instance;
    }

    Sequence<T>* Prepend(T object) override {
        auto* instance = static_cast<ArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::Prepend_Internal(object);
        return instance;
    }

    Sequence<T>* InsertAt(T object, int index) override {
        auto* instance = static_cast<ArraySequence<T>*>(this->Instance());
        instance->ArraySequence<T>::InsertAt_Internal(object, index);
        return instance;
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

    T& operator[](int index) override
    {
        return (*objects)[index];
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
