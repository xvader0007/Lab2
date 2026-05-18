#include <iostream>
#include <cassert>
#include "sequence.h"
#include "option.h"
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"

void test_basic_append_get()
{
    int arr[] = {10, 20, 30};
    Sequence<int>* seq = new MutableArraySequence<int>(arr, 3);

    assert(seq->GetLen() == 3 && "Неверная длина");
    assert(seq->Get(0) == 10 && "Get(0) неверно");
    assert(seq->Get(2) == 30 && "Get(2) неверно");

    seq->Append(40);
    assert(seq->GetLen() == 4 && "Неверная длина после добавления элемента");
    assert(seq->Get(3) == 40 && "Get(3) неверно");

    delete seq;
}

void test_operator()
{
    int arr[] = {5, 10 ,15};
    MutableArraySequence<int> seq(arr, 3);

    assert(seq[1] == 10 && "Чтение провалено");

    seq[1] = 999;
    assert(seq[1] == 999 && "Запись провалена");
}

void test_immutable()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* original = new ImmutableArraySequence<int>(arr, 3);

    Sequence<int>* mod = original->Append(4);

    assert(original->GetLen() == 3 && "Оригинал изменен");
    assert(original->Get(0) == 1 && "Исходные данные изменены");

    assert(mod->GetLen() == 4 && "Неправильно измененная длина");
    assert(mod->Get(3) == 4 && "Неправильно измененные данные");

    delete original;
    delete mod;
}

void test_map()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    Sequence<int>* doubled = seq->Map([](int x) {return x * 2;});

    assert(doubled->GetLen() == 3 && "Неверная длина Map");
    assert(doubled->Get(0) == 2 && "неверный элемент 0 Map");
    assert(doubled->Get(1) == 4 && "неверный элемент 1 Map");
    assert(doubled->Get(2) == 6 && "неверный элемент 2 Map");

    delete seq;
    delete doubled;
}

void test_reduce()
{
    int arr[] = {1, 2, 3, 4};
    Sequence<int>* seq = new ListSequence<int>(arr, 4);

    int sum = seq->Reduce([](int a, int x) {return a + x;}, 0);

    assert(sum == 10 && "Неправильная сумма Reduce");

    delete seq;
}

void test_where()
{
    int arr[] = {1, 2, 3, 4, 5};
    Sequence<int>* seq = new ArraySequence<int>(arr, 5);

    Sequence<int>* res = seq->Where([](int x) {return x % 2 == 0;});

    assert(res->GetLen() == 2 && "Неверная длина Where");
    assert(res->Get(0) == 2 && "Неверный элемент 0 Where");
    assert(res->Get(1) == 4 && "Неверный элемент 0 Where");

    delete seq;
    delete res;
}

void test_zip()
{
    int nums[] = {1, 2};
    std::string strs[] = {"A", "B"};

    Sequence<int>* s1 = new ArraySequence<int>(nums, 2);
    Sequence<std::string>* s2 = new ArraySequence<std::string>(strs, 2);

    auto* zipped = s1->Zip(s2);

    assert(zipped->GetLen() == 2 && "Неверная длина Zip");

    auto pair = zipped->Get(0);
    assert(std::get<0>(pair) == 1 && "Первая пара 0 неверна");
    assert(std::get<1>(pair) == "A" && "Вторая пара 0 неверна");

    auto pair1 = zipped->Get(1);
    assert(std::get<0>(pair1) == 2 && "Первая пара 1 неверна");
    assert(std::get<1>(pair1) == "B" && "Вторая пара 1 неверна");

    delete s1;
    delete s2;
    delete zipped;
}

void test_flatmap()
{
    int arr[] = {1, 2};
    Sequence<int>* seq = new ArraySequence<int>(arr, 2);

    auto* result = seq->FlatMap([](int x) {
            int* data = new int[2]{x, x + 10};
            return new ArraySequence<int>(data, 2);
    });

    assert(result->GetLen() == 4 && "FlatMap неверная длина");
    assert(result->Get(0) == 1 && "FlatMap элемент 0 неверный");
    assert(result->Get(1) == 11 && "FlatMap элемент 1 неверный");
    assert(result->Get(2) == 2 && "FlatMap элемент 2 неверный");
    assert(result->Get(3) == 12 && "FlatMap элемент 3 неверный");

    delete seq;
    delete result;
}

void test_exception()
{
    int arr[] = {1};
    Sequence<int>* seq = new ArraySequence<int>(arr, 1);

    bool thrown = false;
    try
    {
        seq->Get(100);
    }
    catch(const std::out_of_range&)
    {
        thrown = true;
    }

    assert(thrown && "Исключение не генерируется при недопустимом индексе");

    delete seq;
}

void single_test(const std::string& name, void (*test_f)())
{
    std::cout << "# " << name << " ";
    std::cout.flush(); //чтобы тест появился сразу

    test_f();

    std::cout << "Passed!" << std::endl;
}

void test_get_out_of_bounds()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    bool thrown = false;
    try { seq->Get(10); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown && "Get(10) должен выбрасывать out_of_range");

    thrown = false;
    try { seq->Get(-1); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown && "Get(-1) должен выбрасывать out_of_range");

    delete seq;
}

void test_insert_at_invalid_index()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    bool thrown = false;
    try { seq->InsertAt(999, 100); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown && "InsertAt с индексом > size должен выбрасывать исключение");

    delete seq;
}

void test_zip_nullptr()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    bool thrown = false;
    try { seq->Zip<int>(nullptr); } catch (const std::invalid_argument&) { thrown = true; }
    assert(thrown && "Zip(nullptr) должен выбрасывать invalid_argument");

    delete seq;
}

void test_reduce_empty_sequence()
{
    // Создаём пустую последовательность
    int empty[] = {};
    Sequence<int>* seq = new ArraySequence<int>(empty, 0);

    int result = seq->Reduce([](int acc, int x) { return acc + x; }, 42);
    assert(result == 42 && "Reduce на пустой последовательности должен вернуть начальное значение");

    delete seq;
}

void test_try_get_invalid_index()
{
    int arr[] = {1, 2, 3};
    Sequence<int>* seq = new ArraySequence<int>(arr, 3);

    Option<int> opt = seq->TryGet(100);

    assert(!opt.is_exist() && "TryGet(100) должен вернуть None");
    assert(opt.Value_or(-999) == -999 && "ValueOr должен вернуть значение по умолчанию");

    delete seq;
}

void test_get_first_last_empty()
{
    int empty[] = {};
    Sequence<int>* seq = new ArraySequence<int>(empty, 0);

    bool thrown = false;
    try { seq->GetFirst(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown && "GetFirst на пустой последовательности должен выбрасывать исключение");

    thrown = false;
    try { seq->GetLast(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown && "GetLast на пустой последовательности должен выбрасывать исключение");

    delete seq;
}

void run_tests()
{
    std::cout << "_________Начало тестов_________" << std::endl;

    single_test("Append/Get", test_basic_append_get);
    single_test("Operator[]", test_operator);
    single_test("Immutable", test_immutable);
    single_test("Map", test_map);
    single_test("Reduce", test_reduce);
    single_test("Where", test_where);
    single_test("Zip", test_zip);
    single_test("FlatMap", test_flatmap);
    single_test("Exception", test_exception);

    single_test("Get out of bounds", test_get_out_of_bounds);
    single_test("InsertAt invalid index", test_insert_at_invalid_index);
    single_test("Zip nullptr", test_zip_nullptr);
    single_test("Reduce empty seq", test_reduce_empty_sequence);
    single_test("TryGet invalid index", test_try_get_invalid_index);
    single_test("GetFirst/Last empty", test_get_first_last_empty);

    std::cout << "_________Тесты завершены_________" << std::endl << std::endl;
}