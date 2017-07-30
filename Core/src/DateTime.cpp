#include "DateTime.h"

using namespace DynabyteSoftware;

DateTime::DateTime(unsigned short year, unsigned short month, unsigned short day, unsigned short hour,
                   unsigned short minute, unsigned short second, unsigned short millisecond,
                   DateTimeKind kind = DateTimeKind::UTC)
        : implementation(createDateTimeImplementation(year, month, day, hour, minute, second, millisecond, kind))
{

}

DateTime::DateTime(const DateTime& source)
        : DateTime(source.getYear(), source.getMonth(), source.getDay(), source.getHour(), source.getMinute(),
                   source.getSecond(), source.getMillisecond(), source.getKind())
{
}

DateTime::DateTime(DateTime&& source)
        : implementation(source.implementation)
{
  source.implementation = nullptr;
}

DateTime::~DateTime()
{
  destroyDateTimeImplementation(implementation);
}

unsigned short DateTime::getYear() const
{
  return implementation->getYear();
}

unsigned short DateTime::getMonth() const
{
  return implementation->getMonth();
}

unsigned short DateTime::getDay() const
{
  return implementation->getDay();
}

unsigned short DateTime::getHour() const
{
  return implementation->getHour();
}

unsigned short DateTime::getMinute() const
{
  return implementation->getMinute();
}

unsigned short DateTime::getSecond() const
{
  return implementation->getSecond();
}

unsigned short DateTime::getMillisecond() const
{
  return implementation->getMillisecond();
}

DateTimeKind DateTime::getKind() const
{
  return implementation->getKind();
}