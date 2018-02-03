#include "DateTime.h"
#include <iostream>

using namespace DynabyteSoftware;
using namespace std;

enum ErrorCodes
{
  OK = 0
};

int main()
{
  int errorCode = OK;
  clog << DateTime::now() << endl;
  clog << DateTime::now(DateTimeKind::Local) << endl;

  return errorCode;
}