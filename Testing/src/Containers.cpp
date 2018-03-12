#include "Collections/ContainerWrapper.h"
#include <iostream>
#include <vector>

using namespace DynabyteSoftware::Collections;
using namespace std;

int main()
{
  vector<int> original = {2,5,3,1,7};
  ContainerWrapper<vector<int>> wrapper(original);
  TransformEnumerator<int, typename ContainerWrapper<vector<int>>::iterator>::transform_function test;
  for (const auto& value : wrapper.select<int>([](const int& value){return value+1;}))
  {
    cout << value;
  }

  return 0;
}