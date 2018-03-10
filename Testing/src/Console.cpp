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
  const auto key = Console::readKey();
  cout << "Got key " << endl;

  return static_cast<int>(errorCode);
}