#include "Exception.h"

enum ErrorCodes
{
  OK = 0,
  ExceptionNotThrown = -1,
  BadExceptionConstruction = -2
};

using namespace DynabyteSoftware;

int main()
{
  try
  {
    THROW(Exception, "test")
  }
  catch(const Exception& except)
  {
    return OK;
  }

  return ExceptionNotThrown;
}