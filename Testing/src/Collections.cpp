#include "Collections/Wrappers/PointerIterator.h"
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

  clog << "Creating pointer iterator..." << endl;
  int testArray[5] = { 2,3,5,7,11 };
  PointerIterator<int> iteratorTest(&testArray[0], &testArray[0], &testArray[5]);

  clog << "First number in array is " << *iteratorTest << endl;
  clog << "Advancing iterator..." << endl;
  ++iteratorTest;
  clog << "Next number in array is " << *iteratorTest << endl;
  clog << "Backtracking iterator..." << endl;
  --iteratorTest;
  clog << "Previous number in array is " << *iteratorTest << endl;
  clog << "Random access test...fourth number in array is " << iteratorTest[3] << endl;
  clog << "Going out of bounds..." << endl;
  try
  {
    clog << "Accessing seventh position in array " << iteratorTest[6] << endl;
  }
  catch (...)
  {

  }

  return 0;
}