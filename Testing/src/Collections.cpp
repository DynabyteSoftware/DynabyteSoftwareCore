#include "Collections/Enumerator.h"
#include "Collections/Wrappers/ArrayWrapper.h"
#include "Exception.h"
#include "Log.h"
#include <iostream>

using namespace DynabyteSoftware;
using namespace DynabyteSoftware::Collections;
using namespace DynabyteSoftware::Collections::Iterators;
using namespace DynabyteSoftware::Collections::Wrappers;
using namespace std;

int main()
{
  Log::getLogger();
  clog << Log::Information;
  clog << "Collections Unit Test" << endl;

  int testArray[5] = { 2,3,5,7,11 };
  int* testPointerArray[5] = { &testArray[0], &testArray[1], &testArray[2], &testArray[3], &testArray[4] };

  ArrayWrapper<int> arrayWrapper(testArray, 5);
  ArrayWrapper<int*> arrayPointerWrapper(testPointerArray, 5);

  auto loc = std::find(arrayWrapper.begin(), arrayWrapper.end(), 7);
  auto noLoc = std::find(arrayWrapper.begin(), arrayWrapper.end(), 4);

  if (loc != arrayWrapper.end())
    clog << "found " << *loc << endl;;
  if (noLoc == arrayWrapper.end())
    clog << "did not find 4" << endl;

  clog << Log::Information << "Iterate through array wrapper\n\t";
  for(const auto& number : arrayWrapper)
  {
    clog << number << ' ';
  }
  clog << endl;

  clog << Log::Information << "Get first number: " << arrayWrapper.first() << endl;

  clog << Log::Information << "Check any function:\n";
  clog << Log::Information << "\tAny numbers below 13: "
       << arrayPointerWrapper.any([](const int* value) {return *value < 13; }) << "\n";
  clog << Log::Information << "\tAny numbers above 13: "
       << arrayWrapper.any([](const int& value) {return value > 13; }) << endl;

  clog << Log::Information << "Iterate through all numbers above 5\n\t";
  for(const auto& number : arrayWrapper.where([](const int& value){return value > 5;}))
  {
    clog << number << ' ';
  }
  clog << endl;
  
  clog << Log::Information << "Get resulting Euclid numbers\n\t";
  int primeProduct = 1;
  for (const auto& number : arrayWrapper.select<int>([&primeProduct](int& value)
                                                     {primeProduct *= value; return primeProduct + 1; }))
  {
    clog << number << ' ';
  }
  clog << endl;

  try
  {
    arrayWrapper.end()++;
  }
  catch(...)
  {
  }

  BinaryTree<int> tree;
  tree.insert(3);
  tree.insert(2);
  tree.insert(5);
  tree.insert(4);

  clog << Log::Information << "Get binary tree numbers\n\t";
  for(const auto& number : tree)
  {
    clog << number << ' ';
  }
  clog << endl;

  return 0;
}