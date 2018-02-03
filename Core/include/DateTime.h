/***********************************************************************************************************************
 * @file DateTime.h
 * @author Rod Leonard
 * @version 0.0.1
 * @date 2017/07/30
 * @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
 * @brief Header file for DynabyteSoftware's DateTime object
 **********************************************************************************************************************/

#pragma once
#include "CoreExports.h"
#include <ctime>
#include <ostream>

namespace DynabyteSoftware
{
  /********************************************************************************************************************
   * @enum DateTimeKind
   * @ingroup DynabyteSoftware
   * @see DynabyteSoftware::DateTime
   * @brief Enumeration for different kinds of DateTime instance (UTC or Local)
   * @details
   * This enumeration specifies whether a DynabyteSoftware DateTime instance is UTC or in the local time-zone
   *******************************************************************************************************************/
  enum struct DateTimeKind : unsigned short
  {
    UTC = 0,
    Local
  };

  /********************************************************************************************************************
   * @class DateTime
   * @ingroup DynabyteSoftware
   * @brief Represents a date-time combination
   * @details
   * Represents a date-time combination instance
   ********************************************************************************************************************/
  class DateTime final
  {
  public:
      /**
       * Constructor for a DateTime object
       *
       * @param year[in] The year numbered from 1-9999
       * @param month[in] The month numbered from 1-12
       * @param day[in] The day numbered from 1-31 (at most, less depending on month/leap-year constraints)
       * @param hour[in] The hour numbered from 0-24
       * @param minute[in] The minute numbered from 0-60
       * @param second[in] The second numbered from 0-60
       * @param millisecond[in] The millisecond, numbered from 0-999
       * @param kind[in] The DateTime kind (UTC or Local)
       **/
      CORE_EXPORT
      DateTime(unsigned short year, unsigned short month, unsigned short day, unsigned short hour = 0,
               unsigned short minute = 0, unsigned short second = 0, unsigned int millisecond = 0,
               DateTimeKind kind = DateTimeKind::UTC);

      /**
       * @return the year
       **/
      CORE_EXPORT
      unsigned short getYear() const;

      /**
       * the month
       */
      CORE_EXPORT
      unsigned short getMonth() const;

      /**
       * @return the day
       */
      CORE_EXPORT
      unsigned short getDay() const;

      /**
       * @return the hour
       */
      CORE_EXPORT
      unsigned short getHour() const;

      /**
       * @return the minute
       */
      CORE_EXPORT
      unsigned short getMinute() const;

      /**
       * @return the second
       **/
      CORE_EXPORT
      unsigned short getSecond() const;

      /**
       * @return the millisecond
       **/
      CORE_EXPORT
      unsigned int getMillisecond() const;

      /**
       * @return the kind (local or UTC)
       * @see DynabyteSoftware::DateTimeKind
       **/
      CORE_EXPORT
      DateTimeKind getKind() const;

      /**
       *@return a copy of this DateTime in the local timezone
       **/
      CORE_EXPORT
      DateTime toLocalTime() const;

      /**
       *@return a copy of this DateTime in UTC
       **/
      CORE_EXPORT
      DateTime toUniversalTime() const;

      /**
      * Returns the current DateTime
      * @param kind[in] Whether to return DateTime in local time or UTC
      * @return the current DateTime
      **/
      CORE_EXPORT
      static DateTime now(DateTimeKind kind = DateTimeKind::UTC);
  private:
    DateTime(const struct tm& date, unsigned int millisecond, DateTimeKind kind);

    struct tm _date;
    unsigned int _millisecond;
    DateTimeKind _kind;

    friend CORE_EXPORT std::ostream& operator<<(std::ostream&, const DateTime&);
  };
}