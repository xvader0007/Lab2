#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <string>
#include <tuple>
#include "i_collection.h"
#include "option.h"
#include "linked_list.h"
#include "list_sequence.h"
#include "array_sequence.h"
#include "ienumerable.h"

template<class T> class ArraySequence;

template<class T>
class Sequence : public ICollection<T>, public IEnumerable<T>
{
public:
    virtual Sequence<T>* Instance() = 0;
    virtual ~Sequence() = default; //деструктор для полиморфизма

    //-------геттеры-------
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int start, int end) const = 0;
    virtual int GetLen() const = 0;
    virtual const T& operator[](int index) const = 0;

    //операции
    virtual Sequence<T>* Append(T object) = 0;
    virtual Sequence<T>* Prepend(T object) = 0;
    virtual Sequence<T>* InsertAt(T object, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;
    virtual T& operator[](int index) = 0;

    int GetCount() const override
    {
        return static_cast<int>(this->GetLen());
    }

    //создание копии объекта
    virtual Sequence<T>* Clone() const = 0;

    template<typename Func>
    auto Map(Func f) const
    {
        using ResultType = decltype(f(T{}));

        ResultType* results = new ResultType[this->GetLen()];

        for(int i = 0; i < this->GetLen(); i++)
        {
            results[i] = f(this->Get(i));
        }

        Sequence<ResultType>* result = new ArraySequence<ResultType>(results, this->GetLen());
        delete[] results;

        return result;
    }

    template<typename Func, typename Temp>
    Temp Reduce(Func f, Temp init) const
    {
        Temp tm = init;

        for(int i = 0; i < this->GetLen(); i++)
        {
            tm = f(tm, this->Get(i));
        }

        return tm;
    }

    //option + try
    Option<T> TryGet(int index) const
    {
        if(index < 0 || index >= this->GetLen())
        {
            return Option<T>::no_exist();
        }

        return Option<T>::exist(this->Get(index));
    }

    Option<T> TryLast() const
    {
        if(this->GetLen() == 0)
        {
            return Option<T>::no_exist();
        }

        return Option<T>::exist(this->GetLast());
    }

    template<typename Predicate>
    Option<T> TryFind(Predicate pred) const
    {
        for(int i = 0; i < this->GetLen(); i++)
        {
            T val = this->Get(i);

            if(pred(val)) return Option<T>::exist(val);
        }

        return Option<T>::no_exist();
    }

    //=====================доп операции==================
    template<typename Predicate>
    Sequence<T>* Where(Predicate pred) const
    {
        int count = 0;

        for(int i = 0; i < this->GetLen(); i++)
        {
            if(pred(this->Get(i))) count++;
        }

        T* filtered = new T[count];
        int indx = 0;

        for(int i = 0; i < this->GetLen(); i++)
        {
            T val = this->Get(i);
            if(pred(val)) filtered[indx++] = val;
        }

        Sequence<T>* result = new ArraySequence<T>(filtered, count);
        delete[] filtered;

        return result;
    }

    template<typename U>
    Sequence<std::tuple<T, U>>* Zip(Sequence<U>* other) const
    {
        if(other == nullptr) throw std::invalid_argument("Zip: nullptr");

        int len1 = this->GetLen();
        int len2 = other->GetLen();
        int min_len = (len1 < len2) ? len1 : len2;

        using Pair = std::tuple<T, U>;
        Pair* pairs = new Pair[min_len];

        for(int i = 0; i < min_len; i++)
        {
            pairs[i] = std::make_tuple(this->Get(i), other->Get(i));
        }

        Sequence<Pair>* result = new ArraySequence<Pair>(pairs, min_len);
        delete[] pairs;

        return result;
    }

    template<typename Func>
    auto FlatMap(Func f) const
    {
        if(this->GetLen() == 0) throw std::runtime_error("FlatMap: пустая последовательность");

        auto* first = f(this->Get(0));
        using U = decltype(first->Get(0));
        delete first;

        LinkedList<U>* temp = new LinkedList<U>();

        for(int i = 0; i < this->GetLen(); i++)
        {
            Sequence<U>* inner = f(this->Get(i));
            if(inner != nullptr)
            {
                for(int j = 0; j < inner->GetLen(); j++)
                {
                    temp->Append(inner->Get(j));
                }

                delete inner;
            }
        }

        Sequence<U>* result = new ListSequence<U>(*temp);
        delete temp;

        return result;
    }

    virtual IEnumerator<T>* GetEnumerator() = 0;
};

#endif //LAB2_SEQUENCE_H
