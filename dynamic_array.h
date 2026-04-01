#ifndef LAB2_DYNAMIC_ARRAY_H
#define LAB2_DYNAMIC_ARRAY_H

#include <iostream>

template<class T>
class DynamicArray
{
private:
    T* data;    //указатель на массив
    int size;   //количество элементов

    //копирование
    void copy(const T* array, int count)
    {
        for(int i = 0; i < count; i++) data[i] = array[i];
    }

public:
    //------------------Констркуторы------------------

    //конструктор из массива элементов
    DynamicArray(T* objects, int count) : size(count)
    {
        if(count < 0) std::invalid_argument("Число не может быть отрицательным!");

        if(count == 0)
        {
            data = nullptr;
            return;
        }

        data = new T[count];
        copy(objects, count);
    }

    //конструктор с заданным размером
    explicit DynamicArray(int size) : size(size) //explicit для защиты от неявного преобразования
    {
        if(size < 0) throw std::invalid_argument("Число не может быть отрицательным!");

        if(size == 0)
        {
            data = nullptr;
            return;
        }

        data = new T[size](); //() для того, чтобы не было мусора в памяти
    }

    //копирующий конструктор
    DynamicArray(const DynamicArray<T>& other) : size(other.size)
    {
        if(size == 0)
        {
            data = nullptr;
            return;
        }

        data = new T[size];
        copy(other.data, size);
    }

    //конструктор перемещения
    DynamicArray(DynamicArray<T>&& other) noexcept : data(other.data), size(other.size)
    {
        other.data = nullptr;
        other.size = 0;
    }


    //оператор присваивания
    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        if(this != &other)
        {
            delete[] data;
            size = other.size;

            if(size == 0) data = nullptr;
            else
            {
                data = new T[size];
                copy(other.data, size);
            }
        }

        return *this;
    }

    //оператор присваивания с перемещением
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept
    {
        if(this != &other)
        {
            delete[] data;  //освободлаем старую память
            data = other.data;  //перемещаем
            size = other.size;
            other.data = nullptr;   //Обнуляем исходник
            other.size = 0;
        }

        return *this;
    }

    //-------Геттеры-------
    T Get(int index) const //получение элемента по индексу
    {
        if(index < 0 || index >= size)
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
            std::to_string(index) + "не в диапозоне [0, " + std::to_string(size - 1) + "]");
        }

        return data[index];
    }

    int GetSize() const //получение размера массива
    {
        return size;
    }

    //---------Сеттеры---------

    //установка значения элемента по индексу
    void Set(int index, T value)
    {
        if(index < 0 || index >= size)
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
            std::to_string(index) + "не в диапозоне [0, " + std::to_string(size - 1) + "]");
        }

        data[index] = value;
    }

    //изменение размера массива
    void Resize(int new_size)
    {
        if(new_size < 0) throw std::invalid_argument("Число не может быть отрицательным!");

        else if(size == new_size) return;

        else if(size == 0)
        {
            delete[] data;
            data = nullptr;
            size = 0;
            return;
        }

        T* new_data = new T[new_size]();

        int count = (new_size < size) ? new_size : size;

        for(int i = 0; i < count; i++) new_data[i] = data[i];

        delete[] data;

        data = new_data;
        size = new_size;
    }

    //-------Перегрузка операторов-------

    T* operator[](int index)
    {
        if(index < 0 || index >= size)
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
            std::to_string(index) + "не в диапозоне [0, " + std::to_string(size - 1) + "]");
        }

        return data[index];
    }

    T* operator[](int index) const
    {
        if(index < 0 || index >= size)
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
                                    std::to_string(index) + "не в диапозоне [0, " + std::to_string(size - 1) + "]");
        }

        return data[index];
    }

    //-----Деструктор-----
    ~DynamicArray()
    {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    void print() const
    {
        std::cout << "[";
        for(int i = 0; i < size; i++)
        {
            std::cout << data[i];
            if(i < size - 1) std::cout << ", ";
        }

        std::cout << "]";
        return;
    }

};

#endif //LAB2_DYNAMIC_ARRAY_H
