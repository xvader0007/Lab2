#ifndef LAB2_I_COLLECTION_H
#define LAB2_I_COLLECTION_H

template<typename T>
class ICollection
{
public:
    virtual T Get(int index) const = 0;
    virtual int GetCount() const = 0;
    virtual ICollection<T>* Clone() const = 0;
    virtual ~ICollection() = default; //виртуальный деструктор
};

#endif //LAB2_I_COLLECTION_H
