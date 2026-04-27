#ifndef LAB2_IENUMERABLE_H
#define LAB2_IENUMERABLE_H

//IEnumerator
template<typename T>
class IEnumerator
{
public:
    virtual bool MoveNext() = 0; //возвращает true, если элемент есть
    virtual T GetCurrent() const = 0; //получить текущий элемент
    virtual void Reset() = 0; //сброс в начало

    virtual ~IEnumerator() = default;
};

//IEnumerable
template<typename T>
class IEnumerable
{
public:
    virtual IEnumerator<T>* GetEnumerator() = 0;

    virtual ~IEnumerable() = default;
};

#endif //LAB2_IENUMERABLE_H
