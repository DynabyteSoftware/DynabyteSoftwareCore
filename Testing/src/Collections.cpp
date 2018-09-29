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

  clog << "Creating pointer iterator..." << endl;
  int testArray[5] = { 2,3,5,7,11 };
  PointerIterator<int> iteratorTest(&testArray[0], &testArray[0], &testArray[5]);
  tryIterator(iteratorTest);

  clog << Log::Information << "Iterate through array wrapper" << endl;
  ArrayWrapper<int> arrayWrapper(testArray, 5);
  for(const auto& number : arrayWrapper)
  {
    clog << number << endl;
  }

  clog << "Done" << endl;

  return 0;
}