#pragma once
#include "ConsoleKey.h"
#include "ConsoleModifiers.h"

namespace DynabyteSoftware
{
  struct ConsoleKeyInfo final
  {
    const ConsoleModifiers Modifiers;
    const ConsoleKey Key;
    const char KeyChar;
  };
}