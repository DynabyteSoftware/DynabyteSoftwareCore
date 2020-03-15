#pragma once
#include "Internal/IConnection.h"
#include "IPendpoint.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    class Connection : public virtual Internal::IConnection
    {
    public:
      #pragma region Constructors
      Connection(const IPendpoint& endpoint);
      #pragma endregion
    };
  }
}