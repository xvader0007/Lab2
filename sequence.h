#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

#include <string>

template<class T>
class Sequence
{
public:
    virtual ~Sequence() = default; //деструктор для полиморфизма

    //-------геттеры-------
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int start, int end) const = 0;
    virtual int GetLen() const = 0;

    //операции
    virtual Sequence<T>* Append(T object) = 0;
    virtual Sequence<T>* Prepend(T object) = 0;
    virtual Sequence<T>* InsertAt(T object, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;

    //создание копии объекта
    virtual Sequence<T>* Clone() const = 0;
};

#endif //LAB2_SEQUENCE_H
