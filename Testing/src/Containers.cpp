#include "Collections/ContainerWrapper.h"
#include <iostream>
#include <vector>

using namespace DynabyteSoftware::Collections;
using namespace std;

int main()
{
  vector<int> original = {2,5,3,1,7};
  auto wrapper = make_container_wrapper(original);
  for (const auto& value : wrapper.select<int>([](const int& value){return value+1;}))
  {
    cout << value;
  }

  return 0;
}