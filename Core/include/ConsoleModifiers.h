#pragma once
#include "EnumFlagUtilities.h"

namespace DynabyteSoftware
{
  enum struct ConsoleModifiers
  {
    None = 0x0,
    Alt = 0x1,
    Control = 0x2,
    Shift = 0x4
  };

  FLAGS(ConsoleModifiers)  
}