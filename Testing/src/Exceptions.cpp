#include "EnumFlagUtilities.h"
#include "Exception.h"
#include <iostream>

enum struct ErrorCodes
{
  OK = 0,
  ExceptionNotThrown = -0x1
};

FLAGS(ErrorCodes)

using namespace DynabyteSoftware;

int main()
{
  ErrorCodes errorCode = ErrorCodes::OK;
  try
  {
    THROW(Exception, "test")
    errorCode |= ErrorCodes::ExceptionNotThrown;
  }
  catch(const Exception&)
  {
  }

  return static_cast<int>(errorCode);
}