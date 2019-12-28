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
  DateTime utc = DateTime::now();
  clog << utc << endl;
  clog << "converted: " << utc.toLocalTime() << endl;
  DateTime local = DateTime::now(DateTimeKind::Local);
  clog << local << endl;
  DateTime utcConverted = local.toUniversalTime();
  clog << "converted: " << utcConverted << endl;
  clog << "Comparing local to UTC of the same time: " << ((utcConverted == local) ? "true" : "false") << endl;
  DateTime postEpoch(1971, 10, 29);
  clog << postEpoch << endl;
  
  try
  {
    DateTime preEpoch(1870, 10, 29);
  }
  catch (...)
  {

  }

  return errorCode;
}