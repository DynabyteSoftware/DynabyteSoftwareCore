#include "Console.h"
#include "EnumFlagUtilities.h"
#include <iostream>

enum struct ErrorCodes
{
  OK = 0,
};

FLAGS(ErrorCodes)

using namespace DynabyteSoftware;
using namespace std;

int main()
{
  ErrorCodes errorCode = ErrorCodes::OK;
  cout << "Press any key to continue...";
  const auto key = Console::readKey(true);
  cout << "\nGot key (" << key.KeyChar << ")" << endl;

  return static_cast<int>(errorCode);
}
