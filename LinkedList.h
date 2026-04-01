#ifndef LAB2_LINKEDLIST_H
#define LAB2_LINKEDLIST_H

#include <iostream>
#include <string>

template<class T>
class LinkedList
{
private:
    struct Node
    {
        T data;     //значение
        Node* next;     //указатель на следующий элемент

        Node(const T& value) : data(value), next(nullptr) {} //конструктор
    };

    Node* head; //первый элемент
    Node* tail; //последний элемент
    int len;    //количество элементов

    //очистка списка
    void clear()
    {
        while(head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        len = 0;
    }

    //копирование элементов
    void copy(const LinkedList<T>& other)
    {
        if(other.len == 0) return;

        Node* current = other.head;
        while(current != nullptr)
        {
            Append(current->data);
            current = current->next;
        }
    }

public:
    //------------------Констркуторы------------------

    //конструктор
    LinkedList() : head(nullptr), tail(nullptr), len(0) {}

    //конструктор из массива элементов
    LinkedList(const T* objects, int count) : head(nullptr), tail(nullptr), len(0)
    {
        if(count < 0) throw std::invalid_argument("Число не может быть отрицательным!");

        for(int i = 0; i < count; i++) Append(objects[i]);
    }

    //копирующий конструктор
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), len(0)
    {
        copy(other);
    }

    //конструктор перемещения
    LinkedList(const LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), len(other.len)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.len = 0;
    }

    //-------Геттеры-------

    //получение первого элемента
    T GetFirst() const
    {
        if(len == 0) throw std::out_of_range("InvalidOperationsException: список пустой");

        return head->data;
    }

    //получение последнего элемента
    T GetLast() const
    {
        if(len == 0) throw std::out_of_range("InvalidOperationsException: список пустой");

        return tail->data;
    }

    //получение элемента по индексу
    T Get(int index) const
    {
        if(index < 0 || index >= len)
        {
            throw std::out_of_range("IndexOutOfRangeException: индекс " +
                                    std::to_string(index) + "не в диапозоне [0, " + std::to_string(len - 1) + "]");
        }

        Node* current = head;

        for(int i = 0; i < index; i++) current = current->next;

        return current->data;
    }

    //получение подсписка
    LinkedList<T>* GetSublist(int start, int end) const
    {
        if(start < 0 || end >= len || start > end)
        {
            throw std::out_of_range("IndexOutOfRangeException: не в диапозоне [" +
                                    std::to_string(start) + ", " +
                                    std::to_string(end) + "] при длине списка " +
                                    std::string(len));
        }

        LinkedList<T>* result = new LinkedList<T>();
        Node* current = head;

        for(int i = 0; i < start; i++) current = current->next;

        for(int i = start; i <= end; i++)
        {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }

    //получение длины списка
    int GetLen() const
    {
        return len;
    }

    //---------Сеттеры---------
    //-------Перегрузка операторов-------

    //-----Деструктор-----
    ~LinkedList()
    {
        clear();
    }

};

#endif //LAB2_LINKEDLIST_H
