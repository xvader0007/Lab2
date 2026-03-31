#include <iostream>
#include "dynamic_array.h"

int main()
{
  //std::cout << "Hello World!";

  int array[] = {1, 2, 3};

  DynamicArray<int> arr(array, 3);

  //std::cout << arr.Get(23);

  arr.Resize(5);

  std::cout << arr.Get(4);

  std::cout << arr.GetSize();

  arr.print();

  return 0;
}
