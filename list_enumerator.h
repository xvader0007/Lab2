#ifndef LAB2_LIST_ENUMERATOR_H
#define LAB2_LIST_ENUMERATOR_H

#include "ienumerable.h"
#include "linked_list.h"

template<typename T>
class ListEnumerator : public IEnumerator<T>
{
private:
    typename LinkedList<T>::Node* current;
    typename LinkedList<T>::Node* head;//для работы reset
public:
    ListEnumerator(const LinkedList<T>* list)
    {
        this->head = list->head;
        this->current = nullptr;
    }

    bool MoveNext() override
    {
        if(current == nullptr) current = head;
        else current = current->next;

        return (current != nullptr);
    }

    T GetCurrent() const override
    {
        if(current == nullptr) throw std::out_of_range("Неправильная позиция");

        return current->data;
    }

    void Reset() override
    {
        current = nullptr;
    }
};

#endif //LAB2_LIST_ENUMERATOR_H
