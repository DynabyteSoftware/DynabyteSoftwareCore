/***********************************************************************************************************************
* @file EnumFlagUtilities.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/02/04
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Utilities for simplifying use of scoped enums as flag enums
**********************************************************************************************************************/

#pragma once
#include <type_traits>

/**
* @def FLAGS(EnumType)
* @brief Macro used to define bitwise operations for a scoped enum intended to be used as a flag
* @details
* This macro defines a series of bitwise operations to simplify the use of a scoped enum as a flag enum
* @code{.cpp}
* enum struct FlagTest
* {
*   None = 0x0,
*   Cheap = 0x1,
*   Fast = 0x2,
*   Good = 0x4
* }
*
* FLAGS(FlagTest)
*
* void main()
* {
*   FlagTest thisMacro = FlagTest::Cheap | FlagTest::Fast;
*   if(thisMacro >= FlagTest::Fast)
*     cout << "It's fast to implement flags using this macro!" << endl;
* }
* @endcode
*/
#define FLAGS(EnumType) \
  inline EnumType operator~(EnumType enumValue) \
  { \
    return static_cast<EnumType>(~static_cast< typename std::underlying_type_t<EnumType> >(enumValue)); \
  } \
  \
  inline EnumType operator|(EnumType lhs, EnumType rhs) \
  { \
    return static_cast<EnumType>(static_cast< typename std::underlying_type_t<EnumType> >(lhs) | \
                                 static_cast< typename std::underlying_type_t<EnumType> >(rhs)); \
  } \
  \
  inline void operator|=(EnumType& lhs, EnumType rhs) \
  { \
    lhs = lhs | rhs; \
  } \
  \
  inline EnumType operator&(EnumType lhs, EnumType rhs) \
  { \
    return static_cast<EnumType>(static_cast< typename std::underlying_type_t<EnumType> >(lhs) & \
                                 static_cast< typename std::underlying_type_t<EnumType> >(rhs)); \
  } \
  \
  inline void operator&=(EnumType& lhs, EnumType rhs) \
  { \
    lhs = lhs & rhs; \
  } \
  \
  inline bool operator>=(EnumType lhs, EnumType rhs) \
  { \
    return (lhs & rhs) == rhs; \
  } \
  \
  inline bool operator<(EnumType lhs, EnumType rhs) \
  { \
    return !(lhs <= rhs); \
  }
  
