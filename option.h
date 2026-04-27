#ifndef LAB2_OPTION_H
#define LAB2_OPTION_H

#include <iostream>

template<typename T>
class Option
{
private:
    T value;        //хранимое значение
    bool is_value;  //есть ли значение

public:
    //------------------Констркуторы------------------
    Option() : is_value(false) {}

    Option(T val) : value(val), is_value(true) {}

    //-------геттеры-------
    bool is_exist() const {return is_value;}

    T Value_or(T default_value) const
    {
        return is_value ? value : default_value;
    }

    T GetValue() const
    {
        if(!is_value) throw std::runtime_error("Option: Trying to get value from None");

        return value;
    }

    static Option<T> exist(T val)
    {
        return Option<T>(val);
    }

    static Option<T> no_exist()
    {
        return Option<T>();
    }
};

#endif //LAB2_OPTION_H
