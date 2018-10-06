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

void tryIterator(IRandomAccessIterator<int>& iterator)
{
  clog << "First number in array is " << *iterator << endl;
  clog << "Advancing iterator..." << endl;
  ++iterator;
  clog << "Next number in array is " << *iterator << endl;
  clog << "Backtracking iterator..." << endl;
  --iterator;
  clog << "Previous number in array is " << *iterator << endl;
  clog << "Random access test...fourth number in array is " << iterator[3] << endl;
  clog << "Going out of bounds..." << endl;
  try
  {
    clog << "Accessing seventh position in array " << iterator[6] << endl;
  }
  catch (...)
  {

  }
}

int main()
{
  Log::getLogger();
  clog << Log::Information;
  clog << "Collections Unit Test" << endl;

  int testArray[5] = { 2,3,5,7,11 };
  int* testPointerArray[5] = { &testArray[0], &testArray[1], &testArray[2], &testArray[3], &testArray[4] };

  clog << Log::Information << "Iterate through array wrapper\n\t";
  ArrayWrapper<int> arrayWrapper(testArray, 5);
  ArrayWrapper<int*> arrayPointerWrapper(testPointerArray, 5);
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

  try
  {
    arrayWrapper.end()++;
  }
  catch(...)
  {
  }

  return 0;
}