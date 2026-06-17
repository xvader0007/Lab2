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

Sequence<int>* current_seq = nullptr;
Sequence<int>* current_seq2 = nullptr;
int current_type1 = 1;  // Тип для первой последовательности
int current_type2 = 1;  // Тип для второй последовательности
int num_sequences = 1;  // Количество последовательностей (1 или 2)

void clear_input_buffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void print_sequence(Sequence<int>* seq, const std::string& label = "")
{
    if(!seq)
    {
        std::cout << label << "[не создана]\n";
        return;
    }

    std::cout << label << "[";
    for(int i = 0; i < seq->GetLen(); i++)
    {
        std::cout << seq->Get(i);
        if(i < seq->GetLen() - 1) std::cout << ", ";
    }
    std::cout << "] (длина: " << seq->GetLen() << ")\n";
}

void create_sequence(int slot)
{
    int arr[] = {1, 2, 3};
    int type = (slot == 1) ? current_type1 : current_type2;
    Sequence<int>*& target = (slot == 1) ? current_seq : current_seq2;

    delete target;

    switch(type)
    {
        case 1: target = new MutableArraySequence<int>(arr, 3); break;
        case 2: target = new MutableListSequence<int>(arr, 3); break;
        case 3: target = new ImmutableArraySequence<int>(arr, 3); break;
        case 4: target = new ImmutableListSequence<int>(arr, 3); break;
    }

    std::cout << "Создано: Seq" << slot << ": ";
    print_sequence(target, "");
}

int select_type_for_sequence(int slot)
{
    std::cout << "\n=== ТИП ДЛЯ ПОСЛЕДОВАТЕЛЬНОСТИ " << slot << " ===\n";
    std::cout << "1. MutableArraySequence\n";
    std::cout << "2. MutableListSequence\n";
    std::cout << "3. ImmutableArraySequence\n";
    std::cout << "4. ImmutableListSequence\n";
    std::cout << "Выбор (1-4): ";

    int type;
    if(!(std::cin >> type) || type < 1 || type > 4)
    {
        type = 1;
        std::cout << "Неверный ввод. Выбран тип 1.\n";
    }
    clear_input_buffer();

    return type;
}

Sequence<int>*& select_sequence()
{
    if(num_sequences == 1)
    {
        return current_seq;
    }

    std::cout << "Выберите последовательность (1/2): ";
    int choice;
    std::cin >> choice;
    clear_input_buffer();

    if(choice != 1 && choice != 2)
    {
        std::cout << "Неверный выбор! Используем Seq1.\n";
        return current_seq;
    }

    return (choice == 1) ? current_seq : current_seq2;
}

bool check_sequence(Sequence<int>* seq)
{
    if(!seq)
    {
        std::cout << "Последовательность не создана!\n";
        return false;
    }
    return true;
}

int map_k = 1, map_b = 0;
int map_function(int x) { return map_k * x + map_b; }

int reduce_sum(int acc, int x) { return acc + x; }
int reduce_prod(int acc, int x) { return acc * x; }
int reduce_max(int acc, int x) { return (x > acc) ? x : acc; }
int reduce_min(int acc, int x) { return (x < acc) ? x : acc; }

int where_threshold = 0;
char where_op = '>';

bool where_predicate(int x)
{
    switch(where_op)
    {
        case '>': return x > where_threshold;
        case '<': return x < where_threshold;
        case 'b': return x >= where_threshold;
        case 'l': return x <= where_threshold;
        case '!': return x != where_threshold;
        case '=': return x == where_threshold;
        default: return false;
    }
}

int tryfind_threshold = 0;
char tryfind_op = '>';
bool tryfind_predicate(int x)
{
    switch(tryfind_op)
    {
        case '>': return x > tryfind_threshold;
        case '<': return x < tryfind_threshold;
        case 'b': return x >= tryfind_threshold;
        case 'l': return x <= tryfind_threshold;
        case '!': return x != tryfind_threshold;
        case '=': return x == tryfind_threshold;
        default: return false;
    }
}

int flatmap_op = 1, flatmap_N = 0;
Sequence<int>* flatmap_function(int x)
{
    int* data = new int[2];
    if(flatmap_op == 1) { data[0] = x; data[1] = x; }
    else if(flatmap_op == 2) { data[0] = x; data[1] = x * flatmap_N; }
    else { data[0] = x; data[1] = x + flatmap_N; }
    return new ArraySequence<int>(data, 2);
}

//ОПЕРАЦИИ С ПОСЛЕДОВАТЕЛЬНОСТЯМИ

void add_element(bool prepend)
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    int value;
    std::cout << "Введите значение: ";
    if(!(std::cin >> value))
    {
        clear_input_buffer();
        std::cout << "Ошибка ввода!\n";
        return;
    }

    seq = prepend ? seq->Prepend(value) : seq->Append(value);
    std::cout << "Добавлено " << (prepend ? "в начало" : "в конец") << "!\n";

    print_sequence(seq, "Результат: ");
}


void insert_at()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    int value, index;
    std::cout << "Значение: "; std::cin >> value;
    std::cout << "Индекс: "; std::cin >> index;

    try
    {
        seq = seq->InsertAt(value, index);
        std::cout << "Вставлено!\n";

        print_sequence(seq, "Результат: ");
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void get_element()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    int index;
    std::cout << "Индекс: "; std::cin >> index;

    try
    {
        std::cout << "seq[" << index << "] = " << seq->Get(index) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void write_bracket()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    int value, index;
    std::cout << "Индекс: "; std::cin >> index;
    std::cout << "Значение: "; std::cin >> value;

    try
    {
        (*seq)[index] = value;
        std::cout << "Изменено!\n";

        print_sequence(seq, "Результат: ");
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void map_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    std::cout << "f(x) = k*x + b\n";
    std::cout << "k: "; std::cin >> map_k;
    std::cout << "b: "; std::cin >> map_b;
    clear_input_buffer();

    auto* res = seq->Map(&map_function);
    std::cout << "Результат: ";
    print_sequence(res, "");
    delete res;
}

void reduce_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    std::cout << "1: сумма  2: произведение  3: максимум  4: минимум\n";
    int op; std::cin >> op;
    clear_input_buffer();

    try
    {
        int result;
        switch(op)
        {
            case 1: result = seq->Reduce(&reduce_sum, 0); break;
            case 2: result = seq->Reduce(&reduce_prod, 1); break;
            case 3: result = seq->Reduce(&reduce_max, seq->Get(0)); break;
            case 4: result = seq->Reduce(&reduce_min, seq->Get(0)); break;
            default: std::cout << "Неверный выбор\n"; return;
        }
        std::cout << "Результат: " << result << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void where_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    std::cout << "Оператор (>/< /b(>=)/l(<=)/!(!=)/=(==)): ";
    std::cin >> where_op;
    std::cout << "Значение: "; std::cin >> where_threshold;
    clear_input_buffer();

    auto* res = seq->Where(&where_predicate);
    std::cout << "Результат: ";
    print_sequence(res, "");
    delete res;
}

void try_get_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    int index;
    std::cout << "Индекс: "; std::cin >> index;

    Option<int> opt = seq->TryGet(index);
    if(opt.is_exist())
        std::cout << "Найдено: " << opt.GetValue() << "\n";
    else
        std::cout << "Не найдено (по умолчанию: " << opt.Value_or(-999) << ")\n";
}

void try_find_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    std::cout << "Оператор (>/< /b(>=)/l(<=)/!(!=)/=(==)): ";
    std::cin >> tryfind_op;
    std::cout << "Значение: "; std::cin >> tryfind_threshold;
    clear_input_buffer();

    Option<int> found = seq->TryFind(&tryfind_predicate);
    if(found.is_exist())
        std::cout << "Найдено: " << found.GetValue() << "\n";
    else
        std::cout << "Не найдено!\n";
}

void clone_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    Sequence<int>* clone = seq->Clone();
    std::cout << "Клон: ";
    print_sequence(clone, "");
    delete clone;
}

void flatmap_menu()
{
    Sequence<int>*& seq = select_sequence();
    if(!check_sequence(seq)) return;

    std::cout << "1: [x,x]  2: [x,x*N]  3: [x,x+N]\n";
    std::cin >> flatmap_op;
    if(flatmap_op == 2 || flatmap_op == 3)
    {
        std::cout << "N: "; std::cin >> flatmap_N;
    }
    clear_input_buffer();

    auto* res = seq->FlatMap<int>(&flatmap_function);
    std::cout << "Результат: ";
    print_sequence(res, "");
    delete res;
}

void concat_menu()
{
    if(num_sequences == 1)
    {
        std::cout << "Для Concat нужны две последовательности!\n";
        return;
    }

    if(!check_sequence(current_seq) || !check_sequence(current_seq2)) return;

    auto* result = current_seq->Concat(current_seq2);
    std::cout << "Concat: ";
    print_sequence(result, "");
    delete result;
}

void zip_menu()
{
    if(num_sequences == 1)
    {
        std::cout << "Для Zip нужны две последовательности!\n";
        return;
    }

    if(!check_sequence(current_seq)) return;

    std::cout << "Тип второй последовательности:\n";
    std::cout << "1: Строки (A,B,C...)  2: Числа (10,20,30...)\n";
    int type; std::cin >> type;
    clear_input_buffer();

    int len = current_seq->GetLen();

    if(type == 1)
    {
        std::string* strs = new std::string[len];
        for(int i = 0; i < len; i++)
            strs[i] = std::string(1, 'A' + (i % 26));

        auto* s2 = new ArraySequence<std::string>(strs, len);
        auto* zipped = current_seq->Zip(s2);

        std::cout << "Zip результат:\n";
        for(int i = 0; i < zipped->GetLen(); i++)
        {
            auto p = zipped->Get(i);
            std::cout << "  [" << i << "] = (" << std::get<0>(p) << ", \"" << std::get<1>(p) << "\")\n";
        }

        delete[] strs;
        delete zipped;
        delete s2;
    }
    else
    {
        int* nums = new int[len];
        for(int i = 0; i < len; i++)
            nums[i] = (i + 1) * 10;

        auto* s2 = new ArraySequence<int>(nums, len);
        auto* zipped = current_seq->Zip(s2);

        std::cout << "Zip результат:\n";
        for(int i = 0; i < zipped->GetLen(); i++)
        {
            auto p = zipped->Get(i);
            std::cout << "  [" << i << "] = (" << std::get<0>(p) << ", " << std::get<1>(p) << ")\n";
        }

        delete[] nums;
        delete zipped;
        delete s2;
    }
}

//МЕНЮ

void show_main_menu()
{
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
    std::cout << "1. Пересоздать Seq1\n";
    if(num_sequences == 2)
        std::cout << "2. Пересоздать Seq2\n";
    std::cout << "3. Append\n";
    std::cout << "4. Prepend\n";
    std::cout << "5. InsertAt\n";
    std::cout << "6. Get\n";
    std::cout << "7. operator[]\n";
    std::cout << "8. Map\n";
    std::cout << "9. Reduce\n";
    std::cout << "10. Where\n";
    std::cout << "11. TryGet\n";
    std::cout << "12. TryFind\n";
    std::cout << "13. Clone\n";
    std::cout << "14. FlatMap\n";
    if(num_sequences == 2)
    {
        std::cout << "15. Concat\n";
        std::cout << "16. Zip\n";
    }
    std::cout << "17. Тесты\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";
}

void work_menu()
{
    if(!current_seq) create_sequence(1);
    if(num_sequences == 2 && !current_seq2) create_sequence(2);

    int choice;
    do
    {
        show_main_menu();

        if(!(std::cin >> choice))
        {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        try
        {
            switch(choice)
            {
                case 1: create_sequence(1); break;
                case 2:
                    if(num_sequences == 2) create_sequence(2);
                    else std::cout << "Недоступно для одной последовательности!\n";
                    break;
                case 3: add_element(false); break;
                case 4: add_element(true); break;
                case 5: insert_at(); break;
                case 6: get_element(); break;
                case 7: write_bracket(); break;
                case 8: map_menu(); break;
                case 9: reduce_menu(); break;
                case 10: where_menu(); break;
                case 11: try_get_menu(); break;
                case 12: try_find_menu(); break;
                case 13: clone_menu(); break;
                case 14: flatmap_menu(); break;
                case 15:
                    if(num_sequences == 2) concat_menu();
                    else std::cout << "Недоступно для одной последовательности!\n";
                    break;
                case 16:
                    if(num_sequences == 2) zip_menu();
                    else std::cout << "Недоступно для одной последовательности!\n";
                    break;
                case 17: run_tests(); break;
                case 0: break;
                default: std::cout << "Неверный выбор!\n";
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Исключение: " << e.what() << "\n";
        }
    }
    while(choice != 0);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "_____________________________________\n";
    std::cout << "|       Лабораторная работа №2      |\n";
    std::cout << "|   Михеев Дмитрий    Б25-507       |\n";
    std::cout << "|___________________________________|\n";

    //Выбор количества последовательностей
    std::cout << "\n=== СКОЛЬКО ПОСЛЕДОВАТЕЛЬНОСТЕЙ? ===\n";
    std::cout << "1. Одна последовательность\n";
    std::cout << "2. Две последовательности\n";
    std::cout << "Выбор (1-2): ";

    if(!(std::cin >> num_sequences) || num_sequences < 1 || num_sequences > 2)
    {
        num_sequences = 1;
        std::cout << "Неверный ввод. Выбрано: 1.\n";
    }
    clear_input_buffer();

    //Выбор типа для каждой последовательности
    current_type1 = select_type_for_sequence(1);
    if(num_sequences == 2)
    {
        current_type2 = select_type_for_sequence(2);
    }

    //Работа с последовательностями
    work_menu();

    delete current_seq;
    delete current_seq2;

    return 0;
}