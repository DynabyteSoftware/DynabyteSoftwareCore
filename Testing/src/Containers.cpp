#include "Collections/ContainerWrapper.h"
#include <iostream>
#include <vector>

using namespace DynabyteSoftware::Collections;
using namespace std;

int main()
{
  vector<int> original = {2,5,3,1,7};
  ContainerWrapper<vector<int>> wrapper(original);
  for (const auto& value : wrapper.where([](const int& value){return value > 4;}))
  {
    cout << value;
  }

  return 0;
}