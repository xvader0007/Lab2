#include <iostream>
#include <tuple>
#include <string>
#include <limits>
#include <windows.h>
#include "sequence.h"
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"
#include "mutable_list_sequence.h"
#include "immutable_list_sequence.h"
#include "list_sequence.h"

void run_tests();

Sequence<int>* current_seq = nullptr; //глобальная пос. для работы в меню
Sequence<int>* current_seq2 = nullptr;

int current_type = 1;

void clean()
{
    delete current_seq;
    delete current_seq2;
    current_seq = nullptr;
    current_seq2 = nullptr;
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
        if(i < current_seq->GetLen() - 1) std::cout << ", ";
    }
    std::cout << "] (длина: " << current_seq->GetLen() << ")\n";
}

void print_sequence(Sequence<int>* seq, const std::string& lab)
{
    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << lab << "[";
    for(int i = 0; i < seq->GetLen(); i++)
    {
        std::cout << seq->Get(i) << (i < seq->GetLen() - 1 ? ", " : "");
    }

    std::cout << "]\n";
}

void clear_input_buffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Sequence<int>*& select_sequence(const std::string& name)
{
    std::cout << name;
    std::cout << ": выберите последовательность: \n";
    std::cout << "1. Seq1 ";
    print_sequence(current_seq, "");
    std::cout << "2. Seq2 ";
    print_sequence(current_seq2, "");
    std::cout << "Выбор (1/2): ";

    int choice;

    if (!(std::cin >> choice) || (choice != 1 && choice != 2))
    {
        clear_input_buffer();
        std::cout << "Неверный выбор!\n";

        static Sequence<int>* seq3 = nullptr;
        return seq3;
    }
    clear_input_buffer();

    return (choice == 1) ? current_seq : current_seq2;
}

void create_sequence(int slot)
{
    int arr[] = { 1, 2, 3,};
    Sequence<int>*& target = (slot == 1) ? current_seq : current_seq2;

    delete target;

    switch(current_type)
    {
        case 1:
            target = new MutableArraySequence<int>(arr, 3);
            break;
        case 2:
            target = new MutableListSequence<int>(arr, 3);
            break;
        case 3:
            target = new ImmutableArraySequence<int>(arr, 3);
            break;
        case 4:
            target = new ImmutableListSequence<int>(arr, 3);
            break;
    }

    std::cout << "Создано: " << (slot == 1 ? "Seq1" : "Seq2") << ": ";
    print_sequence(target, "");
}

void add_element(bool prepend)
{
    Sequence<int>*& seq = select_sequence(prepend ? "Prepend" : "Append");

    if(!seq)
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

    seq = prepend ? seq->Prepend(value) : seq->Append(value);
    std::cout << "Элемент " << (prepend ? "в начало" : "в конец") << " добавлен!\n";
}

void insert_at()
{
    Sequence<int>*& seq = select_sequence("InsertAt");
    if(!seq)
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
        seq = seq->InsertAt(value, index);
        std::cout << "Вставлено!\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void get_element()
{
    Sequence<int>*& seq = select_sequence("Get");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int index;

    std::cout << "Индекс: ";
    std::cin >> index;

    try
    {
        std::cout << "seq[" << index << "] = " << seq->Get(index) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void read_bracket()
{
    Sequence<int>*& seq = select_sequence("operator[]");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int index;
    std::cout << "Индекс: ";
    std::cin >> index;

    try
    {
        std::cout << "(*seq)[" << index << "] = " << (*seq)[index] << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void write_bracket()
{
    Sequence<int>*& seq = select_sequence("operator[]");

    if(!seq)
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
        (*seq)[index] = value;
        std::cout << "Изменено!\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void map_menu()
{
    Sequence<int>*& seq = select_sequence("Map");

    if(!seq)
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

    auto* res = seq->Map([k, b](int x) {return k * x + b;});
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
    Sequence<int>*& seq = select_sequence("Reduce");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "\nReduce: выберите операцию\n";
    std::cout << "\n1: сумма (+)\n";
    std::cout << "\n2: произведение (*)\n";
    std::cout << "\n3: максимум\n";
    std::cout << "\n4: минимум\n";

    int op;

    std::cin >> op;

    clear_input_buffer();

    switch (op)
    {
        case 1:
        {
            long int sum = seq->Reduce([](long int acc, int x){return acc + x;}, 0);
            std::cout << "Сумма: " << sum << "\n";
            break;
        }
        case 2:
        {
            long int prod = seq->Reduce([](long int acc, int x) { return acc * x; }, 1);
            std::cout << "Произведение: " << prod << "\n";
            break;
        }

        case 3:
        {
            if(seq->GetLen() == 0)
            {
                std::cout << "Пустая последовательность!\n";
                return;
            }

            int maxx = seq->Reduce([](int acc, int x) {return (x > acc) ? x : acc;}, seq->Get(0));
            std::cout << "Максимум: " << maxx << "\n";
            break;
        }

        case 4:
        {
            if(seq->GetLen() == 0)
            {
                std::cout << "Пустая последовательность!\n";
                return;
            }

            int minn = seq->Reduce([](int acc, int x) {return (x < acc) ? x : acc;}, seq->Get(0));
            std::cout << "Минимум: " << minn << "\n";
            break;
        }

        default:
            std::cout << "Неверный выбор\n";
    }
}

void where_menu()
{
    Sequence<int>*& seq = select_sequence("Where");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "Where: выберите оператор (>, <, >= (b), <= (l), != (!), == (=))\n";
    std::cout << "Оператор: ";

    int threshold;
    char op;
    std::cin >> op;
    std::cout << "Значение: ";
    std::cin >> threshold;

    clear_input_buffer();

    Sequence<int>* res = nullptr;

    std::cout << "Фильтр (x " << op << " " << threshold << "): [";
    switch (op)
    {
        case '>':
            res = seq->Where([threshold](int x){return x > threshold;});
            break;
        case '<':
            res = seq->Where([threshold](int x){return x < threshold;});
            break;
        case 'b':
            res = seq->Where([threshold](int x){return x >= threshold;});
            break;
        case 'l':
            res = seq->Where([threshold](int x){return x <= threshold;});
            break;
        case '!':
            res = seq->Where([threshold](int x){return x != threshold;});
            break;
        case '=':
            res = seq->Where([threshold](int x){return x == threshold;});
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
    Sequence<int>*& seq = select_sequence("Flatmap");

    if(!seq)
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

    auto* res = seq->FlatMap([op, N](int x){
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

void try_get()
{
    Sequence<int>*& seq = select_sequence("TryGet");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int index;

    std::cout << "TryGet, индекс: ";
    std::cin >> index;

    Option<int> opt = seq->TryGet(index);
    if(opt.is_exist()) std::cout << "Найдено: " << opt.GetValue() << std::endl;
    else std::cout << "Не найдено (по умолчанию: " << opt.Value_or(-999) << ")\n";
}

void try_find()
{
    Sequence<int>*& seq = select_sequence("TryFind");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    int value;
    char op;

    std::cout << "TryFind: выберите условие (>, <, >= (b), <= (l), != (!), == (=))\n";
    std::cout << "Оператор: ";
    std::cin >> op;

    std::cout << "Значение: ";
    std::cin >> value;

    clear_input_buffer();

    Option<int> found;

    switch(op)
    {
        case '>':
            found = seq->TryFind([value](int x){return x > value;});
            break;
        case '<':
            found = seq->TryFind([value](int x){return x < value;});
            break;
        case 'b':
            found = seq->TryFind([value](int x){return x >= value;});
            break;
        case 'l':
            found = seq->TryFind([value](int x){return x <= value;});
            break;
        case '!':
            found = seq->TryFind([value](int x){return x != value;});
            break;
        case '=':
            found = seq->TryFind([value](int x){return x == value;});
            break;
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }

    if(found.is_exist()) std::cout << "Первое совпадение: " << found.GetValue() << std::endl;
    else std::cout << "Не найдено!\n";
}

void concat_menu()
{
    if(!current_seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    if(!current_seq2)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    std::cout << "Первая последовательность: ";
    print_sequence(current_seq, "");
    std::cout << "Вторая последовательность: ";
    print_sequence(current_seq2, "");

    Sequence<int>* result = current_seq->Concat(current_seq2);

    std::cout << "Результат concat: [";
    for(int i = 0; i < result->GetLen(); i++)
    {
        std::cout << result->Get(i) << (i < result->GetLen() - 1 ? ", " : "");
    }
    std::cout << "]\n";

    delete result;
}

void clone_menu()
{
    Sequence<int>*& seq = select_sequence("Clone");

    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return;
    }

    Sequence<int>* clone = seq->Clone();

    std::cout << "Оригинал: ";
    print_sequence(seq, "");

    std::cout << "Клон: [";
    for(int i = 0; i < clone->GetLen(); i++)
    {
        std::cout << clone->Get(i) << (i < clone->GetLen() - 1 ? ", " : "");
    }
    std::cout << "]\n";

    delete clone;
}

void show_choice()
{
    std::cout << "\n__________TYPE OF SEQUENCE___________\n";
    std::cout << "| 1.MutableArraySequence            |\n";
    std::cout << "| 2.MutableListSequence             |\n";
    std::cout << "| 3.ImmutableArraySequence          |\n";
    std::cout << "| 4.ImmutableListSequence           |\n";
    std::cout << "|___________________________________|\n";
}

void show_menu()
{
    std::cout << "\n________________MENU_________________\n";
    std::cout << "| 1.Создание Seq1                    |\n";
    std::cout << "| 2.Создание Seq2                    |\n";
    std::cout << "|____________________________________|\n";
    std::cout << "| 3.Append                           |\n";
    std::cout << "| 4.Prepend                          |\n";
    std::cout << "| 5.InsertAt                         |\n";
    std::cout << "|____________________________________|\n";
    std::cout << "| Доступ:                            |\n";
    std::cout << "| 6.Get(index)                       |\n";
    std::cout << "| 7.operator[] (чтение)              |\n";
    std::cout << "| 8.operator[] (запись)              |\n";
    std::cout << "| 9.Print sequence                   |\n";
    std::cout << "|____________________________________|\n";
    std::cout << "| Дополнительные функции:            |\n";
    std::cout << "| 10.Map(a*x + b)                    |\n";
    std::cout << "| 11.Reduce(sum/prod/min/max)        |\n";
    std::cout << "| 12.Where(условие)                  |\n";
    std::cout << "| 13.Zip                             |\n";
    std::cout << "| 14.FlatMap                         |\n";
    std::cout << "| 15.Concat                          |\n";
    std::cout << "| 16.Clone                           |\n";
    std::cout << "|____________________________________|\n";
    std::cout << "| Option / Try:                      |\n";
    std::cout << "| 17. TryGet(index)                  |\n";
    std::cout << "| 18. TryFind(условие)               |\n";
    std::cout << "|____________________________________|\n";
    std::cout << "| Система:                           |\n";
    std::cout << "| 19. Запустить все тесты            |\n";
    std::cout << "| 0. Выход                           |\n";
    std::cout << "|____________________________________|\n";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "_____________________________________\n";
    std::cout << "|       Лабораторная работа №2      |\n";
    std::cout << "|                                   |\n";
    std::cout << "| Михеев Дмитрий    группа: Б25-507 |\n";
    std::cout << "|___________________________________|\n";

    //выбор типа
    show_choice();
    std::cout << "Введите номер типа (1-4): ";
    if(!(std::cin >> current_type) || current_type < 1 || current_type > 4)
    {
        current_type = 1;
        std::cout << "Неверный ввод. Выбран тип 1.\n";
    }
    clear_input_buffer();

    int choice;

    do
    {
        show_menu();
        std::cout << "Ваш выбор: ";

        if(!(std::cin >> choice))
        {
            clear_input_buffer();
            std::cout << "Ошибка: введите число от 0 до 25!\n";
            continue;
        }

        clear_input_buffer();
        std::cout << std::endl;

        try
        {
            switch(choice)
            {
                case 1:
                    create_sequence(1);
                    break;
                case 2:
                    create_sequence(2);
                    break;
                case 3:
                    add_element(false); //append
                    break;
                case 4:
                    add_element(true); //prepend
                    break;
                case 5:
                    insert_at();
                    break;
                case 6:
                    get_element();
                    break;
                case 7:
                    read_bracket();
                    break;
                case 8:
                    write_bracket();
                    break;
                case 9:
                    std::cout << "Seq 1: ";
                    print_sequence(current_seq, "");
                    std::cout << "Seq 2: ";
                    print_sequence(current_seq2, "");
                    break;
                case 10:
                    map_menu();
                    break;
                case 11:
                    reduce_map();
                    break;
                case 12:
                    where_menu();
                    break;
                case 13:
                    zip_menu();
                    break;
                case 14:
                    flatmap_menu();
                    break;
                case 15:
                    concat_menu();
                    break;
                case 16:
                    clone_menu();
                    break;
                case 17:
                    try_get();
                    break;
                case 18:
                    try_find();
                    break;
                case 19:
                    run_tests();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Неверный выбор!\n";
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Исключение: " << e.what() << std::endl;
        }
    }
    while(choice != 0);

    return 0;
}
