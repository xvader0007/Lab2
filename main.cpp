#include <iostream>
#include <tuple>
#include <string>
#include <limits>
//#include <chrono>
#include "sequence.h"
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"
#include "mutable_list_sequence.h"
#include "immutable_list_sequence.h"
#include "list_sequence.h"

void run_tests();

Sequence<int>* current_seq = nullptr; //глобальная пос. для работы в меню

void clean()
{
    delete current_seq;
    current_seq = nullptr;
}

void print_current()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "[";
    for(int i = 0; i < current_seq->GetLen(); i++)
    {
        std::cout << current_seq->Get(i);
        if(i < current_seq->GetLen() - 1) std::cout << " , ";
    }
    std::cout << "] (длина: " << current_seq->GetLen() << ")\n";
}

void clear_input_buffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void create_sequence(int type)
{
    clean();
    int arr[] = { 1, 2, 3,};
    switch(type)
    {
        case 1:
            current_seq = new MutableArraySequence<int>(arr, 3);
            std::cout << "MutableArraySequence: создано успешно!";
        case 2:
            current_seq = new MutableListSequence<int>(arr, 3);
            std::cout << "MutableArraySequence: создано успешно!";
        case 3:
            current_seq = new ImmutableArraySequence<int>(arr, 3);
            std::cout << "ImmutableArraySequence: создано успешно!";
        case 4:
            current_seq = new ImmutableListSequence<int>(arr, 3);
            std::cout << "MutableArraySequence: создано успешно!";
    }
}

void add_element(bool prepend)
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int value;
    std::cout << "Введите значение: ";

    if(!(std::cin >> value))
    {
        clear_input_buffer();
        std::cout << "Ошибка ввода!\n";

        return;
    }

    current_seq = prepend ? current_seq->Prepend(value) : current_seq->Append(value);
    std::cout << "Элемент " << (prepend ? "в начало" : "в конец") << "добавлен!\n";
}

void insert_at()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int value, index;
    std::cout << "Значение: ";
    std::cin >> value;
    std::cout << "Индекс: ";
    std::cin >> index;

    try
    {
        current_seq = current_seq->InsertAt(value, index);
        std::cout << "Вставлено!\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void get_element()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int index;

    std::cout << "Индекс: ";
    std::cin >> index;

    try
    {
        std::cout << "seq[" << index << "] = " << current_seq->Get(index) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void read_bracket()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int index;
    std::cout << "Индекс: ";
    std::cin >> index;

    try
    {
        std::cout << "(*seq)[" << index << "] = " << (*current_seq)[index] << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void write_bracket()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int value, index;

    std::cout << "Индекс: ";
    std::cin >> index;
    std::cout << "Значение: ";
    std::cin >> value;

    try
    {
        (*current_seq)[index] = value;
        std::cout << "Изменено!\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void map_menu()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "Настройка Map: введите формулу f(x) = k * x + b\n";
    int k, b;

    std::cout << "Коэффициент k: ";
    std::cin >> k;
    std::cout << "Слагаемое b: ";
    std::cin >> b;
    clear_input_buffer();

    auto* res = current_seq->Map([k, b](int x) {return k * x + b;});
    std::cout << "Результат f(x) = " << k << "*x + " << b << ": [";
    for(int i = 0; i < res->GetLen(); i++)
    {
        std::cout << res->Get(i) << (i < res->GetLen() - 1 ? ", " : "");
    }
    std::cout << "]\n";

    delete res;
}

void reduce_map()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "\nReduce: выберите операцию\n";
    std::cout << "\n1: сумма (+)\n";
    std::cout << "\n2: произведение (*)\n";
    std::cout << "\n3: максимум\n";
    std::cout << "\n4: миниммум\n";

    int op;

    std::cin >> op;

    clear_input_buffer();

    switch (op)
    {
        case 1:
        {
            int sum = current_seq->Reduce([](int acc, int x){return acc + x;}, 0);
            std::cout << "Сумма: " << sum << "\n";
            break;
        }
        case 2:
        {
            int prod = current_seq->Reduce([](int acc, int x) { return acc * x; }, 1);
            std::cout << "Произведение: " << prod << "\n";
            break;
        }

        case 3:
        {
            if(current_seq->GetLen() == 0)
            {
                std::cout << "Пустая последовательность!\n";
                return;
            }

            int maxx = current_seq->Reduce([](int acc, int x) {return (x > acc) ? x : acc;}, current_seq->Get(0));
            std::cout << "Максимум: " << maxx << "\n";
            break;
        }

        case 4:
        {
            if(current_seq->GetLen() == 0)
            {
                std::cout << "Пустая последовательность!\n";
                return;
            }

            int minn = current_seq->Reduce([](int acc, int x) {return (x < acc) ? x : acc;}, current_seq->Get(0));
            std::cout << "Минимум: " << minn << "\n";
            break;
        }

        default:
            std::cout << "Неверный выбор\n";
    }
}

void where_menu()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "Where: выберите оператор (>, <, >= (b), <= (l), != (!), == (=))\n";
    std::cout << "Оператор: ";

    int threhold;
    char op;
    std::cin >> op;
    std::cout << "Значение: ";
    std::cin >> threhold;

    clear_input_buffer();

    Sequence<int>* res = nullptr;

    std::cout << "Фильтр (x " << op << " " << threhold << "): [";
    switch (op)
    {
        case '>':
            res = current_seq->Where([threhold](int x){return x > threhold;});
            break;
        case '<':
            res = current_seq->Where([threhold](int x){return x < threhold;});
            break;
        case 'b':
            res = current_seq->Where([threhold](int x){return x >= threhold;});
            break;
        case 'l':
            res = current_seq->Where([threhold](int x){return x <= threhold;});
            break;
        case '!':
            res = current_seq->Where([threhold](int x){return x != threhold;});
            break;
        case '=':
            res = current_seq->Where([threhold](int x){return x == threhold;});
            break;
        default:
            std::cout << "Неверный выбор!\n";
            return;

    }

    for(int i = 0; i < res->GetLen(); i++)
    {
        std::cout << res->Get(i) << (i < res->GetLen() - 1 ? ", ": "");
    }

    std::cout << "] (найдено: " << res->GetLen() << ")\n";

    delete res;
}

void zip_menu()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "\nZip: тип второй последовательности\n";
    std::cout << "1: Строки (A, B, C...)\n";
    std::cout << "2: Числа (10, 20, 30...)\n";
    std::cout << "3: Ввести вручную\n";

    int type;
    std::cin >> type;
    clear_input_buffer();

    int len = current_seq->GetLen();

    switch (type)
    {
        case 1:
        {
            std::string *strs = new std::string[len];

            for (int i = 0; i < len; i++) {
                strs[i] = std::string(1, 'A' + (i % 26));
            }

            auto *s2 = new ArraySequence<std::string>(strs, len);
            auto *zipped = current_seq->Zip(s2);

            std::cout << "Zip (int, string): \n";
            for (int i = 0; i < zipped->GetLen(); i++) {
                auto p = zipped->Get(i);
                std::cout << " [" << i << "] = (" << std::get<0>(p) << ", \"" << std::get<1>(p) << "\")\n";
            }

            delete[] strs;
            delete zipped;
            delete s2;

            break;
        }

        case 2:
        {
            int* nums = new int[len];

            for(int i = 0; i < len; i++)
            {
                nums[i] = (i + 1) * 10;
            }

            auto* s2 = new ArraySequence<int>(nums, len);
            auto* zipped = current_seq->Zip(s2);

            std::cout << "Zip (int, int): \n";

            for(int i = 0; i < zipped->GetLen(); i++)
            {
                auto p = zipped->Get(i);
                std::cout << " [" << i << "] = (" << std::get<0>(p) << ", \"" << std::get<1>(p) << "\")\n";

            }

            delete[] nums;
            delete s2;
            delete zipped;

            break;
        }

        case 3:
            std::cout << "Введите " << len << " элемент(ов):\n";

            int* vals = new int[len];

            for(int i = 0; i < len; i++)
            {
                std::cout << " [" << i << "]: ";
                std::cin >> vals[i];
            }

            auto* s2 = new ArraySequence<int>(vals, len);
            auto* zipped = current_seq->Zip(s2);

            std::cout << "Zip результат:\n";

            for(int i = 0; i < zipped->GetLen(); i++)
            {
                auto p = zipped->Get(i);
                std::cout << " [" << i << "] = (" << std::get<0>(p) << ", \"" << std::get<1>(p) << "\")\n";
            }

            delete[] vals;
            delete s2;
            delete zipped;

            break;
    }
}

void flatmap_menu()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "\nFlatMap: выберите шаблон:\n";
    std::cout << "1: [x, x]\n";
    std::cout << "2: [x, x*N]\n";
    std::cout << "3: [x, x+N]\n";
    std::cout << "Ввод: ";

    int op, N = 0;
    std::cin >> op;

    if(op == 2 || op == 3)
    {
        std::cout << "Введите N: ";
        std::cin >> N;
    }

    clear_input_buffer();

    auto* res = current_seq->FlatMap([op, N](int x){
        int* data = new int[2];
        if(op == 1) {data[0] = x; data[1] = x;}
        else if(op == 2) {data[0] = x; data[1] = x * N;}
        else if(op == 3) {data[0] = x; data[1] = x + N;}
        return new ArraySequence<int>(data, 2);
    });

    std::cout << "Результат: [";

    for(int i = 0; i < res->GetLen(); i++)
    {
        std::cout << res->Get(i) << (i < res->GetLen() - 1 ? ", " : "");
    }

    std::cout << "]\n";

    delete res;
}

int main()
{


  return 0;
}
