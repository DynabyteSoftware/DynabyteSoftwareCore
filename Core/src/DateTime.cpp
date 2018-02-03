#include "DateTime.h"
#include <chrono>
#include <mutex>
#include <iomanip>

using namespace DynabyteSoftware;
using namespace std;
using namespace std::chrono;

static constexpr const unsigned short EPOCH_YEAR = 1900;
static constexpr const unsigned short EPOCH_MONTH = 1;
static constexpr const char* const UTC = "UTC";
static constexpr const char* const DATE_FORMAT = "%a %b %d %Y %OH:%OI:%OM:%OS.";
static constexpr const char* const TIME_ZONE_FORMAT = "%Z";

static mutex timeMutex;

DateTime::DateTime(unsigned short year, unsigned short month, unsigned short day, unsigned short hour,
                   unsigned short minute, unsigned short second, unsigned int millisecond,
                   DateTimeKind kind)
        : _millisecond(millisecond), _kind(kind)
{
  _date.tm_year = year - EPOCH_YEAR;
  _date.tm_mon = month - EPOCH_MONTH;
  _date.tm_mday = day;
  _date.tm_hour = hour;
  _date.tm_min = minute;
  _date.tm_sec = second;
  _date.tm_wday = 0;
  _date.tm_yday = 0;
  _date.tm_isdst = -1;

  //we do this to allow the library to set wday and isdst for us
  lock_guard<mutex> lock(timeMutex);
  time_t time = mktime(&_date);
  _date = *localtime(&time);
}

DateTime::DateTime(const struct tm& date, unsigned int millisecond, DateTimeKind kind)
        : _date(date), _millisecond(millisecond), _kind(kind)
{
}

unsigned short DateTime::getYear() const
{
  return _date.tm_year + EPOCH_YEAR;
}

unsigned short DateTime::getMonth() const
{
  return _date.tm_mon + EPOCH_MONTH;
}

unsigned short DateTime::getDay() const
{
  return _date.tm_mday;
}

unsigned short DateTime::getHour() const
{
  return _date.tm_hour;
}

unsigned short DateTime::getMinute() const
{
  return _date.tm_min;
}

unsigned short DateTime::getSecond() const
{
  return _date.tm_sec;
}

unsigned int DateTime::getMillisecond() const
{
  return _millisecond;
}

DateTimeKind DateTime::getKind() const
{
  return _kind;
}

DateTime DateTime::toLocalTime() const
{
  if(_kind == DateTimeKind::Local)
    return DateTime(*this);

  struct tm datecopy = _date;
  lock_guard<mutex> lock(timeMutex);
  time_t local;
  #ifdef _WINDOWS
  local = _mkgmtime(&datecopy);
  #else
  local = timegm(&datecopy);
  #endif
  return DateTime(*localtime(&local), _millisecond, DateTimeKind::Local);
}

DateTime DateTime::toUniversalTime() const
{
  if(_kind == DateTimeKind::UTC)
    return DateTime(*this);

  struct tm datecopy = _date;
  lock_guard<mutex> lock(timeMutex);
  time_t utc = mktime(&datecopy);
  return DateTime(*gmtime(&utc), _millisecond, DateTimeKind::UTC);
}

DateTime DateTime::now(DateTimeKind kind)
{
  system_clock::time_point exactTime = system_clock::now();
  system_clock::duration sinceEpoch = exactTime.time_since_epoch();
  time_t time = system_clock::to_time_t(exactTime);
  
  #pragma warning(push)
  #pragma warning(disable:4996) //microsoft warnts to use non-standard localtime_s and gmtime_s functions
  struct tm date;
  lock_guard<mutex> lock(timeMutex); //localtime and gmtime are not threadsafe
  if(kind == DateTimeKind::Local)
    date = *localtime(&time);
  else
    date = *gmtime(&time);
  #pragma warning(pop)

  return
    DateTime(date,
             static_cast<unsigned int>((duration_cast<milliseconds>(sinceEpoch) -
                                        duration_cast<seconds>(sinceEpoch)).count()),
             kind);
}

ostream& DynabyteSoftware::operator<<(ostream& stream, const DateTime& dateTime)
{
  stream << put_time(&dateTime._date, DATE_FORMAT) << dateTime._millisecond << ' ';
  if(dateTime._kind == DateTimeKind::Local)
    stream << put_time(&dateTime._date, TIME_ZONE_FORMAT);
  else
    stream << UTC;
  return stream;
}