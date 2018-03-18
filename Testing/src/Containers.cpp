#include "Collections/ContainerWrapper.h"
#include <iostream>
#include <vector>

using namespace DynabyteSoftware::Collections;
using namespace std;

int main()
{
  vector<int> original = {2,5,3,1,7};
  auto wrapper = make_container_wrapper(original);
  for (const auto& value : wrapper.select<const int&>([](const int& value)->const int&{return value;}))
  {
    cout << value << " ";
  }

  cout << endl;
  for (const auto& value : wrapper.where([](const int& value) {return value > 3;}))
  {
    cout << value << " ";
  }

  cout << endl;
  return 0;
}