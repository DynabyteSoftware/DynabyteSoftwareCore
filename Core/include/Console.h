/*******************************************************************************************************************//**
* @file Console.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's Console class
**********************************************************************************************************************/


#pragma once
#include "ConsoleKeyInfo.h"
#include "CoreExports.h"

namespace DynabyteSoftware
{
  /****************************************************************************************************************//**
  * @class Console
  * @ingroup DynabyteSoftware
  * @brief Class for dealing with console terminal
  * @details
  * Class for performing console I/O operations not supported by iostream methods
  ********************************************************************************************************************/
  class Console final
  {
  public:
    /**
     * Retrieves a single key press from the user (blocks until keypress is entered
     *
     * @param intercept[in] When intercept is true, the keypress will not appear on the screen
     * @return Details on the key pressed @see ConsoleKeyInfo
     * 
     * @note A lot of non-Windows terminals do not expose the information on the keypress, so only
     * characters may be retrieved and Modifiers are reverse-engineeered from the character.
     * If there is no ConsoleKey mapping for the key, the Key variable may be invalid. In all cases
     * the KeyChar variables will be provided with the char entered by the user, even if the key
     * and modifiers cannot be determined.
     **/
    CORE_EXPORT static const ConsoleKeyInfo readKey(bool intercept = false);
  };
}
