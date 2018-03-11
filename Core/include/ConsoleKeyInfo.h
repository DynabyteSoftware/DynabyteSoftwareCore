/***********************************************************************************************************************
* @file ConsoleKeyInfo.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ConsoleKeyInfo struct
**********************************************************************************************************************/

#pragma once
#include "ConsoleKey.h"
#include "ConsoleModifiers.h"

namespace DynabyteSoftware
{
  /********************************************************************************************************************
  * @struct ConsoleKeyInfo
  * @ingroup DynabyteSoftware
  * @brief Struct containing key press info
  * @details
  * Struct containing detailed info on a key press
  ********************************************************************************************************************/
  struct ConsoleKeyInfo final
  {
    const ConsoleModifiers Modifiers; /**< The modifier key pressed along with another key */
    const ConsoleKey Key; /**< The key pressed (not counting modifier keys */
    const char KeyChar; /**< The actual character resulting from the keypress */
  };
}