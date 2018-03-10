#pragma once
#include "ConsoleKeyInfo.h"
#include "CoreExports.h"

namespace DynabyteSoftware
{
  class Console final
  {
  public:
    CORE_EXPORT static const ConsoleKeyInfo readKey(bool intercept = false);
  };
}