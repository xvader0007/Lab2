#ifndef LAB2_ARRAY_ENUMERATOR_H
#define LAB2_ARRAY_ENUMERATOR_H

#include "ienumerable.h"
#include "dynamic_array.h"

template<typename T>
class ArrayEnumerator : public IEnumerator<T>
{
private:
    const DynamicArray<T>* array;   //указатель для чтения данных
    int cur_index;                  //текущая позиция

public:
    ArrayEnumerator(const DynamicArray<T>* arr) : array(arr), cur_index(-1) {}//-1 значит до начала

    bool MoveNext() override
    {
        cur_index++;
        return (cur_index >= 0 && cur_index < array->GetSize());
    }

    T GetCurrent() const override
    {
        if(cur_index < 0 || cur_index >= array->GetSize()) throw std::out_of_range("Enumerator: неверная позиция");

        return array->Get(cur_index);
    }

    void Reset() override
    {
        cur_index = -1;
    }
};

#endif //LAB2_ARRAY_ENUMERATOR_H
