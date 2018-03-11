/***********************************************************************************************************************
* @file ConsoleModifiers.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ConsoleModifiers enum
**********************************************************************************************************************/
#pragma once
#include "EnumFlagUtilities.h"

namespace DynabyteSoftware
{
  /********************************************************************************************************************
  * @enum ConsoleModifiers
  * @ingroup DynabyteSoftware
  * @brief Enumeration describing keyboard keys
  * @details
  * An enumeration describing the modifier keyboard keys
  * @note this is a flag enumeration, meaning that an enumeration value of this type can be a combination of multiple
  * of multiple modifiers. @see FLAGS
  ********************************************************************************************************************/
  enum struct ConsoleModifiers
  {
    None = 0x0,
    Alt = 0x1,
    Control = 0x2,
    Shift = 0x4
  };

  FLAGS(ConsoleModifiers)  
}