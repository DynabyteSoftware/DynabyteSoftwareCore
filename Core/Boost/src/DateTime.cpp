#include "DateTime.h"
#include "boost/locale.hpp"

using namespace DynabyteSoftware;
using namespace boost::locale;

DateTime::DateTimeImplementation* DateTime::createDateTimeImplementation(unsigned short year, unsigned short month,
                                                                         unsigned short day, unsigned short hour,
                                                                         unsigned short minute, unsigned short second,
                                                                         unsigned short millisecond, DateTimeKind kind)
{
  class DateTimeBoost final : public DateTimeImplementation
  {
  public:
    DateTimeBoost(unsigned short year, unsigned short month, unsigned short day, unsigned short hour,
                  unsigned short minute, unsigned short second, unsigned short millisecond, DateTimeKind kind)
      : _dateTime(period::year(year) + period::month(month) + period::day(day) + period::hour(hour) +
                  period::minute(minute) + period::second(second) + period::second(millisecond / 1000),
                  kind == DateTimeKind::UTC ? calendar("UTC") : calendar()),
        _millisecond(millisecond % 1000),
        _kind(kind)
    {
    }

    virtual unsigned short getYear() const override
    {
      return _dateTime.get(period::year());
    }

    virtual unsigned short getMonth() const override
    {
      return _dateTime.get(period::month());
    }

    virtual unsigned short getDay() const override
    {
      return _dateTime.get(period::day());
    }

    virtual unsigned short getHour() const override
    {
      return _dateTime.get(period::hour());
    }

    virtual unsigned short getMinute() const override
    {
      return _dateTime.get(period::minute());
    }

    virtual unsigned short getSecond() const override
    {
      return _dateTime.get(period::second());
    }

    virtual unsigned short getMillisecond() const override
    {
      return _millisecond;
    }

    virtual DateTimeKind getKind() const override
    {
      return _kind;
    }
  private:
    date_time _dateTime;
    DateTimeKind _kind;
    unsigned short _millisecond;
  };

  return new DateTimeBoost(year, month, day, hour, minute, second, millisecond, kind);
}

void DateTime::destroyDateTimeImplementation(const DateTimeImplementation*& implementation)
{
  if(implementation)
  {
    delete implementation;
    implementation = nullptr;
  }
}